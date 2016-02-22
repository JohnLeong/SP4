#include "SceneOptions.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

CSceneOptions::CSceneOptions(void)
	: m_window_width(800)
	, m_window_height(600)
{
}

CSceneOptions::CSceneOptions(const int m_window_width, const int m_window_height)
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

	for(int i = 0; i < NUM_GEOMETRY; ++i)
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
	meshList[GEO_WASD] = MeshBuilder::GenerateQuad("wasd", Color(1, 1, 1), 1.f);
	meshList[GEO_WASD]->textureID = LoadTGA("Image//wasd.tga");
	meshList[GEO_MOUSE] = MeshBuilder::GenerateQuad("mouse", Color(1, 1, 1), 1.f);
	meshList[GEO_MOUSE]->textureID = LoadTGA("Image//mouse.tga");
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	bLightEnabled = true;
}

void CSceneOptions::Update(double dt)
{
	CSceneManager::Update(dt);

	float fDelta = (float)dt;

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

#if _DEBUG
	RenderTextOnScreen(meshList[GEO_TEXT], "SceneOptions", Color(1.f, 1.f, 1.f), 20.f, -160.f, 70.f);

	std::ostringstream ss;
	ss.precision(5);
	ss << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1.f, 1.f, 1.f), 20.f, -160.f, -100.f);
#endif
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
