#ifndef SCENE_LEVELSELECT_H
#define SCENE_LEVELSELECT_H

#include "SceneManager.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class  CSceneLevelSelection : public CSceneManager
{
	enum GEOMETRY_TYPE
	{
		GEO_RAY,
		GEO_AXES,
		GEO_CROSSHAIR,
		GEO_LIGHTBALL,
		GEO_SPHERE,
		GEO_TEXT,
		GEO_LOGO,
		GEO_QUAD,
		GEO_WASD,
		GEO_MOUSE,

		//levels
		GEO_LEVEL1_BUTTON,
		GEO_LEVEL2_BUTTON,
		GEO_LEVEL3_BUTTON,
		GEO_LEVEL4_BUTTON,
		GEO_LEVEL5_BUTTON,
		GEO_LEVEL6_BUTTON,
		GEO_LEVEL7_BUTTON,
		GEO_LEVEL8_BUTTON,

		GEO_LEVEL1_BUTTON_HIGHLIGHTED,
		GEO_LEVEL2_BUTTON_HIGHLIGHTED,
		GEO_LEVEL3_BUTTON_HIGHLIGHTED,
		GEO_LEVEL4_BUTTON_HIGHLIGHTED,
		GEO_LEVEL5_BUTTON_HIGHLIGHTED,
		GEO_LEVEL6_BUTTON_HIGHLIGHTED,
		GEO_LEVEL7_BUTTON_HIGHLIGHTED,
		GEO_LEVEL8_BUTTON_HIGHLIGHTED,

		GEO_BUTTON_LEFT,
		GEO_BUTTON_RIGHT,

		//level overview images
		GEO_LEVEL_OVERVIEW,
		GEO_LEVEL_OVERVIEW2,
		GEO_LEVEL_OVERVIEW3,
		GEO_LEVEL_OVERVIEW4,
		GEO_LEVEL_OVERVIEW5,
		GEO_LEVEL_OVERVIEW6,
		GEO_LEVEL_OVERVIEW7,
		GEO_LEVEL_OVERVIEW8,

		//backdrops
		GEO_DESCRIPTION_BACKDROP,

		//start button
		GEO_START_BUTTON,
		GEO_START_BUTTON_HIGHLIGHTED,

		//quit button
		GEO_QUIT_BUTTON,
		GEO_QUIT_BUTTON_HIGHLIGHTED,

		//Backgrounds
		GEO_BACKGROUND_BASE,

		//Panic button
		GEO_BUTTON_PANIC_OFF,
		GEO_BUTTON_PANIC_ON,

		NUM_GEOMETRY,
	};

public:
	CSceneLevelSelection(void);
	CSceneLevelSelection(const int m_window_width, const int m_window_height);
	~CSceneLevelSelection(void);

	virtual void Init();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);
	// Update Keyboard status
	virtual void UpdateKeyboardStatus(const unsigned char key);
	virtual void Render();
	virtual void Exit();

	void UpdateAnimations(double dt);

	//set the boolean for quit 
	static void SetISQuitToMain(bool b);
	//get the boolean for quit
	static bool GetIsQuitToMain();

	//set the boolean to check if mouse is in col with start button
	static void SetisColWithStartButton(bool b);
	//set the boolean to check if mouse is in col with start button
	static bool GetisColWithStartButton();

	bool m_bChangeState;
	bool m_bQuitToMenu;
protected:
	Mesh* meshList[NUM_GEOMETRY];

	// Window size
	int m_window_width;
	int m_window_height;

	int m_iCurrentPage;

	//for going backc to the main menu
	static bool m_bBacktoMainMenu;

	//check if the keyboard is currently active
	bool m_bisKeyBoard;

	//boolean for mouse in collision with start button
	static bool m_bisColWithStartButton;
	
	//check if selectSound is currently acftive
	bool isSelectSoundPlayingkeyboard;
	bool isSelectSoundPlayingStartQuit;
	
	//virutally create vector positions for the buttons
	Vector3 button_vec[5];
	Vector3 quit_button_vec;
	Vector3 start_button_vec;
	Vector3 panic_button_vec;
	Vector3 left_button_vec;
	Vector3 right_button_vec;

	float m_fLeftAnimOffset;
	float m_fBotAnimOffset;
	bool m_bAnimOffsetDir;
	bool m_bToggleConfirmSound;

	int m_iSelectedLevel;
};

#endif