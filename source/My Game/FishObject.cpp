#include "FishObject.h"
#include <Magick++.h>
#include "ObjectManager.h" //to get the current time

//#include "Common.h"

//get the price of the fish. that's it. :) 
//

FishObject::FishObject(const Vector3& v, int level, int worldSeed) : CObject(UNLOADED_FISH_SPRITE, v) //world seed should be the next random integer from the world
{
	//this->level = level;

	originalXScale = m_fXScale;
	originalYScale = m_fYScale;

	seed = worldSeed;
	linearGenerator.srand(seed);

	step = beginningY;

	m_fSpeed = fmod(linearGenerator.randf(), 0.4f) + 0.1f;
	originalSpeed = m_fSpeed;
	originalPoint = v;

	prevDirection = direction = linearGenerator.randn() % 2;
	if (direction == 0) direction = -1;

	size = (linearGenerator.randn() % 5) + 10;
	if (size % 2 != 0) ++size;

	feedingTime = linearGenerator.randn() % 4;

	beginningY = m_vPos.y; //TODO find out what all the functions do to the vector position
}

int FishObject::GenerateSprite()
{
	spriteIndex = getNextFishSpriteIndex();
	if ((int)spriteIndex == -1)
	{
		printf("No free indices.\n");
		return -1;
	}
	GenerateCreature();
	m_nSpriteIndex = spriteIndex;
	return (int)m_nSpriteIndex;
}

void FishObject::GenerateCreature()
{
	linearGenerator.srand(seed);
	sprite2D.resize(size, std::vector<int>(size));

	for (int i = 0; i < (size / 1.5); ++i)
	{
		int x = (linearGenerator.randn() % ((size / 2) - 1)) + 1;
		int y = (linearGenerator.randn() % (size - 2)) + 1;

		sprite2D[x][y] = 1;
	}

	tempSprite2D = sprite2D;
	for (int i = 0; i < 3; ++i)
	{
		for (int y = 1; y < (size - 1); ++y)
		{
			for (int x = 1; x < ((size / 2)); ++x)
			{
				int count = 0;

				//any live cell with 2 or 3 neighbors lives, else it does
				if (sprite2D[x - 1][y] == 1) ++count;
				if (sprite2D[x + 1][y] == 1) ++count;
				if (sprite2D[x][y - 1] == 1) ++count;
				if (sprite2D[x][y + 1] == 1) ++count;

				if (((count != 2) && (count != 3)) && (sprite2D[x][y] == 1))
					tempSprite2D[x][y] = 0;
				else if ((count <= 1) && (sprite2D[x][x] != 1))
					tempSprite2D[x][y] = 1;
			}
		}
		sprite2D = tempSprite2D;
	}

	//reflect
	for (int y = 1; y < (size - 1); ++y)
	{
		for (int x = 1; x < ((size / 2)); ++x)
		{
			if (sprite2D[x][y] == 1) sprite2D[size - x - 1][y] = 1;
		}
	}

	//generate animated sprite
	int tempValue;
	for (int y = 1; y < (size - 1); ++y)
	{
		for (int x = 1; x < (size - 1); ++x)
		{
			int x1 = (x + (size / 2) - 2) % (size - 2) + 1;
			//if (x1 == 0 || x1 == size - 1) continue;
			tempSprite2D[x][y] = sprite2D[x1][y];
		}
	}

	//add border -- There are a few options when doing this. we can have it as is, or remove either indicated block, only one
	for (int y = 1; y < (size - 1); ++y)
	{
		for (int x = 1; x < (size - 1); ++x)
		{
			if (sprite2D[x][y] == 1)
			{
				if (sprite2D[x - 1][y] != 1) sprite2D[x - 1][y] = 2;
				if (sprite2D[x + 1][y] != 1) sprite2D[x + 1][y] = 2;
				if (sprite2D[x][y - 1] != 1) sprite2D[x][y - 1] = 2;
				if (sprite2D[x][y + 1] != 1) sprite2D[x][y + 1] = 2;

				//removable
				//if (tempSprite2D[x - 1][y] != 1) tempSprite2D[x - 1][y] = 2;
				//if (tempSprite2D[x + 1][y] != 1) tempSprite2D[x + 1][y] = 2;
				//if (tempSprite2D[x][y - 1] != 1) tempSprite2D[x][y - 1] = 2;
				//if (tempSprite2D[x][y + 1] != 1) tempSprite2D[x][y + 1] = 2;
				//end removable
			}
			//removable
			if (tempSprite2D[x][y] == 1)
			{
				if (tempSprite2D[x - 1][y] != 1) tempSprite2D[x - 1][y] = 2;
				if (tempSprite2D[x + 1][y] != 1) tempSprite2D[x + 1][y] = 2;
				if (tempSprite2D[x][y - 1] != 1) tempSprite2D[x][y - 1] = 2;
				if (tempSprite2D[x][y + 1] != 1) tempSprite2D[x][y + 1] = 2;
			}
			//end removable
		}
	}
	if (worldIndex == 1) CreateImage(1);
	else if (worldIndex == 2) CreateImage(0);
}


int FishObject::GetRandomSizeOffset(double mean, double deviation, int size, double one, double two)
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

	std::normal_distribution<double> lateralLineHeight(mean, deviation);
	double percentOfSize = lateralLineHeight(generator);
	if (percentOfSize <= min) percentOfSize = min;
	else if (percentOfSize >= max) percentOfSize = max;
	return percentOfSize;
}

void FishObject::move()
{
	if (direction != prevDirection)
	{
		moveUp = true;
		prevDirection = direction;
	}

	const size_t nFrameCount = m_pRenderer->GetNumFrames(m_nSpriteIndex);
	if (nFrameCount > 1 && m_pStepTimer->GetTotalSeconds() > m_fFrameTimer + m_fSpeed) {
		m_fFrameTimer = m_pStepTimer->GetTotalSeconds();
		if ((isHooked == false) || (isCaught == true)) m_nCurrentFrame = (m_nCurrentFrame + 1) % nFrameCount;
	} //if
	if (isCaught)
	{
		m_fSpeed = originalSpeed;
		m_fRoll = 0.0;
		return;
	}
	if (m_pStepTimer->GetTotalSeconds() > resistTimer + 1.5) //i would like 0.01 to be based of its speed , but reasonable. this is fine for milestone 3
	{
		resistTimer = m_pStepTimer->GetTotalSeconds();
		int n = linearGenerator.randn() % 100;
		if (n <= 35) isResisting = true;
		else isResisting = false;
	}

	if (isHooked == false)
	{
		m_fRoll = 0.0f;
		m_fSpeed = originalSpeed;
		if (moveUp)
		{
			m_vPos.y += 4 * m_fSpeed;
			m_vPos.x += m_fSpeed * unit * direction;
			if (m_vPos.x > m_fWorldWidth / 2) m_vPos.x = -(m_fWorldWidth / 2);
			else if (m_vPos.x < -(m_fWorldWidth / 2)) m_vPos.x = m_fWorldWidth / 2;
			if (m_vPos.y >= beginningY + 60)
			{
				moveUp = false;
				step = m_vPos.y;
			}
		}
		else
		{
			m_vPos.y -= 2 * m_fSpeed;
			m_vPos.x += m_fSpeed * direction * 0.5;
			if (m_vPos.x > m_fWorldWidth / 2) m_vPos.x = -(m_fWorldWidth / 2);
			else if (m_vPos.x < -(m_fWorldWidth / 2)) m_vPos.x = m_fWorldWidth / 2;
			if (m_vPos.y <= beginningY - 60)
			{
				//m_vPos.y = beginningY;
				moveUp = true;
				step = m_vPos.y;
			}
		}
	}
	else
	{
		const float t = m_pStepTimer->GetElapsedSeconds();
		float delta_x = m_vPos.x - anchorPoint.x;
		float delta_y = m_vPos.y - anchorPoint.y;
		float theta_radians = atan2(delta_y, delta_x);

		if (m_vPos.y >= -145.0f)
		{
			//this should behave as if the fish is jumping onto the penguins head
			if (setVec)
			{
				m_vVelocity.x = t * (anchorPoint.x - m_vPos.x); //this should only be set one time
				m_vVelocity.y = 12.0;
				m_pAudio->play(FISH_UNDER_WATER);
				m_pAudio->stop(UNDERWATER);
				m_pAudio->loop(WAVES);
				setVec = false;
			}			

			if (m_vVelocity.y <= 0)
			{
				m_fXScale *= 0.95;
				m_fYScale *= 0.95;
			}
			m_vVelocity -= 20.0f * t * Vector3::UnitY;
			m_vPos += 64.0f * t * m_vVelocity;
			//this condition is a little buggy, sometimes the penguin will not actually catch the fish.
			if (((m_vPos.y >= anchorPoint.y - 20.0f) && (m_vPos.y <= anchorPoint.y + 20.0f)) && ((m_vPos.x >= anchorPoint.x - 20.0f) && (m_vPos.x <= anchorPoint.x + 20.0f)))
			{
				isCaught = true;
				setVec = true; //setup for release
				m_pAudio->play(BLOP);
			}
		}
		else if (isResisting) //user has set the speed but the fish is resisting
		{
			//failsafe
			if (m_fSpeed) resistTimer += 0.2; //if you click while its resisting. you are penalized.
			if (!setVec)
			{
				setVec = true; //setup for release
				isCaught = true;
			}
			m_fRoll = theta_radians + (3 * XM_PI / 2);// -(XM_2PI / 90);
			if (rotateLeft) //we will animate it
			{
				m_fRoll += 0.01f * XM_2PI;
				rotateLeft = false;
			}
			else
			{
				m_fRoll -= 0.01f * XM_2PI;
				rotateLeft = true;
			}
			m_fSpeed = originalSpeed / 2;

			float stepY = (anchorPoint.y - m_vPos.y) / (m_fSpeed * unit);
			float stepX = (anchorPoint.x - m_vPos.x) / stepY;

			//this is super choppy, find a way to make it not choppy
			m_vPos.x -= stepX;
			m_vPos.y -= m_fSpeed * unit;

			m_vVelocity = Vector3::Zero;
		}
		else //the fish is not resisting
		{
			if (!setVec)
			{
				setVec = true; //setup for release
				isCaught = true;
			}
			//had a 'little' help from here: https://gamedev.stackexchange.com/questions/73627/move-a-2d-point-to-a-target-first-accelerate-towards-the-target-then-decelerat
			if (m_fSpeed == 0.0f)
			{
				m_fRoll = 0.0f;
				m_vVelocity.x /= 1.01f;
				m_vVelocity.y /= 1.01f;
				acc = 0;
			}
			else acc = m_fSpeed;

			if (((m_vVelocity.x < 0) && (m_vPos.x > anchorPoint.x)) || ((m_vVelocity.x > 0) && (m_vPos.x < anchorPoint.x)))
			{
				m_fRoll = theta_radians + (XM_PI / 2);
			}

			float distance = sqrt((delta_x * delta_x) + (delta_y * delta_y));
			float dvx = delta_x * (-5) / distance; //-5 should be a common variable based on the fishing pole!!!!!!!!!!!!!!!!!!!!!!
			float dvy = delta_y * (-5) / distance;
			delta_x = dvx - m_vVelocity.x;
			delta_y = dvy - m_vVelocity.y;
			float diffSize = sqrt((delta_x * delta_x) + (delta_y * delta_y));
			float ax = 0.0, ay = 0.0;
			if (diffSize != 0.0f)
			{
				ax = acc * delta_x / diffSize;
				ay = acc * delta_y / diffSize;
			}
			m_vVelocity.x += 64.0f * ax * t; // t is the time that passed since the last frame
			m_vVelocity.y += 64.0f * ay * t; // t is the time that passed since the last frame

			m_vPos += m_vVelocity;
		}
		m_fSpeed = 0.0;
	}
}

void FishObject::CreateImage(int shape)
{
	int n = size * size * 4;
	unsigned char* pixels1 = new unsigned char[n];
	unsigned char* pixels2 = new unsigned char[n];
	
	//maybe ill make some fish transparent. who knows. transparency has to be a rare quality
	//I know you built a random colour generator, but I needed it to use a sort of threshold so that the outline is the same colour but darker
	int i = 0;
	r = (linearGenerator.randn()) % 155 + 101;
	g = (linearGenerator.randn()) % 155 + 101;
	b = (linearGenerator.randn()) % 155 + 101;
	r1 = (linearGenerator.randn()) % 255;
	g1 = (linearGenerator.randn()) % 255;
	b1 = (linearGenerator.randn()) % 255;

	//diamond shape
	if (shape == 0)
	{
		int offset = 0; 
		int middleRight = (size / 2);
		int middleLeft = (size / 2) - 1;
		bool grow = true;

		for (int j = 0; j < size; ++j)
		{
			for (int k = 0; k < size; ++k)
			{
				//r
				if ((k > (middleLeft - offset)) && (k < (middleRight + offset)))
				{
					if (sprite2D[k][j] == 1) pixels1[i++] = r;
					else if (sprite2D[k][j] == 2) pixels1[i++] = r - 100;
					else if (sprite2D[k][j] == 4) pixels1[i++] = r1;
					else pixels1[i++] = 0;

					//b
					if (sprite2D[k][j] == 1) pixels1[i++] = g;
					else if (sprite2D[k][j] == 2) pixels1[i++] = g - 100;
					else if (sprite2D[k][j] == 4) pixels1[i++] = g1;
					else pixels1[i++] = 0;

					//g
					if (sprite2D[k][j] == 1) pixels1[i++] = b;
					else if (sprite2D[k][j] == 2) pixels1[i++] = b - 100;
					else if (sprite2D[k][j] == 4) pixels1[i++] = b1;
					else pixels1[i++] = 0;

					//alpha
					if (sprite2D[k][j] == 3 || sprite2D[k][j] == 0) pixels1[i++] = 0;
					else pixels1[i++] = 255;
				}
				else
				{
					if ((k == (middleLeft - offset - 1)) || (k == (middleRight + offset + 1)))
					{
						
						if (sprite2D[k][j] == 1)
						{
							pixels1[i++] = r - 100;
							pixels1[i++] = g - 100;
							pixels1[i++] = b - 100;
							pixels1[i++] = 255;
						}
						else
						{
							pixels1[i++] = 0;
							pixels1[i++] = 0;
							pixels1[i++] = 0;
							pixels1[i++] = 0;
						}
					}
					else
					{
						pixels1[i++] = 0;
						pixels1[i++] = 0;
						pixels1[i++] = 0;
						pixels1[i++] = 0;
					}
				}

				i -= 4;
				if ((k > (middleLeft - offset)) && (k < (middleRight + offset)))
				{
					//r
					if (tempSprite2D[k][j] == 1) pixels2[i++] = r;
					else if (tempSprite2D[k][j] == 2) pixels2[i++] = r - 100;
					else if (tempSprite2D[k][j] == 4) pixels1[i++] = r1;
					else pixels2[i++] = 0;

					//b
					if (tempSprite2D[k][j] == 1) pixels2[i++] = g;
					else if (tempSprite2D[k][j] == 2) pixels2[i++] = g - 100;
					else if (tempSprite2D[k][j] == 4) pixels1[i++] = g1;
					else pixels2[i++] = 0;

					//g
					if (tempSprite2D[k][j] == 1) pixels2[i++] = b;
					else if (tempSprite2D[k][j] == 2) pixels2[i++] = b - 100;
					else if (tempSprite2D[k][j] == 4) pixels1[i++] = b1;
					else pixels2[i++] = 0;

					//alpha
					if (tempSprite2D[k][j] == 0 || tempSprite2D[k][j] == 3) pixels2[i++] = 0;
					else pixels2[i++] = 255;
				}
				else
				{
					if ((k == (middleLeft - offset - 1)) || (k == (middleRight + offset + 1)))
					{

						if (tempSprite2D[k][j] == 1)
						{
							pixels2[i++] = r - 100;
							pixels2[i++] = g - 100;
							pixels2[i++] = b - 100;
							pixels2[i++] = 255;
						}
						else
						{
							pixels2[i++] = 0;
							pixels2[i++] = 0;
							pixels2[i++] = 0;
							pixels2[i++] = 0;
						}
					}
					else
					{
						pixels2[i++] = 0;
						pixels2[i++] = 0;
						pixels2[i++] = 0;
						pixels2[i++] = 0;
					}
				}
			}
			if (grow) ++offset;
			else --offset;

			if (offset >= (size / 2) - 1) grow = !grow;
		}
	}


	//square shape
	if (shape == 1)
	{
		for (int j = 0; j < size; ++j)
		{
			for (int k = 0; k < size; ++k)
			{
				//r
				if (sprite2D[k][j] == 1) pixels1[i++] = r;
				else if (sprite2D[k][j] == 2) pixels1[i++] = r - 100;
				else if (sprite2D[k][j] == 4) pixels1[i++] = r1;
				else pixels1[i++] = 0;

				//b
				if (sprite2D[k][j] == 1) pixels1[i++] = g;
				else if (sprite2D[k][j] == 2) pixels1[i++] = g - 100;
				else if (sprite2D[k][j] == 4) pixels1[i++] = g1;
				else pixels1[i++] = 0;

				//g
				if (sprite2D[k][j] == 1) pixels1[i++] = b;
				else if (sprite2D[k][j] == 2) pixels1[i++] = b - 100;
				else if (sprite2D[k][j] == 4) pixels1[i++] = b1;
				else pixels1[i++] = 0;

				//alpha
				if (sprite2D[k][j] == 3 || sprite2D[k][j] == 0) pixels1[i++] = 0;
				else pixels1[i++] = 255;

				i -= 4;
				//r
				if (tempSprite2D[k][j] == 1) pixels2[i++] = r;
				else if (tempSprite2D[k][j] == 2) pixels2[i++] = r - 100;
				else if (tempSprite2D[k][j] == 4) pixels1[i++] = r1;
				else pixels2[i++] = 0;

				//b
				if (tempSprite2D[k][j] == 1) pixels2[i++] = g;
				else if (tempSprite2D[k][j] == 2) pixels2[i++] = g - 100;
				else if (tempSprite2D[k][j] == 4) pixels1[i++] = g1;
				else pixels2[i++] = 0;

				//g
				if (tempSprite2D[k][j] == 1) pixels2[i++] = b;
				else if (tempSprite2D[k][j] == 2) pixels2[i++] = b - 100;
				else if (tempSprite2D[k][j] == 4) pixels1[i++] = b1;
				else pixels2[i++] = 0;

				//alpha
				if (tempSprite2D[k][j] == 0 || tempSprite2D[k][j] == 3) pixels2[i++] = 0;
				else pixels2[i++] = 255;
			}
		}
	}

	try {
		newImage.read(size, size, "RGBA", Magick::CharPixel, pixels1);
		newImage.scale(Magick::Geometry((int)size * 4, (int)size * 4));
		if (direction == 1) newImage.flop();
		newImage.write("Media/Images/fishSprite0.png");

		newImage.read(size, size, "RGBA", Magick::CharPixel, pixels2);
		newImage.scale(Magick::Geometry((int)size * 4, (int)size * 4));
		if (direction == 1) newImage.flop();
		newImage.write("Media/Images/fishSprite1.png");
	}
	catch (Magick::Warning error)
	{
		// Process Magick++ file open error
		printf("ERROR: %s\n", error.what());
	}

	newImage = Magick::Image();

	tempSprite2D.clear();
	sprite2D.clear();
	delete[] pixels1;
	delete[] pixels2;
}

constexpr int FishObject::pixelArraySize()
{
	return size * size * 3;
}

//=================== FISH CURRENCY =========================//

//modified based on http://www.cplusplus.com/reference/random/normal_distribution/
int FishObject::normal_dist(int i)
{
	int numRolls = 10000;  // number of experiments
	int numFish = 16; // because there are 16 different color brightness (FEDCBA9876543210)
	int numStars = numFish * 5;    // maximum number of stars to distribute

	//generate normal distribution
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(numFish / 2, numFish / 5); //first value = center point; second value = how much it will spread out

	//create an array
	int p[16] = {}; //same as numFish

	//distribute numbers
	for (int i = 0; i < numRolls; ++i) {
		double number = distribution(generator);
		if ((number >= 0.0) && (number < numFish)) ++p[int(number)];
	}

	//print out the distribution
	//for (int i = 0; i < numFish; ++i) {
	//	std::cout << i + 1 << ": ";
	//	//give at least one star per each
	//	if (p[i] * numStars / numRolls == 0) {
	//		std::cout << '*' << std::endl;
	//	}
	//	else {
	//		std::cout << std::string(p[i] * numStars / numRolls, '*') << std::endl;
	//	}
	//}

	//return currency
	if (p[i] * numStars / numRolls == 0) {
		return 1;
	}
	else {
		return p[i] * numStars / numRolls;
	}
}

//reference: https://www.codespeedy.com/convert-rgb-to-hex-color-code-in-cpp/
string FishObject::RGBtoHex() 
{
	stringstream ss;
	ss << hex << (r << 16 | g << 8 | b);
	return ss.str();
}


int FishObject::getPrice()
{
	//set the initial input for currency and bonus point
	curr = abs(originalPoint.y) + size;

	switch (feedingTime)
	{
	case 0:
		curr *= 1.2;
		break;
	case 1:
		curr *= 1.3;
		break;
	case 2:
		curr *= 2.2;
		break;
	case 3:
		curr *= 2.1;
		break;
	}
	curr /= 10;
	float avgColour = (r + g + b) / 3.0;
	curr = pow(curr, avgColour / 100); //this will yield poor results for dark fish.;
	curr *= m_fSpeed;
	//return the calculated currency to display in the system
	//you can get a fish up to 600000 if its perfect in all attributes.
	return curr;
}