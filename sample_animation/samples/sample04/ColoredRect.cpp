#pragma once
#include "ColoredRect.h"

void ColoredRect::Render(VideoDriver *video, GTexture* texture)
{
	video->DrawRect(this->x, this->y, this->width, this->height, D3DCOLOR_XRGB(this->r, this->g, this->b));
}

ColoredRect::ColoredRect(float x, float y, float width, float height, int r, int b, int g)
{
	this->x = x;	
	this->y = y;
	this->width = width;
	this->height = height;
	this->r = r;
	this->b = b;
	this->g = g;
}

RECT ColoredRect::BoundingBox()
{
	GTexture *t = new GTexture();
	t->FrameHeight = this->height;
	t->FrameWidth = this->width;

	return GameObject::BoundingBox(t);
}