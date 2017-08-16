#include "ball.h"

CBall::CBall(
			 float X, 
			 float Y, 
			 float Vx, 
			 float Vy, 
			 float Width, 
			 float Height)
{
	this->Vx = Vx;
	this->Vy = Vy;
	
	this->X = X;
	this->Y = X;

	this->Width = Width;
	this->Height = Height;
}

void CBall::Next(int t, int ScreenWidth, int ScreenHeight)
{
	//
	// Update position
	//
	X+=Vx*t;
	Y+=Vy*t;

	//
	// Test collision with Screen
	//
	if ((X+Width>ScreenWidth) || (X<0))
	{
		Vx=-Vx;
	}

	if ((Y+Height>ScreenHeight) || (Y<0))
	{
		Vy=-Vy;
	}
}