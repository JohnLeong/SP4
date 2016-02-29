#include "LuaScript.h"
#include "Achievements\Properties.h"

CLuaScript::CLuaScript(string path, string lua_State)
{
	int s = 0;
	string filepath;

	filepath = "LuaScripts//" + path + ".lua";
	if (lua_State == "A")
	{
		luaL_openlibs(A);
		if (luaL_loadfile(A, filepath.c_str()) || lua_pcall(A, 0, 0, 0))
		{
			printf("error: %s", lua_tostring(A, -1));
		}
	}
	else if (lua_State == "AP")
	{
		luaL_openlibs(AP);
		if (luaL_loadfile(AP, filepath.c_str()) || lua_pcall(AP, 0, 0, 0))
		{
			printf("error: %s", lua_tostring(AP, -1));
		}
	}
	else
	{
		luaL_openlibs(L2);
		if (luaL_loadfile(L2, filepath.c_str()) || lua_pcall(L2, 0, 0, 0))
		{
			printf("error: %s", lua_tostring(L2, -1));
		}
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

CAchievements* CLuaScript::getAchievementVariables(string name, vector<CProperties*> checkList)
{
	CAchievements* newAchievement;
	vector<CProperties*> propertyList;
	string addName = "Name";
	string addTotalProperties = "TotalProperties";
	string addProperties = "Properties";
	string addBool = "Bool";

	name += addName;
	lua_getglobal(A, name.c_str());
	string getName = (string)lua_tostring(A, -1);
	name.erase(name.begin() + 1, name.end());

	name += addTotalProperties;
	lua_getglobal(A, name.c_str());
	int totalAchievementProperties = (int)lua_tonumber(A, -1);
	name.erase(name.begin() + 1, name.end() - 10);
	for (int i = 1; i < totalAchievementProperties + 1; i++)
	{
		ostringstream converter;
		converter << i;
		name += converter.str();
		lua_getglobal(A, name.c_str());
		string getPropertyName = (string)lua_tostring(A, -1);
		for (int i = 0; i < checkList.size(); i++)
		{
			if (checkList[i]->GetName() == getPropertyName)
			{
				propertyList.push_back(checkList[i]);
			}
		}
		name.erase(name.begin() + 11);
	}

	name.erase(name.begin() + 1, name.end());
	name += addBool;
	lua_getglobal(A, name.c_str());
	bool getBool = (bool)lua_toboolean(A, -1);

	newAchievement = new CAchievements(getName, propertyList, getBool);
	return newAchievement;
}

CProperties* CLuaScript::getAchievementPropertiesVariables(string name)
{
	CProperties* newProperty;
	string addName = "Name";
	string addValue = "Value";
	string addActive = "Active";
	string addActValue = "ActValue";
	string addBool = "Bool";

	name += addName;
	lua_getglobal(AP, name.c_str());
	string getName = (string)lua_tostring(AP, -1);
	name.erase(name.begin() + 1, name.end());

	name += addValue;
	lua_getglobal(AP, name.c_str());
	int getValue = (int)lua_tonumber(AP, -1);
	name.erase(name.begin() + 1, name.end());

	name += addActive;
	lua_getglobal(AP, name.c_str());
	string getActive = (string)lua_tostring(AP, -1);
	name.erase(name.begin() + 1, name.end());

	name += addActValue;
	lua_getglobal(AP, name.c_str());
	int getActValue = (int)lua_tonumber(AP, -1);
	name.erase(name.begin() + 1, name.end());

	name += addBool;
	lua_getglobal(AP, name.c_str());
	bool getBool = (bool)lua_toboolean(AP, -1);
	
	newProperty = new CProperties(getName, getValue, getActive, getActValue, getBool);
	return newProperty;
}

void CLuaScript::recordAchievementProgress(string name)
{
	ostringstream convertor;
	string changeBool = "Bool";
	string value = "FALSE";
	string changedValue = "TRUE";

	name.erase(name.begin() + 1, name.end());
	name = name + changeBool + " = FALSE";
	const char * Search = name.c_str();
	const char * ChoseReplacement = value.c_str();
	const char * Replacment = changedValue.c_str();
	luaL_gsub(L2, Search, ChoseReplacement, Replacment);
}


void CLuaScript::recordAchievementPropertiesProgressValue(string name, string value, string changedValue)
{
	string changeValue = "Value";
	name.erase(name.begin() + 1, name.end());
	name = name + changeValue + " = " + value;
	const char * Search = name.c_str();
	const char * ChoseReplacement = value.c_str();
	const char * Replacment = changedValue.c_str();

	luaL_gsub(L2, Search, ChoseReplacement, Replacment);
}

void CLuaScript::recordAchievementPropertiesProgressBool(string name)
{
	ostringstream convertor;
	string changeBool = "Bool";
	string value = "FALSE";
	string changedValue = "TRUE";

	name.erase(name.begin() + 1, name.end());
	name = name + changeBool + " = FALSE";
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