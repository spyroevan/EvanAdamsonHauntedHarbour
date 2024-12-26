#include "stdafx.h"
#include "BulletObject.h"
#include <math.h>


BulletObject::BulletObject(void):GraphicsObject("../pics/PurpleFire.bmp",0,0)
{
	fired=false;
	height=12;
	width=12;
	distanceTravelled=0;
	maxDistance=300;
	xspeed=0;
	yspeed=0;
	hitHeight=height;
	hitWidth=width;
	exploding=false;




}

void BulletObject::move()
{
	animate();
	if(exploding)
	{
		
		if(currentCell==endCell)
		{

			reset();

		}

	}
	else
	{

	
		x+=xspeed;
		y+=yspeed;
		distanceTravelled+=abs(xspeed)+abs(yspeed);
		if(distanceTravelled>maxDistance)
		{

			fired=false;
			distanceTravelled=0;

		}
	}
}


void BulletObject::setExplode()
{

	picY=12;
	picX=0;
	width=31;
	height=32;
	x-=12;
	y-=12;
	loopCells=false;
	endCell=2;
	currentCell=0;
	exploding = true;




}

void BulletObject::reset()
{

	exploding=false;
	fired=false;
	currentCell=0;
	picY=0;
	picX=0;
	width=12;
	height=12;
	distanceTravelled=0;
	endCell=0;

}


BulletObject::~BulletObject(void)
{
}
