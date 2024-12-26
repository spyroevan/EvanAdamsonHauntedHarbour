#pragma once
#include "WeaponsObject.h"
#define MOVERIGHT 1
#define MOVELEFT 2
#define STANDRIGHT 3
#define STANDLEFT 4
#define JUMPRIGHT 5
#define JUMPLEFT 6
#define SHOOTRIGHT 7
#define SHOOTLEFT 8

class PlayerObject:public WeaponsObject
{
public:
	PlayerObject(void);
	int xspeed;
	int yspeed;
	void move();
	int state;

	// TO DO: Replace SHOOTRIGHT and SHOOTLEFT with a boolean that doesn't halt movement
	// Implement a better velocity system
	// Fix jumping

	void setMoveRight();
	void setMoveLeft();

	void setStandRight();
	void setStandLeft();

	void setJumpRight();
	void setJumpLeft();

	void setShootRight();
	void setShootLeft();

	bool isJumping();
	
	bool stopRight;
	bool stopLeft;

	void checkCollisionWithBlock(GraphicsObject *block);
	int prevX;
	int prevY;

	

	~PlayerObject(void);
};

