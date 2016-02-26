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
	glClearColor(1.f, 1.f, 1.f, 0.0f);
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("splash", Color(1, 0.f, 1), 80.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//splash.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Font/8BitWonder.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);
	meshList[GEO_GRADIENT] = MeshBuilder::GenerateQuad("splash", Color(1, 0.f, 1), 80.f);
	meshList[GEO_GRADIENT]->textureID = LoadTGA("Image//Background/gradient_circle.tga");
	meshList[GEO_BEAM] = MeshBuilder::GenerateQuad("splash", Color(1, 0.f, 1), 40.f);
	meshList[GEO_BEAM]->textureID = LoadTGA("Image//Background/beam.tga");
	meshList[GEO_CHAR_1] = MeshBuilder::GenerateQuad("splash", Color(1, 0.f, 1), 40.f);
	meshList[GEO_CHAR_1]->textureID = LoadTGA("Image//Background/logo_v.tga");
	meshList[GEO_CHAR_2] = MeshBuilder::GenerateQuad("splash", Color(1, 0.f, 1), 40.f);
	meshList[GEO_CHAR_2]->textureID = LoadTGA("Image//Background/logo_j.tga");
	meshList[GEO_CHAR_3] = MeshBuilder::GenerateQuad("splash", Color(1, 0.f, 1), 40.f);
	meshList[GEO_CHAR_3]->textureID = LoadTGA("Image//Background/logo_k.tga");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	
	rotateAngle = 0;

	bLightEnabled = true;
	srand(static_cast<unsigned>(time(NULL)));
	m_fTimer = 1.f;
	camera.Init(Vector3(0, 0, 0), Vector3(0, 0, -1.f), Vector3(0, 1.f, 0));
	m_fScreenCol = 1.f;
	m_fLogo1PosY = 120.f;
	m_fLogo2PosY = 120.f;
	m_fLogo3PosY = 120.f;
	m_fLogoTranslateY = 1.f;
	m_fBeamScaleX = 0.00001f;
	cAnimState = ANIM_0;
	m_fShakeRadius = 20.f;
	m_fShakeAngle = rand() % 360;
	m_fShakeOffsetX = 0.f;
	m_fShakeOffsetY = 0.f;
	m_bDoShake = false;
}

void CSceneSplash::Update(double dt)
{
	CSceneManager::Update(dt);

	float fDelta = (float)dt;

	if (m_bDoShake)
	{
		m_fShakeRadius *= 0.9f;
		m_fShakeAngle = rand() % 360;
		m_fShakeOffsetX = sin(m_fShakeAngle) * m_fShakeRadius;
		m_fShakeOffsetY = cos(m_fShakeAngle) * m_fShakeRadius;
		if (m_fShakeRadius < 2.f)
		{
			m_fShakeRadius = 20.f;
			m_fShakeOffsetX = 0.f;
			m_fShakeOffsetY = 0.f;
			m_bDoShake = false;
		}
	}

	//std::cout << "X" << m_fShakeOffsetX << "Y" << m_fShakeOffsetY << std::endl;
	switch (cAnimState)
	{
	case ANIM_0:
		//Update screen colour
		glClearColor(m_fScreenCol, m_fScreenCol, m_fScreenCol, 1.0f);

		if (m_fScreenCol <= 0.f)
		{
			m_fScreenCol = 0.f;
			cAnimState = ANIM_1;
		}
		else
			m_fScreenCol -= fDelta;
		break;
	case CSceneSplash::ANIM_1:
		m_fLogoTranslateY += (m_fLogoTranslateY * fDelta) * 10;
		m_fLogo1PosY -= m_fLogoTranslateY;
		if (m_fLogo1PosY < 0.f)
		{
			m_fLogoTranslateY = 1.f;
			cAnimState = ANIM_2;
			m_fLogo1PosY = 0.f;
			m_bDoShake = true;
		}
		break;
	case CSceneSplash::ANIM_2:
		if (m_bDoShake)
			break;
		m_fLogoTranslateY += (m_fLogoTranslateY * fDelta) * 10;
		m_fLogo2PosY -= m_fLogoTranslateY;
		if (m_fLogo2PosY < 0.f)
		{
			m_fLogoTranslateY = 1.f;
			cAnimState = ANIM_3;
			m_fLogo2PosY = 0.f;
			m_bDoShake = true;
		}
		break;
	case CSceneSplash::ANIM_3:
		if (m_bDoShake)
			break;
		m_fLogoTranslateY += (m_fLogoTranslateY * fDelta) * 10;
		m_fLogo3PosY -= m_fLogoTranslateY;
		if (m_fLogo3PosY < 0.f)
		{
			m_fLogoTranslateY = 1.f;
			cAnimState = ANIM_4;
			m_fLogo3PosY = 0.f;
			m_bDoShake = true;
		}
		break;
	case CSceneSplash::ANIM_4:
		if (m_bDoShake)
			break;
		m_fBeamScaleX += fDelta * 20;
		if (m_fBeamScaleX >= 2.5f)
		{
			m_fBeamScaleX = 2.5f;
			cAnimState = ANIM_5;
		}
		break;
	case CSceneSplash::ANIM_5:
		m_fTimer -= fDelta;
		break;
	default:
		break;
	}
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
	//glUseProgram(0);

	//glUseProgram(m_programID);

	RenderMeshIn2D(meshList[GEO_BEAM], false, m_fBeamScaleX, 1.f, 0.f, 25.f);
	RenderMeshIn2D(meshList[GEO_BEAM], false, m_fBeamScaleX, 1.f, 0.f, -25.f);
	if (m_bDoShake)
	{
		RenderMeshIn2D(meshList[GEO_CHAR_1], false, 1.f, 1.f, -25.f + m_fShakeOffsetX * 0.1, m_fLogo1PosY + m_fShakeOffsetY * 0.11);
		RenderMeshIn2D(meshList[GEO_CHAR_2], false, 1.f, 1.f, -5.f - m_fShakeOffsetX * 0.09, m_fLogo2PosY - m_fShakeOffsetY * 0.1);
		RenderMeshIn2D(meshList[GEO_CHAR_3], false, 1.f, 1.f, 25.f + m_fShakeOffsetX * 0.11, m_fLogo3PosY - m_fShakeOffsetY * 0.09);
	}
	else
	{
		RenderMeshIn2D(meshList[GEO_CHAR_1], false, 1.f, 1.f, -25.f, m_fLogo1PosY );
		RenderMeshIn2D(meshList[GEO_CHAR_2], false, 1.f, 1.f, -5.f, m_fLogo2PosY);
		RenderMeshIn2D(meshList[GEO_CHAR_3], false, 1.f, 1.f, 25.f, m_fLogo3PosY);
	}

	//RenderMeshIn2D(meshList[GEO_GRADIENT], false, m_fGradientScale, m_fGradientScale, 0.f, 0.f);


#if _DEBUG
	//RenderTextOnScreen(meshList[GEO_TEXT], "SceneSplash", Color(1.f, 1.f, 1.f), 20.f, -160.f, 70.f);

	//std::ostringstream ss;
	//ss.precision(5);
	//ss << fps;
	//RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1.f, 1.f, 1.f), 20.f, -160.f, -100.f);
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
