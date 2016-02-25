#include "SceneMenu.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

#define buttonXoffset 55.5f
#define buttonYoffset 8.0f

CSceneMenu::CSceneMenu(void):
isKeyBoard(false)
{
}

CSceneMenu::~CSceneMenu(void)
{
}

void CSceneMenu::Init()
{
	CSceneManager::Init();

	//init the choice
	Application::setChoiceVal(4);

	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Font/8BitWonder.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	//create virtual positions for the buttons
	for (int i = 0; i < 4; i++) //left side of button
	{
		//0 = play 1 = instructions 2 = options 3 = exit
		geo_pos[i].Set(61.0f, 67.0f - (16.0f * i), 0.0f);
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

	//Backgrounds
	meshList[GEO_BACKGROUND_BASE] = MeshBuilder::Generate2DMeshCenter("background", Color(1, 1, 1), 0.0f, 0.0f, 1.5f, 0.85f);
	meshList[GEO_BACKGROUND_BASE]->textureID = LoadTGA("Image//Background/gradient_background.tga");
	meshList[GEO_TEMPLE] = MeshBuilder::Generate2DMeshCenter("background", Color(1, 1, 1), 0.0f, 0.0f, 0.8f, 0.8f);
	meshList[GEO_TEMPLE]->textureID = LoadTGA("Image//Background/temple.tga");
	meshList[GEO_GROUND] = MeshBuilder::Generate2DMeshCenter("background", Color(1, 1, 1), 0.0f, -1.63f, 1.5f, 0.2f);
	meshList[GEO_GROUND]->textureID = LoadTGA("Image//Background/ground.tga");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	rotateAngle = 0;

	bLightEnabled = true;
}

void CSceneMenu::Update(double dt)
{
	CSceneManager::Update(dt);
	
	if (CSceneManager::IsKeyDownOnce('w') || CSceneManager::IsKeyDownOnce(VK_UP))
	{

		Application::setChoiceVal(Application::getChoiceVal() + 1);
		//1 = play, 2 = instructions, 3 = options, 4 = exit
		if (Application::getChoiceVal() > 4)
			Application::setChoiceVal(1);

		isKeyBoard = true;
		//cout << "choice: " << getChoiceVal() << endl;
	}
	else if (CSceneManager::IsKeyDownOnce('s') || CSceneManager::IsKeyDownOnce(VK_DOWN))
	{
		Application::setChoiceVal(Application::getChoiceVal() - 1);
		//1 = play, 2 = instructions, 3 = options, 4 = exit
		if (Application::getChoiceVal()  < 1)
			Application::setChoiceVal(4);

		isKeyBoard = true;
		//cout << "choice: " << getChoiceVal() << endl;
	}

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

	glDisable(GL_DEPTH_TEST);

	//Render backgrounds
	RenderMesh(meshList[GEO_BACKGROUND_BASE], false);
	RenderMesh(meshList[GEO_GROUND], false);
	//RenderMesh(meshList[GEO_TEMPLE], false);

	if (Application::IsKeyPressed('1'))
	{
		cout << "current mouse x: " << Application::getMouseWorldX() << endl;
		cout << "current mouse y: " << Application::getMouseWorldY() << endl;
		cout << "geo_pos.x: " << geo_pos[1].x << endl;
		cout << "geo_pos.y: " << geo_pos[1].y << endl;
		cout << "geo_pos.x R: " << geo_pos[1].x + 55.5f << endl;
		cout << "geo_pos.y R: " << geo_pos[1].y + 8.0f << endl;

	}
	
	//Update image on mouse hover
	if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), geo_pos[0].x, geo_pos[0].y, geo_pos[0].x + buttonXoffset, geo_pos[0].y + buttonYoffset)) // play button
	{
		Application::setChoiceVal(4);
		isKeyBoard = false;
	}
	else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), geo_pos[1].x, geo_pos[1].y, geo_pos[1].x + buttonXoffset, geo_pos[1].y + buttonYoffset)) // instructions button
	{
		Application::setChoiceVal(3);
		isKeyBoard = false;
	}
	else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), geo_pos[2].x, geo_pos[2].y, geo_pos[2].x + buttonXoffset, geo_pos[2].y + buttonYoffset)) // options button
	{
		Application::setChoiceVal(2);
		isKeyBoard = false;
	}
	else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), geo_pos[3].x, geo_pos[3].y, geo_pos[3].x + buttonXoffset, geo_pos[3].y + buttonYoffset)) // exit button
	{
		Application::setChoiceVal(1);
		isKeyBoard = false;
	}
	else
	{
		if (!isKeyBoard)
			Application::setChoiceVal(0);
	}

	

	switch (Application::getChoiceVal())
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
	default: //default, no option chosen
		RenderMeshIn2D(meshList[GEO_PLAY], false, 1, 1, -50.0f, 30.0f);
		RenderMeshIn2D(meshList[GEO_INSTRUCTIONS], false, 1, 1, -50.0f, 2.5f);
		RenderMeshIn2D(meshList[GEO_OPTIONS], false, 1, 1, -50.0f, -25.0f);
		RenderMeshIn2D(meshList[GEO_EXIT], false, 1, 1, -50.0f, -52.5f);
		break;
	}
#if _DEBUG
	RenderTextOnScreen(meshList[GEO_TEXT], "SceneMenu", Color(1.f, 1.f, 1.f), 20.f, -160.f, 70.f);
#endif

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
