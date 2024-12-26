#include "stdafx.h"
#include "GraphicsObject.h"


GraphicsObject::GraphicsObject(CString fileName,int xpos,int ypos,int w, int h)
{

	ID=fileName;
	width=w;
	height=h;
	x=xpos;
	y=ypos;
	picX=0;
	picY=0;
	image.Load(ID);
	currentCell=0;
	startCell=0;
	endCell=0;
	loopCells=true;
	animatecount=0;
	hitHeight=h;
	hitWidth=w;



	
}

void GraphicsObject::draw(HDC offScreenDC)
{

	
	image.SetTransparentColor(RGB(255,174,201));
	image.TransparentBlt(offScreenDC,x-mapPosition,y,width,height,picX,picY,width,height);


}

void GraphicsObject::animate()
{
	
	currentCell++;
	if (currentCell>=endCell)
	{
		if (loopCells==true)
		{
			currentCell=startCell;
		}
		else
		{
			currentCell=endCell;
		}
	}
	picX=width*currentCell;

}

void GraphicsObject::animate2()
{
	
		
	currentCell--;
	if (currentCell<=endCell)
	{
			currentCell=startCell;
	}
	picX=width*currentCell;

}

bool GraphicsObject::hitTest(GraphicsObject *object)
{

	if((x+hitWidth>object->x) && (x<object->x+object->hitWidth))
	{
		if ((y+hitHeight>object->y)&&(y<object->y+object->hitHeight))
		{

			return true;

		}
	}
	return false;



}







GraphicsObject::~GraphicsObject(void)
{
}
