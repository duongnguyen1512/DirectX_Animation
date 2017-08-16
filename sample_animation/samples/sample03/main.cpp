#include <windows.h>
#include "kitty.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CKitty rec(hInstance,L"Keyboard sample",GAME_SCREEN_RESOLUTION_800_600_24,0,60);
	
	rec.Init();
	rec.Run();

	return 0;
}


