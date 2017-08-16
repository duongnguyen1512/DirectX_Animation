#pragma once
#include "GameObject.h"

class Sprite : public GameObject
{
public:
	GTexture *texture;
	LPD3DXSPRITE SpriteHandler;

	Sprite(float x, float y, GTexture *texture);
	Sprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow);
	Sprite(){}
	void Render(VideoDriver *);
	void Render(VideoDriver *, GTexture*);
};