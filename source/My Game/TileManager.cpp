#include "TileManager.h"

#include <Magick++.h>

TileManager::TileManager(int seed, int density)
{
	generator.seed(seed);
	linearGenerator.srand(seed);

	this->density = density; //this is how far apart we should be placing points before we connect them.

	int currentMin = 44000;
	int forwardMin = currentMin + 2000;
	int backwardMin = currentMin - 2000;

	border.resize((int)m_fWorldWidth);

	printf("DONe");
	generateTerrain();

	generateFill();

	//order matters
	currentChunk = drawChunk(currentMin, currentMin + m_fChunkSize, TERRAIN2, border);
	forwardChunk = drawChunk(forwardMin, forwardMin + m_fChunkSize, TERRAIN1, border);
	backwardChunk = drawChunk(backwardMin, backwardMin + m_fChunkSize, TERRAIN3, border);

	printf("%f\n", currentChunk->m_vPos.x);
}

void TileManager::generateTerrain()
{
	//first generate points for the size of the world
	//for the ground, we need points to be consistently deeper the further we go from x = 0

	vector<double> pointList;
	float oceanHeight = -10000.0f;
	int maxLandY = -700;
	float ratio = -0.20444444;
	double standard_deviation;
	double mean;
	int endX = (int)m_fWorldWidth;
	double percentOfHeight;
	double result;

	for (int currX = 0; currX < endX; currX += density)
	{
		standard_deviation = ((ratio / 10) * abs(currX - 45000)) + 10;
		mean = (ratio * abs(currX - 45000)) + maxLandY;
		percentOfHeight = -GetRandomSizeOffset(mean, standard_deviation, maxLandY, oceanHeight);
		pointList.push_back(int(oceanHeight * percentOfHeight)); //we dont need to plot floats. the precision is not very important

		//backgroundBorder.push_back((ratio * currX) + maxY); //TODO
	}
	pointList[(17 * (int)m_fChunkSize) / density] = pointList[((28 * (int)m_fChunkSize) / density)];
	vector<double>::iterator first, last;

	//TODO make these variable.
	vector<int> r;

	//first = pointList.begin() + ((17 * m_fChunkSize) / density);
	//last = pointList.begin() + ((28 * m_fChunkSize) / density) + density + 1;
	//vector<double> section = vector<double>(first, last);
	border = connectJaggedTerrain(pointList);
	//copy(r.begin(), r.end(), border.begin() + (17 * m_fChunkSize));

	printf("Loaded Terrain\n");
	printf("%d,\n", r.size());
}

CSpriteDesc3D* TileManager::drawChunk(int start, int end, int spriteIndex, vector<int>& pointList)
{
	printf("%d,\n", pointList.size());
	int minX = start, minY = pointList[start], maxX = end, maxY = pointList[start];
	if (spriteIndex == TERRAIN_FILL)
	{
		maxY = 0;
		minY = -600;
	}
	else
	{
		for (int i = start; i < end; i++)
		{
			//printf("%d\n", pointList[i]);
			if (pointList[i] < minY) minY = pointList[i];
			if (pointList[i] > maxY) maxY = pointList[i];
		}
	}
	vector<vector<int>> sprite2D;
	int sizeY = (maxY - minY) / quality; //500 is an offset so that the camera does not see 'holes' in the terrain
	int sizeX = (end - start) / quality;

	sprite2D.resize(sizeX, std::vector<int>(sizeY));

	int index = 0;
	for (int i = start; i < end; i += quality)
	{
		for (int y = abs(pointList[i] - maxY) / quality; y < sizeY; ++y)
		{
			sprite2D[index][y] = 1;
		}
		++index;
	}
	int x, y, c = 2;
	for (int i = 0; i < 1000; ++i)
	{
		x = (linearGenerator.randn() % (sizeX - 2)) + 1;
		y = (linearGenerator.randn() % (sizeY - 2)) + 1;

		if (sprite2D[x][y] == 1)
		{
			sprite2D[x][y] = c;
			if (quality < 3)
			{
				sprite2D[x + 1][y] = c;
				sprite2D[x - 1][y] = c;
				sprite2D[x][y + 1] = c;
				sprite2D[x][y - 1] = c;
				sprite2D[x + 1][y - 1] = c;
				sprite2D[x + 1][y + 1] = c;
				sprite2D[x - 1][y + 1] = c;
				sprite2D[x - 1][y - 1] = c;
			}
		}
		++c;
		if (c > 3) c = 2;
	}

	int i = 0;
	int n = sizeX * sizeY * 4;
	unsigned char* pixels1 = new unsigned char[n];

	for (int j = 0; j < sizeY; ++j)
	{
		for (int k = 0; k < sizeX; ++k)
		{
			if (sprite2D[k][j] == 1) pixels1[i++] = 240;
			else if (sprite2D[k][j] == 2) pixels1[i++] = 255;
			else if (sprite2D[k][j] == 3) pixels1[i++] = 230;
			else pixels1[i++] = 0;

			if (sprite2D[k][j] == 1) pixels1[i++] = 246;
			else if (sprite2D[k][j] == 2) pixels1[i++] = 255;
			else if (sprite2D[k][j] == 3) pixels1[i++] = 237;
			else pixels1[i++] = 0;

			if (sprite2D[k][j] == 1) pixels1[i++] = 200;
			else if (sprite2D[k][j] == 2) pixels1[i++] = 255;
			else if (sprite2D[k][j] == 3) pixels1[i++] = 183;
			else pixels1[i++] = 0;

			if (sprite2D[k][j] >= 1) pixels1[i++] = 255;
			else pixels1[i++] = 0;
		}
	}

	try {
		terrainImage.read(sizeX, sizeY, "RGBA", Magick::CharPixel, pixels1);
		if (spriteIndex == TERRAIN_FILL) terrainImage.write("Media/Images/terrainFill.png");
		else terrainImage.write("Media/Images/terrain.png");
	}
	catch (Magick::Warning error)
	{
		// Process Magick++ file open error
		printf("ERROR: %s\n", error.what());
	}

	terrainImage = Magick::Image();
	sprite2D.clear();
	delete[] pixels1;

	if (spriteIndex == TERRAIN_FILL) m_pRenderer->LoadFill();
	else m_pRenderer->LoadImages(spriteIndex, false);

	CSpriteDesc3D* newSprite = new CSpriteDesc3D();
	newSprite->m_nSpriteIndex = spriteIndex;
	newSprite->m_fXScale = newSprite->m_fYScale *= quality;
	if (spriteIndex != TERRAIN_FILL)
	{
		newSprite->m_vPos = Vector3(((start + end) / 2) - (m_fWorldWidth / 2), ((minY + maxY) / 2), 1990);
	}
	return newSprite;
}

vector<int> TileManager::connectJaggedTerrain(vector<double> input)
{
	//we will feature 4 terrain types for the 4 different oceans - crater, jagged, pillow, normal (smooth and curvy)
	//for now we will only have the jagged one because it is easier to debug everything
	double x0, x1, y0, y1;
	int interval = density;
	vector<int> result;
	for (int i = 1; i < input.size(); ++i)
	{
		y0 = input[i - 1];
		y1 = input[i];

		x0 = interval;
		x1 = interval + density;

		float m = (y1 - y0) / (x1 - x0);
		float b = y0 - (m * x0);
		//printf("(%f - %f) / (%f - %f) = %f\n", y1, y0, x1, x0, m);

		for (int j = x0; j < x1; ++j)
		{
			result.push_back(int((m * j) + b));
		}
		interval += density;
	}
	return result;
}

vector<int> TileManager::connectSmoothTerrain(vector<double> input)
{
	vector<double> pointList;
	vector<int> results;
	int index = 0; //testing DELETE THIS
	for (auto i : input)
	{
		pointList.push_back(index);
		pointList.push_back(i);
		index += density;
	}
	for (double i : bezierCurve.GenerateBezierCurve(pointList, 11000)) results.push_back(i);
	//for (auto i : results) printf("%d\n", i);
	return results;
}

double TileManager::GetRandomSizeOffset(double mean, double deviation, double one, double two)
{
	int min, max;
	int result;
	if (one > two)
	{
		max = one;
		min = two;
	}
	else
	{
		max = two;
		min = one;
	}

	normal_distribution<double> lateralLineHeight(mean, deviation);
	double percentOfSize = lateralLineHeight(generator);
	if (percentOfSize <= min) percentOfSize = min;
	else if (percentOfSize >= max) percentOfSize = max;
	return percentOfSize / 10000;
}

void TileManager::generateFill()
{
	vector<int> pointList;
	for (int i = 0; i < 2000; ++i)
	{
		pointList.push_back(0);
	}
	fill = drawChunk(0, 2000, TERRAIN_FILL, pointList);
}

void TileManager::setPosition()
{
	if (currChunk > worldEndChunk)
	{
		currentChunk->m_vPos.x = ((((worldStartChunk * m_fChunkSize) + ((worldStartChunk + 1) * m_fChunkSize)) / 2) - (m_fWorldWidth / 2));
		printf("%f\n", currentChunk->m_vPos.x);
	}
	else if (currChunk < worldStartChunk)
	{
		currentChunk->m_vPos.x = ((((worldEndChunk * m_fChunkSize) + ((worldEndChunk + 1) * m_fChunkSize)) / 2) - (m_fWorldWidth / 2));
		printf("%f\n", currentChunk->m_vPos.x);
	}
	else
	{
		currentChunk->m_vPos.x = ((((currChunk * m_fChunkSize) + ((currChunk + 1) * m_fChunkSize)) / 2) - (m_fWorldWidth / 2));
	}
	forwardChunk->m_vPos.x = currentChunk->m_vPos.x + m_fChunkSize;
	backwardChunk->m_vPos.x = currentChunk->m_vPos.x - m_fChunkSize;

	printf("current load: %f to %f\n", currentChunk->m_vPos.x, currentChunk->m_vPos.x + m_fChunkSize);
}

bool TileManager::setChunk(int chunk)
{
	if (abs(chunk - currChunk) != 1)
	{
		if (currChunk > worldEndChunk) currChunk = worldStartChunk;
		else if (currChunk < worldStartChunk) currChunk = worldEndChunk;
		else if (currChunk == worldEndChunk) currChunk = worldStartChunk - 1;
		else if (currChunk == worldStartChunk) currChunk = worldEndChunk + 1;
	}
	if (currChunk != chunk)
	{
		int currentMin = chunk * m_fChunkSize;
		printf("chunk: %d currChunk: %d\n", chunk, currChunk);
		if (currChunk < chunk) //this means the we moved to the forwards chunk
		{
			int forwardMin = currentMin + m_fChunkSize;

			if (chunk == worldEndChunk)
			{
				forwardMin = (worldStartChunk * (int)m_fChunkSize);
				chunk = worldStartChunk - 1;
			}

			if (forwardMin > m_fWorldWidth) return false;
			int spriteIndex = backwardChunk->m_nSpriteIndex;

			backwardChunk = currentChunk;
			currentChunk = forwardChunk;
			forwardChunk = drawChunk(forwardMin, forwardMin + m_fChunkSize, spriteIndex, border);
			printf("forward load: %d to %f\n", currentMin, currentMin + m_fChunkSize);
		}
		else if (currChunk > chunk)
		{
			int backwardMin = currentMin - m_fChunkSize;
			if (chunk == worldStartChunk)
			{
				backwardMin = (worldEndChunk * (int)m_fChunkSize);
				chunk = worldEndChunk + 1;
			}
			if (backwardMin < 0) return false;
			int spriteIndex = forwardChunk->m_nSpriteIndex;

			forwardChunk = currentChunk;
			currentChunk = backwardChunk;
			backwardChunk = drawChunk(backwardMin, backwardMin + m_fChunkSize, spriteIndex, border);
			printf("backward load: %d to %f\n", currentMin, currentMin + m_fChunkSize);
		}
		currChunk = chunk;
		setPosition();
	}
	return true;
}

bool TileManager::testCollision(Vector3 pos)
{
	int x = pos.x + 45000;
	int y = pos.y;
	
	if (border[x] >= y) return true;
	return false;
}

CSpriteDesc3D* TileManager::getForwardChunk()
{
	return forwardChunk;
}

CSpriteDesc3D* TileManager::getCurrentChunk()
{
	return currentChunk;
}

CSpriteDesc3D* TileManager::getBackwardChunk()
{
	return backwardChunk;
}

CSpriteDesc3D* TileManager::getFill()
{
	return fill;
}