#pragma once
#include "GameObject.h"

class ColoredRect : public GameObject
{
public:
	int r, b, g;
	float width, height;

	ColoredRect(float, float, float, float, int, int, int);

	void Render(VideoDriver *, GTexture*);
	//void Update();
};