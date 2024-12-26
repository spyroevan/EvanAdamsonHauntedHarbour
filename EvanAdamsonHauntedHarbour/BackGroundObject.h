#pragma once
#include "GraphicsObject.h"

class BackGroundObject:public GraphicsObject
{
public:
	BackGroundObject(CString filename, int posx, int posy, int h, int w, double ss);

	double scrollSpeed;

	void draw(HDC offScreenDC);
	~BackGroundObject(void);

};

