#include "SceneSplash.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

CSceneSplash::CSceneSplash(void)
{
}

CSceneSplash::CSceneSplash(const int m_window_width, const int m_window_height)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

CSceneSplash::~CSceneSplash(void)
{
}

void CSceneSplash::Init()
{
	CSceneManager::Init();
	glClearColor(0.f, 0.f, 0.f, 0.0f);
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("splash", Color(1, 0.f, 1), 80.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//splash.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Font/anonymous.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	
	rotateAngle = 0;

	bLightEnabled = true;

	m_fTimer = 2.f;
}

void CSceneSplash::Update(double dt)
{
	CSceneManager::Update(dt);

	float fDelta = (float)dt;

	m_fTimer -= fDelta;
}

/********************************************************************************
 Update Camera position
 ********************************************************************************/
void CSceneSplash::UpdateCameraStatus(const unsigned char key, const bool status)
{
}

/********************************************************************************
 Update Weapon status
 ********************************************************************************/
void CSceneSplash::UpdateKeyboardStatus(const unsigned char key)
{
}

/********************************************************************************
 Render this scene
 ********************************************************************************/
void CSceneSplash::Render()
{
	CSceneManager::Render();

	RenderMeshIn2D(meshList[GEO_QUAD], false, 1.f, 1.f, 0.f, 0.f);

#if _DEBUG
	RenderTextOnScreen(meshList[GEO_TEXT], "SceneSplash", Color(1.f, 1.f, 1.f), 20.f, -160.f, 70.f);

	std::ostringstream ss;
	ss.precision(5);
	ss << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1.f, 1.f, 1.f), 20.f, -160.f, -100.f);
#endif
}

/********************************************************************************
 Exit process for this scene
 ********************************************************************************/
void CSceneSplash::Exit()
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
