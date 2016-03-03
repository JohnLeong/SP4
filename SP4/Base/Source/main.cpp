

#include "Application.h"

INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR lpCmdLine, INT nCmdShow)

{
	Application &app = Application::GetInstance();
	app.Init();
	app.Run();
	app.Exit();
}