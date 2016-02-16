#include "ScenePlay.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

extern "C"{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#define MatchTimeLimit 15.f

CScenePlay::CScenePlay(void)
	: m_window_width(800)
	, m_window_height(600)
	, m_cAvatar(NULL)
	, m_bExitPlay(false)
{
}

CScenePlay::CScenePlay(const int m_window_width, const int m_window_height)
	: m_cAvatar(NULL)
	, m_bExitPlay(false)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

CScenePlay::~CScenePlay(void)
{
	if (m_cAvatar)
	{
		delete m_cAvatar;
		m_cAvatar = NULL;
	}
}

void CScenePlay::Init()
{
	CSceneManager::Init();

	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference");//, 1000, 1000, 1000);
	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateCrossHair("crosshair");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Font/anonymous.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 0, 0), 18, 36, 1.f);

	// Load the ground mesh and texture
	meshList[GEO_GRASS_DARKGREEN] = MeshBuilder::GenerateQuad("GRASS_DARKGREEN", Color(1, 1, 1), 1.f);
	meshList[GEO_GRASS_DARKGREEN]->textureID = LoadTGA("Image//grass_darkgreen.tga");
	meshList[GEO_GRASS_LIGHTGREEN] = MeshBuilder::GenerateQuad("GEO_GRASS_LIGHTGREEN", Color(1, 1, 1), 1.f);
	meshList[GEO_GRASS_LIGHTGREEN]->textureID = LoadTGA("Image//grass_lightgreen.tga");

	meshList[GEO_TILE_FLOOR_STONE_01] = MeshBuilder::GenerateQuad("GRASS_DARKGREEN", Color(1, 1, 1), 1.f);
	meshList[GEO_TILE_FLOOR_STONE_01]->textureID = LoadTGA("Image//grass_darkgreen.tga");
	meshList[GEO_TILE_WALL_STONE_01] = MeshBuilder::GenerateQuad("GEO_GRASS_LIGHTGREEN", Color(1, 1, 1), 1.f);
	meshList[GEO_TILE_WALL_STONE_01]->textureID = LoadTGA("Image//grass_lightgreen.tga");

	meshList[GEO_PLAYER] = MeshBuilder::GenerateSpriteAnimation2D("GEO_PLAYER", 4, 3);
	meshList[GEO_PLAYER]->textureID = LoadTGA("Image//Entities//explorer.tga");

	// Initialise and load a model into it
	m_cAvatar = new CPlayInfo3PV();
	//m_cAvatar->SetModel(MeshBuilder::GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f));
	Mesh* newmesh = new Mesh("player");
	newmesh = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//legoman2.obj");
	newmesh->textureID = LoadTGA("Image//chair.tga");
	m_cAvatar->SetModel(newmesh);

	Math::InitRNG();

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	
	std::cout << "Variables" << std::endl;

	m_cPlayer = new CPlayer();
	m_cPlayer->Init(0, 0, dynamic_cast<SpriteAnimation*>(meshList[GEO_PLAYER]));
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	bLightEnabled = true;

	InitTilemap();
}

void CScenePlay::InitTilemap()
{
	m_cLevel.InitTilemap("LevelMap//MapDesign.csv", 10, 10, 25.f);
}

void CScenePlay::Update(double dt)
{
	CSceneManager::Update(dt);

	if(Application::IsKeyPressed('I'))
		lights[0].position.z -= (float)(10.f * dt);
	if(Application::IsKeyPressed('K'))
		lights[0].position.z += (float)(10.f * dt);
	if(Application::IsKeyPressed('J'))
		lights[0].position.x -= (float)(10.f * dt);
	if(Application::IsKeyPressed('L'))
		lights[0].position.x += (float)(10.f * dt);
	if(Application::IsKeyPressed('O'))
		lights[0].position.y -= (float)(10.f * dt);
	if(Application::IsKeyPressed('P'))
		lights[0].position.y += (float)(10.f * dt);

	m_cPlayer->Update(dt, m_cLevel.GetTilemap());
	if (IsKeyDownOnce('w'))
	{
		m_cPlayer->MoveUpDown(true, m_cLevel.GetTilemap());
		cout << "works";
	}
	else if (IsKeyDownOnce('s'))
	{
		m_cPlayer->MoveUpDown(false, m_cLevel.GetTilemap());
	}
	else if (IsKeyDownOnce('d'))
	{
		m_cPlayer->MoveLeftRight(true, m_cLevel.GetTilemap());
	}
	else if (IsKeyDownOnce('a'))
	{
		m_cPlayer->MoveLeftRight(false, m_cLevel.GetTilemap());
	}
	camera.UpdatePosition(Vector3(static_cast<float>(m_cPlayer->GetPos_x() * m_cLevel.GetTilemap()->GetTileSize() + m_cPlayer->GetOffSet_x()), static_cast<float>(m_cPlayer->GetPos_y()* m_cLevel.GetTilemap()->GetTileSize() + m_cPlayer->GetOffSet_y()), 0.f));

	//m_cAvatar->Update(dt);
	//m_cAvatar->SetPos_y(-10.f);
	//camera.UpdatePosition( m_cAvatar->GetPosition(), m_cAvatar->GetDirection() );
}

/********************************************************************************
 Update Camera position
 ********************************************************************************/
void CScenePlay::UpdateCameraStatus(const unsigned char key, const bool status)
{
	//camera.UpdateStatus(key, status);
}

/********************************************************************************
 Update Avatar position
 ********************************************************************************/
void CScenePlay::UpdateAvatarStatus(const unsigned char key, const bool status)
{

}

/********************************************************************************
 Update Weapon status
 ********************************************************************************/
void CScenePlay::UpdateWeaponStatus(const unsigned char key)
{
	
}

/********************************************************************************
 Render mobile objects
 ********************************************************************************/
void CScenePlay::RenderGUI()
{
	// Render the crosshair
	RenderMeshIn2D(meshList[GEO_CROSSHAIR], false, 10.0f);
}

void CScenePlay::RenderPlayer()
{
	// Render the player
	modelStack.PushMatrix();
	modelStack.Translate((static_cast<float>(m_cPlayer->GetPos_x() * m_cLevel.GetTilemap()->GetTileSize()) + m_cPlayer->GetOffSet_x()), (static_cast<float>(m_cPlayer->GetPos_y()* m_cLevel.GetTilemap()->GetTileSize()) + m_cPlayer->GetOffSet_y()), 0.f);
	modelStack.Scale(static_cast<float>(m_cLevel.GetTilemap()->GetTileSize()), static_cast<float>(m_cLevel.GetTilemap()->GetTileSize()), 1.f);
	RenderMesh(meshList[GEO_PLAYER], false);
	//m_cPlayer->GetSpriteAnimation()->Render();
	modelStack.PopMatrix();
}

void CScenePlay::RenderTilemap(void)
{
	for (int i = 0; i < m_cLevel.GetTilemap()->GetNumOfTiles_Height(); i++)
	{
		for (int k = 0; k < m_cLevel.GetTilemap()->GetNumOfTiles_Width(); k++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(static_cast<float>(i * m_cLevel.GetTilemap()->GetTileSize()), static_cast<float>(k * m_cLevel.GetTilemap()->GetTileSize()), 0.f);
			modelStack.Scale(static_cast<float>(m_cLevel.GetTilemap()->GetTileSize()), static_cast<float>(m_cLevel.GetTilemap()->GetTileSize()), 1.f);
			RenderMesh(meshList[GEO_GRASS_DARKGREEN], false);
			//RenderMesh(m_cLevel.GetTilemap()->GetTile(i, k), false);
			modelStack.PopMatrix();
		}
	}
}

/********************************************************************************
 Render this scene
 ********************************************************************************/
void CScenePlay::Render()
{
	CSceneManager::Render2D();
	glDisable(GL_DEPTH_TEST);
	RenderTilemap();
	RenderPlayer();
	//RenderGround();
	//RenderSkybox();
	//RenderFixedObjects();
	//RenderMobileObjects();

	//RenderGUI();
#if _DEBUG
	RenderTextOnScreen(meshList[GEO_TEXT], "ScenePlay", Color(1.f, 1.f, 1.f), 20.f, -160.f, 70.f);
#endif
}

/********************************************************************************
 Exit process for this scene
 ********************************************************************************/
void CScenePlay::Exit()
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
