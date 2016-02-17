#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "PlayInfo3PV.h"

#define NUMKEYS 255

class CSceneManager : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_TYPE,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

public:
	CSceneManager(void);
	CSceneManager(const int m_window_width, const int m_window_height);
	~CSceneManager(void);

	virtual void Init();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);
	// Update Avatar position
	virtual void UpdateAvatarStatus(const unsigned char key, const bool status = true);
	// Update Weapon status
	virtual void UpdateWeaponStatus(const unsigned char key);
	virtual void UpdateKeyboardStatus(const unsigned char key);
	virtual void Render();
	virtual void Render2D();
	virtual void Exit();

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	//void RenderMeshIn2D(Mesh *mesh, bool enableLight, float size=1.0f, float x=0.0f, float y=0.0f, bool rotate=false);
	void RenderMeshIn2D(Mesh *mesh, bool enableLight, float sizeX = 1.0f, float sizeY = 1.0f, float x = 0.0f, float y = 0.0f, bool rotate = false);
	void RenderMesh(Mesh *mesh, bool enableLight);

	// Render the main components of this scene
	void RenderLights();

	//Is key currently active
	virtual bool IsKeyDown(unsigned short key);
	//Is key pressed once
	virtual bool IsKeyDownOnce(unsigned short key);
	//set the key when pressedx
	virtual void SetKeyDown(unsigned short key, bool b);

	//get the value of choice
	int getChoiceVal(void);
	//set the value of choice
	void setChoiceVal(int choice);

	//get X cursor position in world space 
	float GetWorldX();
	//get Y cursor position in world space
	float GetWorldY();
	//set X cursor position in world space
	void SetWorldX(float worldX);
	//set Y cursor position in world space
	void SetWorldY(float worldY);

	//check for collision
	bool checkForcollision(float mouseX, float mouseY, float pos_buttonX, float pos_buttonY, float pos_buttonWidth, float pos_buttonHeight);

	enum WEAPON_ACTION
	{
		WA_NIL = 0,
		WA_FIRE,
		WA_FIRE_SECONDARY,
		WA_RELOAD,
		WA_CHANGEWEAPON,
		WA_TOTAL,
	};

protected:
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	// Handler to the camera
	Camera3 camera;

	// Rotation angle for use with the model stack
	float rotateAngle;

	// Matrices for Model, View and Projection stack
	MS modelStack;
	MS viewStack;
	MS projectionStack;

	// Window size
	int m_window_width;
	int m_window_height;

	//World size
	float m_world_width;
	float m_world_height;

	//get mouse position in world space
	float worldX;
	float worldY;

	//for transversing the menu buttons
	int choice;

	Light lights[2];
	bool bLightEnabled;

	float fps;

	//Keys
	bool myKeys[NUMKEYS];			//Current state of keys
	bool myKeysActive[NUMKEYS];		//Previous state of keys
};

#endif