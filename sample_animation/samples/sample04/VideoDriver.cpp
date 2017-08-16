#pragma once

#include"VideoDriver.h"

void VideoDriver::DrawRect(RECT rect, D3DCOLOR color)
{
	d3ddv->ColorFill(surface, NULL, color);

	d3ddv->StretchRect(
		surface,			// from 
		NULL,				// which portion?
		back_buffer,		// to 
		&rect,				// which portion?
		D3DTEXF_NONE);
}

void VideoDriver::DrawRect(float x, float y, float width, float height, D3DCOLOR color)
{
	RECT rect;
	
	rect.left = x;
	rect.right = x + width;
	rect.top = y;
	rect.bottom = y + height;

	DrawRect(rect, color);
}

VideoDriver::VideoDriver(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DSURFACE9 back_buffer, LPDIRECT3DSURFACE9 surface)
{
	this->d3d = d3d;
	this->d3ddv = d3ddev;
	this->back_buffer = back_buffer;
	this->surface = surface;

	D3DXCreateSprite(d3ddev, &G_SpriteHandler);
}

void VideoDriver::DrawSprite(float x, float y, GTexture *texture)
{
	RECT srect;
	srect.left = 0;
	srect.right = texture->FrameWidth;
	srect.top = 0;
	srect.bottom = texture->FrameHeight;

	this->DrawSprite(x, y, texture, srect);
}

void VideoDriver::DrawSprite(float x, float y, GTexture *texture, RECT srect)
{
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = x;
	position.y = y;

	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	G_SpriteHandler->Draw(
		texture->Texture,
		&srect,
		NULL,
		&position,
		0xFFFFFFFF //color
		);
	G_SpriteHandler->End();
}