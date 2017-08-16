#pragma once
#include <d3d9.h>
#include<d3dx9.h>
#include"GTexture.h"

class VideoDriver
{
private:
	LPDIRECT3D9 d3d = NULL;
	LPDIRECT3DDEVICE9 d3ddv = NULL;
	LPDIRECT3DSURFACE9 back_buffer = NULL;
	LPDIRECT3DSURFACE9 surface = NULL;

	LPD3DXSPRITE G_SpriteHandler;
public:
	VideoDriver(LPDIRECT3D9, LPDIRECT3DDEVICE9, LPDIRECT3DSURFACE9, LPDIRECT3DSURFACE9);
	//VideoDriver(LPDIRECT3D9, LPDIRECT3DDEVICE9, LPDIRECT3DSURFACE9, LPDIRECT3DSURFACE9, LPD3DXSPRITE);

	void DrawRect(RECT, D3DCOLOR);
	void DrawRect(float, float, float, float, D3DCOLOR);

	void DrawSprite(float x, float y, GTexture *texture);

	void DrawSprite(float x, float y, GTexture *texture, RECT);
};