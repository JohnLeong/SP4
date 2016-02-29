#pragma once
#include <string>
#include "Entities\EnemyZombie.h"
#include "Achievements\Achievements.h"


using std::string;

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class CLuaScript
{
private:
	lua_State *L2 = lua_open();
	lua_State *A = lua_open();
	lua_State *AP = lua_open();
public:
	CLuaScript(string path, string lua_State);
	~CLuaScript();

	string getStringVariable(string name);
	int getIntVariable(string name);
	bool getBoolVariable(string name);
	float getFloatVariable(string name);

	CEnemyZombie* getNsetZombieVariables(string name);

	CAchievements* getAchievementVariables(string name, vector<CProperties*>  checkList);
	CProperties* getAchievementPropertiesVariables(string name);

	void recordAchievementProgress(string name);
	void recordAchievementPropertiesProgressValue(string name, string value, string changedValue);
	void recordAchievementPropertiesProgressBool(string name);

	int luaAdd(int x, int y);
	int luaMinus(int x, int y);
};

