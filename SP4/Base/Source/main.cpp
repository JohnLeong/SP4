
#define WINAPI      __stdcall
#include "Application.h"

INT __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	Application &app = Application::GetInstance();
	app.Init();
	app.Run();
	app.Exit();
}