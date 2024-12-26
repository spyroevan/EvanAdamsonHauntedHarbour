#pragma once
class GraphicsObject
{
public:
	GraphicsObject(CString fileName,int xpos,int ypos, int w = 55, int h = 42);

	CString ID;
	CImage image;
	int height;
	int width;
	int x; 
	int y;
	int picX;
	int picY;
	int startCell;
	int endCell;
	int currentCell;
	//int poopyCell;
	bool loopCells;
	int animatecount;
	bool hitTest(GraphicsObject *object);
	int hitHeight;
	int hitWidth;



	void animate();
	void animate2();

	void draw(HDC offScreenDC);

	~GraphicsObject(void);

};

