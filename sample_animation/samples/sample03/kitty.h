#ifndef _RECTANGLES_H_
#define _RECTANGLES_H_

#include <d3dx9.h>

#include "game.h"
#include "sprite.h"

class CKitty: public CGame
{
public: 
	CKitty(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate);
	~CKitty();

	LPD3DXSPRITE _SpriteHandler;

	// IMPORTANT: This is only a SAMPLE, in real game, this should go to a separate class!!!
	int kitty_x;		// position of kitty
	int kitty_y;		

	float kitty_vx;		// velocity of kitty
	float kitty_vy;		

	float kitty_vx_last;  // last vx of kitty before stop ( to determine the direction of kitty )

	DWORD last_time;	 // this is to control the animate rate of kitty

	LPDIRECT3DSURFACE9 Background;
	CSprite * kitty_right; 
	CSprite * kitty_left; 




protected:
	LPDIRECT3DSURFACE9 _Background;

	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);

	virtual void OnKeyDown(int KeyCode);
};
#endif