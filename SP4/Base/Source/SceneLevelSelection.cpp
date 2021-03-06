#include "SceneLevelSelection.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

#define buttonXoffset 42.3f
#define buttonYoffset 12.0f

#define buttonSizeOffset 1.15f

#define NUM_PAGES 2

bool CSceneLevelSelection::m_bBacktoMainMenu = false;
bool CSceneLevelSelection::m_bisColWithStartButton = false;

CSceneLevelSelection::CSceneLevelSelection(void)
: m_window_width(800)
, m_window_height(600)
, m_bAnimOffsetDir(true)
, m_bChangeState(false)
, m_bToggleConfirmSound(false)
, isSelectSoundPlayingkeyboard(false)
, isSelectSoundPlayingStartQuit(false)
, m_iCurrentPage(1)
{
}

CSceneLevelSelection::CSceneLevelSelection(const int m_window_width, const int m_window_height)
: m_bAnimOffsetDir(true)
, m_bChangeState(false)
, m_bToggleConfirmSound(false)
, isSelectSoundPlayingkeyboard(false)
, isSelectSoundPlayingStartQuit(false)
, m_iCurrentPage(1)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

CSceneLevelSelection::~CSceneLevelSelection(void)
{
}

void CSceneLevelSelection::Init()
{
	CSceneManager::Init();

	m_bBacktoMainMenu = false;

	//init the choice
	Application::setChoiceVal(1);
	m_bBacktoMainMenu = false;
	//vector of quit button pos
	quit_button_vec.Set(136.0f, 7.5f, 0.0f);

	//vector of start button pos
	start_button_vec.Set(69.0f, 7.5f, 0.0f);
	panic_button_vec = Vector3(90.0f, 7.5f, 0.0f);
	left_button_vec = Vector3(12.7f, 7.5f, 0.f);
	right_button_vec = Vector3(32.7f, 7.5f, 0.f);

	//vector positions of the level buttons
	for (int i = 0; i < 4; i++)
	{
		button_vec[i].Set(5.7f, 69.0f + (i * -16.8f), 0.0f);
	}

	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}

	meshList[GEO_RAY] = MeshBuilder::GenerateRay("ray", 10.0f);
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference");//, 1000, 1000, 1000);
	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateCrossHair("crosshair");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Font/8BitWonder.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);
	meshList[GEO_LOGO] = MeshBuilder::GenerateQuad("play", Color(1, 1, 1), 1.f);
	meshList[GEO_LOGO]->textureID = LoadTGA("Image//GUI/button_unselected_play.tga");
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("play", Color(1, 0.f, 1), 1.f);
	meshList[GEO_QUAD]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.f, 0.f, 0.f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.f, 0.f, 0.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//GUI/blank_tile.tga");

	//levels buttons
	meshList[GEO_LEVEL1_BUTTON] = MeshBuilder::Generate2DMeshCenter("lv1 button highlighted", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL1_BUTTON]->textureID = LoadTGA("Image/LEVELS//level1_button.tga");
	meshList[GEO_LEVEL2_BUTTON] = MeshBuilder::Generate2DMeshCenter("lv2 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL2_BUTTON]->textureID = LoadTGA("Image/LEVELS//level2_button.tga");
	meshList[GEO_LEVEL3_BUTTON] = MeshBuilder::Generate2DMeshCenter("lv3 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL3_BUTTON]->textureID = LoadTGA("Image/LEVELS//level3_button.tga");
	meshList[GEO_LEVEL4_BUTTON] = MeshBuilder::Generate2DMeshCenter("lv4 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL4_BUTTON]->textureID = LoadTGA("Image/LEVELS//level4_button.tga");
	meshList[GEO_LEVEL5_BUTTON] = MeshBuilder::Generate2DMeshCenter("lv4 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL5_BUTTON]->textureID = LoadTGA("Image/LEVELS//level5_button.tga");
	meshList[GEO_LEVEL6_BUTTON] = MeshBuilder::Generate2DMeshCenter("lv4 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL6_BUTTON]->textureID = LoadTGA("Image/LEVELS//level6_button.tga");
	meshList[GEO_LEVEL7_BUTTON] = MeshBuilder::Generate2DMeshCenter("lv4 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL7_BUTTON]->textureID = LoadTGA("Image/LEVELS//level7_button.tga");
	meshList[GEO_LEVEL8_BUTTON] = MeshBuilder::Generate2DMeshCenter("lv4 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL8_BUTTON]->textureID = LoadTGA("Image/LEVELS//level8_button.tga");

	//levels buttons highlighted
	meshList[GEO_LEVEL1_BUTTON_HIGHLIGHTED] = MeshBuilder::Generate2DMeshCenter("lv1 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL1_BUTTON_HIGHLIGHTED]->textureID = LoadTGA("Image/LEVELS//h_level1_button.tga");
	meshList[GEO_LEVEL2_BUTTON_HIGHLIGHTED] = MeshBuilder::Generate2DMeshCenter("lv2 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL2_BUTTON_HIGHLIGHTED]->textureID = LoadTGA("Image/LEVELS//h_level2_button.tga");
	meshList[GEO_LEVEL3_BUTTON_HIGHLIGHTED] = MeshBuilder::Generate2DMeshCenter("lv3 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL3_BUTTON_HIGHLIGHTED]->textureID = LoadTGA("Image/LEVELS//h_level3_button.tga");
	meshList[GEO_LEVEL4_BUTTON_HIGHLIGHTED] = MeshBuilder::Generate2DMeshCenter("lv4 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL4_BUTTON_HIGHLIGHTED]->textureID = LoadTGA("Image/LEVELS//h_level4_button.tga");
	meshList[GEO_LEVEL5_BUTTON_HIGHLIGHTED] = MeshBuilder::Generate2DMeshCenter("lv1 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL5_BUTTON_HIGHLIGHTED]->textureID = LoadTGA("Image/LEVELS//h_level5_button.tga");
	meshList[GEO_LEVEL6_BUTTON_HIGHLIGHTED] = MeshBuilder::Generate2DMeshCenter("lv2 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL6_BUTTON_HIGHLIGHTED]->textureID = LoadTGA("Image/LEVELS//h_level6_button.tga");
	meshList[GEO_LEVEL7_BUTTON_HIGHLIGHTED] = MeshBuilder::Generate2DMeshCenter("lv3 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL7_BUTTON_HIGHLIGHTED]->textureID = LoadTGA("Image/LEVELS//h_level7_button.tga");
	meshList[GEO_LEVEL8_BUTTON_HIGHLIGHTED] = MeshBuilder::Generate2DMeshCenter("lv4 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL8_BUTTON_HIGHLIGHTED]->textureID = LoadTGA("Image/LEVELS//h_level8_button.tga");

	meshList[GEO_BUTTON_LEFT] = MeshBuilder::Generate2DMeshCenter("start button", Color(1, 1, 1), 0.0f, 0.0f, 15.f, 15.0f);
	meshList[GEO_BUTTON_LEFT]->textureID = LoadTGA("Image/GUI//button_left.tga");
	meshList[GEO_BUTTON_RIGHT] = MeshBuilder::Generate2DMeshCenter("start button", Color(1, 1, 1), 0.0f, 0.0f, 15.f, 15.0f);
	meshList[GEO_BUTTON_RIGHT]->textureID = LoadTGA("Image/GUI//button_right.tga");
	
	//start button
	meshList[GEO_START_BUTTON] = MeshBuilder::Generate2DMeshCenter("start button", Color(1, 1, 1), 0.0f, 0.0f, 30.0f, 15.0f);
	meshList[GEO_START_BUTTON]->textureID = LoadTGA("Image/LEVELS//start_button.tga");
	
	//start highlighted
	meshList[GEO_START_BUTTON_HIGHLIGHTED] = MeshBuilder::Generate2DMeshCenter("start button highlighted", Color(1, 1, 1), 0.0f, 0.0f, 30.0f, 15.0f);
	meshList[GEO_START_BUTTON_HIGHLIGHTED]->textureID = LoadTGA("Image/LEVELS//h_start_button.tga");

	//quit buttons
	meshList[GEO_QUIT_BUTTON] = MeshBuilder::Generate2DMeshCenter("quit button", Color(1, 1, 1), 0.0f, 0.0f, 30.0f, 15.0f);
	meshList[GEO_QUIT_BUTTON]->textureID = LoadTGA("Image/INVENTORY//Quit.tga");

	//quit buttons highlighted
	meshList[GEO_QUIT_BUTTON_HIGHLIGHTED] = MeshBuilder::Generate2DMeshCenter("quit button highlighted", Color(1, 1, 1), 0.0f, 0.0f, 30.0f, 15.0f);
	meshList[GEO_QUIT_BUTTON_HIGHLIGHTED]->textureID = LoadTGA("Image/INVENTORY//h_Quit.tga");

	//Panic buttons
	meshList[GEO_BUTTON_PANIC_OFF] = MeshBuilder::Generate2DMeshCenter("start button", Color(1, 1, 1), 0.0f, 0.0f, 15.f, 15.0f);
	meshList[GEO_BUTTON_PANIC_OFF]->textureID = LoadTGA("Image/GUI//button_panic_off.tga");
	meshList[GEO_BUTTON_PANIC_ON] = MeshBuilder::Generate2DMeshCenter("start button", Color(1, 1, 1), 0.0f, 0.0f, 15.f, 15.0f);
	meshList[GEO_BUTTON_PANIC_ON]->textureID = LoadTGA("Image/GUI//button_panic_on.tga");

	//description backdrop
	meshList[GEO_DESCRIPTION_BACKDROP] = MeshBuilder::Generate2DMeshCenter("description box", Color(1, 1, 1), 0.0f, 0.0f, 160.0f, 50.0f);
	meshList[GEO_DESCRIPTION_BACKDROP]->textureID = LoadTGA("Image/LEVELS//Description_box.tga");

	//level overview
	meshList[GEO_LEVEL_OVERVIEW] = MeshBuilder::Generate2DMeshCenter("level overview", Color(1, 1, 1), 0.0f, 0.0f, 170.0f, 95.0f);
	meshList[GEO_LEVEL_OVERVIEW]->textureID = LoadTGA("Image/LEVELS//level1_overview.tga"); //default load lv 1

	meshList[GEO_LEVEL_OVERVIEW2] = MeshBuilder::Generate2DMeshCenter("level overview", Color(1, 1, 1), 0.0f, 0.0f, 170.0f, 95.0f);
	meshList[GEO_LEVEL_OVERVIEW2]->textureID = LoadTGA("Image/LEVELS//level2_overview.tga"); //default load lv 2

	meshList[GEO_LEVEL_OVERVIEW3] = MeshBuilder::Generate2DMeshCenter("level overview", Color(1, 1, 1), 0.0f, 0.0f, 170.0f, 95.0f);
	meshList[GEO_LEVEL_OVERVIEW3]->textureID = LoadTGA("Image/LEVELS//level3_overview.tga"); //default load lv 3

	meshList[GEO_LEVEL_OVERVIEW4] = MeshBuilder::Generate2DMeshCenter("level overview", Color(1, 1, 1), 0.0f, 0.0f, 170.0f, 95.0f);
	meshList[GEO_LEVEL_OVERVIEW4]->textureID = LoadTGA("Image/LEVELS//level4_overview.tga"); //default load lv 4

	meshList[GEO_LEVEL_OVERVIEW5] = MeshBuilder::Generate2DMeshCenter("level overview", Color(1, 1, 1), 0.0f, 0.0f, 170.0f, 95.0f);
	meshList[GEO_LEVEL_OVERVIEW5]->textureID = LoadTGA("Image/LEVELS//level5_overview.tga"); //default load lv 5 

	meshList[GEO_LEVEL_OVERVIEW6] = MeshBuilder::Generate2DMeshCenter("level overview", Color(1, 1, 1), 0.0f, 0.0f, 170.0f, 95.0f);
	meshList[GEO_LEVEL_OVERVIEW6]->textureID = LoadTGA("Image/LEVELS//level6_overview.tga"); //default load lv 6

	meshList[GEO_LEVEL_OVERVIEW7] = MeshBuilder::Generate2DMeshCenter("level overview", Color(1, 1, 1), 0.0f, 0.0f, 170.0f, 95.0f);
	meshList[GEO_LEVEL_OVERVIEW7]->textureID = LoadTGA("Image/LEVELS//level7_overview.tga"); //default load lv 7

	meshList[GEO_LEVEL_OVERVIEW8] = MeshBuilder::Generate2DMeshCenter("level overview", Color(1, 1, 1), 0.0f, 0.0f, 170.0f, 95.0f);
	meshList[GEO_LEVEL_OVERVIEW8]->textureID = LoadTGA("Image/LEVELS//level8_overview.tga"); //default load lv 8

	//Backgrounds
	meshList[GEO_BACKGROUND_BASE] = MeshBuilder::Generate2DMeshCenter("background", Color(1, 1, 1), 0.0f, 0.0f, 45.5f, 25.5f);
	meshList[GEO_BACKGROUND_BASE]->textureID = LoadTGA("Image//Background/gradient_background.tga");

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	m_fBotAnimOffset = -210.f;
	m_fLeftAnimOffset = -210.f;

	bLightEnabled = false;

	m_iSelectedLevel = 1;
}

void CSceneLevelSelection::Update(double dt)
{
	CSceneManager::Update(dt);

	UpdateAnimations(dt);

	//keyboard controls
	if (CSceneManager::IsKeyDownOnce('w') || CSceneManager::IsKeyDownOnce(VK_UP))
	{

		Application::setChoiceVal(Application::getChoiceVal() - 1);
		//1 = play, 2 = instructions, 3 = options, 4 = exit
		if (Application::getChoiceVal()  < 1)
			Application::setChoiceVal(4);

		Application::Sound.playSound("media/scroll_sound.wav");
		m_bisKeyBoard = true;
	}
	else if (CSceneManager::IsKeyDownOnce('s') || CSceneManager::IsKeyDownOnce(VK_DOWN))
	{
		Application::setChoiceVal(Application::getChoiceVal() + 1);
		//1 = play, 2 = instructions, 3 = options, 4 = exit

		if (Application::getChoiceVal() > 4)
			Application::setChoiceVal(1);

		Application::Sound.playSound("media/scroll_sound.wav");

		m_bisKeyBoard = true;
	}

	if (Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
	{
		if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), left_button_vec.x, left_button_vec.y, left_button_vec.x + 7.5f, left_button_vec.y + 7.5f))
			m_iCurrentPage = (m_iCurrentPage == 1 ? m_iCurrentPage : --m_iCurrentPage);
		else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), right_button_vec.x, right_button_vec.y, right_button_vec.x + 7.5f, right_button_vec.y + 7.5f))
			m_iCurrentPage = (m_iCurrentPage == NUM_PAGES ? m_iCurrentPage : ++m_iCurrentPage);
	}


	//on mouse hover level buttons
	if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), button_vec[0].x, button_vec[0].y, button_vec[0].x + buttonXoffset, button_vec[0].y + buttonYoffset) )
	{
		//reset the sound effect boolean on mouse up
		if (!Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
			isSelectSoundPlayingkeyboard = false;

		if (Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
		{
			//level 1 button
			Application::setChoiceVal(1);
			m_iSelectedLevel = 1;
			if (isSelectSoundPlayingkeyboard == false)
			{
				Application::Sound.playSound("media/scroll_sound.wav");
				isSelectSoundPlayingkeyboard = true;
			}
		}
		m_bisKeyBoard = false;
	}
	else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), button_vec[1].x, button_vec[1].y, button_vec[1].x + buttonXoffset, button_vec[1].y + buttonYoffset))
	{
		//reset the sound effect boolean on mouse up
		if (!Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
			isSelectSoundPlayingkeyboard = false;

		if (Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
		{
			//level 2 button
			Application::setChoiceVal(2);
			m_iSelectedLevel = 2;
			if (isSelectSoundPlayingkeyboard == false)
			{
				Application::Sound.playSound("media/scroll_sound.wav");
				isSelectSoundPlayingkeyboard = true;
			}
		}

		m_bisKeyBoard = false;
	}
	else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), button_vec[2].x, button_vec[2].y, button_vec[2].x + buttonXoffset, button_vec[2].y + buttonYoffset))
	{
		//reset the sound effect boolean on mouse up
		if (!Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
			isSelectSoundPlayingkeyboard = false;

		if (Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
		{
			//level 3 button
			Application::setChoiceVal(3);
			m_iSelectedLevel = 3;
			if (isSelectSoundPlayingkeyboard == false)
			{
				Application::Sound.playSound("media/scroll_sound.wav");
				isSelectSoundPlayingkeyboard = true;
			}
		}

		m_bisKeyBoard = false;
	}
	else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), button_vec[3].x, button_vec[3].y, button_vec[3].x + buttonXoffset, button_vec[3].y + buttonYoffset))
	{
		//reset the sound effect boolean on mouse up
		if (!Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
			isSelectSoundPlayingkeyboard = false;

		if (Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
		{
			//level 4 button
			Application::setChoiceVal(4);
			m_iSelectedLevel = 4;
			if (isSelectSoundPlayingkeyboard == false)
			{
				Application::Sound.playSound("media/scroll_sound.wav");
				isSelectSoundPlayingkeyboard = true;
			}
		}
		m_bisKeyBoard = false;
	}

	float fDelta = (float)dt;

	static bool LMouse = false;
	if (Application::IsMousePressed(GLFW_MOUSE_BUTTON_1) && !LMouse)
	{
		if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), panic_button_vec.x, panic_button_vec.y, panic_button_vec.x + 7.5f, panic_button_vec.y + 7.5f))
		{
			LMouse = true;
			Application::m_bScreenShake = !Application::m_bScreenShake;
		}
	}
	else if (!Application::IsMousePressed(GLFW_MOUSE_BUTTON_1) && LMouse)
		LMouse = false;

	if (IsKeyDownOnce(VK_RIGHT))
		m_iCurrentPage = (m_iCurrentPage == NUM_PAGES ? m_iCurrentPage : ++m_iCurrentPage);
	if (IsKeyDownOnce(VK_LEFT))
		m_iCurrentPage = (m_iCurrentPage == 1 ? m_iCurrentPage : --m_iCurrentPage);
	if (IsKeyDownOnce(VK_RETURN) && m_bAnimOffsetDir)
	{
		m_bAnimOffsetDir = false;
		if (m_iCurrentPage != 1)
			Application::CurrentLevel = Application::getChoiceVal() + (m_iCurrentPage - 1) * 4;
		else
			Application::CurrentLevel = Application::getChoiceVal();
	}
}

void CSceneLevelSelection::UpdateAnimations(double dt)
{
	float fDelta = static_cast<float>(dt);
	if (m_bAnimOffsetDir)
	{
		if (m_fLeftAnimOffset < 0.f)
		{
			m_fLeftAnimOffset += (-m_fLeftAnimOffset * 0.1f) + (fDelta * 10.f);
			if (m_fLeftAnimOffset > 0.f)
				m_fLeftAnimOffset = 0.f;
		}
		if (m_fBotAnimOffset < 0.f)
		{
			m_fBotAnimOffset += (-m_fBotAnimOffset * 0.08f) + (fDelta * 10.f);
			if (m_fBotAnimOffset > 0.f)
				m_fBotAnimOffset = 0.f;
		}
	}
	else
	{
		if (m_fLeftAnimOffset > -210.f)
		{
			m_fLeftAnimOffset -= (-m_fLeftAnimOffset * 0.5f) + (fDelta * 15.f);
			if (m_fLeftAnimOffset < -210.f)
				m_fLeftAnimOffset = -210.f;
		}
		if (m_fBotAnimOffset > -250.f)
		{
			m_fBotAnimOffset -= (-m_fBotAnimOffset * 0.3f) + (fDelta * 15.f);
			if (m_fBotAnimOffset < -250.f)
			{
				m_fBotAnimOffset = -250.f;
				m_bChangeState = true;
			}
		}
	}
}

/********************************************************************************
Update Camera position
********************************************************************************/
void CSceneLevelSelection::UpdateCameraStatus(const unsigned char key, const bool status)
{
}

/********************************************************************************
Update Weapon status
********************************************************************************/
void CSceneLevelSelection::UpdateKeyboardStatus(const unsigned char key)
{
}

/********************************************************************************
Set is quit to main
********************************************************************************/
void CSceneLevelSelection::SetISQuitToMain(bool b)
{
	m_bBacktoMainMenu = b;
}

/********************************************************************************
Get is quit to main
********************************************************************************/
bool CSceneLevelSelection::GetIsQuitToMain()
{
	return m_bBacktoMainMenu;
}

/********************************************************************************
set the boolean to check if mouse is in col with start button
********************************************************************************/
bool CSceneLevelSelection::GetisColWithStartButton()
{
	return m_bisColWithStartButton;
}

/********************************************************************************
set the boolean to check if mouse is in col with start button
********************************************************************************/
void CSceneLevelSelection::SetisColWithStartButton(bool b)
{
	CSceneLevelSelection::m_bisColWithStartButton = b;
}

/********************************************************************************
Render this scene
********************************************************************************/
void CSceneLevelSelection::Render()
{
	CSceneManager::Render();

	//Render backgrounds
	RenderMesh(meshList[GEO_BACKGROUND_BASE], false);

	if(Application::m_bScreenShake)
		RenderMeshIn2D(meshList[GEO_BUTTON_PANIC_ON], false, 1.0f, 1.0f, 10.0f, -70.0f + m_fBotAnimOffset);
	else
		RenderMeshIn2D(meshList[GEO_BUTTON_PANIC_OFF], false, 1.0f, 1.0f, 10.0f, -70.0f + m_fBotAnimOffset);

	RenderMeshIn2D(meshList[GEO_BUTTON_LEFT], false, 1.0f, 1.0f, -130.0f + m_fLeftAnimOffset, -70.0f);
	RenderMeshIn2D(meshList[GEO_BUTTON_RIGHT], false, 1.0f, 1.0f, -95.0f + m_fLeftAnimOffset, -70.0f);

	//on mouse hover quit button
	if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), quit_button_vec.x, quit_button_vec.y, quit_button_vec.x + 16.0f, quit_button_vec.y + 7.5f)
		|| CSceneManager::IsKeyDown('q'))
	{
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON_HIGHLIGHTED], false, 1.25f, 1.25f, 100.0f, -70.0f + m_fBotAnimOffset);

		if (Application::IsMousePressed(GLFW_MOUSE_BUTTON_1) || CSceneManager::IsKeyDown('q'))
		{
			SetISQuitToMain(true);
			m_bAnimOffsetDir = false;

			if (!m_bToggleConfirmSound)
			{
				Application::Sound.playSound("media/confirm_sound.wav");
				m_bToggleConfirmSound = true;
			}
		}

		if (isSelectSoundPlayingStartQuit == false)
		{
			Application::Sound.playSound("media/scroll_sound.wav");
			isSelectSoundPlayingStartQuit = true;
		}
	}
	else 
	{
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON], false, 1.0f, 1.0f, 100.0f, -70.0f + m_fBotAnimOffset);
		//SetISQuitToMain(false);

		if (!Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), start_button_vec.x, start_button_vec.y, start_button_vec.x + 16.6f, start_button_vec.y + 7.5f))
			isSelectSoundPlayingStartQuit = false;
	}

	
	//on mouse hover start button 
	if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), start_button_vec.x, start_button_vec.y, start_button_vec.x + 16.6f, start_button_vec.y + 7.5f))
	{
		RenderMeshIn2D(meshList[GEO_START_BUTTON_HIGHLIGHTED], false, 1.25f, 1.25f, -20.0f, -70.0f + m_fBotAnimOffset);

		if (Application::IsMousePressed(GLFW_MOUSE_BUTTON_1) )
		{
			SetisColWithStartButton(true);
			m_bAnimOffsetDir = false;
			//Do level selection here

			if (m_iCurrentPage != 1)
				Application::CurrentLevel = Application::getChoiceVal() + (m_iCurrentPage - 1) * 4;
			else
				Application::CurrentLevel = Application::getChoiceVal();

			
			if (!m_bToggleConfirmSound)
			{
				Application::Sound.playSound("media/confirm_sound.wav");
				m_bToggleConfirmSound = true;
			}


		}

		if (isSelectSoundPlayingStartQuit == false)
		{
			Application::Sound.playSound("media/scroll_sound.wav");
			isSelectSoundPlayingStartQuit = true;
		}
	}
	else 
	{
		RenderMeshIn2D(meshList[GEO_START_BUTTON], false, 1.0f, 1.0f, -20.0f, -70.0f + m_fBotAnimOffset);

		if (!Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), quit_button_vec.x, quit_button_vec.y, quit_button_vec.x + 16.0f, quit_button_vec.y + 7.5f))
			isSelectSoundPlayingStartQuit = false;
	}


	//Render the description box
	RenderMeshIn2D(meshList[GEO_DESCRIPTION_BACKDROP], false, 1.25f, 1.25f, 40.0f, -55.0f + m_fBotAnimOffset);

	//print the text
	RenderTextOnScreen(meshList[GEO_TEXT], "Description", Color(0.1f, 0.1f, 0.1f), 10.0f, -42.f, -42.f + m_fBotAnimOffset);
	std::ostringstream dialogue;
	dialogue << "";
	switch (m_iCurrentPage)
	{
		case 1:
		{
			  switch (Application::getChoiceVal())
			  {
			  case 1:
				  dialogue << "That temple awaits..";
				  break;
			  case 2:
				  dialogue << "Who is that guy...? is he friendly?";
				  break;
			  case 3:
				  dialogue << "KEYS!?..........Door?!......hmmm";
				  break;
			  case 4:
				  dialogue << "4 dead and mentally challenged brothers challenges you on the 4th level";
			  default:
				  break;
			  }
		}
			break;
		case 2:
		{
				  switch (Application::getChoiceVal())
				  {
				  case 1:
					  dialogue << "HOI!";
					  break;
				  case 2:
					  dialogue << "AHHHHHHHHHHHHHHHHHHHHHH";
					  break;
				  case 3:
					  dialogue << "The end is near...";
					  break;
				  case 4:
					  dialogue << "I'm almost at the top of the temple!";
				  default:
					  break;
				  }
		}
			break;
	}
	RenderTextOnScreen(meshList[GEO_TEXT], dialogue.str(), Color(0.f, 0.f, 0.f), 7.0f, -43.f, -45.f + m_fBotAnimOffset, 23.f);

	switch (m_iCurrentPage)
	{
	case 1:
		RenderMeshIn2D(meshList[GEO_LEVEL1_BUTTON], false, 1.0f, 1.0f, -111.5f + m_fLeftAnimOffset, 45.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL2_BUTTON], false, 1.0f, 1.0f, -111.5f + m_fLeftAnimOffset, 15.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL3_BUTTON], false, 1.0f, 1.0f, -111.5f + m_fLeftAnimOffset, -15.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL4_BUTTON], false, 1.0f, 1.0f, -111.5f + m_fLeftAnimOffset, -45.0f);
		switch (Application::getChoiceVal())
		{
		case 1: //level 1 button highlighted
			RenderMeshIn2D(meshList[GEO_LEVEL1_BUTTON_HIGHLIGHTED], false, buttonSizeOffset, buttonSizeOffset, -111.5f + m_fLeftAnimOffset, 45.0f);
			RenderMeshIn2D(meshList[GEO_LEVEL_OVERVIEW], false, 1.0f, 1.0f, 40.0f, 30.0f + m_fBotAnimOffset);
			break;
		case 2: //level 2 button highlighted
			RenderMeshIn2D(meshList[GEO_LEVEL2_BUTTON_HIGHLIGHTED], false, buttonSizeOffset, buttonSizeOffset, -111.5f + m_fLeftAnimOffset, 15.0f);
			RenderMeshIn2D(meshList[GEO_LEVEL_OVERVIEW2], false, 1.0f, 1.0f, 40.0f, 30.0f + m_fBotAnimOffset);
			break;
		case 3: //level 3 button highlighted
			RenderMeshIn2D(meshList[GEO_LEVEL3_BUTTON_HIGHLIGHTED], false, buttonSizeOffset, buttonSizeOffset, -111.5f + m_fLeftAnimOffset, -15.0f);
			RenderMeshIn2D(meshList[GEO_LEVEL_OVERVIEW3], false, 1.0f, 1.0f, 40.0f, 30.0f + m_fBotAnimOffset);
			break;
		case 4: //level 4 button highlighted
			RenderMeshIn2D(meshList[GEO_LEVEL4_BUTTON_HIGHLIGHTED], false, buttonSizeOffset, buttonSizeOffset, -111.5f + m_fLeftAnimOffset, -45.0f);
			RenderMeshIn2D(meshList[GEO_LEVEL_OVERVIEW4], false, 1.0f, 1.0f, 40.0f, 30.0f + m_fBotAnimOffset);
			break;
		default: //default, no option chosen
			break;
		}
		break;
	case 2:
		RenderMeshIn2D(meshList[GEO_LEVEL5_BUTTON], false, 1.0f, 1.0f, -111.5f + m_fLeftAnimOffset, 45.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL6_BUTTON], false, 1.0f, 1.0f, -111.5f + m_fLeftAnimOffset, 15.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL7_BUTTON], false, 1.0f, 1.0f, -111.5f + m_fLeftAnimOffset, -15.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL8_BUTTON], false, 1.0f, 1.0f, -111.5f + m_fLeftAnimOffset, -45.0f);

		switch (Application::getChoiceVal())
		{
		case 1: //level 1 button highlighted
			RenderMeshIn2D(meshList[GEO_LEVEL5_BUTTON_HIGHLIGHTED], false, buttonSizeOffset, buttonSizeOffset, -111.5f + m_fLeftAnimOffset, 45.0f);
			RenderMeshIn2D(meshList[GEO_LEVEL_OVERVIEW5], false, 1.0f, 1.0f, 40.0f, 30.0f + m_fBotAnimOffset);
			break;
		case 2: //level 2 button highlighted
			RenderMeshIn2D(meshList[GEO_LEVEL6_BUTTON_HIGHLIGHTED], false, buttonSizeOffset, buttonSizeOffset, -111.5f + m_fLeftAnimOffset, 15.0f);
			RenderMeshIn2D(meshList[GEO_LEVEL_OVERVIEW6], false, 1.0f, 1.0f, 40.0f, 30.0f + m_fBotAnimOffset);
			break;
		case 3: //level 3 button highlighted
			RenderMeshIn2D(meshList[GEO_LEVEL7_BUTTON_HIGHLIGHTED], false, buttonSizeOffset, buttonSizeOffset, -111.5f + m_fLeftAnimOffset, -15.0f);
			RenderMeshIn2D(meshList[GEO_LEVEL_OVERVIEW7], false, 1.0f, 1.0f, 40.0f, 30.0f + m_fBotAnimOffset);
			break;
		case 4: //level 4 button highlighted
			RenderMeshIn2D(meshList[GEO_LEVEL8_BUTTON_HIGHLIGHTED], false, buttonSizeOffset, buttonSizeOffset, -111.5f + m_fLeftAnimOffset, -45.0f);
			RenderMeshIn2D(meshList[GEO_LEVEL_OVERVIEW8], false, 1.0f, 1.0f, 40.0f, 30.0f + m_fBotAnimOffset);
			break;
		default: //default, no option chosen
			break;
		}
		break;
	default:
		break;
	}
	

}

/********************************************************************************
Exit process for this scene
********************************************************************************/
void CSceneLevelSelection::Exit()
{
	// Cleanup VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}
