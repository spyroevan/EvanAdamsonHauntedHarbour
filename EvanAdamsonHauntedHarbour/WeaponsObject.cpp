#include "stdafx.h"
#include "WeaponsObject.h"


WeaponsObject::WeaponsObject(CString filename, int xpos, int ypos):GraphicsObject(filename,xpos,ypos)
{






}

void WeaponsObject::moveBullets()
{
	for(int i = 0; i<numBullets; i++){

		if(bullets[i]->fired==true)
		{
			bullets[i]->move();

		}
	}
}

void WeaponsObject::drawBullets(HDC offScreenDC)
{

	for(int i = 0; i<numBullets; i++){

		if(bullets[i]->fired==true)
		{
			bullets[i]->draw(offScreenDC);

		}
	}

}

void WeaponsObject::fireBullet(int x, int y, int xs, int ys)
{

	for(int i = 0; i<numBullets; i++)
	{
		if(bullets[i]->fired==false)
		{

			bullets[i]->x=x;
			bullets[i]->y=y;
			bullets[i]->xspeed=xs;
			bullets[i]->yspeed=ys;
			bullets[i]->fired=true;
			bullets[i]->distanceTravelled=0;

			break;

		}
	}

}

void WeaponsObject::checkBulletCollisionWithBlock(GraphicsObject*block)
{

	for(int i = 0; i<numBullets; i++)
	{

		if(bullets[i]->fired==true)
		{

			if(bullets[i]->hitTest(block)==true && bullets[i]->exploding==false)
			{
				bullets[i]->setExplode();
				
			}

		}

	}





}



WeaponsObject::~WeaponsObject(void)
{
}
