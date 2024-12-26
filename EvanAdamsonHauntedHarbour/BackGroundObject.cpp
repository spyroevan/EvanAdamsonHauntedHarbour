#include "stdafx.h"
#include "BackGroundObject.h"


BackGroundObject::BackGroundObject(CString filename, int posx, int posy, int h, int w,double ss):GraphicsObject(filename,posx,posy)
{
	height = h;
	width=w;
	scrollSpeed=ss;


}



BackGroundObject::~BackGroundObject(void)
{
}

void BackGroundObject::draw(HDC offScreenDC)
{
	int relativeX= (int)((x-mapPosition)*scrollSpeed)%width;

	image.SetTransparentColor(RGB(255,174,201));
	image.TransparentBlt(offScreenDC,relativeX,y,width,height,0,0,width,height);
	image.TransparentBlt(offScreenDC,relativeX+width,y,width,height,0,0,width,height);
	image.TransparentBlt(offScreenDC,relativeX-width,y,width,height,0,0,width,height);

}