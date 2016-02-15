#include "SceneMenu.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

CSceneMenu::CSceneMenu(void)
	: m_window_width(800)
	, m_window_height(600)
	, choice(1)
{
}

CSceneMenu::CSceneMenu(const int m_window_width, const int m_window_height)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

CSceneMenu::~CSceneMenu(void)
{
}

void CSceneMenu::Init()
{
	CSceneManager::Init();

	//init the choice
	choice = 4;

	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Font/Anonymous.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	//play button
	meshList[GEO_PLAY] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 10.0f, 3.0f);
	meshList[GEO_PLAY]->textureID = LoadTGA("Image/MENU//play_button.tga");
	//instructions button
	meshList[GEO_INSTRUCTIONS] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 10.0f, 3.0f);
	meshList[GEO_INSTRUCTIONS]->textureID = LoadTGA("Image/MENU//instructions_button.tga");
	//options button
	meshList[GEO_OPTIONS] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 10.0f, 3.0f);
	meshList[GEO_OPTIONS]->textureID = LoadTGA("Image/MENU//options_button.tga");
	//exit button
	meshList[GEO_EXIT] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 10.0f, 3.0f);
	meshList[GEO_EXIT]->textureID = LoadTGA("Image/MENU//exit_button.tga");

	//play button highlighted
	meshList[GEO_PLAY_H] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 10.0f, 3.0f);
	meshList[GEO_PLAY_H]->textureID = LoadTGA("Image/MENU//h_play_button.tga");
	//instructions button highlighted
	meshList[GEO_INSTRUCTIONS_H] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 10.0f, 3.0f);
	meshList[GEO_INSTRUCTIONS_H]->textureID = LoadTGA("Image/MENU//h_instructions_button.tga");
	//options button highlighted
	meshList[GEO_OPTIONS_H] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 10.0f, 3.0f);
	meshList[GEO_OPTIONS_H]->textureID = LoadTGA("Image/MENU//h_options_button.tga");
	//exit button highlighted
	meshList[GEO_EXIT_H] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 10.0f, 3.0f);
	meshList[GEO_EXIT_H]->textureID = LoadTGA("Image/MENU//h_exit_button.tga");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	
	rotateAngle = 0;

	bLightEnabled = true;
}

void CSceneMenu::Update(double dt)
{
	CSceneManager::Update(dt);

	float fDelta = (float)dt;
}

/********************************************************************************
 Update Camera position
 ********************************************************************************/
void CSceneMenu::UpdateCameraStatus(const unsigned char key, const bool status)
{
}

/********************************************************************************
 Update Weapon status
 ********************************************************************************/
void CSceneMenu::UpdateKeyboardStatus(const unsigned char key)
{
}

/********************************************************************************
 Render this scene
 ********************************************************************************/
void CSceneMenu::Render()
{
	CSceneManager::Render();
#if _DEBUG
	RenderTextOnScreen(meshList[GEO_TEXT], "SceneMenu", Color(1.f, 1.f, 1.f), 20.f, -160.f, 70.f);
#endif

	if (CSceneManager::IsKeyDownOnce('w') || CSceneManager::IsKeyDownOnce(VK_UP))
	{
		choice++;

		//1 = play, 2 = instructions, 3 = options, 4 = exit
		if (choice > 4)
			choice = 4;

		//cout << "choice: " << choice << endl;
	}
	else if(CSceneManager::IsKeyDownOnce('s') || CSceneManager::IsKeyDownOnce(VK_DOWN))
	{
		choice--;

		//1 = play, 2 = instructions, 3 = options, 4 = exit
		if (choice < 1)
			choice = 1;

		//cout << "choice: " << choice << endl;
	}

	switch (choice)
	{
	case 4: //play button highlighted
		RenderMeshIn2D(meshList[GEO_PLAY_H], false, 10, 5, -50.0f, 30.0f);
		RenderMeshIn2D(meshList[GEO_INSTRUCTIONS], false, 10, 5, -50.0f, 2.5f);
		RenderMeshIn2D(meshList[GEO_OPTIONS], false, 10, 5, -50.0f, -25.0f);
		RenderMeshIn2D(meshList[GEO_EXIT], false, 10, 5, -50.0f, -52.5f);

		break;
	case 3: //instructions button highlighted
		RenderMeshIn2D(meshList[GEO_PLAY], false, 10, 5, -50.0f, 30.0f);
		RenderMeshIn2D(meshList[GEO_INSTRUCTIONS_H], false, 10, 5, -50.0f, 2.5f);
		RenderMeshIn2D(meshList[GEO_OPTIONS], false, 10, 5, -50.0f, -25.0f);
		RenderMeshIn2D(meshList[GEO_EXIT], false, 10, 5, -50.0f, -52.5f);

		break;
	case 2: //options button highlighted
		RenderMeshIn2D(meshList[GEO_PLAY], false, 10, 5, -50.0f, 30.0f);
		RenderMeshIn2D(meshList[GEO_INSTRUCTIONS], false, 10, 5, -50.0f, 2.5f);
		RenderMeshIn2D(meshList[GEO_OPTIONS_H], false, 10, 5, -50.0f, -25.0f);
		RenderMeshIn2D(meshList[GEO_EXIT], false, 10, 5, -50.0f, -52.5f);

		break;
	case 1: //exit button highlighted
		RenderMeshIn2D(meshList[GEO_PLAY], false, 10, 5, -50.0f, 30.0f);
		RenderMeshIn2D(meshList[GEO_INSTRUCTIONS], false, 10, 5, -50.0f, 2.5f);
		RenderMeshIn2D(meshList[GEO_OPTIONS], false, 10, 5, -50.0f, -25.0f);
		RenderMeshIn2D(meshList[GEO_EXIT_H], false, 10, 5, -50.0f, -52.5f);

		break;
	}


}

/********************************************************************************
 Exit process for this scene
 ********************************************************************************/
void CSceneMenu::Exit()
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
