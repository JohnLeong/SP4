#include <iostream>
using namespace std;

#include "../Application.h"
#include "GameStateManager.h"
#include "playstate.h"
#include "gamestate.h"
#include "OptionsState.h"
#include "MenuState.h"

COptionsState COptionsState::theOptionsState;

void COptionsState::Init()
{
#if _DEBUG
	cout << "COptionsState::Init" << endl;
#endif

	scene = new CSceneOptions(1280, 720);
	scene->Init();
}

void COptionsState::Init(const int width, const int height)
{
#if _DEBUG
	cout << "COptionsState::Init" << endl;
#endif
	isConfirmsoundPlaying = false;
	scene = new CSceneOptions(width, height);
	scene->Init();
}

void COptionsState::Cleanup()
{
#if _DEBUG
	cout << "COptionsState::Cleanup" << endl;
#endif
	// Delete the scene
	scene->Exit();
	delete scene;
	scene = NULL;
}

void COptionsState::Pause()
{
#if _DEBUG
	cout << "COptionsState::Pause" << endl;
#endif
}

void COptionsState::Resume()
{
#if _DEBUG
	cout << "COptionsState::Resume" << endl;
#endif
}

void COptionsState::HandleEvents(CGameStateManager* theGSM)
{
#if _DEBUG
	//int m_iUserChoice = -1;

	//do {
	//	cout << "COptionsState: Choose one <0> Go to Intro State, <1> Go to Play State : " ;
	//	cin >> m_iUserChoice;
	//	cin.get();

	//	switch (m_iUserChoice) {
	//		case 0:
	//			theGSM->ChangeState( CIntroState::Instance() );
	//			break;

	//		case 1:
	//			theGSM->ChangeState( CPlayState::Instance() );
	//			break;
	//		default:
	//			cout << "Invalid choice!\n";
	//			m_iUserChoice = -1;
	//			break;
	//	}
	//} while (m_iUserChoice == -1);
#endif
}

void COptionsState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
	if (key == 'B' && status)
	{
		theGSM->ChangeState(CMenuState::Instance());
	}
	if (key == 'F' && status)
	{
		Application::m_bChangeRes = true;
	}

	scene->SetKeyDown(key, status);
}

void COptionsState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							  const int button_Left, const int button_Middle, const int button_Right)
{

}

void COptionsState::Update(CGameStateManager* theGSM) 
{
#if _DEBUG
	cout << "COptionsState::Update" << endl;
#endif
	scene->Update(0.16667);
}

void COptionsState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	scene->Update(m_dElapsedTime);

	if (scene->IsKeyDown(VK_RETURN) && Application::getChoiceVal() == 1
		|| ((Application*)scene)->IsMousePressed(GLFW_MOUSE_BUTTON_1) && Application::getChoiceVal() == 1)
	{
		if (isConfirmsoundPlaying == false)
		{
			Application::Sound.playSound("../irrKlang/media/confirm_sound.wav");
			isConfirmsoundPlaying = true;
		}

		theGSM->ChangeState(CMenuState::Instance());
	}

}

void COptionsState::Draw(CGameStateManager* theGSM) 
{
	scene->Render();
}
