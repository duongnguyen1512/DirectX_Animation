#include <windows.h>
#include <d3d9.h>
#include"ColoredRect.h"
#include"Sprite.h"
#include"Animation.h"

#define APP_CLASS "SampleWindow"
#define MAIN_WINDOW_TITLE "Sample"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//key board
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

#define FRAME_RATE 30

#define SPEED 1.4f;

LPDIRECT3D9 d3d = NULL; 
LPDIRECT3DDEVICE9 d3ddv = NULL;
LPDIRECT3DSURFACE9 back_buffer = NULL;
LPDIRECT3DSURFACE9 surface = NULL;

Sprite *sprite;

Animation *ani;//animation kitty

ColoredRect *rect;
VideoDriver *video;
GTexture *texture;

DWORD DeltaTime;// Time between the last frame and current frame

ColoredRect *rect_barrier1, *rect_barrier2;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message) {
		case WM_DESTROY: 
			PostQuitMessage(0);
			break;
		default: 
			return DefWindowProc(hWnd, message, wParam,lParam);
	}

	return 0;

}

int GameInit(HINSTANCE hInstance, HWND hWnd) 
{
	

	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp; 

	ZeroMemory( &d3dpp, sizeof(d3dpp) );

	d3dpp.Windowed   = TRUE; // FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;

	d3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&d3ddv);

	if (d3ddv==NULL) 
	{
		return 0;
	}
	
	d3ddv->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&back_buffer);

	// Create a small off-screen surface (will fill it contain in GameRun)
	int result =
		d3ddv->CreateOffscreenPlainSurface(
			100,					// width 				
			100,					// height
			D3DFMT_X8R8G8B8,		// format
			D3DPOOL_DEFAULT,		// where? (VRAM or RAM)
			&surface,
			NULL);

	
	texture = new GTexture(d3ddv, "kitty_left.png", 3, 2, 6);

	//rect_barrier1 = new ColoredRect(200, 200, 50, 80, 0, 255, 255);
	//rect_barrier2 = new ColoredRect(550, 400, 50, 80, 0, 255, 255);

	rect = new ColoredRect(0, 0, 80, 80, 255, 0, 0);
	video = new VideoDriver(d3d, d3ddv, back_buffer, surface);
	sprite = new Sprite(100, 100, texture);
	ani = new Animation(texture, d3ddv, 3, 6);

	return 1;
}

bool CheckCollision()
{
	/*if ((rect->y + rect->height < rect_barrier1->y && rect->x + rect->width < rect_barrier1->x)
		|| (rect->y + rect->height < rect_barrier1->y && rect->x > rect_barrier1->x + rect_barrier1->width)
		|| (rect->y > rect_barrier1->y + rect_barrier1->height && rect->x + rect->width < rect_barrier1->x)
		|| (rect->y > rect_barrier1->y + rect_barrier1->height && rect->x > rect_barrier1->x + rect_barrier1->width)
		)
		return false;*/
	return true;
}

void GameRun(HWND hWnd)
{
	if (d3ddv->BeginScene()) 
	{
		// Clear back buffer with BLACK
		d3ddv->ColorFill(back_buffer,NULL,D3DCOLOR_XRGB(0,0,0));

		//rect->Render(video);
		//rect_barrier1->Render(video);
		//rect_barrier2->Render(video);
		//sprite->Render(video);

		ani->x += ani->vx * DeltaTime;

		if (ani->vx != 0)
			ani->Next();

		if (ani->vx > 0)
			ani->Render_Object_Right(video);
		else if (ani->vx < 0)
			ani->Render_Object_Left(video);
		else if (ani->kitty_vx_last < 0)
			ani->Render_Object_Left(video);
		else
			ani->Render_Object_Right(video);

		d3ddv->EndScene();

		//keydown
		if (KEYDOWN(VK_RIGHT))
		{
			ani->vx = SPEED;
			ani->kitty_vx_last = ani->vx;
		}
		else
			if (KEYDOWN(VK_LEFT))
			{
			ani->vx = -SPEED;
			ani->kitty_vx_last = ani->vx;
			}
			else
			{
				ani->vx = 0;
				ani->Reset();
			}
	}

	d3ddv->Present(NULL,NULL,NULL,NULL);
}

void GameEnd()
{
	if (d3ddv!=NULL) d3ddv->Release();
	if (d3d!=NULL) d3d->Release();
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APP_CLASS;
	wc.hIconSm = NULL;
	
	RegisterClassEx(&wc);

	HWND hWnd = 
		CreateWindow(
			APP_CLASS,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, 
//			WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT, 
			800,
			600,
			NULL,
			NULL,
			hInstance,
			NULL);
	
	if (!hWnd) { 
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	GameInit(hInstance, hWnd);

	// Enter game message loop
	MSG msg;
	int done = 0;
	DWORD frame_start = GetTickCount();;
	DWORD tick_per_frame = 100 / FRAME_RATE;
	while (!done) 
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT) done=1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		}

		DWORD now = GetTickCount();
		DeltaTime = now - frame_start;
		if (DeltaTime >= tick_per_frame)
		{
			frame_start = now;
			GameRun(hWnd);
		}
	}

	GameEnd();
	return 0;
}