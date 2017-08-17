#pragma once
#include "GameObject.h"

class ColoredRect : public GameObject
{
public:
	int r, b, g;
	float width, height;

	ColoredRect(float x, float y, float width, float height, int r, int b, int g);

	void Render(VideoDriver *, GTexture*);
	RECT BoundingBox();
	//void Update();
};