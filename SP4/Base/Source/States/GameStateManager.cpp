#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "gamestate.h"

void CGameStateManager::Init(const char* title, int width, int height, 
						 int bpp, bool fullscreen)
{
	m_window_width	= width;
	m_window_height	= height;

	m_bFullscreen = fullscreen;
	m_bRunning = true;

#if _DEBUG
	cout << "CGameStateManager::Init" << endl;
#endif
}

void CGameStateManager::Cleanup()
{
	// cleanup the all states
	while ( !StackOfStates.empty() ) {
		StackOfStates.back()->Cleanup();
		StackOfStates.pop_back();
	}

	// switch back to windowed mode so other 
	// programs won't get accidentally resized
	if ( m_bFullscreen ) {
	}

#if _DEBUG
	cout << "CGameStateManager::Cleanup" << endl;
#endif
}

void CGameStateManager::ChangeState(CGameState* state) 
{
	// cleanup the current state
	if ( !StackOfStates.empty() ) {
		StackOfStates.back()->Cleanup();
		StackOfStates.pop_back();
	}

	// store and init the new state
	StackOfStates.push_back(state);
	StackOfStates.back()->Init(m_window_width, m_window_height);
#if _DEBUG
	cout << "CGameStateManager::ChangeState" << endl;
#endif
}

void CGameStateManager::ChangeState(CGameState* state, int i, bool b)
{
	// cleanup the current state
	if (!StackOfStates.empty()) {
		StackOfStates.back()->Cleanup();
		StackOfStates.pop_back();
	}

	// store and init the new state
	StackOfStates.push_back(state);
	StackOfStates.back()->InitHoldData(m_window_width, m_window_height, i, b);
#if _DEBUG
	cout << "CGameStateManager::ChangeState" << endl;
#endif
}

void CGameStateManager::PushState(CGameState* state)
{
	// pause current state
	if ( !StackOfStates.empty() ) {
		StackOfStates.back()->Pause();
	}

	// store and init the new state
	StackOfStates.push_back(state);
	StackOfStates.back()->Init(m_window_width, m_window_height);
#if _DEBUG
	cout << "CGameStateManager::PushState" << endl;
#endif
}

void CGameStateManager::PopState()
{
	// cleanup the current state
	if ( !StackOfStates.empty() ) {
		StackOfStates.back()->Cleanup();
		StackOfStates.pop_back();
	}

	// resume previous state
	if ( !StackOfStates.empty() ) {
		StackOfStates.back()->Resume();
	}
#if _DEBUG
	cout << "CGameStateManager::PopState" << endl;
#endif
}

void CGameStateManager::HandleEvents() 
{
	// let the state handle events
	StackOfStates.back()->HandleEvents(this);
}

void CGameStateManager::HandleEvents(const unsigned char key, const bool status)
{
	// let the state handle events
	StackOfStates.back()->HandleEvents(this, key, status);
}

void CGameStateManager::HandleEvents(const double mouse_x, const double mouse_y,
									 const int button_Left, const int button_Middle, const int button_Right)
{
	// let the state handle events
	StackOfStates.back()->HandleEvents(this, mouse_x, mouse_y, button_Left, button_Middle, button_Right);
}

void CGameStateManager::Update(const double m_dElapsedTime) 
{
	// let the state update the theGSM
	StackOfStates.back()->Update(this, m_dElapsedTime);
}

void CGameStateManager::Draw() 
{
	// let the state draw the screen
	StackOfStates.back()->Draw(this);
}
