#include "SceneOptions.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include "LuaScript.h"

#define buttonXoffset 38.0f
#define buttonYoffset 11.5f

CSceneOptions::CSceneOptions(void)
: isSelectSoundPlaying(false)
, m_bisKeyBoard(false)
, m_volControl(0)
{
}

CSceneOptions::CSceneOptions(const int m_window_width, const int m_window_height)
: isSelectSoundPlaying(false)
, m_bisKeyBoard(false)
, m_volControl(0)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

CSceneOptions::~CSceneOptions(void)
{
}

void CSceneOptions::Init()
{
	CSceneManager::Init();

	//create virtual positions for the buttons (back)
	geo_pos[1].Set(70.0f, 15.0f, 0.0f);
	geo_pos[2].Set(130.0f, 15.0f, 0.0f);

	for(int i = 0; i < NUM_GEOMETRY; ++i)
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

	//back button
	meshList[GEO_BACK] = MeshBuilder::Generate2DMeshCenter("back button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image/MENU//back_button.tga");

	//back button highlighted
	meshList[GEO_BACK_H] = MeshBuilder::Generate2DMeshCenter("back button highlighted", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_BACK_H]->textureID = LoadTGA("Image/MENU//h_back_button.tga");

	//background base
	meshList[GEO_BACKGROUND_BASE] = MeshBuilder::Generate2DMeshCenter("background", Color(1, 1, 1), 0.0f, 0.0f, 1.5f, 0.85f);
	meshList[GEO_BACKGROUND_BASE]->textureID = LoadTGA("Image//Background/gradient_background.tga");

	//background image
	meshList[GEO_BACKGROUND_IMAGE] = MeshBuilder::Generate2DMeshCenter("background", Color(1, 1, 1), 0.0f, 0.0f, 1.0f, 0.85f);
	meshList[GEO_BACKGROUND_IMAGE]->textureID = LoadTGA("Image//Background/background_image_options.tga");

	//mute image
	meshList[GEO_MUTE_IMAGE] = MeshBuilder::Generate2DMeshCenter("background", Color(1, 1, 1), 0.0f, 0.3f, 0.3f, 0.3f);
	meshList[GEO_MUTE_IMAGE]->textureID = LoadTGA("Image//MENU/tiki_mute.tga");

	//unmute image
	meshList[GEO_VOL_HIGH] = MeshBuilder::Generate2DMeshCenter("background", Color(1, 1, 1), 0.0f, 0.3f, 0.3f, 0.3f);
	meshList[GEO_VOL_HIGH]->textureID = LoadTGA("Image//MENU/tiki_vol_high.tga");

	meshList[GEO_VOL_MID] = MeshBuilder::Generate2DMeshCenter("background", Color(1, 1, 1), 0.0f, 0.3f, 0.3f, 0.3f);
	meshList[GEO_VOL_MID]->textureID = LoadTGA("Image//MENU/tiki_vol_mid.tga");

	meshList[GEO_VOL_LOW] = MeshBuilder::Generate2DMeshCenter("background", Color(1, 1, 1), 0.0f, 0.3f, 0.3f, 0.3f);
	meshList[GEO_VOL_LOW]->textureID = LoadTGA("Image//MENU/tiki_vol_low.tga");

	//reset button
	meshList[GEO_RESET] = MeshBuilder::Generate2DMeshCenter("reset button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_RESET]->textureID = LoadTGA("Image/GUI//button_clear.tga");

	//reset button highlighted
	meshList[GEO_RESET_H] = MeshBuilder::Generate2DMeshCenter("reset button highlighted", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_RESET_H]->textureID = LoadTGA("Image/GUI//button_clear_h.tga");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	bLightEnabled = true;
}

void CSceneOptions::Update(double dt)
{
	CSceneManager::Update(dt);

	//for debugging
	if (Application::IsKeyPressed('1'))
	{
		//cout << "boolean: " << GetIsQuitToMain() << endl;
		//cout << "current mouse x: " << Application::getMouseWorldX() << endl;
		//cout << "current mouse y: " << Application::getMouseWorldY() << endl;
		//cout << "current mouse x: " << Application::mouse_current_x << endl;
		//cout << "current mouse y: " << Application::mouse_current_y << endl;
		cout << "vol: " << Application::Sound.GetCurrentVolume() << endl;
	}

	//adjust the volume control
	if (CSceneManager::IsKeyDownOnce('a') && Application::Sound.GetCurrentVolume() > 0)
	{
		Application::Sound.decreaseVolume();
		Application::Sound.playSound("../irrKlang/media/scroll_sound.wav");
	}
	else if (CSceneManager::IsKeyDownOnce('d') && Application::Sound.GetCurrentVolume() < 100 )
	{
		Application::Sound.increaseVolume();
		Application::Sound.playSound("../irrKlang/media/scroll_sound.wav");
	}

	if (Application::Sound.GetCurrentVolume() > 0 && Application::Sound.GetCurrentVolume()  <= 30)
	{
		m_ivolControl = VOL_LOW;
		
	}
	else if (Application::Sound.GetCurrentVolume() > 30 && Application::Sound.GetCurrentVolume() <= 60)
	{
		m_ivolControl = VOL_MID;
	}
	else if (Application::Sound.GetCurrentVolume() > 61 && Application::Sound.GetCurrentVolume() <= 100)
	{
		m_ivolControl = VOL_HIGH;
	}
	else
	{
		Application::Sound.pause();
		m_ivolControl = VOL_MUTE;
	}

	//button control
	if (CSceneManager::IsKeyDownOnce('w') || CSceneManager::IsKeyDownOnce(VK_UP))
	{

		Application::setChoiceVal(Application::getChoiceVal() - 1);
		//1 = play, 2 = instructions, 3 = options, 4 = exit
		if (Application::getChoiceVal() < 0)
			Application::setChoiceVal(2);

		Application::Sound.playSound("../irrKlang/media/scroll_sound.wav");


		m_bisKeyBoard = true;
	}
	else if (CSceneManager::IsKeyDownOnce('s') || CSceneManager::IsKeyDownOnce(VK_DOWN))
	{
		Application::setChoiceVal(Application::getChoiceVal() + 1);
		//1 = play, 2 = instructions, 3 = options, 4 = exit
		if (Application::getChoiceVal() > 2)
			Application::setChoiceVal(0);

		Application::Sound.playSound("../irrKlang/media/scroll_sound.wav");

		m_bisKeyBoard = true;
	}

	//Update image on mouse hover
	if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), geo_pos[1].x, geo_pos[1].y, static_cast<float>(geo_pos[1].x + buttonXoffset), geo_pos[1].y + buttonYoffset)) // back button
	{
		Application::setChoiceVal(1);
		m_bisKeyBoard = false;

		if (isSelectSoundPlaying == false)
		{
			Application::Sound.playSound("../irrKlang/media/scroll_sound.wav");
			isSelectSoundPlaying = true;
		}

	}
	else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), geo_pos[2].x, geo_pos[2].y, static_cast<float>(geo_pos[2].x + buttonXoffset), geo_pos[2].y + buttonYoffset)) // reset button
	{
		Application::setChoiceVal(2);
		m_bisKeyBoard = false;

		m_cLuaScript->resetProfileValues();
		m_cLuaScript->resetAchievementValues();
		m_cLuaScript->resetAchievementPropertiesValues();

		/*m_cLuaScript = new CLuaScript("Achievements");
		m_cLuaScript->resetAchievementValues();
		delete m_cLuaScript;
		m_cLuaScript = new CLuaScript("AchievementProperties");
		m_cLuaScript->resetAchievementPropertiesValues();
		delete m_cLuaScript;
		m_cLuaScript = new CLuaScript("Profile");
		m_cLuaScript->resetProfileValues();
		delete m_cLuaScript;*/
	}
	else if (!Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), geo_pos[0].x, geo_pos[0].y, static_cast<float>(geo_pos[0].x + buttonXoffset), geo_pos[0].y + buttonYoffset)
		&& !m_bisKeyBoard)
	{
		Application::setChoiceVal(0);

		isSelectSoundPlaying = false;
	}

	float fDelta = (float)dt;
	if (IsKeyDownOnce('f'))
		Application::m_bChangeRes = true;
}

/********************************************************************************
 Update Camera position
 ********************************************************************************/
void CSceneOptions::UpdateCameraStatus(const unsigned char key, const bool status)
{
}

/********************************************************************************
 Update Weapon status
 ********************************************************************************/
void CSceneOptions::UpdateKeyboardStatus(const unsigned char key)
{
}

/********************************************************************************
 Render this scene
 ********************************************************************************/
void CSceneOptions::Render()
{
	CSceneManager::Render();


	glDisable(GL_DEPTH_TEST);

//#if _DEBUG
//	RenderTextOnScreen(meshList[GEO_TEXT], "SceneOptions", Color(1.f, 1.f, 1.f), 20.f, -160.f, 70.f);
//
//	std::ostringstream ss;
//	ss.precision(5);
//	ss << fps;
//	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1.f, 1.f, 1.f), 20.f, -160.f, -100.f);
//#endif


	//Render the background
	RenderMesh(meshList[GEO_BACKGROUND_BASE], false);

	//Render the tiki image
	RenderMesh(meshList[GEO_BACKGROUND_IMAGE], false);

	//Render the volume button according to the current volume set
	switch (m_ivolControl)
	{
	case VOL_HIGH:
		//render the high vol button
		RenderMesh(meshList[GEO_VOL_HIGH], false);
		break;
	case VOL_MID:
		//render the mid vol button
		RenderMesh(meshList[GEO_VOL_MID], false);
		break;
	case VOL_LOW:
		//render the low vol button
		RenderMesh(meshList[GEO_VOL_LOW], false);
		break;
	case VOL_MUTE:
		//render the mute button
		RenderMesh(meshList[GEO_MUTE_IMAGE], false);
		break;
	}

	//render the back button
	switch (Application::getChoiceVal())
	{
	case 1:
		RenderMeshIn2D(meshList[GEO_BACK_H], false, 1.15f, 1.15f, 0.0f, -52.5f);
		RenderMeshIn2D(meshList[GEO_RESET], false, 1, 1, 100.0f, -52.5f);
		break;
	case 2:
		RenderMeshIn2D(meshList[GEO_BACK], false, 1, 1, 0.0f, -52.5f);
		RenderMeshIn2D(meshList[GEO_RESET_H], false, 1.15f, 1.15f, 100.0f, -52.5f);
		break;
	default:
		RenderMeshIn2D(meshList[GEO_BACK], false, 1, 1, 0.0f, -52.5f);
		RenderMeshIn2D(meshList[GEO_RESET], false, 1, 1, 100.0f, -52.5f);
		break;
	}
}

/********************************************************************************
 Exit process for this scene
 ********************************************************************************/
void CSceneOptions::Exit()
{
	// Cleanup VBO
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}
