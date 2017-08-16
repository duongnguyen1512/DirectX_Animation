#ifndef _BALL_H_
#define _BALL_H_
class CBall
{
public: 
	float Vx;
	float Vy;

	float X;				
	float Y;

	float Width; 
	float Height;
	
	CBall(float X, float Y, float Width, float Height, float Vx, float Vy);

	void Next(int t, int ScreenWidth, int ScreenHeight);
};
#endif