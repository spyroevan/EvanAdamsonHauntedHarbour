// EvanAdamsonHauntedHarbour.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "EvanAdamsonHauntedHarbour.h"
#include "GraphicsObject.h"
#include "PlayerObject.h"
#include "BackGroundObject.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void setScreen();
void drawScreen(HWND hWnd);

PlayerObject victor; // do not forget this exists
GraphicsObject block("../pics/Crate.bmp",200,380,64,64);
GraphicsObject badGuy("../pics/JellyFish.bmp",300,100);
BackGroundObject background("../pics/Background3.jpg",0,0,800,5118,0.2);
BackGroundObject ground("../pics/Ground.bmp",0,GROUND,128,774,1); // Originally this was called "floor" but after upgrading to VS2019, I had to rename it as apparently floor was taken
HDC offScreenDC;
int mapPosition=0;
bool movingLeft = false;
bool movingRight = false;






int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_EVANADAMSONHAUNTEDHARBOUR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EVANADAMSONHAUNTEDHARBOUR));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EVANADAMSONHAUNTEDHARBOUR));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_EVANADAMSONHAUNTEDHARBOUR);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 700, 580, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   SetTimer(hWnd,1,25,NULL);
   setScreen();

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN:

		switch (wParam)
		{
			case VK_RIGHT:
				if(victor.isJumping()==true)
				{
					victor.picY=86;
					victor.xspeed=10;
					victor.state=JUMPRIGHT;
				}
				else
				{
					victor.setMoveRight();
					movingRight = true;
				}
				victor.stopRight=false;

				break;
			case VK_LEFT:
				if(victor.isJumping()==true)
				{
					victor.picY=146;
					victor.xspeed=-10;
					victor.state=JUMPLEFT;
				}
				else
				{
					victor.setMoveLeft();
					movingLeft = true;
				}
				victor.stopLeft=false;

				break;
			case VK_UP:
				
					if((victor.state==MOVERIGHT)||(victor.state==STANDRIGHT))
					{
						victor.setJumpRight();
					}
					else if((victor.state==MOVELEFT)||(victor.state==STANDLEFT))
					{
						victor.setJumpLeft();
					}

				
				break;

			case VK_SPACE:
				if((victor.state==MOVERIGHT)||(victor.state==STANDRIGHT))
				{
					victor.setShootRight();
				}
				else if((victor.state==MOVELEFT)||(victor.state==STANDLEFT))
				{
					victor.setShootLeft();
				}
				
				if (victor.state==MOVERIGHT||victor.state==STANDRIGHT||victor.state==SHOOTRIGHT||victor.state==JUMPRIGHT)
				{
					victor.fireBullet(victor.x+victor.width-20,victor.y+7,20+victor.xspeed,0);
				}
				else
				{
					victor.fireBullet(victor.x+5,victor.y+7,-20+victor.xspeed,0);
				}

				break;

		}
		break;

	case WM_KEYUP:

		switch (wParam)
		{
			case VK_RIGHT:
				if (movingLeft == false){
					victor.setStandRight();
				}
				movingRight = false;
				victor.stopRight=true;
				break;

			case VK_LEFT:
				if (movingRight == false){
					victor.setStandLeft();
				}
				movingLeft = false;
				victor.stopLeft=true;
				break;

			case VK_SPACE:
				if(victor.state==SHOOTRIGHT)
				{
					if(movingRight==true)
					{
						victor.setMoveRight();
					}
					else
					{
						victor.setStandRight();
					}
					
				}
				else if(victor.state==SHOOTLEFT)
				{
					if(movingLeft==true)
					{
						victor.setMoveLeft();
					}
					else
					{
						victor.setStandLeft();
					}
				}
			break;
		}


	case WM_TIMER:

		victor.move();
		victor.moveBullets();
		

		victor.checkCollisionWithBlock(&block);
		victor.checkBulletCollisionWithBlock(&block);



		PostMessage(hWnd,WM_PAINT,0,0);
		
		


	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		background.draw(offScreenDC);
		ground.draw(offScreenDC);
		victor.draw(offScreenDC); //         Important Draw Location That Is Easy To Miss
		block.draw(offScreenDC);
		badGuy.draw(offScreenDC);
		victor.drawBullets(offScreenDC);

		
		
		drawScreen(hWnd);

		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void setScreen()
{
	HDC hTempDC;
	HBITMAP offScreenBMP;
	hTempDC = GetDC(0);
	//poopy buffer thing
	offScreenDC=CreateCompatibleDC(hTempDC);
	offScreenBMP = CreateCompatibleBitmap(hTempDC,800,600);
	SelectObject(offScreenDC,offScreenBMP);
	ReleaseDC(0,hTempDC);
}

void drawScreen(HWND hWnd)
{
	HDC ScreenDC;
	ScreenDC=GetDC(hWnd);
	TransparentBlt(ScreenDC,0,0,700,550,offScreenDC,0,0,700,550,RGB(255,174,201));
	DeleteDC(ScreenDC);
}