#include "SceneInstruction.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

#define buttonXoffset 55.5

CSceneInstruction::CSceneInstruction(void)
: m_window_width(800)
, m_window_height(600)
{
}

CSceneInstruction::CSceneInstruction(const int m_window_width, const int m_window_height)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

CSceneInstruction::~CSceneInstruction(void)
{
}

void CSceneInstruction::Init()
{
	CSceneManager::Init();

	//reset choice back to 0 (default)
	setChoiceVal(0);

	//create virtual positions for the buttons (back)
	geo_pos.Set(61.0f, 19.0f, 0.0f);

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

	//back button
	meshList[GEO_BACK] = MeshBuilder::Generate2DMesh("backs button", Color(1, 1, 1), 0.0f, 0.0f, 100.0f, 15.0f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image/MENU/back_button.tga");
	//back button highlighted
	meshList[GEO_BACK_H] = MeshBuilder::Generate2DMesh("back button highlighted", Color(1, 1, 1), 0.0f, 0.0f, 100.0f, 15.0f);
	meshList[GEO_BACK_H]->textureID = LoadTGA("Image/MENU//h_back_button.tga");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	bLightEnabled = true;
}

void CSceneInstruction::Update(double dt)
{
	CSceneManager::Update(dt);

	if (Application::IsKeyPressed('1'))
	{
		cout << "Cursor X: " << CSceneManager::GetWorldX() << endl;
		cout << "Cursor Y: " << CSceneManager::GetWorldY() << endl;

		cout << "choice: " << choice << endl;
	}

	//update choice on button press
	if (CSceneManager::IsKeyDownOnce('w') || CSceneManager::IsKeyDownOnce(VK_UP))
	{
		choice++;
		setChoiceVal(choice);
		// 0 = default 1 = back 
		if (choice > 1)
			setChoiceVal(0);
	}
	else if (CSceneManager::IsKeyDownOnce('s') || CSceneManager::IsKeyDownOnce(VK_DOWN))
	{
		choice--;
		setChoiceVal(choice);
		// 0 = default 1 = back 
		if (choice < 0)
			setChoiceVal(1);
	}

	//Update image on mouse hover
	if (checkForcollision(worldX, worldY, geo_pos.x, geo_pos.y, static_cast<float>(geo_pos.x + buttonXoffset), geo_pos.y + 8)) // back button
	{
		setChoiceVal(1);
	}
	//else
	//{
	//	setChoiceVal(0);
	//}

	float fDelta = (float)dt;

}

/********************************************************************************
Update Camera position
********************************************************************************/
void CSceneInstruction::UpdateCameraStatus(const unsigned char key, const bool status)
{
}

/********************************************************************************
Update Weapon status
********************************************************************************/
void CSceneInstruction::UpdateKeyboardStatus(const unsigned char key)
{
}

/********************************************************************************
Render this scene
********************************************************************************/
void CSceneInstruction::Render()
{
	CSceneManager::Render();

#if _DEBUG
	RenderTextOnScreen(meshList[GEO_TEXT], "SceneInstructions", Color(1.f, 1.f, 1.f), 20.f, -160.f, 70.f);

	std::ostringstream ss;
	ss.precision(5);
	ss << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1.f, 1.f, 1.f), 20.f, -160.f, -100.f);
#endif

	switch (choice)
	{
	case 1:
		RenderMeshIn2D(meshList[GEO_BACK_H], false, 1, 1, -50.0f, -52.5f);
		break;

	default: //default, no option chosen
		RenderMeshIn2D(meshList[GEO_BACK], false, 1, 1, -50.0f, -52.5f);
		break;
	}

}

/********************************************************************************
Exit process for this scene
********************************************************************************/
void CSceneInstruction::Exit()
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
