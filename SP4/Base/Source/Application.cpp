
#include "Application.h"

//Include GLEW
/*#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>
*/

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
double Application::mouse_last_x = 0.0, Application::mouse_last_y = 0.0, 
	   Application::mouse_current_x = 0.0, Application::mouse_current_y = 0.0,
	   Application::mouse_diff_x = 0.0, Application::mouse_diff_y = 0.0;
double Application::camera_yaw = 0.0, Application::camera_pitch = 0.0;
int Application::m_iPrevScoreBlue = 0, Application::m_iPrevScoreRed = 0;
bool Application::m_bChangeRes = false, Application::m_bFullscreen = false;
int Application::m_window_width = 1280; int Application::m_window_height = 720;
int Application::choice = 0; float Application::mouseWorldX = 0; float Application::mouseWorldY = 0;
CSoundManager Application::Sound; 
bool Application::AppisRunning = true;
//CSoundManager Application::Sound;
vector<CProfile*>  Application::m_cProfileList;
vector<CAchievements*>  Application::m_cAchievementList;
vector<CProperties*>  Application::m_cPropertyList;
bool Application::m_bPauseDT = false;
int Application::CurrentLevel = 1;
bool Application::m_bScreenShake = false;
/********************************************************************************
 Define an error callback
 ********************************************************************************/
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

/********************************************************************************
 Define the key input callback
 ********************************************************************************/
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

/********************************************************************************
 Callback function when the window is resized
 ********************************************************************************/
void resize_callback(GLFWwindow* window, int w, int h)
{
	//std::cout << "W " << w << " H " << h << std::endl;
	Application::m_window_height = h;
	Application::m_window_width = w;
	glViewport(0, 0, w, h);
}

/********************************************************************************
 Get keyboard's key states
 ********************************************************************************/
bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

/********************************************************************************
Get Mouse press states
********************************************************************************/
bool Application::IsMousePressed(unsigned short key) //0 - Left, 1 - Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}
/********************************************************************************
Get windows height
********************************************************************************/
int Application::getWindowWidth()
{
	return m_window_width;
}
/********************************************************************************
Get windows width
********************************************************************************/
int Application::getWindowHeight()
{
	return m_window_height;
}
/********************************************************************************
Get the number in choice
********************************************************************************/
int Application::getChoiceVal(void)
{
	return choice;
}

/********************************************************************************
Get the number in choice
********************************************************************************/
float Application::getMouseWorldX(void)
{
	return mouseWorldX;
}

/********************************************************************************
Get the number in choice
********************************************************************************/
float Application::getMouseWorldY(void)
{
	return mouseWorldY;
}

/********************************************************************************
Set the number in choice
********************************************************************************/
void Application::setChoiceVal(int choice)
{
	Application::choice = choice;
}
/********************************************************************************
check for collision
********************************************************************************/
bool Application::checkForcollision(float mouseX, float mouseY, float pos_buttonX, float pos_buttonY, float pos_buttonWidth, float pos_buttonHeight)
{
	if (mouseX > pos_buttonX && mouseX < pos_buttonWidth) //within the x
	{
		if (mouseY > pos_buttonY && mouseY < pos_buttonHeight) //within the x and y
		{
			//mouse position is inside the button
			return true;
		}
	}
	else
	{
		return false;
	}
	return false;
}

/********************************************************************************
 Get mouse updates
 ********************************************************************************/
bool Application::GetMouseUpdate()
{
    glfwGetCursorPos(m_window, &mouse_current_x, &mouse_current_y);

	// Calculate the difference in positions
	mouse_diff_x = mouse_current_x - mouse_last_x;
	mouse_diff_y = mouse_current_y - mouse_last_y;

	//Calculate the yaw and pitch
	camera_yaw = (float) mouse_diff_x * 0.0174555555555556f;// * 3.142f / 180.0f;
	camera_pitch = mouse_diff_y * 0.0174555555555556f;// 3.142f / 180.0f );

	mouseWorldX = static_cast<float>(Application::mouse_current_x * m_world_width / Application::getWindowWidth());
	mouseWorldY = (static_cast<float>(Application::getWindowHeight() - Application::mouse_current_y) * m_world_height / Application::getWindowHeight());

	// Do a wraparound if the mouse cursor has gone out of the deadzone
	/*if ((mouse_current_x < m_window_deadzone) || (mouse_current_x > m_window_width-m_window_deadzone))
	{
		mouse_current_x = m_window_width >> 1;
		glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	}
	if ((mouse_current_y < m_window_deadzone) || (mouse_current_y > m_window_height-m_window_deadzone))
	{
		mouse_current_y = m_window_height >> 1;
		glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	}
*/
	// Store the current position as the last position
	mouse_last_x = mouse_current_x;
	mouse_last_y = mouse_current_y;

	// Get the mouse button status
	Button_Left   = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
	Button_Middle = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_MIDDLE);
	Button_Right  = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT);;

	// Update the GSM
	theGSM->HandleEvents( mouse_current_x, mouse_current_x, Button_Left, Button_Middle, Button_Right);

	// Get the mouse button status
//	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
//		scene->UpdateWeaponStatus(scene->WA_FIRE);

    return false;
}

/********************************************************************************
 Get keyboard updates
 ********************************************************************************/
bool Application::GetKeyboardUpdate()
{
	theGSM->HandleEvents(VK_RETURN, IsKeyPressed(VK_RETURN));
	
	theGSM->HandleEvents('n', IsKeyPressed('N'));
	theGSM->HandleEvents('r', IsKeyPressed('R'));
	theGSM->HandleEvents('p', IsKeyPressed('P'));
	theGSM->HandleEvents('g', IsKeyPressed('G'));
	theGSM->HandleEvents('q', IsKeyPressed('Q'));
	theGSM->HandleEvents('w', IsKeyPressed('W'));
	theGSM->HandleEvents('s', IsKeyPressed('S'));
	theGSM->HandleEvents('a', IsKeyPressed('A'));
	theGSM->HandleEvents('d', IsKeyPressed('D'));
	theGSM->HandleEvents('1', IsKeyPressed('1'));
	theGSM->HandleEvents('2', IsKeyPressed('2'));
	theGSM->HandleEvents('3', IsKeyPressed('3'));
	theGSM->HandleEvents('4', IsKeyPressed('4'));
	theGSM->HandleEvents(VK_LEFT, IsKeyPressed(VK_LEFT));
	theGSM->HandleEvents(VK_RIGHT, IsKeyPressed(VK_RIGHT));
	theGSM->HandleEvents(VK_UP, IsKeyPressed(VK_UP));
	theGSM->HandleEvents(VK_DOWN, IsKeyPressed(VK_DOWN));
	return true;
}

/********************************************************************************
 Constructor
 ********************************************************************************/
Application::Application()
: theGSM(NULL)
, m_window_name("Application")
{

}

/********************************************************************************
 Destructor
 ********************************************************************************/
Application::~Application()
{
	if (theGSM)
	{
		delete theGSM;
		theGSM = NULL;
	}
}

/********************************************************************************
 Initialise this program
 ********************************************************************************/
void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Calculating aspect ratio
	m_world_height = 100.f;
	m_world_width = m_world_height * (float)Application::getWindowWidth() / Application::getWindowHeight();//m_window_width/ m_window_height;

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	// Set these 2 variables to zero
	m_dElapsedTime = 0.0;
	m_dAccumulatedTime_ThreadOne = 0.0;
	m_dAccumulatedTime_ThreadTwo = 0.0;

	InitWindow(false);

	m_cLuaScript = new CLuaScript("Profile");
	CProfile* test = m_cLuaScript->getProfileVariables();
	m_cProfileList.push_back(test);
	delete m_cLuaScript;

	m_cLuaScript = new CLuaScript("AchievementProperties");
	int totalProperties = 0;
	totalProperties = m_cLuaScript->getIntVariable("TotalProperties");
	for (int i = 1; i < totalProperties + 1; i++)
	{
		ostringstream converter;
		string changedInt = "";
		converter << i;
		changedInt = converter.str();
		CProperties* test = m_cLuaScript->getAchievementPropertiesVariables(changedInt);
		m_cPropertyList.push_back(test);
	}
	delete m_cLuaScript;

	m_cLuaScript = new CLuaScript("Achievements");
	int totalAchievements = 0;
	totalAchievements = m_cLuaScript->getIntVariable("TotalAchievements");
	for (int i = 1; i < totalProperties + 1; i++)
	{
		ostringstream converter;
		string changedInt = "";
		converter << i;
		changedInt = converter.str();
		CAchievements* testTest = m_cLuaScript->getAchievementVariables(changedInt);
		m_cAchievementList.push_back(testTest);
	}
	delete m_cLuaScript;

	// Initialise the GSM
	theGSM = new CGameStateManager();
	theGSM->Init("DM2240 Assignment 1", m_window_width, m_window_height);
	theGSM->ChangeState( CSplashState::Instance() );
	//theGSM->ChangeState(CLevelSelectionState::Instance());
	//theGSM->ChangeState(CMenuState::Instance());
}

void Application::InitWindow(bool fullscreen)
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	//Create a window and create its OpenGL context
	if (!fullscreen)
		m_window = glfwCreateWindow(m_window_width, m_window_height, m_window_name.c_str(), NULL, NULL);
	else
	{
		m_window = glfwCreateWindow(mode->width, mode->height, m_window_name.c_str(), glfwGetPrimaryMonitor(), NULL);
		this->m_window_height = GetSystemMetrics(SM_CYSCREEN);
		this->m_window_width = GetSystemMetrics(SM_CXSCREEN);
	}


	//m_window = glfwCreateWindow(mode->width, mode->height, "Y2S2_Framework", glfwGetPrimaryMonitor(), NULL);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);
	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	// Hide the cursor
	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

/********************************************************************************
 Run this program
 ********************************************************************************/
void Application::Run()
{
	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE) && AppisRunning)
	{
		if (Application::m_bChangeRes)
		{
			if (!Application::m_bFullscreen)
			{
				glfwDestroyWindow(m_window);
				InitWindow(true);
				theGSM->ChangeState(COptionsState::Instance());
			}
			else
			{
				glfwDestroyWindow(m_window);
				InitWindow(false);
				theGSM->ChangeState(COptionsState::Instance());
			}
			Application::m_bFullscreen = !Application::m_bFullscreen;
			Application::m_bChangeRes = false;
		}
	
		// Get the elapsed time
		m_dElapsedTime = m_timer.getElapsedTime();
		m_dAccumulatedTime_ThreadOne += m_dElapsedTime;
		m_dAccumulatedTime_ThreadTwo += m_dElapsedTime;
		if (m_dAccumulatedTime_ThreadOne > 0.03)
		{
			// Get inputs
			GetMouseUpdate();
			GetKeyboardUpdate();

			// Update the GSM
			theGSM->HandleEvents();
			if (Application::m_bPauseDT)
			{
				theGSM->Update(0.0);
				Application::m_bPauseDT = false;
			}
			else
				theGSM->Update(m_dElapsedTime);

			for (int i = 0; i < Application::m_cPropertyList.size(); i++)
			{
				Application::m_cPropertyList[i]->Update();
			}
			for (int i = 0; i < Application::m_cAchievementList.size(); i++)
			{
				Application::m_cAchievementList[i]->Update(m_cPropertyList, m_dElapsedTime);
			}

			m_dAccumulatedTime_ThreadOne = 0.0;
		}
		if (m_dAccumulatedTime_ThreadTwo > 1.0)
		{
			//UpdateAI();
			m_dAccumulatedTime_ThreadTwo = 0.0;
		}
		// Render the scene
		theGSM->Draw();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed

	// Clean up the GSM
	theGSM->Cleanup();
}

/********************************************************************************
 Exit this program
 ********************************************************************************/
void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
