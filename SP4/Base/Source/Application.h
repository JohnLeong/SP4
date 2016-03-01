#ifndef APPLICATION_H
#define APPLICATION_H


#include "timer.h"
#include "States\GameStateManager.h"
#include "States\playstate.h"
#include "States\MenuState.h"
#include "States\SplashState.h"
#include "States\OptionsState.h"
#include "SoundManager.h"
#include "States\InstructionState.h"
#include "States\LevelSelectionState.h"
#include <string>
#include "Achievements\Achievements.h"
#include "Achievements\Properties.h"
#include <sstream>

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}

	static bool IsKeyPressed(unsigned short key);
	static bool IsMousePressed(unsigned short key);

	bool GetMouseUpdate();
	bool GetKeyboardUpdate();

	static int getWindowHeight();
	static int getWindowWidth();

	static float getMouseWorldX();
	static float getMouseWorldY();

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

	//Handle to pause dt - dt set to 0 when true
	static bool m_bPauseDT;

	//get the value of choice
	static int getChoiceVal(void);
	//set the value of choice
	static void setChoiceVal(int choice);

	//check for collision
	static bool checkForcollision(float mouseX, float mouseY, float pos_buttonX, float pos_buttonY, float pos_buttonWidth, float pos_buttonHeight);

	//Sound Manager
	static CSoundManager Sound;

	//Boolean to close app if ran
	static bool AppisRunning;

	static vector<CAchievements*> m_cAchievementList;
	static vector<CProperties*> m_cPropertyList;

private:
	Application();
	~Application();

	// Declare the window width and height as constant integer
	const static int m_window_deadzone;
	
	std::string m_window_name;
	//Declare a window object
	StopWatch m_timer;
	double m_dElapsedTime;
	double m_dAccumulatedTime_ThreadOne;
	double m_dAccumulatedTime_ThreadTwo;

	static int m_window_width;
	static int m_window_height;

	//get mouse position in world space
	static float mouseWorldX;
	static float mouseWorldY;

	//World size
	float m_world_width;
	float m_world_height;

	//transverse the menu
	static int choice;

	// Game State Management
	CGameStateManager* theGSM;
	CAchievements* m_cAchievements;
	CProperties* m_cProperties;
	CLuaScript* m_cLuaScript;
	CScenePlay* m_cScenePlay;
};

#endif