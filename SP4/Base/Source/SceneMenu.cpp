#include "SceneMenu.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

#define buttonYoffset 55.5
CSceneMenu::CSceneMenu(void):
choice(1)
{
}

CSceneMenu::~CSceneMenu(void)
{
}

void CSceneMenu::Init()
{
	CSceneManager::Init();

	//Calculating aspect ratio
	m_world_height = 100.f;
	m_world_width = m_world_height * (float)Application::getWindowWidth() / Application::getWindowHeight();//m_window_width/ m_window_height;
	
	//init the choice
	choice = 4;

	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Font/Anonymous.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	//create virtual positions for the buttons
	for (int i = 0; i < 4; i++) //left side of button
	{
		//0 = play 1 = instructions 2 = options 3 = exit
		geo_pos[i].Set(61, 67 - (16 * i), 0);
		cout << geo_pos[i] << endl;
	}

	//play button
	meshList[GEO_PLAY] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 100.0f, 15.0f);
	meshList[GEO_PLAY]->textureID = LoadTGA("Image/MENU//play_button.tga");
	//instructions button
	meshList[GEO_INSTRUCTIONS] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 100.0f, 15.0f);
	meshList[GEO_INSTRUCTIONS]->textureID = LoadTGA("Image/MENU//instructions_button.tga");
	//options button
	meshList[GEO_OPTIONS] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 100.0f, 15.0f);
	meshList[GEO_OPTIONS]->textureID = LoadTGA("Image/MENU//options_button.tga");
	//exit button
	meshList[GEO_EXIT] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 100.0f, 15.0f);
	meshList[GEO_EXIT]->textureID = LoadTGA("Image/MENU//exit_button.tga");

	//play button highlighted
	meshList[GEO_PLAY_H] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 100.0f, 15.0f);
	meshList[GEO_PLAY_H]->textureID = LoadTGA("Image/MENU//h_play_button.tga");
	//instructions button highlighted
	meshList[GEO_INSTRUCTIONS_H] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 100.0f, 15.0f);
	meshList[GEO_INSTRUCTIONS_H]->textureID = LoadTGA("Image/MENU//h_instructions_button.tga");
	//options button highlighted
	meshList[GEO_OPTIONS_H] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 100.0f, 15.0f);
	meshList[GEO_OPTIONS_H]->textureID = LoadTGA("Image/MENU//h_options_button.tga");
	//exit button highlighted
	meshList[GEO_EXIT_H] = MeshBuilder::Generate2DMesh("play button", Color(1, 1, 1), 0.0f, 0.0f, 100.0f, 15.0f);
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

	worldX = Application::mouse_current_x * m_world_width / Application::getWindowWidth();
	worldY = (Application::getWindowHeight() - Application::mouse_current_y) * m_world_height / Application::getWindowHeight();
	
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
 Get the number in choice 
********************************************************************************/
int CSceneMenu::getChoiceVal(void)
{
	return choice;
}

/********************************************************************************
Set the number in choice
********************************************************************************/
void CSceneMenu::setChoiceVal(int choice)
{
	this->choice = choice;
}

/********************************************************************************
Check for collisions with button
********************************************************************************/
bool CSceneMenu::checkForcollision(float mouseX, float mouseY, float pos_buttonX, float pos_buttonY, float pos_buttonWidth, float pos_buttonHeight)
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
 Render this scene
 ********************************************************************************/
void CSceneMenu::Render()
{
	CSceneManager::Render();
#if _DEBUG
	RenderTextOnScreen(meshList[GEO_TEXT], "SceneMenu", Color(1.f, 1.f, 1.f), 20.f, -160.f, 70.f);
#endif
	if (Application::IsKeyPressed('1'))
	{
		cout << "current mouse x: " << worldX << endl;
		cout << "current mouse y: " << worldY << endl;
		cout << "geo_pos.x: " << geo_pos[1].x << endl;
		cout << "geo_pos.y: " << geo_pos[1].y << endl;
		cout << "geo_pos.x R: " << geo_pos[1].x + 55.5 << endl;
		cout << "geo_pos.y R: " << geo_pos[1].y + 8 << endl;

	}
	
	//Update image on mouse hover
	if (checkForcollision(worldX, worldY, geo_pos[0].x, geo_pos[0].y, geo_pos[0].x + buttonYoffset, geo_pos[0].y + 8)) // play button
	{
		setChoiceVal(4);
	}
	else if (checkForcollision(worldX, worldY, geo_pos[1].x, geo_pos[1].y, geo_pos[1].x + buttonYoffset, geo_pos[1].y + 8)) // instructions button
	{
		setChoiceVal(3);
	}
	else if (checkForcollision(worldX, worldY, geo_pos[2].x, geo_pos[2].y, geo_pos[2].x + buttonYoffset, geo_pos[2].y + 8)) // options button
	{
		setChoiceVal(2);
	}
	else if (checkForcollision(worldX, worldY, geo_pos[3].x, geo_pos[3].y, geo_pos[3].x + buttonYoffset, geo_pos[3].y + 8)) // exit button
	{
		setChoiceVal(1);
	}

	if (CSceneManager::IsKeyDownOnce('w') || CSceneManager::IsKeyDownOnce(VK_UP))
	{
		choice++;
		setChoiceVal(choice);
		//1 = play, 2 = instructions, 3 = options, 4 = exit
		if (choice > 4)
			setChoiceVal(4);

		//cout << "choice: " << getChoiceVal() << endl;
	}
	else if(CSceneManager::IsKeyDownOnce('s') || CSceneManager::IsKeyDownOnce(VK_DOWN))
	{
		choice--;
		setChoiceVal(choice);
		//1 = play, 2 = instructions, 3 = options, 4 = exit
		if (choice < 1)
			setChoiceVal(1);

		//cout << "choice: " << getChoiceVal() << endl;
	}

	switch (choice)
	{
	case 4: //play button highlighted
		RenderMeshIn2D(meshList[GEO_PLAY_H], false, 1, 1, -50.0f, 30.0f);
		RenderMeshIn2D(meshList[GEO_INSTRUCTIONS], false, 1, 1, -50.0f, 2.5f);
		RenderMeshIn2D(meshList[GEO_OPTIONS], false, 1, 1, -50.0f, -25.0f);
		RenderMeshIn2D(meshList[GEO_EXIT], false, 1, 1, -50.0f, -52.5f);

		break;
	case 3: //instructions button highlighted
		RenderMeshIn2D(meshList[GEO_PLAY], false, 1, 1, -50.0f, 30.0f);
		RenderMeshIn2D(meshList[GEO_INSTRUCTIONS_H], false, 1, 1, -50.0f, 2.5f);
		RenderMeshIn2D(meshList[GEO_OPTIONS], false, 1, 1, -50.0f, -25.0f);
		RenderMeshIn2D(meshList[GEO_EXIT], false, 1, 1, -50.0f, -52.5f);

		break;
	case 2: //options button highlighted
		RenderMeshIn2D(meshList[GEO_PLAY], false, 1, 1, -50.0f, 30.0f);
		RenderMeshIn2D(meshList[GEO_INSTRUCTIONS], false, 1, 1, -50.0f, 2.5f);
		RenderMeshIn2D(meshList[GEO_OPTIONS_H], false, 1, 1, -50.0f, -25.0f);
		RenderMeshIn2D(meshList[GEO_EXIT], false, 1, 1, -50.0f, -52.5f);

		break;
	case 1: //exit button highlighted
		RenderMeshIn2D(meshList[GEO_PLAY], false, 1, 1, -50.0f, 30.0f);
		RenderMeshIn2D(meshList[GEO_INSTRUCTIONS], false, 1, 1, -50.0f, 2.5f);
		RenderMeshIn2D(meshList[GEO_OPTIONS], false, 1, 1, -50.0f, -25.0f);
		RenderMeshIn2D(meshList[GEO_EXIT_H], false, 1, 1, -50.0f, -52.5f);

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
