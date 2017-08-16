#ifndef _RECTANGLES_H_
#define _RECTANGLES_H_
#include "game.h"
#include "ball.h"

class CBalls: public CGame
{
public: 
	CBalls(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate);
	~CBalls();

protected:
	CBall **_Balls;
	int _BallCount;
	
	LPDIRECT3DSURFACE9 _Surface;

	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);


};
#endif