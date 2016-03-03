#include "ScenePlay.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"
#include "Utility.h"
#include <sstream>
#include "MeshBuilder.h"
#include "LoadTGA.h"
#include "Achievements\Properties.h"

#define buttonXoffset 22.0f
#define buttonYoffset 8.5f

bool CScenePlay::m_bBacktoMainMenu = false;
CScenePlay::CScenePlay(void)
: m_window_width(800)
, m_window_height(600)
, m_bExitPlay(false)
, m_iCurrentLevel(3)
, m_bShowWin(false)
, m_bShowLose(false)
, m_bQuitselectsound(false)
, m_bMouseisPressed(false)
, m_bPlayWinSound(false)
, m_bPlayLoseSound(false)
, m_bToFinishScreen(false)
{
}

CScenePlay::CScenePlay(const int m_window_width, const int m_window_height)
:m_bExitPlay(false)
, m_iCurrentLevel(5)
, m_bShowWin(false)
, m_bShowLose(false)
, m_bQuitselectsound(false)
, m_bMouseisPressed(false)
, m_bPlayWinSound(false)
, m_bPlayLoseSound(false)
, m_bToFinishScreen(false)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

CScenePlay::CScenePlay(const int m_window_width, const int m_window_height, int iLevel, bool bPanic)
:m_bExitPlay(false)
{
	this->m_iCurrentLevel = iLevel;
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

CScenePlay::~CScenePlay(void)
{
	//std::cout << "DESTROY";
	//m_cLevel.Exit();
	//for (int i = 0; i < NUM_GEOMETRY; ++i)
	//{
	//	if (meshList[i])
	//		delete meshList[i];
	//}
	//if (m_cPlayer)
	//	delete m_cPlayer;
}

void CScenePlay::Init()
{
	CSceneManager::Init();

	//init the boolean for quit
	SetISQuitToMain(false);

	Application::Sound.Stop();

	Application::Sound.playSound("media/Level1_BGM.mp3");
	Application::Sound.setVolume(30);


	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));
	srand(static_cast<unsigned>(time(NULL)));

	//vector of quit button pos
	quit_button_vec.Set(161.0f, 77.8f, 0.0f);
	//vector of restart button pos
	restart_button_vec.Set(161.0f, 69.0f, 0.0f);
	//vector of next level button pos (winpage)
	nextLevel_button_vec_winScreen.Set(50.0f, 17.5f, 0.0f);
	//vector of restart button pos (winpage)
	restart_button_vec_winScreen.Set(77.0f, 17.5f, 0.0f);
	//vector of exit button pos (winpage)
	exit_button_vec_winScreen.Set(105.0f, 17.5f, 0.0f);
	//vector of restart button pos (losepage)
	restart_button_vec_loseScreen.Set(63.0f, 17.5f, 0.0f);
	//vector of exit button pos (losepage)
	quit_button_vec_loseScreen.Set(91.0f, 17.5f, 0.0f);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference");//, 1000, 1000, 1000);
	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateCrossHair("crosshair");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Font/8BitWonder.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 0, 0), 18, 36, 1.f);

	// Load the ground mesh and texture
	meshList[GEO_GRASS_DARKGREEN] = MeshBuilder::GenerateQuad("GRASS_DARKGREEN", Color(1, 1, 1), 1.f);
	meshList[GEO_GRASS_DARKGREEN]->textureID = LoadTGA("Image//grass_darkgreen.tga");
	meshList[GEO_GRASS_LIGHTGREEN] = MeshBuilder::GenerateQuad("GEO_GRASS_Lcx	IGHTGREEN", Color(1, 1, 1), 1.f);
	meshList[GEO_GRASS_LIGHTGREEN]->textureID = LoadTGA("Image//grass_lightgreen.tga");

	meshList[GEO_BACKGROUND] = MeshBuilder::Generate2DMeshCenter("background", Color(1, 1, 1), 0.0f, 0.0f, 320.5f, 200.f);
	meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//Background/wall_drawing.tga");

	meshList[GEO_OVERLAY_RED] = MeshBuilder::GenerateQuad("OVERLAY_RED", Color(1, 1, 1), 1.f);
	meshList[GEO_OVERLAY_RED]->textureID = LoadTGA("Image//Tiles/cross.tga");
	meshList[GEO_QUESTION_MARK] = MeshBuilder::GenerateQuad("MARK", Color(1, 1, 1), 1.f);
	meshList[GEO_QUESTION_MARK]->textureID = LoadTGA("Image//Entities/question_mark.tga");

	meshList[GEO_TEXTBOX] = MeshBuilder::GenerateQuad("box", Color(1, 1, 1), 1.f);
	meshList[GEO_TEXTBOX]->textureID = LoadTGA("Image//GUI/box_blue.tga");
	meshList[GEO_TRANSPARENT_LAYER] = MeshBuilder::GenerateQuad("box", Color(1, 1, 1), 1.f);
	meshList[GEO_TRANSPARENT_LAYER]->textureID = LoadTGA("Image//GUI/square_transparent.tga");

	meshList[GEO_STAR] = MeshBuilder::GenerateQuad("star", Color(1, 1, 1), 40.f);
	meshList[GEO_STAR]->textureID = LoadTGA("Image//GUI/star.tga");
	meshList[GEO_STAROUTLINE] = MeshBuilder::GenerateQuad("box", Color(1, 1, 1), 40.f);
	meshList[GEO_STAROUTLINE]->textureID = LoadTGA("Image//GUI/star_outline.tga");

	//Load Tile textures
	meshList[GEO_TILE_FLOOR_STONE_01] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_FLOOR_STONE_01]->textureID = LoadTGA("Image//Tiles/TILE_FLOOR_STONE_01.tga");
	meshList[GEO_TILE_FLOOR_ICE_01] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 2, 7);
	meshList[GEO_TILE_FLOOR_ICE_01]->textureID = LoadTGA("Image//Tiles/TILE_FLOOR_ICE_01.tga");
	meshList[GEO_TILE_WALL_STONE_01] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
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
	meshList[GEO_TILE_FORCE_LEFT] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_FORCE_LEFT]->textureID = LoadTGA("Image//Tiles/TILE_FORCE_LEFT.tga");
	meshList[GEO_TILE_FORCE_RIGHT] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_FORCE_RIGHT]->textureID = LoadTGA("Image//Tiles/TILE_FORCE_RIGHT.tga");
	meshList[GEO_TILE_STAIRCASE] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_STAIRCASE]->textureID = LoadTGA("Image//Tiles/TILE_STAIRCASE.tga");
	meshList[GEO_TILE_MONKEY] = MeshBuilder::GenerateSpriteAnimation2D("Geo", 1, 1);
	meshList[GEO_TILE_MONKEY]->textureID = LoadTGA("Image//Tiles/TILE_MONKEY.tga");
	meshList[GEO_PLAYER] = MeshBuilder::GenerateSpriteAnimation2D("GEO_PLAYER", 4, 3);
	meshList[GEO_PLAYER]->textureID = LoadTGA("Image//Entities//explorer.tga");

	//Scroll background
	meshList[GEO_SCROLL] = MeshBuilder::Generate2DMesh("scroll background", Color(1, 1, 1), 0.0f, 0.0f, 100.0f, 180.0f);
	meshList[GEO_SCROLL]->textureID = LoadTGA("Image/INVENTORY//Scroll.tga");

	//Quit button
	meshList[GEO_QUIT_BUTTON] = MeshBuilder::Generate2DMeshCenter("quit button", Color(1, 1, 1), 0.0f, 0.0f, 20.0f, 10.0f);
	meshList[GEO_QUIT_BUTTON]->textureID = LoadTGA("Image/INVENTORY//Quit.tga");
	meshList[GEO_QUIT_BUTTON_HIGHLIGHTED] = MeshBuilder::Generate2DMeshCenter("quit button", Color(1, 1, 1), 0.0f, 0.0f, 20.0f, 10.0f);
	meshList[GEO_QUIT_BUTTON_HIGHLIGHTED]->textureID = LoadTGA("Image/INVENTORY//h_Quit.tga");
	//Restart button
	meshList[GEO_RESTART_BUTTON] = MeshBuilder::Generate2DMeshCenter("restart button", Color(1, 1, 1), 0.0f, 0.0f, 20.0f, 10.0f);
	meshList[GEO_RESTART_BUTTON]->textureID = LoadTGA("Image/GUI//button_restart.tga");
	meshList[GEO_RESTART_BUTTON_HIGHLIGHTED] = MeshBuilder::Generate2DMeshCenter("restart button", Color(1, 1, 1), 0.0f, 0.0f, 20.0f, 10.0f);
	meshList[GEO_RESTART_BUTTON_HIGHLIGHTED]->textureID = LoadTGA("Image/GUI//h_button_restart.tga");
	meshList[GEO_NEXT_BUTTON] = MeshBuilder::Generate2DMeshCenter("next button", Color(1, 1, 1), 0.0f, 0.0f, 20.0f, 10.0f);
	meshList[GEO_NEXT_BUTTON]->textureID = LoadTGA("Image/GUI//button_next.tga");
	meshList[GEO_NEXT_BUTTON_HIGHLIGHTED] = MeshBuilder::Generate2DMeshCenter("next button", Color(1, 1, 1), 0.0f, 0.0f, 20.0f, 10.0f);
	meshList[GEO_NEXT_BUTTON_HIGHLIGHTED]->textureID = LoadTGA("Image/GUI//h_button_next.tga");

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
	coins_sprite->m_anim = new Animation(0, 7, 0, 0.7f);

	keys_sprite_blue = dynamic_cast<SpriteAnimation*>(meshList[GEO_KEYS_BLUE]);
	keys_sprite_blue->m_anim = new Animation(0, 10, 0, 0.7f);

	keys_sprite_red = dynamic_cast<SpriteAnimation*>(meshList[GEO_KEYS_RED]);
	keys_sprite_red->m_anim = new Animation(0, 10, 0, 0.7f);

	keys_sprite_green = dynamic_cast<SpriteAnimation*>(meshList[GEO_KEYS_GREEN]);
	keys_sprite_green->m_anim = new Animation(0, 10, 0, 0.7f);

	keys_sprite_yellow = dynamic_cast<SpriteAnimation*>(meshList[GEO_KEYS_YELLOW]);
	keys_sprite_yellow->m_anim = new Animation(0, 10, 0, 0.7f);

	m_cPlayer = new CPlayer();
	m_cPlayer->Init(m_cLevel.GetTilemap(), 1, 1, dynamic_cast<SpriteAnimation*>(meshList[GEO_PLAYER]), &m_cLevel.m_cEntityIPosList);
	//Init level after player
	m_iCurrentLevel = Application::CurrentLevel;
	InitLevel();

	m_bDied = false;
	m_bTimerCheck = false;
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
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_WALL_STONE_01, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_WALL_STONE_01]), new Animation(0, 0, 1, 1.f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_HOLE_STONE_01, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_HOLE_STONE_01]), new Animation(0, 0, 1, 0.3f));
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_HOLE_STONE_FILLED_01, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_HOLE_STONE_FILLED_01]), new Animation(0, 0, 1, 0.3f));
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
	m_cLevel.m_cTilemap->SetMeshArray(CTiledata::TILE_MONKEY, dynamic_cast<SpriteAnimation*>(meshList[GEO_TILE_MONKEY]), new Animation(0, 0, 1, 1.f));
	//m_cLevel.LoadTilemap("LevelMap//" + getLevel + ".csv");

	m_cLevel.LoadTilemap(getLevel);
}

void CScenePlay::Update(double dt)
{
	CSceneManager::Update(dt);


	if (Application::IsKeyPressed('1'))
	{
		cout << "current mouse x: " << Application::getMouseWorldX() << endl;
		cout << "current mouse y: " << Application::getMouseWorldY() << endl;

		//cout << "choice: " << Application::getChoiceVal() << endl;
	}

	if (!m_cPlayer->IsAlive() && m_bDied == false)
	{
		for (unsigned i = 0; i < Application::m_cPropertyList.size(); i++)
		{
			if (Application::m_cPropertyList[i]->GetTitle() == "Death")
			{
				Application::m_cPropertyList[i]->ChangeValue(1);
				m_bDied = true;
			}
		}
	}
	if (!m_cPlayer->IsAlive() && !m_cPlayer->IsActive() && !m_bShowLose)
	{
		Application::Sound.playSound("media/lose_sound.mp3");
		m_bPlayLoseSound = true;
		m_bShowLose = true;
	}

	//Player control
	if (m_cLevel.IsMovementReady() && !m_cPlayer->GetHasReachedEndLevel() && m_cPlayer->IsAlive())
	{
		if (IsKeyDown('w'))
		{
			m_cPlayer->SetFace(CPlayer::PD_UP);
			m_cPlayer->SetNextDirection(CPlayer::PD_UP);
		}
		else if (IsKeyDown('s'))
		{
			m_cPlayer->SetFace(CPlayer::PD_DOWN);
			m_cPlayer->SetNextDirection(CPlayer::PD_DOWN);
		}
		else if (IsKeyDown('d'))
		{
			m_cPlayer->SetFace(CPlayer::PD_RIGHT);
			m_cPlayer->SetNextDirection(CPlayer::PD_RIGHT);
		}
		else if (IsKeyDown('a'))
		{
			m_cPlayer->SetFace(CPlayer::PD_LEFT);
			m_cPlayer->SetNextDirection(CPlayer::PD_LEFT);
		}
	}

	if (IsKeyDownOnce(VK_RETURN))
		m_cPlayer->UseItem(CPlayer::SLOT_01);

	//Update player
	if (m_cPlayer->IsActive())
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
	if (Application::m_bScreenShake)
	{
		m_fShakeAngle = static_cast<float>(rand() % 360);
		m_fShakeOffsetX = sin(m_fShakeAngle) * 20;
		m_fShakeOffsetY = cos(m_fShakeAngle) * 20;

		camera.UpdatePosition(Vector3(static_cast<float>((m_cPlayer->GetXIndex() * m_cLevel.GetTilemap()->GetTileSize() + m_cPlayer->GetXOffset())) + 50.f + m_fShakeOffsetX, static_cast<float>(m_cPlayer->GetYIndex() * -m_cLevel.GetTilemap()->GetTileSize() + m_cPlayer->GetYOffset()) + m_fShakeOffsetY, 0.f));
	}
	else
		camera.UpdatePosition(Vector3(static_cast<float>((m_cPlayer->GetXIndex() * m_cLevel.GetTilemap()->GetTileSize() + m_cPlayer->GetXOffset())) + 50.f, static_cast<float>(m_cPlayer->GetYIndex() * -m_cLevel.GetTilemap()->GetTileSize() + m_cPlayer->GetYOffset()), 0.f));

	if (m_cPlayer->GetHasReachedEndLevel() && !m_bShowWin)
	{
		//End Level
		if (!m_bPlayWinSound)
		{
			Application::Sound.playSound("media/Win_sound.mp3");
			m_bPlayWinSound = true;
		}
		m_bShowWin = true;
		m_cLevel.CalculateScore();
	}
	else if (m_bShowWin)
	{
		if (IsKeyDownOnce('n') && m_iCurrentLevel <= 8)
		{
			++m_iCurrentLevel;
			ostringstream convertor;
			string getLevel = "Level";
			convertor << m_iCurrentLevel;
			getLevel.append(convertor.str());
			m_cLevel.SetLevelName(getLevel);
			m_cLevel.Reset();
			m_bShowWin = false;
			m_bShowLose = false;
			m_bPlayWinSound = false;
		}
		else if (IsKeyDown('n') && m_iCurrentLevel == 8)
		{
			m_bToFinishScreen = true;
		}
	}

	if (IsKeyDownOnce('r'))
	{
		m_cLevel.Reset();
		Application::Sound.playSound("media/confirm_sound.wav");
		m_bShowWin = false;
		m_bShowLose = false;
		m_bPlayWinSound = false;
		m_bPlayLoseSound = false;
	}

	//update win screen
	if ((m_bShowWin && Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), nextLevel_button_vec_winScreen.x, nextLevel_button_vec_winScreen.y, nextLevel_button_vec_winScreen.x + buttonXoffset, nextLevel_button_vec_winScreen.y + buttonYoffset)
		&& m_iCurrentLevel <= 8 && Application::IsMousePressed(GLFW_MOUSE_BUTTON_1)) || IsKeyDownOnce('l')) // play button
	{
		if (m_iCurrentLevel == 8)
		{
			m_bToFinishScreen = true;
		}
		else
		{
			++m_iCurrentLevel;
			ostringstream convertor;
			string getLevel = "Level";
			convertor << m_iCurrentLevel;
			getLevel.append(convertor.str());
			m_cLevel.SetLevelName(getLevel);
			m_cLevel.Reset();
			m_bShowWin = false;
		}

		m_bPlayWinSound = false;

	}
	else if (m_bShowWin && Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), restart_button_vec_winScreen.x, restart_button_vec_winScreen.y, restart_button_vec_winScreen.x + buttonXoffset, restart_button_vec_winScreen.y + buttonYoffset)
		&& Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
	{
		m_cLevel.Reset();
		Application::Sound.playSound("media/confirm_sound.wav");
		m_bShowWin = false;
		m_bPlayWinSound = false;
		m_bPlayLoseSound = false;
	}
	else if (m_bShowWin && Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), exit_button_vec_winScreen.x, exit_button_vec_winScreen.y, exit_button_vec_winScreen.x + buttonXoffset, exit_button_vec_winScreen.y + buttonYoffset)
		&& Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
	{
		SetISQuitToMain(true);
	}

	//update lose screen
	if (m_bShowLose && Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), restart_button_vec_loseScreen.x, restart_button_vec_loseScreen.y, restart_button_vec_loseScreen.x + buttonXoffset, restart_button_vec_loseScreen.y + buttonYoffset)
		&& Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
	{
		m_cLevel.Reset();
		Application::Sound.playSound("media/confirm_sound.wav");
		m_bShowWin = false;
		m_bShowLose = false;
		m_bPlayWinSound = false;
		m_bPlayLoseSound = false;
		m_bDied = false;
	}
	else if (m_bShowLose && Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), quit_button_vec_loseScreen.x, quit_button_vec_loseScreen.y, quit_button_vec_loseScreen.x + buttonXoffset, quit_button_vec_loseScreen.y + buttonYoffset)
		&& Application::IsMousePressed(GLFW_MOUSE_BUTTON_1))
	{
		SetISQuitToMain(true);
	}
}

/********************************************************************************
 Render mobile objects
 ********************************************************************************/
void CScenePlay::RenderGUI()
{
	if (m_bShowWin)
		RenderWin();
	if (m_bShowLose)
		RenderLose();

	for (unsigned i = 0; i < Application::m_cAchievementList.size(); i++)
	{
		if (Application::m_cAchievementList[i]->GetUnlocked() == 1 && Application::m_cAchievementList[i]->GetShowedOnce() == 0)
		{
			Application::m_cAchievementList[i]->SetShowedOnce(1);
			CLuaScript* m_cLuaScript;
			m_cLuaScript = new CLuaScript("Achievements");
			m_cLuaScript->saveAchievementValues();
			delete m_cLuaScript;
			Application::m_cAchievementList[i]->SetTimer(0.0);
			Application::m_cAchievementList[i]->SetAppearedOnce(false);
		}
		if (Application::m_cAchievementList[i]->GetAppearedOnce() == false && Application::m_cAchievementList[i]->GetTimer() >= 0.0)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "You've got the \"" + Application::m_cAchievementList[i]->GetTitle() + "\" title!", Color(0.0f, 1.0f, 0.0f), 15.0f, -150.0f, 70.0f);
			Application::m_cAchievementList[i]->SetTimer(Application::m_cAchievementList[i]->GetTimer() + 0.0166);
			if (Application::m_cAchievementList[i]->GetTimer() > 2)
			{
				Application::m_cAchievementList[i]->SetAppearedOnce(true);
				Application::m_cAchievementList[i]->SetTimer(-1.0);
			}
		}
	}
}

void CScenePlay::RenderWin(void)
{

	RenderMeshIn2D(meshList[GEO_TRANSPARENT_LAYER], false, 350.f, 180.f, 0, 0);
	RenderMeshIn2D(meshList[GEO_TEXTBOX], false, 300.f, 150.f, 0, 0);
	if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), nextLevel_button_vec_winScreen.x, nextLevel_button_vec_winScreen.y, nextLevel_button_vec_winScreen.x + buttonXoffset, nextLevel_button_vec_winScreen.y + buttonYoffset)
		&& m_iCurrentLevel <= 8) // play button
	{
		RenderMeshIn2D(meshList[GEO_NEXT_BUTTON_HIGHLIGHTED], false, 2, 1.5f, -50.f, -50.f);
		RenderMeshIn2D(meshList[GEO_RESTART_BUTTON], false, 2, 1.5f, 0.f, -50.f);
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON], false, 2, 1.5f, 50.f, -50.f);
	}
	else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), restart_button_vec_winScreen.x, restart_button_vec_winScreen.y, restart_button_vec_winScreen.x + buttonXoffset, restart_button_vec_winScreen.y + buttonYoffset))
	{
		RenderMeshIn2D(meshList[GEO_NEXT_BUTTON], false, 2, 1.5f, -50.f, -50.f);
		RenderMeshIn2D(meshList[GEO_RESTART_BUTTON_HIGHLIGHTED], false, 2, 1.5f, 0.f, -50.f);
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON], false, 2, 1.5f, 50.f, -50.f);
	}
	else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), exit_button_vec_winScreen.x, exit_button_vec_winScreen.y, exit_button_vec_winScreen.x + buttonXoffset, exit_button_vec_winScreen.y + buttonYoffset))
	{
		RenderMeshIn2D(meshList[GEO_NEXT_BUTTON], false, 2, 1.5f, -50.f, -50.f);
		RenderMeshIn2D(meshList[GEO_RESTART_BUTTON], false, 2, 1.5f, 0.f, -50.f);
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON_HIGHLIGHTED], false, 2, 1.5f, 50.f, -50.f);
	}
	else
	{
		RenderMeshIn2D(meshList[GEO_NEXT_BUTTON], false, 2, 1.5f, -50.f, -50.f);
		RenderMeshIn2D(meshList[GEO_RESTART_BUTTON], false, 2, 1.5f, 0.f, -50.f);
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON], false, 2, 1.5f, 50.f, -50.f);
	}

	for (int i = 0; i < m_cLevel.GetNumStars(); ++i)
		RenderMeshIn2D(meshList[GEO_STAR], false, 1.f, 1.f, -50.f + (i * 50.f), 10.f);

	for (int i = 0; i < 3 - m_cLevel.GetNumStars(); ++i)
		RenderMeshIn2D(meshList[GEO_STAROUTLINE], false, 1.f, 1.f, 50.f - (i * 50.f), 10.f);

	RenderTextOnScreen(meshList[GEO_TEXT], "VICTORY!", Color(1.f, 1.f, 1.f), 50, -70.f, 10.f);
	ostringstream s_score;
	s_score << "Moves:" << m_cLevel.GetNumberOfMoves() << " / " << m_cLevel.GetSmallestMoves();
	if (m_cLevel.GetNumberOfMoves() <= m_cLevel.GetSmallestMoves())
		RenderTextOnScreen(meshList[GEO_TEXT], s_score.str(), Color(0.f, 1.f, 0.f), 20, -70.f, -35.f);
	else
		RenderTextOnScreen(meshList[GEO_TEXT], s_score.str(), Color(1.f, 1.f, 1.f), 20, -70.f, -35.f);

	ostringstream s_coins;
	s_coins << "Coins:" << m_cPlayer->GetCoins() << " / " << m_cLevel.GetTotalCoins();
	if (m_cPlayer->GetCoins() >= m_cLevel.GetTotalCoins())
		RenderTextOnScreen(meshList[GEO_TEXT], s_coins.str(), Color(0.f, 1.f, 0.f), 20, -70.f, -45.f);
	else
		RenderTextOnScreen(meshList[GEO_TEXT], s_coins.str(), Color(1.f, 1.f, 1.f), 20, -70.f, -45.f);
}

void CScenePlay::RenderLose(void)
{
	RenderMeshIn2D(meshList[GEO_TRANSPARENT_LAYER], false, 350.f, 180.f, 0, 0);
	RenderMeshIn2D(meshList[GEO_TEXTBOX], false, 300.f, 150.f, 0, 0);
	RenderTextOnScreen(meshList[GEO_TEXT], "DEFEAT", Color(1.f, 1.f, 1.f), 50, -60.f, 10.f);
	RenderTextOnScreen(meshList[GEO_TEXT], "rekt", Color(1.f, 1.f, 1.f), 5, -10.f, -10.f);

	if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), restart_button_vec_loseScreen.x, restart_button_vec_loseScreen.y, restart_button_vec_loseScreen.x + buttonXoffset, restart_button_vec_loseScreen.y + buttonYoffset))
	{
		RenderMeshIn2D(meshList[GEO_RESTART_BUTTON_HIGHLIGHTED], false, 2, 1.5f, -25.f, -50.f);
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON], false, 2, 1.5f, 25.f, -50.f);
	}
	else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), quit_button_vec_loseScreen.x, quit_button_vec_loseScreen.y, quit_button_vec_loseScreen.x + buttonXoffset, quit_button_vec_loseScreen.y + buttonYoffset))
	{
		RenderMeshIn2D(meshList[GEO_RESTART_BUTTON], false, 2, 1.5f, -25.f, -50.f);
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON_HIGHLIGHTED], false, 2, 1.5f, 25.f, -50.f);
	}
	else
	{
		RenderMeshIn2D(meshList[GEO_RESTART_BUTTON], false, 2, 1.5f, -25.f, -50.f);
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON], false, 2, 1.5f, 25.f, -50.f);
	}
}

/********************************************************************************
Render the player
********************************************************************************/
void CScenePlay::RenderPlayer()
{
	modelStack.PushMatrix();
	modelStack.Translate(m_cPlayer->GetRenderPosX(), m_cPlayer->GetRenderPosY(), 0.f);
	modelStack.Scale(static_cast<float>(m_cLevel.GetTilemap()->GetTileSize()), static_cast<float>(m_cLevel.GetTilemap()->GetTileSize()), 1.f);
	RenderMesh(meshList[GEO_PLAYER], false);
	modelStack.PopMatrix();
}

/********************************************************************************
Render the entities
********************************************************************************/
void CScenePlay::RenderEntities()
{
	//Render text worldspace entities
	for (std::vector<CTextBox*>::iterator entity = m_cLevel.m_cTextBoxList.begin(); entity != m_cLevel.m_cTextBoxList.end(); entity++)
	{
		modelStack.PushMatrix();
		modelStack.Translate((*entity)->GetRenderPosX(), (*entity)->GetRenderPosY(), 0.f);
		modelStack.Scale(TILE_SIZE - 5, TILE_SIZE - 5, 1.f);
		RenderMesh(meshList[GEO_QUESTION_MARK], false);
		modelStack.PopMatrix();
	}

	for (std::vector<CEntityIPos*>::iterator entity = m_cLevel.m_cEntityIPosList.begin(); entity != m_cLevel.m_cEntityIPosList.end(); entity++)
	{
		if (!(*entity)->IsActive())
			continue;
		modelStack.PushMatrix();
		modelStack.Translate((*entity)->GetRenderPosX(), (*entity)->GetRenderPosY(), 0.f);
		modelStack.PushMatrix();
		modelStack.Scale(TILE_SIZE, TILE_SIZE, 1.f);
		if ((*entity)->GetSprite() == NULL)
			RenderMesh(meshList[GEO_GRASS_DARKGREEN], false);
		else
			RenderMesh((*entity)->GetSprite(), false);
		modelStack.PopMatrix();
		if ((*entity)->IsHoldingObj() && (*entity)->IsAlive())
		{
			modelStack.Translate(0.f, KEY_HUD_OFFSET, 0.f);
			modelStack.Scale(KEY_HUD_SIZE, KEY_HUD_SIZE, 1.f);
			RenderMesh((*entity)->GetHoldingObj()->GetSprite(), false);
		}

		modelStack.PopMatrix();
	}
}

void CScenePlay::RenderTextBox()
{
	//Render textbox background
	if (CTextBox::ShowBox())
	{
		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x - 95.f, camera.position.y - 135.f, 0.f);
		modelStack.Scale(CTextBox::GetBoxScaleX(), 95.f, 1.f);
		RenderMesh(meshList[GEO_TEXTBOX], false);
		modelStack.PopMatrix();
	}

	//Render text inside textbox
	if (CTextBox::ShowText())
	{
		for (std::vector<CTextBox*>::iterator entity = m_cLevel.m_cTextBoxList.begin(); entity != m_cLevel.m_cTextBoxList.end(); entity++)
		{
			if ((*entity)->IsActivated())
			{
				modelStack.PushMatrix();
				modelStack.Translate(camera.position.x - 280.f, camera.position.y - 125.f, 0.f);
				modelStack.Scale(30.f, 30.f, 1.f);
				//RenderMesh(meshList[GEO_GRASS_DARKGREEN], false);
				//if ((*entity)->ShowText())
				RenderText(meshList[GEO_TEXT], (*entity)->GetText(), Color(1.f, 1.f, 1.f), 0.7f, 180.f, (*entity)->GetCurrentCharIndex());
				modelStack.PopMatrix();
				break;
			}
		}
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
	RenderMeshIn2D(meshList[GEO_KEYS_BLUE], false, 25, 25, 80, -40);
	RenderMeshIn2D(meshList[GEO_KEYS_RED], false, 25, 25, 120, -40);
	RenderMeshIn2D(meshList[GEO_KEYS_GREEN], false, 25, 25, 80, -25);
	RenderMeshIn2D(meshList[GEO_KEYS_YELLOW], false, 25, 25, 120, -25);

	//Render the number of coins obtained
	RenderMeshIn2D(meshList[GEO_COIN], false, 20, 20, 80, -70.f);

	//Fetch and Render the amount of keys/coins
	ostringstream s_coins;
	s_coins << m_cPlayer->GetCoins() << "/" << m_cLevel.GetTotalCoins();
	if (m_cPlayer->GetCoins() >= m_cLevel.GetTotalCoins())
		RenderTextOnScreen(meshList[GEO_TEXT], s_coins.str(), Color(0.2f, 1.0f, 0.2f), 20.0f, 92.0f, -84.0f);
	else
		RenderTextOnScreen(meshList[GEO_TEXT], s_coins.str(), Color(0.0f, 0.0f, 0.0f), 20.0f, 92.0f, -84.0f);

	ostringstream s_keys_red;
	s_keys_red << m_cPlayer->GetKeys_Red();
	RenderTextOnScreen(meshList[GEO_TEXT], s_keys_red.str(), Color(0.0f, 0.0f, 0.0f), 15.0f, 135.0f, -50.0f);

	ostringstream s_keys_blue;
	s_keys_blue << m_cPlayer->GetKeys_Blue();
	RenderTextOnScreen(meshList[GEO_TEXT], s_keys_blue.str(), Color(0.0f, 0.0f, 0.0f), 15.0f, 92.0f, -50.0f);

	ostringstream s_keys_green;
	s_keys_green << m_cPlayer->GetKeys_Green();
	RenderTextOnScreen(meshList[GEO_TEXT], s_keys_green.str(), Color(0.0f, 0.0f, 0.0f), 15.0f, 92.0f, -36.0f);

	ostringstream s_keys_yellow;
	s_keys_yellow << m_cPlayer->GetKeys_Yellow();
	RenderTextOnScreen(meshList[GEO_TEXT], s_keys_yellow.str(), Color(0.0f, 0.0f, 0.0f), 15.0f, 135.0f, -36.0f);

	ostringstream s_player_moves;
	s_player_moves << m_cLevel.GetNumberOfMoves();
	RenderTextOnScreen(meshList[GEO_TEXT], "Moves:" + s_player_moves.str(), Color(0.1f, 0.1f, 0.1f), 20.0f, 72.0f, 0.0f);

	ostringstream s_move_goal;
	s_move_goal << m_cLevel.GetSmallestMoves();
	RenderTextOnScreen(meshList[GEO_TEXT], "Goal:" + s_move_goal.str(), Color(0.1f, 0.1f, 0.1f), 20.0f, 72.0f, -10.0f);

	RenderMeshIn2D(meshList[GEO_PLAYER], false, TILE_SIZE, TILE_SIZE, 100.f, 45.f);

	//on mouse hover quit button
	if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), quit_button_vec.x, quit_button_vec.y, quit_button_vec.x + 11.0f, quit_button_vec.y + 5.42f)
		|| CSceneManager::IsKeyDown('q'))
	{
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON_HIGHLIGHTED], false, 1.1f, 1.1f, 140.0f, 55);
		RenderMeshIn2D(meshList[GEO_RESTART_BUTTON], false, 1.f, 1.f, 140.0f, 40.f);

		if (!m_bQuitselectsound)
		{
			m_bQuitselectsound = true;
			Application::Sound.playSound("media/scroll_sound.wav");
		}

		if (Application::IsMousePressed(GLFW_MOUSE_BUTTON_1) || CSceneManager::IsKeyDown('q'))
		{
			SetISQuitToMain(true);
			Application::Sound.playSound("media/confirm_sound.wav");
		}
	}
	else if (Application::checkForcollision(Application::getMouseWorldX(), Application::getMouseWorldY(), restart_button_vec.x, restart_button_vec.y, restart_button_vec.x + 11.0f, restart_button_vec.y + 5.42f))
	{
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON], false, 1.f, 1.f, 140.0f, 55);
		RenderMeshIn2D(meshList[GEO_RESTART_BUTTON_HIGHLIGHTED], false, 1.1f, 1.1f, 140.0f, 40.f);

		if (!m_bQuitselectsound)
		{
			m_bQuitselectsound = true;
			Application::Sound.playSound("media/scroll_sound.wav");
		}

		if (!Application::IsMousePressed(GLFW_MOUSE_BUTTON_1) && m_bMouseisPressed)
		{
			m_bMouseisPressed = false;
		}

		if (Application::IsMousePressed(GLFW_MOUSE_BUTTON_1) && m_bMouseisPressed == false)
		{
			m_cLevel.Reset();
			m_bMouseisPressed = true;
			Application::Sound.playSound("media/confirm_sound.wav");
			m_bShowWin = false;
		}
	}
	else
	{
		RenderMeshIn2D(meshList[GEO_QUIT_BUTTON], false, 1.f, 1.f, 140.0f, 55);
		RenderMeshIn2D(meshList[GEO_RESTART_BUTTON], false, 1.f, 1.f, 140.0f, 40.f);
		SetISQuitToMain(false);
		m_bQuitselectsound = false;
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
			{
			//	RenderMesh(meshList[GEO_GRASS_DARKGREEN], false);
			}
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

	RenderMeshIn2D(meshList[GEO_BACKGROUND], false);

	RenderTilemap();

	RenderEntities();
	RenderPlayer();
	RenderTextBox();
	RenderInventory();
	RenderGUI();
}

/********************************************************************************
 Exit process for this scene
 ********************************************************************************/
void CScenePlay::Exit()
{
	// Cleanup VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
	m_cLevel.Exit();
	if (m_cPlayer)
		delete m_cPlayer;
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}
