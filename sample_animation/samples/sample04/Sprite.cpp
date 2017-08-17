#include "Sprite.h"

Sprite::Sprite(float x, float y, GTexture *texture)
{
	this->x = x;
	this->y = y;
	this->texture = texture;
}

Sprite::Sprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow)
{
	
}

void Sprite::Render(VideoDriver *video, GTexture*)
{
	video->DrawSprite(this->x, this->y, this->texture);
}

void Sprite::Render(VideoDriver *video)
{
	Render(video, NULL);
}

RECT Sprite::BoundingBox()
{
	return GameObject::BoundingBox(texture);
}