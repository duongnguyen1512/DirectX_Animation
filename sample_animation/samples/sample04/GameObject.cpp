#pragma once

#include"GameObject.h"

RECT GameObject::BoundingBox(GTexture *texture)
{
	RECT BoundingBox;
	BoundingBox.left = this->x;
	BoundingBox.right = BoundingBox.left + texture->FrameWidth;
	BoundingBox.top = this->y;
	BoundingBox.bottom = BoundingBox.top + texture->FrameHeight;

	return BoundingBox;
}