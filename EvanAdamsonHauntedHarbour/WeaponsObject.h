#pragma once
#include "graphicsobject.h"
#include "BulletObject.h"
class WeaponsObject :
	public GraphicsObject
{
public:
	WeaponsObject(CString filename, int xpos, int ypos);
	int numBullets;
	BulletObject *bullets[50];

	void fireBullet(int x, int y, int xs, int ys);
	void drawBullets(HDC offScreenDC);
	void moveBullets();
	void checkBulletCollisionWithBlock(GraphicsObject *block);


	~WeaponsObject(void);
};

