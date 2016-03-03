#include "SceneInstruction.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

#define buttonXoffset 38.0f
#define buttonYoffset 11.5f

CSceneInstruction::CSceneInstruction(void)
: m_window_width(800)
, m_window_height(600)
, isSelectSoundPlaying(false)
, m_bAnimOffsetDir(true)
, m_bChangeState(false)
{
}

CSceneInstruction::CSceneInstruction(const int m_window_width, const int m_window_height)
: isSelectSoundPlaying(false)
, m_bAnimOffsetDir(true)
, m_bChangeState(false)
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

	//init the choice
	Application::setChoiceVal(0);

	//create virtual positions for the buttons (back)
	geo_pos.Set(70.0f,15.0f, 0.0f);

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
	meshList[GEO_BACKGROUND_BASE] = MeshBuilder::Generate2DMeshCenter("background", Color(1, 1, 1), 0.0f, 0.0f, 1.5f, 0.85f);
	meshList[GEO_BACKGROUND_BASE]->textureID = LoadTGA("Image//Background/gradient_background.tga");
	//back button
	meshList[GEO_BACK] = MeshBuilder::Generate2DMeshCenter("backs button", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image/MENU/back_button.tga");
	//back button highlighted
	meshList[GEO_BACK_H] = MeshBuilder::Generate2DMeshCenter("back button highlighted", Color(1, 1, 1), 0.0f, 0.0f, 70.0f, 20.0f);
	meshList[GEO_BACK_H]->textureID = LoadTGA("Image/MENU//h_back_button.tga");
	meshList[GEO_MONKEY] = MeshBuilder::Generate2DMeshCenter("back button highlighted", Color(1, 1, 1), 0.0f, -0.05f, 0.8f, 0.8f);
	meshList[GEO_MONKEY]->textureID = LoadTGA("Image/Background//golden_monkey.tga");
	meshList[GEO_HEADER] = MeshBuilder::Generate2DMeshCenter("back button", Color(1, 1, 1), -0.55f, 3.5f, 0.7f, 0.1f);
	meshList[GEO_HEADER]->textureID = LoadTGA("Image/GUI//instructions_text.tga");
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	bLightEnabled = true;

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	m_fBotAnimOffset = -210.f;
	m_fLeftAnimOffset = -210.f;
}

void CSceneInstruction::Update(double dt)
{
	CSceneManager::Update(dt);
	UpdateAnimations(dt);
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
		if (Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
			m_bAnimOffsetDir = false;
	}
	else if (!Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), geo_pos.x, geo_pos.y, static_cast<float>(geo_pos.x + buttonXoffset), geo_pos.y + buttonYoffset)
		&& !m_bisKeyBoard)
	{
		Application::setChoiceVal(0);

		isSelectSoundPlaying = false;
	}

	float fDelta = (float)dt;

}

void CSceneInstruction::UpdateAnimations(double dt)
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

	RenderMesh(meshList[GEO_BACKGROUND_BASE], false);


	//Render header
	modelStack.PushMatrix();
	modelStack.Translate(m_fLeftAnimOffset * 0.005, 0.f, 0.f);
	RenderMesh(meshList[GEO_HEADER], false);
	RenderMesh(meshList[GEO_MONKEY], false);
	modelStack.PopMatrix();

	switch (Application::getChoiceVal())
	{
	case 1:
		RenderMeshIn2D(meshList[GEO_BACK_H], false, 1.15f, 1.15f, 0.0f, -52.5f + m_fBotAnimOffset);
		break;

	default:
		RenderMeshIn2D(meshList[GEO_BACK], false, 1, 1, 0.0f, -52.5f + m_fBotAnimOffset);
		break;
	}

	RenderTextOnScreen(meshList[GEO_TEXT], "Take control of your character as you journey into a mysterious temple, in search of the fabled golden/nmonkey!", Color(1.f, 1.f, 1.f), 20.f, -150.f, 35.f + m_fBotAnimOffset, 15.f);
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
