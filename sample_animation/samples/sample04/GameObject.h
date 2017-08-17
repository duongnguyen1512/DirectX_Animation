#pragma once

#include "VideoDriver.h"

#define GROUND_Y 200

#define KITTY_IMAGE_RIGHT "kitty_right.bmp"
#define KITTY_IMAGE_LEFT "kitty_left.bmp"


class GameObject
{
public:
	float x, y;
	float vx, vy;
	float kitty_vx_last;  // last vx of kitty before stop ( to determine the direction of kitty )

	virtual void Render(VideoDriver *, GTexture*) = 0;
	RECT BoundingBox(GTexture*);
	//virtual void Update() = 0;
};