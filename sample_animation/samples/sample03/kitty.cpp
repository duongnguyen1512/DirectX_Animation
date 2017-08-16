#include <time.h>
#include <d3dx9.h>
#include "kitty.h"
#include "utils.h"

#define KITTY_IMAGE_RIGHT L"kitty_right.bmp"
#define KITTY_IMAGE_LEFT L"kitty_left.bmp"
#define KITTY_SPEED 1.4f
#define GROUND_Y 450

#define BACKGROUND_FILE L"bg.bmp"

#define ANIMATE_RATE 30

CKitty::CKitty(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate):
CGame(hInstance,Name,Mode,IsFullScreen, FrameRate)
{
	kitty_right = NULL;
	kitty_left = NULL;

}

CKitty::~CKitty()
{
	delete kitty_left;
	delete kitty_right;
}

void CKitty::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	srand((unsigned)time(NULL));

	// TO-DO: not a very good place to initial sprite handler
	D3DXCreateSprite(d3ddv,&_SpriteHandler);

	Background = CreateSurfaceFromFile(_d3ddv, BACKGROUND_FILE);

	HRESULT res = D3DXCreateSprite(_d3ddv,&_SpriteHandler);

	kitty_x = 50;
	kitty_y = GROUND_Y;

	kitty_vx = 0;
	kitty_vx_last = 1.0f;
	kitty_vy = 0;

	kitty_right = new CSprite(_SpriteHandler,KITTY_IMAGE_RIGHT,91,60,6,3);
	kitty_left = new CSprite(_SpriteHandler,KITTY_IMAGE_LEFT,91,60,6,3);
}

void CKitty::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	// TO-DO: should enhance CGame to put a separate virtual method for updating game status


	// NOTES: If there is a class for kitty, this should be Kitty->Update(t);
	// Update kitty status
	kitty_x += kitty_vx * t;
	kitty_y += kitty_vy * t;

	// Animate kitty if she is running
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		if (kitty_vx > 0)
			kitty_right->Next();
		if (kitty_vx < 0)
			kitty_left->Next();

		last_time = now;
	}

	// Simulate fall down
	if (kitty_y < GROUND_Y) kitty_vy += 0.5f;
	else 
	{
		kitty_y = GROUND_Y;
		kitty_vy = 0;
	}

	// Background
	d3ddv->StretchRect(
			Background,			// from 
			NULL,				// which portion?
			_BackBuffer,		// to 
			NULL,				// which portion?
			D3DTEXF_NONE);


	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	
	// Kitty
	// If there is a class for kitty, this should be Kitty->Render();
	/*if (kitty_vx > 0)
		kitty_right->Render(_BackBuffer,kitty_x,kitty_y);
	else if (kitty_vx < 0)
		kitty_left->Render(_BackBuffer,kitty_x,kitty_y);
	else if (kitty_vx_last < 0)
		kitty_left->Render(_BackBuffer,kitty_x,kitty_y);
	else 
		kitty_right->Render(_BackBuffer,kitty_x,kitty_y);
	*/

	if (kitty_vx > 0)
		kitty_right->Render(kitty_x,kitty_y);
	else if (kitty_vx < 0)
		kitty_left->Render(kitty_x,kitty_y);
	else if (kitty_vx_last < 0)
		kitty_left->Render(kitty_x,kitty_y);
	else 
		kitty_right->Render(kitty_x,kitty_y);

	_SpriteHandler->End();
}

void CKitty::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	if (IsKeyDown(DIK_RIGHT))
	{
		kitty_vx = KITTY_SPEED;
		kitty_vx_last = kitty_vx;
	}	
	else 
		if (IsKeyDown(DIK_LEFT))
		{
			kitty_vx = -KITTY_SPEED;
			kitty_vx_last = kitty_vx;
		}
		else 
		{
			kitty_vx = 0;
			kitty_left->Reset();
			kitty_right->Reset();
		}
}

void CKitty::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
		case DIK_SPACE:
			if (kitty_y >= GROUND_Y) kitty_vy-=3.0f;			// start jump if is not "on-air"
			break;
	}
}