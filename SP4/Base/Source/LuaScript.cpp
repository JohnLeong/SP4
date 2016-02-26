#include "LuaScript.h"
#include "Achievements\Properties.h"

CLuaScript::CLuaScript(string path)
{
	int s = 0;
	string filepath;

	filepath = "LuaScripts//" + path + ".lua";

	luaL_openlibs(L2);
	if (luaL_loadfile(L2, filepath.c_str()) || lua_pcall(L2, 0, 0, 0))
	{
		printf("error: %s", lua_tostring(L2, -1));
	}
	
}


CLuaScript::~CLuaScript()
{
	lua_close(L2);
}

void checkStack(lua_State* L, int check)
{
	if (!lua_checkstack(L, 1))
	{
		lua_remove(L, 1);
	}
}

string CLuaScript::getStringVariable(string name)
{
	checkStack(L2, 1);
	lua_getglobal(L2, name.c_str());
	if (!lua_isstring(L2, -1))
	{
		return "NULL";
	}
	string variableStr = (string)lua_tostring(L2, -1);
	return variableStr;
}

int CLuaScript::getIntVariable(string name)
{
	checkStack(L2, 1);
	lua_getglobal(L2, name.c_str());
	if (!lua_isnumber(L2, -1))
	{
		return -1;
	}
	int value = (int)lua_tonumber(L2, -1);
	return value;
}

bool CLuaScript::getBoolVariable(string name)
{
	checkStack(L2, 1);
	lua_checkstack(L2, 1);
	lua_getglobal(L2, name.c_str());
	if (!lua_isboolean(L2, -1))
	{
		return -1;
	}
	bool value = (bool)lua_toboolean(L2, -1);
	return value;
}

float CLuaScript::getFloatVariable(string name)
{
	checkStack(L2, 1);
	lua_checkstack(L2, 1);
	lua_getglobal(L2, name.c_str());
	if (!lua_isboolean(L2, -1))
	{
		return -1.f;
	}
	float value = (float)lua_toboolean(L2, -1);
	return value;
}

//CEnemyZombie* CLuaScript::getNsetZombieVariables(string name)
//{
//	string addPosX = "PosX";
//	string addPosY = "PosY";
//
//	name += addPosX;
//	lua_getglobal(L2, name.c_str());
//	int getPosX = (int)lua_tonumber(L2, -1);
//	name.erase(name.begin() + 7, name.end() - 4);
//
//	name += addPosY;
//	lua_getglobal(L2, name.c_str());
//	int getPosY = (int)lua_tonumber(L2, -1);
//
//	//CEnemyZombie* zombie = new CEnemyZombie(getPosX, getPosY, );
//}


CAchievements* CLuaScript::getAchievementVariables(string name, vector<CProperties*> checkList)
{
	checkStack(L2, 1);
	CAchievements* newAchievement;
	vector<CProperties*> propertyList;
	string addName = "Name";
	string addProperties = "Properties";

	name += addName;
	lua_getglobal(L2, name.c_str());
	string getName = (string)lua_tostring(L2, -1);
	name.erase(name.begin() + 1);

	name += addProperties;

	int totalAchievementProperties = 0;
	for (int i = 1; i < totalAchievementProperties + 1; i++)
	{
		ostringstream converter;
		converter << i;
		name = converter.str();
		lua_getglobal(L2, name.c_str());
		string getPropertyName = (string)lua_tostring(L2, -1);
		for (int i = 0; i < checkList.size(); i++)
		{
			if (checkList[i]->GetName() == getPropertyName)
			{
				propertyList.push_back(checkList[i]);
			}
		}
	}
	newAchievement = new CAchievements(getName, propertyList, false);
	return newAchievement;
}

CProperties* CLuaScript::getAchievementPropertiesVariables(string name)
{
	checkStack(L2, 1);
	CProperties* newProperty;
	string addName = "Name";
	string addValue = "Value";
	string addActive = "Active";
	string addActValue = "ActValue";

	name += addName;
	lua_getglobal(L2, name.c_str());
	string getName = (string)lua_tostring(L2, -1);
	name.erase(name.begin() + 5);

	name += addValue;
	lua_getglobal(L2, name.c_str());
	int getValue = (int)lua_tonumber(L2, -1);
	name.erase(name.begin() + 6);

	name += addActive;
	lua_getglobal(L2, name.c_str());
	string getActive = (string)lua_tostring(L2, -1);
	name.erase(name.begin() + 7);

	name += addActValue;
	lua_getglobal(L2, name.c_str());
	int getActValue = (int)lua_tonumber(L2, -1);

	newProperty = new CProperties(getName, getValue, getActive, getActValue, false);
	return newProperty;
}

void CLuaScript::recordAchievementProgress(string name, string value, string changedValue)
{
	name = name + " = " + value;
	const char * Search = name.c_str();
	const char * ChoseReplacement = value.c_str();
	const char * Replacment = changedValue.c_str();

	luaL_gsub(L2, Search, ChoseReplacement, Replacment);
}


void CLuaScript::recordAchievementPropertiesProgress(string name, string value, string changedValue)
{
	name = name + " = " + value;
	const char * Search = name.c_str();
	const char * ChoseReplacement = value.c_str();
	const char * Replacment = changedValue.c_str();

	luaL_gsub(L2, Search, ChoseReplacement, Replacment);
}

int CLuaScript::luaAdd(int x, int y)
{
	int sum;

	/* the function name */
	lua_getglobal(L2, "add");

	/* the first argument */
	lua_pushnumber(L2, x);

	/* the second argument */
	lua_pushnumber(L2, y);

	/* call the function with 2 arguments, return 1 result */
	lua_call(L2, 2, 1);

	/* get the result */
	sum = (int)lua_tointeger(L2, -1);
	lua_pop(L2, -1);

	return sum;
}

int CLuaScript::luaMinus(int x, int y)
{
	int minus;

	/* the function name */
	lua_getglobal(L2, "minus");

	/* the first argument */
	lua_pushnumber(L2, x);

	/* the second argument */
	lua_pushnumber(L2, y);

	/* call the function with 2 arguments, return 1 result */
	lua_call(L2, 2, 1);

	/* get the result */
	minus = (int)lua_tointeger(L2, -1);
	lua_pop(L2, -1);

	return minus;
}