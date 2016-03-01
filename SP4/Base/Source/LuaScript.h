#pragma once
#include <string>
#include "Entities\EnemyZombie.h"
#include "Achievements\Achievements.h"
#include <fstream>

using std::fstream;
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

public:
	CLuaScript(string path);
	~CLuaScript();

	string getStringVariable(string name);
	int getIntVariable(string name);
	bool getBoolVariable(string name);
	float getFloatVariable(string name);

	CEnemyZombie* getNsetZombieVariables(string name);

	CAchievements* getAchievementVariables(string name);
	CProperties* getAchievementPropertiesVariables(string name);

	void saveAchievementValues();
	void saveAchievementPropertiesValues();

	int luaAdd(int x, int y);
	int luaMinus(int x, int y);
};

