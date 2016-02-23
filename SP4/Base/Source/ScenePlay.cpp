#include "ScenePlay.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"
#include "Utility.h"
#include <sstream>
#include "MeshBuilder.h"
#include "LoadTGA.h"

#define MatchTimeLimit 15.f

CScenePlay::CScenePlay(void)
	: m_window_width(800)
	, m_window_height(600)
	, m_bExitPlay(false)
	, m_iCurrentLevel(1)
{
}

CScenePlay::CScenePlay(const int m_window_width, const int m_window_height)
	:m_bExitPlay(false)
	, m_iCurrentLevel(1)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

CScenePlay::~CScenePlay(void)
{
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

	meshList[GEO_OVERLAY_RED] = MeshBuilder::GenerateQuad("OVERLAY_RED", Color(1, 1, 1), 1.f);
	meshList[GEO_OVERLAY_RED]->textureID = LoadTGA("Image//Tiles/cross.tga");

	//Load Tile textures
	meshList[GEO_TILE_FLOOR_STONE_01] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_FLOOR_STONE_01]->textureID = LoadTGA("Image//Tiles/TILE_FLOOR_STONE_01.tga");
	meshList[GEO_TILE_FLOOR_ICE_01] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 2, 2);
	meshList[GEO_TILE_FLOOR_ICE_01]->textureID = LoadTGA("Image//Tiles/TILE_FLOOR_ICE_01.tga");
	meshList[GEO_TILE_WALL_STONE_01] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 2, 2);
	meshList[GEO_TILE_WALL_STONE_01]->textureID = LoadTGA("Image//Tiles/TILE_WALL_STONE_01.tga");
	meshList[GEO_TILE_HOLE_STONE_01] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_HOLE_STONE_01]->textureID = LoadTGA("Image//Tiles/TILE_HOLE_STONE_01.tga");
	meshList[GEO_TILE_DOOR_RED] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_DOOR_RED]->textureID = LoadTGA("Image//Tiles/TILE_DOOR_RED.tga");

	meshList[GEO_PLAYER] = MeshBuilder::GenerateSpriteAnimation2D("GEO_PLAYER", 4, 3);
	meshList[GEO_PLAYER]->textureID = LoadTGA("Image//Entities//explorer.tga");

	Math::InitRNG();

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	
	std::cout << "Variables" << std::endl;

	bLightEnabled = true;



	m_cPlayer = new CPlayer();
	m_cPlayer->Init(m_cLevel.GetTilemap(), 1, 1, dynamic_cast<SpriteAnimation*>(meshList[GEO_PLAYER]), &m_cLevel.m_cEntityIPosList);
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//Init level after player
	InitLevel();

	/*To be removed*/
	m_cLevel.GenerateZombieEntity(3, 3, CEnemy::HOLDING_KEY_RED);
	//m_cLevel.GenerateSuperRetardZombieEntity(5, 3, CEnemy::HOLDING_KEY_RED);
	Mesh* temp_mesh;
	//temp_mesh = MeshBuilder::GenerateSpriteAnimation2D("ZAMBIE", 4, 3);
	//temp_mesh->textureID = LoadTGA("Image//Entities//explorer2.tga");
	//CEnemyZombie* enemy = new CEnemyZombie(3, 3, m_cLevel.GetTilemap(), dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayer, &m_cLevel.m_cEntityIPosList);
	//m_cLevel.m_cEntityIPosList.push_back(enemy);
	temp_mesh = MeshBuilder::GenerateSpriteAnimation2D("BOX", 1, 1);
	temp_mesh->textureID = LoadTGA("Image//Entities//box.tga");
	CEntity_Block_Movable* entity = new CEntity_Block_Movable(6, 6, m_cLevel.GetTilemap(), dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayer, &m_cLevel.m_cEntityIPosList);
	m_cLevel.m_cEntityIPosList.push_back(entity);
	entity = new CEntity_Block_Movable(6, 8, m_cLevel.GetTilemap(), dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayer, &m_cLevel.m_cEntityIPosList);
	m_cLevel.m_cEntityIPosList.push_back(entity);
	entity = new CEntity_Block_Movable(3, 1, m_cLevel.GetTilemap(), dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayer, &m_cLevel.m_cEntityIPosList);
	m_cLevel.m_cEntityIPosList.push_back(entity);
	/*temp_mesh = MeshBuilder::GenerateSpriteAnimation2D("KEEE", 1, 11);
	temp_mesh->textureID = LoadTGA("Image//Entities//key.tga");
	CEntity_Key_Red* key = new CEntity_Key_Red(8, 8, m_cLevel.GetTilemap(), dynamic_cast<SpriteAnimation*>(temp_mesh), new Animation(0, 10, 0, 0.3f), this->m_cPlayer, &m_cLevel.m_cEntityIPosList);
	m_cLevel.m_cEntityIPosList.push_back(key);*/
	m_cLevel.GenerateRedKeyEntity(8, 8);
	m_cLevel.GenerateBlueKeyEntity(9, 8);
	m_cLevel.GenerateGreenKeyEntity(10, 8);
	m_cLevel.GenerateYellowKeyEntity(11, 8);
	temp_mesh = MeshBuilder::GenerateSpriteAnimation2D("FIYAH", 2, 5);
	temp_mesh->textureID = LoadTGA("Image//Entities//fire.tga");
	CEntity_Fire* fire = new CEntity_Fire(9, 9, CEntity_Fire::STATE_01, m_cLevel.GetTilemap(), dynamic_cast<SpriteAnimation*>(temp_mesh), this->m_cPlayer, &m_cLevel.m_cEntityIPosList);
	m_cLevel.m_cEntityIPosList.push_back(fire);
	m_cLevel.GenerateCoinEntity(9, 10);
	m_cLevel.GenerateCoinEntity(9, 11);
	m_cLevel.GenerateCoinEntity(9, 12);
	m_cLevel.GenerateCoinEntity(9, 13);

	CProperties * test = new CProperties("Deaths", 0, CProperties::ACTIVE_GREATER, 1, false);
	m_cPropertyList.push_back(test);
	string testAchievement = "You died";
	CAchievements* testTest = new CAchievements(testAchievement, m_cPropertyList);
	/*To be removed*/

	

	InitAchievements();
}

void CScenePlay::InitLevel()
{
	m_cLevel.SetPlayerPtr(this->m_cPlayer);
	// Init Level entities
	ostringstream convertor;
	string getLevel = "Level";
	convertor << m_iCurrentLevel;
	getLevel.append(convertor.str());

	m_cLevel.InitLua(getLevel);

	//Init level tilemap
	m_cLevel.InitTilemap(14, 18, TILE_SIZE);
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_FLOOR_STONE_01, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_FLOOR_STONE_01]), new Animation(0, 0, 1, 0.5f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_FLOOR_ICE_01, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_FLOOR_ICE_01]), new Animation(0, 3, 0, 0.5f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_WALL_STONE_01, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_WALL_STONE_01]), new Animation(0, 3, 0, 1.f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_HOLE_STONE_01, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_HOLE_STONE_01]), new Animation(0, 0, 1, 0.3f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_WIND_UP, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_WALL_STONE_01]), new Animation(0, 3, 0, 1.f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_DOOR_RED, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_DOOR_RED]), new Animation(0, 0, 1, 1.f));
	//m_cLevel.LoadTilemap("LevelMap//" + getLevel + ".csv");
	m_cLevel.LoadTilemap("LevelMap//MapDesign.csv");
}

void CScenePlay::InitAchievements()
{

}

void CScenePlay::Update(double dt)
{
	CSceneManager::Update(dt);

	if (m_cLevel.IsMovementReady())
	{
		if (IsKeyDownOnce('w'))
			m_cPlayer->SetNextDirection(CPlayer::PD_UP);
		else if (IsKeyDownOnce('s'))
			m_cPlayer->SetNextDirection(CPlayer::PD_DOWN);
		else if (IsKeyDownOnce('d'))
			m_cPlayer->SetNextDirection(CPlayer::PD_RIGHT);
		else if (IsKeyDownOnce('a'))
			m_cPlayer->SetNextDirection(CPlayer::PD_LEFT);
	}

	//Update player
	m_cPlayer->Update(dt, m_cLevel.GetTilemap());

	if (IsKeyDownOnce('g'))
	{
		m_cLevel.UpdateMovement(static_cast<float>(dt), this->m_cPlayer);
	}

	//Update level
	m_cLevel.Update(static_cast<float>(dt), this->m_cPlayer);

	//Update camera position based on player position
	camera.UpdatePosition(Vector3(static_cast<float>(m_cPlayer->GetXIndex() * m_cLevel.GetTilemap()->GetTileSize() + m_cPlayer->GetXOffset()), static_cast<float>(m_cPlayer->GetYIndex() * -m_cLevel.GetTilemap()->GetTileSize() + m_cPlayer->GetYOffset()), 0.f));


	if (m_cPlayer->GetHasReachedEndLevel() == true)
	{
		//End Level
	}
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
	//RenderMeshIn2D(meshList[GEO_CROSSHAIR], false, 10.0f);

	if (m_cPlayer->IsAlive())
		RenderTextOnScreen(meshList[GEO_TEXT], "ALIVE", Color(0.f, 0.f, 0.f), 20.f, -160.f, 10.f);
	else
		RenderTextOnScreen(meshList[GEO_TEXT], "DEAD", Color(0.f, 0.f, 0.f), 20.f, -160.f, 10.f);
}

void CScenePlay::RenderPlayer()
{
	// Render the player
	modelStack.PushMatrix();
	modelStack.Translate((static_cast<float>(m_cPlayer->GetXIndex() * m_cLevel.GetTilemap()->GetTileSize()) + m_cPlayer->GetXOffset()), (static_cast<float>(m_cPlayer->GetYIndex() * -m_cLevel.GetTilemap()->GetTileSize()) + m_cPlayer->GetYOffset()), 0.f);
	modelStack.Scale(static_cast<float>(m_cLevel.GetTilemap()->GetTileSize()), static_cast<float>(m_cLevel.GetTilemap()->GetTileSize()), 1.f);
	RenderMesh(meshList[GEO_PLAYER], false);
	//m_cPlayer->GetSpriteAnimation()->Render();
	modelStack.PopMatrix();
}

void CScenePlay::RenderEntities()
{
	for (std::vector<CEntityIPos*>::iterator entity = m_cLevel.m_cEntityIPosList.begin(); entity != m_cLevel.m_cEntityIPosList.end(); entity++)
	{
		if (!(*entity)->IsAlive())
			continue;
		modelStack.PushMatrix();
		modelStack.Translate((static_cast<float>((*entity)->GetXIndex() * m_cLevel.GetTilemap()->GetTileSize())) + (*entity)->GetXOffset()
			, (static_cast<float>((*entity)->GetYIndex()* -m_cLevel.GetTilemap()->GetTileSize())) + (*entity)->GetYOffset()
			, 0.f);
		modelStack.PushMatrix();
		modelStack.Scale(TILE_SIZE, TILE_SIZE, 1.f);
		if ((*entity)->GetSprite() == NULL)
			RenderMesh(meshList[GEO_GRASS_DARKGREEN], false);
		else
			RenderMesh((*entity)->GetSprite(), false);
		modelStack.PopMatrix();
		if ((*entity)->IsHoldingKey())
		{
			modelStack.Translate(0.f, KEY_HUD_OFFSET, 0.f);
			modelStack.Scale(KEY_HUD_SIZE, KEY_HUD_SIZE, 1.f);
			RenderMesh((*entity)->m_cKeyPtr->GetSprite(), false);
		}

		modelStack.PopMatrix();
	}
	int test;
}

void CScenePlay::RenderTilemap(void)
{
	for (int i = 0; i < m_cLevel.GetTilemap()->GetNumOfTiles_Width(); ++i)
	{
		for (int j = 0; j < m_cLevel.GetTilemap()->GetNumOfTiles_Height(); ++j)
		{
			modelStack.PushMatrix();
			modelStack.Translate(static_cast<float>(i * m_cLevel.GetTilemap()->GetTileSize()), static_cast<float>(-j * m_cLevel.GetTilemap()->GetTileSize()), 0.f);
			modelStack.Scale(static_cast<float>(m_cLevel.GetTilemap()->GetTileSize()), static_cast<float>(m_cLevel.GetTilemap()->GetTileSize()), 1.f);

			if (m_cLevel.m_cTilemap->GetTileSprite(m_cLevel.GetTilemap()->GetTile(i, j).GetTileId()) == NULL)
				RenderMesh(meshList[GEO_GRASS_DARKGREEN], false);
			else
				RenderMesh(m_cLevel.m_cTilemap->GetTileSprite(m_cLevel.GetTilemap()->GetTile(i, j).GetTileId()), false);

			if (m_cLevel.GetTilemap()->GetTile(i, j).IsTinted())
				RenderMesh(meshList[GEO_OVERLAY_RED], false);
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

	RenderTilemap();

	RenderEntities();
	RenderPlayer();

	RenderGUI();
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
