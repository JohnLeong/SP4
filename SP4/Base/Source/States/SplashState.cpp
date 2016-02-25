#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "SplashState.h"
#include "playstate.h"
#include "gamestate.h"
#include "menustate.h"


CSplashState CSplashState::theMenuState;

void CSplashState::Init()
{
#if GSM_DEBUG_MODE
	cout << "CSplashState::Init\n" << endl;
#endif

	scene = new CSceneSplash(1280, 720);
	scene->Init();

}

void CSplashState::Init(const int width, const int height)
{
#if GSM_DEBUG_MODE
	cout << "CSplashState::Init\n" << endl;
#endif

	scene = new CSceneSplash(width, height);
	scene->Init();
	Application::Sound.playBackgroundSound("../irrKlang/media/mainMenuBGM.mp3");
}

void CSplashState::Cleanup()
{
#if GSM_DEBUG_MODE
	cout << "CSplashState::Cleanup\n" << endl;
#endif
}

void CSplashState::Pause()
{
#if GSM_DEBUG_MODE
	cout << "CSplashState::Pause\n" << endl;
#endif
}

void CSplashState::Resume()
{
#if GSM_DEBUG_MODE
	cout << "CSplashState::Resume\n" << endl;
#endif
}

void CSplashState::HandleEvents(CGameStateManager* theGSM)
{
}

void CSplashState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
	scene->SetKeyDown(key, status);
}

void CSplashState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							  const int button_Left, const int button_Middle, const int button_Right)
{

}

void CSplashState::Update(CGameStateManager* theGSM) 
{
#if GSM_DEBUG_MODE
	cout << "CSplashState::Update\n" << endl;
#endif
	if (scene->IsKeyDown(VK_RETURN))
		theGSM->ChangeState(CMenuState::Instance());
	scene->Update(0.16667);
}

void CSplashState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	scene->Update(m_dElapsedTime);
	if (scene->IsKeyDown(VK_RETURN))
		theGSM->ChangeState(CMenuState::Instance());
	if (((CSceneSplash*)scene)->m_fTimer < 0.f)
	{
		std::cout << "Changing to MENU state" << std::endl;
		theGSM->ChangeState(CMenuState::Instance());
	}
}

void CSplashState::Draw(CGameStateManager* theGSM) 
{
#if GSM_DEBUG_MODE
	//cout << "CSplashState::Draw\n" << endl;
#endif

	scene->Render();
}
