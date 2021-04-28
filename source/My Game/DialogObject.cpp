#include <iomanip>
#include <locale>
#include <sstream>

#include "DialogObject.h"

void DialogObject::write(string s)
{

	
	int centerOffset = 0;

	for (int i = 0; i < s.length(); ++i)
	{
		CSpriteDesc3D* letter = new CSpriteDesc3D();
		//please use all caps/...//.../
		switch (s[i])
		{
		case '\n':
			centerOffset = (size - currX) / 2;
			for (auto j : displayList)
			{
				if (j->m_vPos.y == currY) j->m_vPos.x += centerOffset;
			}
			currY -= 20;
			break;
		case ' ':
			centerOffset = (size - currX) / 2;
			currX += 8;
			break;

		case '0':
			letter->m_nSpriteIndex = LETTER_0;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case '1':
			letter->m_nSpriteIndex = LETTER_1;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case '2':
			letter->m_nSpriteIndex = LETTER_2;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case '3':
			letter->m_nSpriteIndex = LETTER_3;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case '4':
			letter->m_nSpriteIndex = LETTER_4;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case '5':
			letter->m_nSpriteIndex = LETTER_5;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case '6':
			letter->m_nSpriteIndex = LETTER_6;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case '7':
			letter->m_nSpriteIndex = LETTER_7;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case '8':
			letter->m_nSpriteIndex = LETTER_8;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case '9':
			letter->m_nSpriteIndex = LETTER_9;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;

		case ',':
			letter->m_nSpriteIndex = LETTER_COMMA_NORMAL;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case '?':
			letter->m_nSpriteIndex = LETTER_QUESTION;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;

		case 'A':
			letter->m_nSpriteIndex = LETTER_A;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 12;
			break;
		case 'B':
			letter->m_nSpriteIndex = LETTER_B;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'C':
			letter->m_nSpriteIndex = LETTER_C;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'D':
			letter->m_nSpriteIndex = LETTER_D;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'E':
			letter->m_nSpriteIndex = LETTER_E;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'F':
			letter->m_nSpriteIndex = LETTER_F;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'G':
			letter->m_nSpriteIndex = LETTER_G;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'H':
			letter->m_nSpriteIndex = LETTER_H;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'I':
			letter->m_nSpriteIndex = LETTER_I;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 12;
			break;
		case 'J':
			letter->m_nSpriteIndex = LETTER_J;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'K':
			letter->m_nSpriteIndex = LETTER_K;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'L':
			letter->m_nSpriteIndex = LETTER_L;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'M':
			letter->m_nSpriteIndex = LETTER_M;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 12;
			break;
		case 'N':
			letter->m_nSpriteIndex = LETTER_N;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 12;
			break;
		case 'O':
			letter->m_nSpriteIndex = LETTER_O;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 12;
			break;
		case 'P':
			letter->m_nSpriteIndex = LETTER_P;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'Q':
			letter->m_nSpriteIndex = LETTER_Q;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'R':
			letter->m_nSpriteIndex = LETTER_R;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'S':
			letter->m_nSpriteIndex = LETTER_S;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'T':
			letter->m_nSpriteIndex = LETTER_T;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'U':
			letter->m_nSpriteIndex = LETTER_U;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'V':
			letter->m_nSpriteIndex = LETTER_V;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		case 'W':
			letter->m_nSpriteIndex = LETTER_W;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 12;
			break;
		case 'X':
			letter->m_nSpriteIndex = LETTER_X;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break; 
		case 'Y':
			letter->m_nSpriteIndex = LETTER_Y;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break; 
		case 'Z':
			letter->m_nSpriteIndex = LETTER_Z;
			letter->m_vPos = Vector3(currX - 170, currY, 999);
			currX += 10;
			break;
		
		}
		if (currX >= size - 20)
		{
			while (s[i] != ' ')
			{
				--i;
				displayList.pop_back();
			}
			currX = 0;
			

			for (auto j : displayList)
			{
				if (j->m_vPos.y == currY) j->m_vPos.x += centerOffset;
			}
			currY -= 20;
			continue;
		}
		letter->m_vPos.x += PC->m_vPos.x;
		letter->m_vPos.y += PC->m_vPos.y;
		displayList.push_back(letter);

		
	}
}

DialogObject::DialogObject(Vector3& v, dialogType t, int price) : CObject(DIALOG_BOX, v)
{
	if (price) this->price = price;

	type = t;
	size = GetWidth(DIALOG_BOX) - 4; //i could check if its negative.

	confirmButton = new CSpriteDesc3D();
	confirmButton->m_nSpriteIndex = CONFIRM_BUTTON;
	confirmButton->m_vPos = Vector3(m_vPos.x - 100, m_vPos.y - 65, 999);
	
	cancelButton = new CSpriteDesc3D();
	cancelButton->m_nSpriteIndex = CANCEL_BUTTON;
	cancelButton->m_vPos = Vector3(m_vPos.x + 100, m_vPos.y - 65, 999);
}

void DialogObject::move()
{
	m_vPos = PC->m_vPos;
	confirmButton->m_vPos = Vector3(m_vPos.x - 100, m_vPos.y - 50, 999);
	cancelButton->m_vPos = Vector3(m_vPos.x - 100, m_vPos.y - 50, 999);
}

void DialogObject::handleMouseHover(POINT p)
{
	int x = ((p.x - (m_nWinWidth / 2)) * 0.625) + (int)PC->m_vPos.x;
	int y = 0.63 * ((m_nWinHeight - p.y) - 402);

	confirmButton->m_nSpriteIndex = CONFIRM_BUTTON;
	cancelButton->m_nSpriteIndex = CANCEL_BUTTON;

	//okay button
	if ((x > (m_vPos.x  - 100) - 40) && (x < (m_vPos.x - 100) + 40))
	{
		if ((y > (m_vPos.y - 92) - 15) && (y < (m_vPos.y - 92) + 15))
		{
			if (confirmButton->m_nSpriteIndex == CONFIRM_BUTTON) confirmButton->m_nSpriteIndex = CONFIRM_BUTTON_HIGHLIGHTED;
		}
	}

	if ((x > (m_vPos.x + 100) - 40) && (x < (m_vPos.x + 100) + 40))
	{
		if ((y > (m_vPos.y - 92) - 15) && (y < (m_vPos.y - 92) + 15))
		{
			if (cancelButton->m_nSpriteIndex == CANCEL_BUTTON) cancelButton->m_nSpriteIndex = CANCEL_BUTTON_HIGHLIGHTED;
		}
	}
}

int DialogObject::handleMouseClick(POINT p)
{
	
	int x = ((p.x - (m_nWinWidth / 2)) * 0.625) + (int)PC->m_vPos.x;
	int y = 0.63 * ((m_nWinHeight - p.y) - 402);

	//okay button
	if ((x > (m_vPos.x - 100) - 40) && (x < (m_vPos.x - 100) + 40))
	{
		if ((y > (m_vPos.y - 92) - 15) && (y < (m_vPos.y - 92) + 15))
		{
			if (confirmButton->m_nSpriteIndex == CONFIRM_BUTTON_HIGHLIGHTED) return 1;
		}
	}

	else if ((x > (m_vPos.x + 100) - 40) && (x < (m_vPos.x + 100) + 40))
	{
		if ((y > (m_vPos.y - 92) - 15) && (y < (m_vPos.y - 92) + 15))
		{
			if (cancelButton->m_nSpriteIndex == CANCEL_BUTTON_HIGHLIGHTED) return 2;
		}
	}
	return 0;
}

void DialogObject::setDialog(int breedType)
{
	currX = 0;
	currY = 80;
	//DEBUG price = 12345;
	stringstream ss;
	ss.imbue(locale(""));
	ss << std::fixed << price;
	string amount;
	switch (type)
	{
	case SELL_DIALOG:
		write("WOULD YOU LIKE TO SELL THE SELECTED FISH FOR\n\n");
		currX = 0;
		write(ss.str() + "\n\n");
		currX = 0;
		write("SAND DOLLARS?\n");
		break;
	case INFO_DIALOG:
		//display info.
		break;
	case BREED_DIALOG:
		switch (breedType)
		{
		case 0:
			write("PLEASE SELECT 2 FISH YOU WOULD LIKE TO BREED\n");
			break;
		case 1:
			write("WOULD YOU LIKE TO BREED THE SELECTED FISH?\n");
			break;
		case 2:
			write("PLEASE ONLY HAVE 2 FISH SELECTED FOR BREEDING\n");
			break;
		case 3:
			write("MAKE SURE TO HAVE SPACE IN YOUR INVENTORY FOR YOUR BRED FISH UNLESS YOU WANT IT TO JUMP BACK INTO THE OCEAN\n");
			break;
		case 4:
			write("PROGRAMMERS\n");
			currX = 0;
			write("CHRISTIANA RAMEY AND GLORIA KIM\n\n");
			currX = 0;
			write("ART\n");
			currX = 0;
			write("TREE AND BOAT PNGS BY VECTEEZY\n");
			break;
		case 5:
			write("SOUNDS\n");
			currX = 0;
			write("MARK DIANGELO, MIKE KOENIG, DANIEL SIMION, AND CHRISTIANA RAMEY\n");
		}	
		break;
	case RELEASE_DIALOG:
		write("ARE YOU SURE YOU WANT TO RELEASE THE SELECTED FISH?\n");
		break;
	case BUY_DIALOG:
		
		switch (breedType)
		{
		case 0:
			amount = "100,000";
			buyPrice = -10;
			break;
		case 1:
			amount = "1,000,000";
			buyPrice = -1000000;
			break;
		case 2:
			amount = "10,000,000";
			buyPrice = -10000000;
			break;
		case 3: //this is the default pole
			amount = "0";
			buyPrice = 0;
			break;
		case 4:
			amount = "20,000";
			buyPrice = -20000;
			break;
		case 5:
			amount = "115,000";
			buyPrice = -115000;
			break;
		case 6:
			amount = "500,000";
			buyPrice = -500000;
			break;
		case 7:
			amount = "1,000,000";
			buyPrice = -1000000;
			break;
		case 8:
			amount = "100,000,000";
			buyPrice = -100000000;
			break;
		case 9:
			amount = "100,000";
			buyPrice = -100000;
			break;
		case 10:
			amount = "1,000,000";
			buyPrice = -1000000;
			break;
		case 11:
			amount = "10,000,000";
			buyPrice = -10000000;
			break;
		}
		write("WOULD YOU LIKE TO PURCHASE THE SELECTED ITEM FOR\n\n");
		currX = 0;
		write(amount + "\n\n");
		currX = 0;
		write("SAND DOLLARS?\n");
		buyPrice = 0;
		break;

	case FAIL_DIALOG:
		write("YOU DO NOT HAVE ENOUGH MONEY\n");
		break;
	}
	
	ss.clear();
}

list<CSpriteDesc3D*> DialogObject::getDisplayList()
{
	//major bug here
	list<CSpriteDesc3D*> result;
	if (confirmButton && cancelButton)
	{
		result.push_back(confirmButton);
		result.push_back(cancelButton);
	}
	for (auto& i : displayList)
	{
		result.push_back(i);
	}
	return result;
}
