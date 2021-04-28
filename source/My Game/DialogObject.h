#pragma once

#include <String>

#include "Object.h"


class DialogObject : 
	public CObject,
	public CSettings
{
private:
	int size;
	int price = 0;
	int currX = 0;
	int currY = 80;

	
	CSpriteDesc3D* confirmButton = nullptr;
	CSpriteDesc3D* cancelButton = nullptr;
	list<CSpriteDesc3D*> displayList;

	void write(string s);
public:
	int buyPrice = 0;
	int result = 0;
	dialogType type;

	DialogObject(Vector3& v, dialogType t, int price = 0);
	void move();
	void handleMouseHover(POINT p);
	int handleMouseClick(POINT p);
	void setDialog(int breedDialog = 0); 
	list<CSpriteDesc3D*> getDisplayList();
};

