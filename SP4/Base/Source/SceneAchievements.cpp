#include "SceneAchievements.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

#define buttonXoffset 38.0f
#define buttonYoffset 11.5f

CSceneAchievements::CSceneAchievements(void)
: m_window_width(800)
, m_window_height(600)
, isSelectSoundPlaying(false)
{
}

CSceneAchievements::CSceneAchievements(const int m_window_width, const int m_window_height)
: isSelectSoundPlaying(false)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

CSceneAchievements::~CSceneAchievements(void)
{
}

void CSceneAchievements::Init()
{
	CSceneManager::Init();

	//init the choice
	Application::setChoiceVal(0);

	//create virtual positions for the buttons (back)
	geo_pos.Set(70.0f, 15.0f, 0.0f);

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

	//back button
	meshList[GEO_BACK] = MeshBuilder::Generate2DMeshCenter("backs button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image/MENU/back_button.tga");
	//back button highlighted
	meshList[GEO_BACK_H] = MeshBuilder::Generate2DMeshCenter("back button highlighted", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_BACK_H]->textureID = LoadTGA("Image/MENU//h_back_button.tga");

	//background base
	meshList[GEO_BACKGROUND_BASE] = MeshBuilder::Generate2DMeshCenter("background", Color(1, 1, 1), 0.0f, 0.0f, 1.5f, 0.85f);
	meshList[GEO_BACKGROUND_BASE]->textureID = LoadTGA("Image//Background/gradient_background.tga");

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	bLightEnabled = true;

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));
}

void CSceneAchievements::Update(double dt)
{
	CSceneManager::Update(dt);

	if (Application::IsKeyPressed('1'))
	{
		//cout << "current mouse x: " << Application::getMouseWorldX() << endl;
		//cout << "current mouse y: " << Application::getMouseWorldY() << endl;

		cout << "choice: " << Application::getChoiceVal() << endl;
	}

	if (CSceneManager::IsKeyDownOnce('w') || CSceneManager::IsKeyDownOnce(VK_UP))
	{

		Application::setChoiceVal(Application::getChoiceVal() - 1);
		//1 = play, 2 = instructions, 3 = options, 4 = exit
		if (Application::getChoiceVal() < 0)
			Application::setChoiceVal(1);

		Application::Sound.playSound("media/scroll_sound.wav");


		m_bisKeyBoard = true;
	}
	else if (CSceneManager::IsKeyDownOnce('s') || CSceneManager::IsKeyDownOnce(VK_DOWN))
	{
		Application::setChoiceVal(Application::getChoiceVal() + 1);
		//1 = play, 2 = instructions, 3 = options, 4 = exit
		if (Application::getChoiceVal() > 1)
			Application::setChoiceVal(0);


		Application::Sound.playSound("media/scroll_sound.wav");


		m_bisKeyBoard = true;
	}

	//Update image on mouse hover
	if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), geo_pos.x, geo_pos.y, static_cast<float>(geo_pos.x + buttonXoffset), geo_pos.y + buttonYoffset)) // back button
	{
		Application::setChoiceVal(1);
		m_bisKeyBoard = false;

		if (isSelectSoundPlaying == false)
		{
			Application::Sound.playSound("media/scroll_sound.wav");
			isSelectSoundPlaying = true;
		}

	}
	else if (!Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), geo_pos.x, geo_pos.y, static_cast<float>(geo_pos.x + buttonXoffset), geo_pos.y + buttonYoffset)
		&& !m_bisKeyBoard)
	{
		Application::setChoiceVal(0);

		isSelectSoundPlaying = false;
	}

	float fDelta = (float)dt;

}

/********************************************************************************
Update Camera position
********************************************************************************/
void CSceneAchievements::UpdateCameraStatus(const unsigned char key, const bool status)
{
}

/********************************************************************************
Update Weapon status
********************************************************************************/
void CSceneAchievements::UpdateKeyboardStatus(const unsigned char key)
{
}

/********************************************************************************
Render this scene
********************************************************************************/
void CSceneAchievements::Render()
{
	CSceneManager::Render();

	glDisable(GL_DEPTH_TEST);
	//Render the background
	RenderMesh(meshList[GEO_BACKGROUND_BASE], false);

	for (unsigned i = 0; i < Application::m_cAchievementList.size(); i++)
	{
		if (Application::m_cAchievementList[i]->GetUnlocked() == false)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], Application::m_cAchievementList[i]->GetTitle(), Color(0.f, 0.f, 0.f), 15.f, -130.f, 50.f + (i * -20.f));
		}
		else if (Application::m_cAchievementList[i]->GetUnlocked() == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], Application::m_cAchievementList[i]->GetTitle(), Color(0.f, 1.f, 0.f), 15.f, -130.f, 50.f + (i * -20.f));
		}
	}
//#if _DEBUG
//	RenderTextOnScreen(meshList[GEO_TEXT], "SceneAchievements", Color(1.f, 1.f, 1.f), 20.f, -160.f, 70.f);
//
//	std::ostringstream ss;
//	ss.precision(5);
//	ss << fps;
//	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1.f, 1.f, 1.f), 20.f, -160.f, -100.f);
//#endif

	switch (Application::getChoiceVal())
	{
	case 1:
		RenderMeshIn2D(meshList[GEO_BACK_H], false, 1.15f, 1.15f, 0.0f, -52.5f);
		break;

	default:
		RenderMeshIn2D(meshList[GEO_BACK], false, 1, 1, 0.0f, -52.5f);
		break;
	}

}

/********************************************************************************
Exit process for this scene
********************************************************************************/
void CSceneAchievements::Exit()
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
