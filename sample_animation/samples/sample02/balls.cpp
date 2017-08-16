#include <time.h>
#include <d3dx9.h>
#include "balls.h"

#define BALL_IMAGE_FILE L"ball.bmp"
#define BALL_WIDTH 25
#define BALL_HEIGHT 25

CBalls::CBalls(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate):
CGame(hInstance,Name,Mode,IsFullScreen, FrameRate)
{
	_Surface = NULL;
}

CBalls::~CBalls()
{
	for (int i=0;i<_BallCount;i++)
	{
		delete _Balls[i];
	}

	free(_Balls);
}

void CBalls::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	// Create a small off-screen surface (will fill it contain in GameRun)
	d3ddv->CreateOffscreenPlainSurface(
			BALL_WIDTH,				// width 				
			BALL_HEIGHT,			// height
			_BackBufferFormat,		// format
			D3DPOOL_DEFAULT,		// where? (VRAM or RAM)
			&_Surface,
			NULL);

	// Load ball image
	int res = D3DXLoadSurfaceFromFile(
			_Surface, 		// surface
			NULL,			// destination palette	
			NULL,			// destination rectangle 
			BALL_IMAGE_FILE,		
			NULL,			// source rectangle
			D3DX_DEFAULT, 	// filter image
			D3DCOLOR_XRGB(0,0,0),				// transparency (0 = none)
			NULL);			// reserved

	_BallCount = 50;
	_Balls = (CBall **)malloc(sizeof(CBall *)*_BallCount);

	int x = _ScreenWidth / 2;
	int y = _ScreenHeight / 2;

	for (int i=0;i<_BallCount;i++)
	{
		// Min speed is 0.1
		float vx = (  ((rand() % 80)+20) * (rand()%2==0?1:-1)  ) / 100.0;
		float vy = (  ((rand() % 80)+20) * (rand()%2==0?1:-1)  ) / 100.0;

		_Balls[i] = new CBall(x,y,vx,vy,BALL_WIDTH, BALL_HEIGHT);
	}

	if (res!=D3D_OK)
	{

	}
	srand((unsigned)time(NULL));
}

void CBalls::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
		d3ddv->ColorFill(_BackBuffer,NULL,D3DCOLOR_XRGB(0,0,0));

		for (int i=0;i<_BallCount;i++)
		{
			CBall *ball = _Balls[i];
			ball->Next(Delta, _ScreenWidth, _ScreenHeight);

			RECT rect; 
			rect.left = (long)ball->X;
			rect.top = (long)ball->Y;
			rect.right = rect.left + BALL_WIDTH;
			rect.bottom = rect.top + BALL_HEIGHT;

			// Draw the surface onto the back buffer
			d3ddv->StretchRect(
				_Surface,			// from 
				NULL,				// which portion?
				_BackBuffer,		// to 
				&rect,				// which portion?
				D3DTEXF_NONE);	
		}
}

