#include "stdafx.h"
#include "PlayerObject.h"


PlayerObject::PlayerObject(void):WeaponsObject("../pics/ViktorTesla.bmp",100,100)
{

	setStandRight();
	xspeed = 0;
	yspeed=0;
	state=STANDRIGHT;
	numBullets=10;
	for(int i = 0; i<numBullets; i++)
	{

		bullets[i]=new BulletObject();

	}


	hitHeight=42;
	hitWidth=54;


}


void PlayerObject::move()
{
	prevX=x;
	prevY=y;


	x+=xspeed;
	y+=yspeed;

	yspeed+=GRAVITY;

	if(y>(GROUND)-height)
	{
		if(state==JUMPLEFT&&stopLeft==true){setStandLeft();}//same here
		if(state==JUMPRIGHT&&stopRight==true){setStandRight();}//remove later pls
		if(state==JUMPLEFT&&stopLeft==false){setMoveLeft();}
		if(state==JUMPRIGHT&&stopRight==false){setMoveRight();}
		
		y=GROUND-height;
		yspeed=0;
		
	}
	if((x-mapPosition<180 && xspeed<0 ) || (x-mapPosition>350 && xspeed>0))
	{
	mapPosition+=xspeed;
	}


	if (state==MOVERIGHT)
	{
		animate2();
	}
	else
	{
		animate();
	}
	

}

void PlayerObject::setMoveRight()
{
	width=54;
	height=42;
	picY=0;
	endCell=0;
	loopCells=true;
	startCell=7;
	xspeed=10;
	picX=60;
	state=MOVERIGHT;
	//currentCell=7;
}

void PlayerObject::setMoveLeft()
{
	width=54;
	height=42;
	picY=42;
	endCell=9;
	loopCells=true;
	startCell=1;
	xspeed=-10;
	state=MOVELEFT;
	//currentCell=1;
}

void PlayerObject::setStandRight()
{
	width=54;
	height=42;
	picY=0;
	endCell=8;
	loopCells=false;
	startCell=8;
	xspeed=0;
	state=STANDRIGHT;
	currentCell=8;
}

void PlayerObject::setStandLeft()
{
	width=54;
	height=42;
	picY=42;
	endCell=0;
	loopCells=false;
	startCell=0;
	xspeed=0;
	state=STANDLEFT;
	currentCell=0;
}

void PlayerObject::setJumpRight()
{
	width=48;
	height=56;
	picY=86;
	endCell=5;
	loopCells=false;
	startCell=0;
	yspeed=-15;
	state=JUMPRIGHT;
	currentCell=0;
}

void PlayerObject::setJumpLeft()
{
	width=48;
	height=56;
	picY=146;
	endCell=5;
	loopCells=false;
	startCell=0;
	yspeed=-15;
	state=JUMPLEFT;
	currentCell=0;
}

void PlayerObject::setShootRight()
{
	width=60;
	height=38;
	picY=199;
	endCell=0;
	loopCells=false;
	startCell=0;
	xspeed=0;
	state=SHOOTRIGHT;
	currentCell=0;
}

void PlayerObject::setShootLeft()
{
	width=60;
	height=38;
	picY=237;
	endCell=0;
	loopCells=false;
	startCell=0;
	xspeed=0;
	state=SHOOTLEFT;
	currentCell=0;
}

bool PlayerObject::isJumping()
{
	return(state==JUMPLEFT || state==JUMPRIGHT);
}

void PlayerObject::checkCollisionWithBlock(GraphicsObject *block)
{
	
	if (hitTest(block))
	{
		if(prevX+hitWidth<=block->x)
		{

			x=block->x-hitWidth;
			
		}

		else if(prevX>=block->x+block->hitWidth)
		{

			x=block->x+block->hitWidth;

		}

		else if(prevY+hitHeight<=block->y)
		{
			if(state==JUMPLEFT&&stopLeft==true){
				setStandLeft();
			}
			else if(state==JUMPRIGHT&&stopRight==true){

				setStandRight();
			}
			else if (state==JUMPLEFT&&stopLeft==false){

				setMoveLeft();
			}
			else if(state==JUMPRIGHT&&stopRight==false)
			{
				setMoveRight();
			}


			y=block->y-hitHeight;
			yspeed=0;

		}
		else if(prevY >= block->y + block -> hitHeight)
		{
			
			y=block->y+block->hitHeight+1;
			yspeed=0;

		}

	}

}




PlayerObject::~PlayerObject(void)
{
}
