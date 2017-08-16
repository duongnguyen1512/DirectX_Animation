#ifndef _GAME_H_
#define _GAME_H_
#include <windows.h>
#include <d3d9.h>
#include <dinput.h>

//
// Screen resolution
//
#define GAME_SCREEN_RESOLUTION_640_480_24   0
#define GAME_SCREEN_RESOLUTION_800_600_24   1
#define GAME_SCREEN_RESOLUTION_1024_768_24  2

#define GAME_SCREEN_RESOLUTION_640_480_32   10
#define GAME_SCREEN_RESOLUTION_800_600_32   11
#define GAME_SCREEN_RESOLUTION_1024_768_32  12

#define KEY_DOWN(code) ( IsKeyDown(code) )

#define KEYBOARD_BUFFER_SIZE	1024

class CGame
{
protected:
	LPDIRECT3D9 _d3d; 
	LPDIRECT3DDEVICE9 _d3ddv;
	LPDIRECT3DSURFACE9 _BackBuffer;

	LPDIRECTINPUT8       _di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 _Keyboard;	// The keyboard device 

	BYTE  _KeyStates[256];			// DirectInput keyboard state buffer 

	// Buffered keyboard data
	DIDEVICEOBJECTDATA _KeyEvents[ KEYBOARD_BUFFER_SIZE ];

	void _Init();
	
	DWORD _DeltaTime;		// Time between the last frame and current frame
	int _Mode;				// Screen mode 
	int _IsFullScreen;		// Is running in fullscreen mode?
	int _FrameRate; 
	
	int _ScreenWidth;
	int _ScreenHeight;
	int _Depth;

	D3DFORMAT _BackBufferFormat;

	HINSTANCE _hInstance;	// Handle of the game instance
	HWND _hWnd;				// Handle of the Game Window

	LPWSTR _Name;			// Name of game will be used as Window Class Name

	void _SetScreenDimension(int Mode);

	static LRESULT CALLBACK _WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void _InitWindow();
	void _InitDirectX();
	void _InitKeyboard();
	
	// Render a single frame
	void _RenderFrame();

	void _ProcessKeyBoard();
	int IsKeyDown(int KeyCode);

	// Place holder for sub classes
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);

	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

public:
	LPDIRECT3D9 GetDirectX();
	LPDIRECT3DDEVICE9 GetDevice();
	LPDIRECT3DSURFACE9 GetBackBuffer();

	int GetMode();

	int GetScreenWidth();
	int GetScreenHeight();
	int GetDepth();

	int FrameRate;			// Desired frame rate of game

	CGame(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullscreen, int FrameRate);
	~CGame();

	// Initialize the game with set parameters
	void Init();

	// Run game
	void Run();
};

#endif