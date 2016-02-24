#include "SceneLevelSelection.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

#define buttonXoffset 55.5f
bool CSceneLevelSelection::m_bBacktoMainMenu = false;

CSceneLevelSelection::CSceneLevelSelection(void)
: m_window_width(800)
, m_window_height(600)
{
}

CSceneLevelSelection::CSceneLevelSelection(const int m_window_width, const int m_window_height)
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

	//reset choice back to 0 (default)
	/*setChoiceVal(0);*/

	//vector of quit button pos
	button_vec[0].Set(161.0f, 77.8f, 0.0f);

	//vector positions of the level buttons
	for (int i = 1; i < 5; i++)
	{
		button_vec[i].Set(5.7f, 67.0f + (i * -13.4f), 0.0f);
	}

	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}

	meshList[GEO_RAY] = MeshBuilder::GenerateRay("ray", 10.0f);
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference");//, 1000, 1000, 1000);
	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateCrossHair("crosshair");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Font/Anonymous.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);
	meshList[GEO_LOGO] = MeshBuilder::GenerateQuad("play", Color(1, 1, 1), 1.f);
	meshList[GEO_LOGO]->textureID = LoadTGA("Image//GUI/button_unselected_play.tga");
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("play", Color(1, 0.f, 1), 1.f);
	meshList[GEO_QUAD]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.f, 0.f, 0.f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.f, 0.f, 0.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//GUI/blank_tile.tga");

	//quit buttons
	meshList[GEO_QUIT_BUTTON] = MeshBuilder::Generate2DMesh("quit button", Color(1, 1, 1), 0.0f, 0.0f, 20.0f, 10.0f);
	meshList[GEO_QUIT_BUTTON]->textureID = LoadTGA("Image/INVENTORY//Quit.tga");

	//levels buttons
	meshList[GEO_LEVEL1_BUTTON] = MeshBuilder::Generate2DMeshCenter("lv1 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL1_BUTTON]->textureID = LoadTGA("Image/LEVELS//level1.tga");

	meshList[GEO_LEVEL2_BUTTON] = MeshBuilder::Generate2DMesh("lv2 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL2_BUTTON]->textureID = LoadTGA("Image/LEVELS//level2.tga");

	meshList[GEO_LEVEL3_BUTTON] = MeshBuilder::Generate2DMesh("lv3 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL3_BUTTON]->textureID = LoadTGA("Image/LEVELS//level3.tga");

	meshList[GEO_LEVEL4_BUTTON] = MeshBuilder::Generate2DMesh("lv4 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL4_BUTTON]->textureID = LoadTGA("Image/LEVELS//level4.tga");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	bLightEnabled = true;
}

void CSceneLevelSelection::Update(double dt)
{
	CSceneManager::Update(dt);

	if (Application::IsKeyPressed('1'))
	{
		//cout << "boolean: " << GetIsQuitToMain() << endl;
		cout << "current mouse x: " << Application::getMouseWorldX() << endl;
		cout << "current mouse y: " << Application::getMouseWorldY() << endl;
	}


	float fDelta = (float)dt;

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
	CSceneLevelSelection::m_bBacktoMainMenu = b;
}

/********************************************************************************
Get is quit to main
********************************************************************************/
bool CSceneLevelSelection::GetIsQuitToMain()
{
	return m_bBacktoMainMenu;
}

/********************************************************************************
Render this scene
********************************************************************************/
void CSceneLevelSelection::Render()
{
	CSceneManager::Render();

#if _DEBUG
	RenderTextOnScreen(meshList[GEO_TEXT], "SceneLevelSelection", Color(1.f, 1.f, 1.f), 20.f, -160.f, 70.f);

	std::ostringstream ss;
	ss.precision(5);
	ss << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1.f, 1.f, 1.f), 20.f, -160.f, -100.f);
#endif

	//on mouse hover quit button
	if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), button_vec[0].x, button_vec[0].y, button_vec[0].x + 11.0f, button_vec[0].y + 5.42f)
		|| CSceneManager::IsKeyDown('q'))
	{
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON], false, 1.1f, 1.1f, 128.0f, 50.0f);

		if (Application::IsMousePressed(GLFW_MOUSE_BUTTON_1) || CSceneManager::IsKeyDown('q'))
		{
			SetISQuitToMain(true);
		}

	}
	else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), button_vec[1].x, button_vec[1].y, button_vec[1].x + 11.0f, button_vec[1].y + 5.42f))
	{
		//level 1 button
	}
	//else
	//{
	//	RenderMeshIn2D(meshList[GEO_QUIT_BUTTON], false, 1, 1, 130, 50);
	//	SetISQuitToMain(false);
	//}

	RenderMeshIn2D(meshList[GEO_LEVEL1_BUTTON], false, 1.1f, 1.1f, -115.0f, 30.0f);
	RenderMeshIn2D(meshList[GEO_LEVEL2_BUTTON], false, 1.1f, 1.1f, -150.0f, 0.0f);
	RenderMeshIn2D(meshList[GEO_LEVEL3_BUTTON], false, 1.1f, 1.1f, -150.0f, -30.0f);
	RenderMeshIn2D(meshList[GEO_LEVEL4_BUTTON], false, 1.1f, 1.1f, -150.0f, -60.0f);
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
