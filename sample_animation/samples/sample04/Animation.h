#pragma once

#include"Sprite.h"
#include"GameObject.h"

#define ANIMATE_RATE 30

class Animation : public GameObject
{
public:
	GTexture* kitty_left;
	GTexture* kitty_right;

	LPD3DXSPRITE SpriteHandler;
	int _Count; 
	int _SpritePerRow;
	int _Index;

	DWORD _last_time;	 // this is to control the animate rate of kitty

	Animation(GTexture *, LPDIRECT3DDEVICE9, int SpritePerRow, int Count);
	Animation(){}

	void Load(GTexture *);
	void Render(VideoDriver *, GTexture *);

	void Render_Object_Left(VideoDriver *);
	void Render_Object_Right(VideoDriver *);

	void Next();
	void Reset();

	RECT BoundingBox();//bounding box for object
};