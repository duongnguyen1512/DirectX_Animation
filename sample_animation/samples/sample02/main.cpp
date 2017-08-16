#include <windows.h>
#include "balls.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CBalls rec(hInstance,L"Ball game",GAME_SCREEN_RESOLUTION_800_600_24,1, 24);
	
	rec.Init();
	rec.Run();

	return 0;
}


