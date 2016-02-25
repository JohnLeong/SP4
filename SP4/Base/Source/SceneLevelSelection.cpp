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

bool CSceneLevelSelection::m_bBacktoMainMenu = false;
bool CSceneLevelSelection::m_bisColWithStartButton = false;

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

	//init the choice
	Application::setChoiceVal(1);

	//vector of quit button pos
	quit_button_vec.Set(136.0f, 7.5f, 0.0f);

	//vector of start button pos
	start_button_vec.Set(69.0f, 7.5f, 0.0f);

	//vector positions of the level buttons
	for (int i = 0; i < 4; i++)
	{
		button_vec[i].Set(5.7f, 69.0f + (i * -16.8f), 0.0f);
		cout << button_vec[i] << endl;
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

	//quit buttons
	meshList[GEO_QUIT_BUTTON] = MeshBuilder::Generate2DMeshCenter("quit button", Color(1, 1, 1), 0.0f, 0.0f, 30.0f, 15.0f);
	meshList[GEO_QUIT_BUTTON]->textureID = LoadTGA("Image/INVENTORY//Quit.tga");

	//levels buttons
	meshList[GEO_LEVEL1_BUTTON] = MeshBuilder::Generate2DMeshCenter("lv1 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL1_BUTTON]->textureID = LoadTGA("Image/LEVELS//level1.tga");

	meshList[GEO_LEVEL2_BUTTON] = MeshBuilder::Generate2DMeshCenter("lv2 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL2_BUTTON]->textureID = LoadTGA("Image/LEVELS//level2.tga");

	meshList[GEO_LEVEL3_BUTTON] = MeshBuilder::Generate2DMeshCenter("lv3 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL3_BUTTON]->textureID = LoadTGA("Image/LEVELS//level3.tga");

	meshList[GEO_LEVEL4_BUTTON] = MeshBuilder::Generate2DMeshCenter("lv4 button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_LEVEL4_BUTTON]->textureID = LoadTGA("Image/LEVELS//level4.tga");
	
	//start button
	meshList[GEO_START_BUTTON] = MeshBuilder::Generate2DMeshCenter("start button", Color(1, 1, 1), 0.0f, 0.0f, 30.0f, 15.0f);
	meshList[GEO_START_BUTTON]->textureID = LoadTGA("Image/LEVELS//start_button.tga");

	//description backdrop
	meshList[GEO_DESCRIPTION_BACKDROP] = MeshBuilder::Generate2DMeshCenter("description box", Color(1, 1, 1), 0.0f, 0.0f, 160.0f, 50.0f);
	meshList[GEO_DESCRIPTION_BACKDROP]->textureID = LoadTGA("Image/LEVELS//Description_box.tga");

	//level overview
	meshList[GEO_LEVEL_OVERVIEW] = MeshBuilder::Generate2DMeshCenter("level overview", Color(1, 1, 1), 0.0f, 0.0f, 170.0f, 95.0f);
	meshList[GEO_LEVEL_OVERVIEW]->textureID = LoadTGA("Image/LEVELS//level1_overview.tga"); //default load lv 1

	//Backgrounds
	meshList[GEO_BACKGROUND_BASE] = MeshBuilder::Generate2DMeshCenter("background", Color(1, 1, 1), 0.0f, 0.0f, 45.5f, 30.5f);
	meshList[GEO_BACKGROUND_BASE]->textureID = LoadTGA("Image//Background/gradient_background.tga");

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

	//for debugging
	if (Application::IsKeyPressed('1'))
	{
		//cout << "boolean: " << GetIsQuitToMain() << endl;
		cout << "current mouse x: " << Application::getMouseWorldX() << endl;
		cout << "current mouse y: " << Application::getMouseWorldY() << endl;
		//cout << "current mouse x: " << Application::mouse_current_x << endl;
		//cout << "current mouse y: " << Application::mouse_current_y << endl;
		//cout << "choice: " << Application::getChoiceVal() << endl;
	}

	//keyboard controls
	if (CSceneManager::IsKeyDownOnce('w') || CSceneManager::IsKeyDownOnce(VK_UP))
	{

		Application::setChoiceVal(Application::getChoiceVal() - 1);
		//1 = play, 2 = instructions, 3 = options, 4 = exit
		if (Application::getChoiceVal()  < 1)
			Application::setChoiceVal(4);

		m_bisKeyBoard = true;
	}
	else if (CSceneManager::IsKeyDownOnce('s') || CSceneManager::IsKeyDownOnce(VK_DOWN))
	{
		Application::setChoiceVal(Application::getChoiceVal() + 1);
		//1 = play, 2 = instructions, 3 = options, 4 = exit

		if (Application::getChoiceVal() > 4)
			Application::setChoiceVal(1);

		m_bisKeyBoard = true;
	}

	//on mouse hover level buttons
	if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), button_vec[0].x, button_vec[0].y, button_vec[0].x + buttonXoffset, button_vec[0].y + buttonYoffset)
		&& Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
	{
		//level 1 button
		Application::setChoiceVal(1);
		m_bisKeyBoard = false;
	}
	else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), button_vec[1].x, button_vec[1].y, button_vec[1].x + buttonXoffset, button_vec[1].y + buttonYoffset)
		&& Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
	{
		//level 2 button
		Application::setChoiceVal(2);
		m_bisKeyBoard = false;
	}
	else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), button_vec[2].x, button_vec[2].y, button_vec[2].x + buttonXoffset, button_vec[2].y + buttonYoffset)
		&& Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
	{
		//level 3 button
		Application::setChoiceVal(3);
		m_bisKeyBoard = false;
	}
	else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), button_vec[3].x, button_vec[3].y, button_vec[3].x + buttonXoffset, button_vec[3].y + buttonYoffset)
		&& Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
	{
		//level 4 button
		Application::setChoiceVal(4);
		m_bisKeyBoard = false;
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
	
	//on mouse hover quit button
	if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), quit_button_vec.x, quit_button_vec.y, quit_button_vec.x + 16.0f, quit_button_vec.y + 7.5f)
		|| CSceneManager::IsKeyDown('q'))
	{
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON], false, 1.25f, 1.25f, 100.0f, -70.0f);

		if (Application::IsMousePressed(GLFW_MOUSE_BUTTON_1) || CSceneManager::IsKeyDown('q'))
		{
			SetISQuitToMain(true);
		}

	}
	else
	{
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON], false, 1.0f, 1.0f, 100.0f, -70.0f);
		SetISQuitToMain(false);
	}

	
	//on mouse hover start button 
	if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), start_button_vec.x, start_button_vec.y, start_button_vec.x + 16.6f, start_button_vec.y + 7.5f))
	{
		RenderMeshIn2D(meshList[GEO_START_BUTTON], false, 1.25f, 1.25f, -20.0f, -70.0f);

		if (Application::IsMousePressed(GLFW_MOUSE_BUTTON_1) )
		{
			SetisColWithStartButton(true);
		}

	}
	else
	{
		RenderMeshIn2D(meshList[GEO_START_BUTTON], false, 1.0f, 1.0f, -20.0f, -70.0f);
		//SetISQuitToMain(false);
	}


	//Render the description box
	RenderMeshIn2D(meshList[GEO_DESCRIPTION_BACKDROP], false, 1.25f, 1.25f, 40.0f, -55.0f);

	//print the text
	if (Application::getChoiceVal() == 1)
	{
		//Render the text dialogue for lv 1 
		std::ostringstream dialogue;
		dialogue << "Description:" << endl;
		dialogue << "That temple awaits..";
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue.str(), Color(0.f, 0.f, 0.f), 5.0f, -42.f, -40.f);
	}
	else if (Application::getChoiceVal() == 2)
	{
		//Render the text dialogue for lv 2 
		std::ostringstream dialogue;
		dialogue << "Description:" << "\n" << "Development in progress..";
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue.str(), Color(0.f, 0.f, 0.f), 5.0f, -42.f, -40.f);
	}
	else if (Application::getChoiceVal() == 3)
	{
		//Render the text dialogue for lv 3 
		std::ostringstream dialogue;
		dialogue << "Description:" << "\n" << "Development in progress..";
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue.str(), Color(0.f, 0.f, 0.f), 5.0f, -42.f, -40.f);
	}
	else if (Application::getChoiceVal() == 4)
	{
		//Render the text dialogue for lv 4 
		std::ostringstream dialogue;
		dialogue << "Description:" << "\n" << "Development in progress..";
		RenderTextOnScreen(meshList[GEO_TEXT], dialogue.str(), Color(0.f, 0.f, 0.f), 5.0f, -42.f, -40.f);
	}


	switch (Application::getChoiceVal())
	{
	case 1: //level 1 button highlighted
		RenderMeshIn2D(meshList[GEO_LEVEL1_BUTTON], false, 1.25f, 1.25f, -111.5f, 45.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL2_BUTTON], false, 1.0f, 1.0f, -111.5f, 15.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL3_BUTTON], false, 1.0f, 1.0f, -111.5f, -15.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL4_BUTTON], false, 1.0f, 1.0f, -111.5f, -45.0f);

		//level 1 overview image
		RenderMeshIn2D(meshList[GEO_LEVEL_OVERVIEW], false, 1.0f, 1.0f, 40.0f, 30.0f);
		break;
	case 2: //level 2 button highlighted
		RenderMeshIn2D(meshList[GEO_LEVEL1_BUTTON], false, 1.0f, 1.0f, -111.5f, 45.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL2_BUTTON], false, 1.25f, 1.25f, -111.5f, 15.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL3_BUTTON], false, 1.0f, 1.0f, -111.5f, -15.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL4_BUTTON], false, 1.0f, 1.0f, -111.5f, -45.0f);

		break;
	case 3: //level 3 button highlighted
		RenderMeshIn2D(meshList[GEO_LEVEL1_BUTTON], false, 1.0f, 1.0f, -111.5f, 45.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL2_BUTTON], false, 1.0f, 1.0f, -111.5f, 15.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL3_BUTTON], false, 1.25f, 1.25f, -111.5f, -15.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL4_BUTTON], false, 1.0f, 1.0f, -111.5f, -45.0f);

		break;
	case 4: //level 4 button highlighted
		RenderMeshIn2D(meshList[GEO_LEVEL1_BUTTON], false, 1.0f, 1.0f, -111.5f, 45.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL2_BUTTON], false, 1.0f, 1.0f, -111.5f, 15.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL3_BUTTON], false, 1.0f, 1.0f, -111.5f, -15.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL4_BUTTON], false, 1.25f, 1.25f, -111.5f, -45.0f);
	default: //default, no option chosen
		RenderMeshIn2D(meshList[GEO_LEVEL1_BUTTON], false, 1.0f, 1.0f, -111.5f, 45.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL2_BUTTON], false, 1.0f, 1.0f, -111.5f, 15.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL3_BUTTON], false, 1.0f, 1.0f, -111.5f, -15.0f);
		RenderMeshIn2D(meshList[GEO_LEVEL4_BUTTON], false, 1.0f, 1.0f, -111.5f, -45.0f);
		break;
	}

#if _DEBUG
	RenderTextOnScreen(meshList[GEO_TEXT], "SceneLevelSelection", Color(1.f, 1.f, 1.f), 10.f, -160.f, 80.f);

	//std::ostringstream ss;
	//ss.precision(5);
	//ss << fps;
	//RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1.f, 1.f, 1.f), 10.f, -180.f, -90.f);
#endif
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
