#ifndef APPLICATION_H
#define APPLICATION_H


#include "timer.h"
#include "States\GameStateManager.h"
#include "States\playstate.h"
#include "States\MenuState.h"
#include "States\SplashState.h"
#include "States\OptionsState.h"
#include <string>

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}

	static bool IsKeyPressed(unsigned short key);

	bool GetMouseUpdate();
	bool GetKeyboardUpdate();

	void Init();
	void InitWindow(bool fullscreen);
	void Run();
	void Exit();

	//Declare variables to store the last and current mouse position
	static double mouse_last_x, mouse_last_y, mouse_current_x, mouse_current_y, mouse_diff_x, mouse_diff_y;
	int Button_Left, Button_Middle, Button_Right;
	static double camera_yaw, camera_pitch;

	static int m_iPrevScoreRed;
	static int m_iPrevScoreBlue;
	static bool m_bFullscreen;
	static bool m_bChangeRes;

private:
	Application();
	~Application();

	// Declare the window width and height as constant integer
	const static int m_window_deadzone = 100;
	int m_window_width;
	int m_window_height;
	std::string m_window_name;
	//Declare a window object
	StopWatch m_timer;
	double m_dElapsedTime;
	double m_dAccumulatedTime_ThreadOne;
	double m_dAccumulatedTime_ThreadTwo;

	// Game State Management
	CGameStateManager* theGSM;
};

#endif