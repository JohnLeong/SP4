#include "ScenePlay.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"
#include "Utility.h"
#include <sstream>
#include "MeshBuilder.h"
#include "LoadTGA.h"

#define MatchTimeLimit 15.f
bool CScenePlay::m_bBacktoMainMenu = false;

CScenePlay::CScenePlay(void)
	: m_window_width(800)
	, m_window_height(600)
	, m_bExitPlay(false)
	, m_iCurrentLevel(3)
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

	//init the boolean for quit
	SetISQuitToMain(false);

	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//vector of quit button pos
	quit_button_vec.Set(161.0f, 77.8f, 0.0f);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference");//, 1000, 1000, 1000);
	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateCrossHair("crosshair");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Font/8BitWonder.tga");
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
	meshList[GEO_TILE_FLOOR_ICE_01] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 2, 7);
	meshList[GEO_TILE_FLOOR_ICE_01]->textureID = LoadTGA("Image//Tiles/TILE_FLOOR_ICE_01.tga");
	meshList[GEO_TILE_WALL_STONE_01] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 2, 2);
	meshList[GEO_TILE_WALL_STONE_01]->textureID = LoadTGA("Image//Tiles/TILE_WALL_STONE_01.tga");
	meshList[GEO_TILE_HOLE_STONE_01] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_HOLE_STONE_01]->textureID = LoadTGA("Image//Tiles/TILE_HOLE_STONE_01.tga");
	meshList[GEO_TILE_HOLE_STONE_FILLED_01] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_HOLE_STONE_FILLED_01]->textureID = LoadTGA("Image//Tiles/TILE_HOLE_STONE_FILLED_01.tga");
	meshList[GEO_TILE_DOOR_RED] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_DOOR_RED]->textureID = LoadTGA("Image//Tiles/TILE_DOOR_RED.tga");
	meshList[GEO_TILE_DOOR_BLUE] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_DOOR_BLUE]->textureID = LoadTGA("Image//Tiles/TILE_DOOR_BLUE.tga");
	meshList[GEO_TILE_DOOR_GREEN] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_DOOR_GREEN]->textureID = LoadTGA("Image//Tiles/TILE_DOOR_GREEN.tga");
	meshList[GEO_TILE_DOOR_YELLOW] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_DOOR_YELLOW]->textureID = LoadTGA("Image//Tiles/TILE_DOOR_YELLOW.tga");
	meshList[GEO_TILE_RUNE] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 2, 5);
	meshList[GEO_TILE_RUNE]->textureID = LoadTGA("Image//Tiles/TILE_RUNE.tga");
	meshList[GEO_TILE_RUNE_USED] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_RUNE_USED]->textureID = LoadTGA("Image//Tiles/TILE_RUNE_USED.tga");
	meshList[GEO_TILE_FORCE_UP] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_FORCE_UP]->textureID = LoadTGA("Image//Tiles/TILE_FORCE_UP.tga");
	meshList[GEO_TILE_FORCE_DOWN] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_FORCE_DOWN]->textureID = LoadTGA("Image//Tiles/TILE_FORCE_DOWN.tga");
	meshList[GEO_TILE_FORCE_LEFT ] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_FORCE_LEFT]->textureID = LoadTGA("Image//Tiles/TILE_FORCE_LEFT.tga");
	meshList[GEO_TILE_FORCE_RIGHT] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_FORCE_RIGHT]->textureID = LoadTGA("Image//Tiles/TILE_FORCE_RIGHT.tga");
	meshList[GEO_TILE_STAIRCASE] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_STAIRCASE]->textureID = LoadTGA("Image//Tiles/TILE_STAIRCASE.tga");

	meshList[GEO_PLAYER] = MeshBuilder::GenerateSpriteAnimation2D("GEO_PLAYER", 4, 3);
	meshList[GEO_PLAYER]->textureID = LoadTGA("Image//Entities//explorer.tga");

	//Scroll background
	meshList[GEO_SCROLL] = MeshBuilder::Generate2DMesh("scroll background", Color(1, 1, 1), 0.0f, 0.0f, 100.0f, 180.0f);
	meshList[GEO_SCROLL]->textureID = LoadTGA("Image/INVENTORY//Scroll.tga");
	
	//Quit button
	meshList[GEO_QUIT_BUTTON] = MeshBuilder::Generate2DMeshCenter("quit button", Color(1, 1, 1), 0.0f, 0.0f, 20.0f, 10.0f);
	meshList[GEO_QUIT_BUTTON]->textureID = LoadTGA("Image/INVENTORY//Quit.tga");

	//back cover
	meshList[GEO_BACKCOVER] = MeshBuilder::Generate2DMesh("back cover", Color(0.9f, 0.9f, 0.9f), 0.0f, 0.0f, 100.0f, 180.0f);

	//coin
	meshList[GEO_COIN] = MeshBuilder::GenerateSpriteAnimation2D("coin", 1, 8);
	meshList[GEO_COIN]->textureID = LoadTGA("Image//Entities//coin.tga");

	//blue keys
	meshList[GEO_KEYS_BLUE] = MeshBuilder::GenerateSpriteAnimation2D("blue key", 1, 11);
	meshList[GEO_KEYS_BLUE]->textureID = LoadTGA("Image//Entities//key_blue.tga");

	//red keys
	meshList[GEO_KEYS_RED] = MeshBuilder::GenerateSpriteAnimation2D("red key", 1, 11);
	meshList[GEO_KEYS_RED]->textureID = LoadTGA("Image//Entities//key_red.tga");

	//green keys
	meshList[GEO_KEYS_GREEN] = MeshBuilder::GenerateSpriteAnimation2D("green key", 1, 11);
	meshList[GEO_KEYS_GREEN]->textureID = LoadTGA("Image//Entities//key_green.tga");

	//yellow keys
	meshList[GEO_KEYS_YELLOW] = MeshBuilder::GenerateSpriteAnimation2D("yellow key", 1, 11);
	meshList[GEO_KEYS_YELLOW]->textureID = LoadTGA("Image//Entities//key_yellow.tga");

	Math::InitRNG();

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	
	std::cout << "Variables" << std::endl;

	bLightEnabled = true;

	coins_sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_COIN]);
	coins_sprite->m_anim = new Animation(0, 7, 0, 1.0f);

	keys_sprite_blue = dynamic_cast<SpriteAnimation*>(meshList[GEO_KEYS_BLUE]);
	keys_sprite_blue->m_anim = new Animation(0, 10, 0, 1.0f);

	keys_sprite_red = dynamic_cast<SpriteAnimation*>(meshList[GEO_KEYS_RED]);
	keys_sprite_red->m_anim = new Animation(0, 10, 0, 1.0f);

	keys_sprite_green = dynamic_cast<SpriteAnimation*>(meshList[GEO_KEYS_GREEN]);
	keys_sprite_green->m_anim = new Animation(0, 10, 0, 1.0f);

	keys_sprite_yellow = dynamic_cast<SpriteAnimation*>(meshList[GEO_KEYS_YELLOW]);
	keys_sprite_yellow->m_anim = new Animation(0, 10, 0, 1.0f);


	m_cPlayer = new CPlayer();
	m_cPlayer->Init(m_cLevel.GetTilemap(), 1, 1, dynamic_cast<SpriteAnimation*>(meshList[GEO_PLAYER]), &m_cLevel.m_cEntityIPosList);
	//Init level after player
	InitLevel();

	/*To be removed*/
	//m_cLevel.GenerateRedKeyEntity(8, 8);
	//m_cLevel.GenerateBlueKeyEntity(9, 8);
	//m_cLevel.GenerateGreenKeyEntity(2, 4);
	//m_cLevel.GenerateYellowKeyEntity(11, 8);
	/*m_cLevel.GenerateCoinEntity(9, 10);
	m_cLevel.GenerateCoinEntity(9, 11);
	m_cLevel.GenerateCoinEntity(9, 12);
	m_cLevel.GenerateCoinEntity(9, 13);
	m_cLevel.GenerateFireEntity(9, 9, CEntity_Fire::STATE_01);*/
	//m_cLevel.GenerateZombieEntity(2, 2, CEnemy::HOLDING_COIN);
	//m_cLevel.GenerateZombieEntity(5, 6, CEnemy::HOLDING_KEY_GREEN);

	/*To be removed*/
}

void CScenePlay::InitLevel()
{
	m_cLevel.SetPlayerPtr(this->m_cPlayer);
	ostringstream convertor;
	string getLevel = "Level";
	convertor << m_iCurrentLevel;
	getLevel.append(convertor.str());
	// Init Level entities
	m_cLevel.InitLua(getLevel);

	//Init level tilemap
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_FLOOR_STONE_01, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_FLOOR_STONE_01]), new Animation(0, 0, 1, 0.5f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_FLOOR_ICE_01, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_FLOOR_ICE_01]), new Animation(0, 13, 0, 0.5f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_WALL_STONE_01, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_WALL_STONE_01]), new Animation(0, 3, 0, 1.f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_HOLE_STONE_01, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_HOLE_STONE_01]), new Animation(0, 0, 1, 0.3f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_HOLE_STONE_FILLED_01, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_HOLE_STONE_FILLED_01]), new Animation(0, 0, 1, 0.3f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_WIND_UP, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_WALL_STONE_01]), new Animation(0, 3, 0, 1.f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_DOOR_RED, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_DOOR_RED]), new Animation(0, 0, 1, 1.f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_DOOR_BLUE, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_DOOR_BLUE]), new Animation(0, 0, 1, 1.f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_DOOR_GREEN, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_DOOR_GREEN]), new Animation(0, 0, 1, 1.f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_DOOR_YELLOW, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_DOOR_YELLOW]), new Animation(0, 0, 1, 1.f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_RUNE, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_RUNE]), new Animation(0, 9, 0, 0.4f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_RUNE_USED, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_RUNE_USED]), new Animation(0, 0, 1, 1.f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_WIND_UP, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_FORCE_UP]), new Animation(0, 0, 1, 1.f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_WIND_DOWN, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_FORCE_DOWN]), new Animation(0, 0, 1, 1.f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_WIND_LEFT, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_FORCE_LEFT]), new Animation(0, 0, 1, 1.f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_WIND_RIGHT, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_FORCE_RIGHT]), new Animation(0, 0, 1, 1.f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_STAIRCASE, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_STAIRCASE]), new Animation(0, 0, 1, 1.f));
	//m_cLevel.LoadTilemap("LevelMap//" + getLevel + ".csv");

	m_cLevel.LoadTilemap(getLevel);


}

void CScenePlay::InitAchievements()
{

}

void CScenePlay::Update(double dt)
{
	CSceneManager::Update(dt);

	if (Application::IsKeyPressed('Q'))
	{
		cout << "boolean: " << GetIsQuitToMain() << endl;
	}

	//Player control
	if (m_cLevel.IsMovementReady() && !m_cPlayer->GetHasReachedEndLevel() && m_cPlayer->IsAlive())
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
	if (IsKeyDownOnce('1'))
		m_cPlayer->UseItem(CPlayer::SLOT_01);
	if (IsKeyDownOnce('2'))
		m_cPlayer->UseItem(CPlayer::SLOT_02);
	if (IsKeyDownOnce('3'))
		m_cPlayer->UseItem(CPlayer::SLOT_03);
	if (IsKeyDownOnce('4'))
		m_cPlayer->UseItem(CPlayer::SLOT_04);


	//Update player
	m_cPlayer->Update(dt, m_cLevel.GetTilemap());

	//coins sprite update
	coins_sprite->Update(dt);

	//keys sprites update
	keys_sprite_blue->Update(dt);
	keys_sprite_red->Update(dt);
	keys_sprite_green->Update(dt);
	keys_sprite_yellow->Update(dt);

	//Update level
	m_cLevel.Update(static_cast<float>(dt), this->m_cPlayer);

	//Update camera position based on player position
	camera.UpdatePosition(Vector3(static_cast<float>((m_cPlayer->GetXIndex() * m_cLevel.GetTilemap()->GetTileSize() + m_cPlayer->GetXOffset())) + 50.f, static_cast<float>(m_cPlayer->GetYIndex() * -m_cLevel.GetTilemap()->GetTileSize() + m_cPlayer->GetYOffset()), 0.f));

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
	if (m_cPlayer->GetHasReachedEndLevel())
		RenderTextOnScreen(meshList[GEO_TEXT], "YOU WIN!", Color(1.f, 1.f, 1.f), 20.f, -100.f, 0.f);
	if (!m_cPlayer->IsAlive())
		RenderTextOnScreen(meshList[GEO_TEXT], "U DED", Color(1.f, 1.f, 1.f), 20.f, -100.f, 0.f);
	// Render the crosshair
	//RenderMeshIn2D(meshList[GEO_CROSSHAIR], false, 10.0f);

	/*if (m_cPlayer->IsAlive())
		RenderTextOnScreen(meshList[GEO_TEXT], "ALIVE", Color(0.f, 0.f, 0.f), 10.f, -160.f, 10.f);
	else
		RenderTextOnScreen(meshList[GEO_TEXT], "DEAD", Color(0.f, 0.f, 0.f), 10.f, -160.f, 10.f);*/
}

/********************************************************************************
Render the player
********************************************************************************/
void CScenePlay::RenderPlayer()
{
	modelStack.PushMatrix();
	modelStack.Translate((static_cast<float>(m_cPlayer->GetXIndex() * m_cLevel.GetTilemap()->GetTileSize()) + m_cPlayer->GetXOffset()), (static_cast<float>(m_cPlayer->GetYIndex() * -m_cLevel.GetTilemap()->GetTileSize()) + m_cPlayer->GetYOffset()), 0.f);
	modelStack.Scale(static_cast<float>(m_cLevel.GetTilemap()->GetTileSize()), static_cast<float>(m_cLevel.GetTilemap()->GetTileSize()), 1.f);
	RenderMesh(meshList[GEO_PLAYER], false);
	//m_cPlayer->GetSpriteAnimation()->Render();
	modelStack.PopMatrix();
}

/********************************************************************************
Render the entities
********************************************************************************/
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
		if ((*entity)->IsHoldingObj())
		{
			modelStack.Translate(0.f, KEY_HUD_OFFSET, 0.f);
			modelStack.Scale(KEY_HUD_SIZE, KEY_HUD_SIZE, 1.f);
			RenderMesh((*entity)->GetHoldingObj()->GetSprite(), false);
		}

		modelStack.PopMatrix();
	}
}

/********************************************************************************
Set is quit to main
********************************************************************************/
void CScenePlay::SetISQuitToMain(bool b)
{
	CScenePlay::m_bBacktoMainMenu = b;
}

/********************************************************************************
Get is quit to main
********************************************************************************/
bool CScenePlay::GetIsQuitToMain()
{
	return m_bBacktoMainMenu;
}

/********************************************************************************
Render the inventory
********************************************************************************/
void CScenePlay::RenderInventory()
{
	//Render the scroll background and back cover
	RenderMeshIn2D(meshList[GEO_BACKCOVER], false, 1, 1, 60, -90);
	RenderMeshIn2D(meshList[GEO_SCROLL], false, 1, 1, 60, -90);

	//Render the number of keys obtained
	RenderMeshIn2D(meshList[GEO_KEYS_BLUE], false, 25, 25, 80, -30);
	RenderMeshIn2D(meshList[GEO_KEYS_RED], false, 25, 25, 120, -30);
	RenderMeshIn2D(meshList[GEO_KEYS_GREEN], false, 25, 25, 80, -15);
	RenderMeshIn2D(meshList[GEO_KEYS_YELLOW], false, 25, 25, 120, -15);

	//Render the number of coins obtained
	RenderMeshIn2D(meshList[GEO_COIN], false, 20, 20, 80, -55);

	//Fetch and Render the amount of keys/coins
	ostringstream s_coins;
	s_coins << m_cPlayer->GetCoins();
	RenderTextOnScreen(meshList[GEO_TEXT], ":" + s_coins.str(), Color(0.0f, 0.0f, 0.0f), 7.0f, 92.0f, -60.0f);

	ostringstream s_keys_red;
	s_keys_red << m_cPlayer->GetKeys_Red();
	RenderTextOnScreen(meshList[GEO_TEXT], ":" + s_keys_red.str(), Color(0.0f, 0.0f, 0.0f), 7.0f, 135.0f, -32.0f);

	ostringstream s_keys_blue;
	s_keys_blue << m_cPlayer->GetKeys_Blue();
	RenderTextOnScreen(meshList[GEO_TEXT], ":" + s_keys_blue.str(), Color(0.0f, 0.0f, 0.0f), 7.0f, 92.0f, -32.0f);

	ostringstream s_keys_green;
	s_keys_green << m_cPlayer->GetKeys_Green();
	RenderTextOnScreen(meshList[GEO_TEXT], ":" + s_keys_green.str(), Color(0.0f, 0.0f, 0.0f), 7.0f, 92.0f, -18.0f);

	ostringstream s_keys_yellow;
	s_keys_yellow << m_cPlayer->GetKeys_Yellow();
	RenderTextOnScreen(meshList[GEO_TEXT], ":" + s_keys_yellow.str(), Color(0.0f, 0.0f, 0.0f), 7.0f, 135.0f, -18.0f);

	ostringstream s_player_moves;
	s_player_moves << m_cLevel.GetNumberOfMoves();
	RenderTextOnScreen(meshList[GEO_TEXT], "Moves:" + s_player_moves.str(), Color(0.0f, 0.0f, 0.0f), 7.0f, 72.0f, 55.0f);

	//on mouse hover quit button
	if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), quit_button_vec.x, quit_button_vec.y, quit_button_vec.x + 11.0f, quit_button_vec.y + 5.42f)
		|| CSceneManager::IsKeyDown('q'))
	{
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON], false, 1.1f, 1.1f, 140.0f, 55);
		
		if (Application::IsMousePressed(GLFW_MOUSE_BUTTON_1) || CSceneManager::IsKeyDown('q'))
		{
			SetISQuitToMain(true);
		}
	}
	else
	{
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON], false, 1.f, 1.f, 140.0f, 55);
		SetISQuitToMain(false);
	}
}

/********************************************************************************
Render the tilemap
********************************************************************************/
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
	RenderInventory();

	RenderGUI();
#if _DEBUG
	//RenderTextOnScreen(meshList[GEO_TEXT], "ScenePlay", Color(1.f, 1.f, 1.f), 20.f, -160.f, 70.f);
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
