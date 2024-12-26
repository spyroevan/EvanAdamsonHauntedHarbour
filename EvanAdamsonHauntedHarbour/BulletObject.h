#pragma once
#include "GraphicsObject.h"

class BulletObject:public GraphicsObject
{
public:
	BulletObject(void);

	int xspeed;
	int yspeed;
	int distanceTravelled;
	int maxDistance;
	bool fired;
	bool exploding;
	void move();
	void setExplode();
	void reset();






	~BulletObject(void);
};

