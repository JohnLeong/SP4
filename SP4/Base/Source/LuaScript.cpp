#include "LuaScript.h"
#include "Achievements\Properties.h"
#include "Application.h"

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
	lua_getglobal(L2, name.c_str());
	if (!lua_isstring(L2, -1))
	{
		return "NULL";
	}
	string variableStr = (string)lua_tostring(L2, -1);
	lua_remove(L2, -1);
	return variableStr;
}

int CLuaScript::getIntVariable(string name)
{
	lua_getglobal(L2, name.c_str());
	if (!lua_isnumber(L2, -1))
	{
		return -1;
	}
	int value = (int)lua_tonumber(L2, -1);
	lua_remove(L2, -1);
	return value;
}

bool CLuaScript::getBoolVariable(string name)
{
	checkStack(L2, 1);
	lua_checkstack(L2, 1);
	lua_getglobal(L2, name.c_str());
	if (!lua_isboolean(L2, -1))
	{
		return false;
	}
	bool value = (bool)lua_toboolean(L2, -1);
	lua_remove(L2, -1);
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
	lua_remove(L2, -1);
	return value;
}

CProfile* CLuaScript::getProfileVariables()
{
	CProfile* getProfile;

	string highestLevelUnlocked = "HighestLevelUnlocked";

	lua_getglobal(L2, highestLevelUnlocked.c_str());
	int getHighestLevelUnlocked = (int)lua_tonumber(L2, -1);
	lua_remove(L2, -1);

	getProfile = new CProfile(getHighestLevelUnlocked);
	return getProfile;
}

CAchievements* CLuaScript::getAchievementVariables(string name)
{
	CAchievements* newAchievement;
	vector<string> propertyList;
	string addName = "Name";
	string addTitle = "Title";
	string addTotalProperties = "TotalProperties";
	string addProperties = "Properties";
	string addExtraProp = "_";
	string addBool = "Bool";
	string addShowedOnce = "ShowOnce";

	name = addName + name;
	lua_getglobal(L2, name.c_str());
	string getName = (string)lua_tostring(L2, -1);
	lua_remove(L2, -1);
	name.erase(name.begin(), name.end() - 1);

	name = addTitle + name;
	lua_getglobal(L2, name.c_str());
	string getTitle = (string)lua_tostring(L2, -1);
	lua_remove(L2, -1);
	name.erase(name.begin(), name.end() - 1);

	name = addTotalProperties + name;
	lua_getglobal(L2, name.c_str());
	int totalAchievementProperties = (int)lua_tonumber(L2, -1);
	lua_remove(L2, -1);
	name.erase(name.begin(), name.end() - 11);

	for (int i = 1; i < totalAchievementProperties + 1; i++)
	{	
		name = name + addExtraProp;
		ostringstream converter;
		converter << i;	
		name = name + converter.str();
		lua_getglobal(L2, name.c_str());
		string getPropertyName = (string)lua_tostring(L2, -1);
		lua_remove(L2, -1);
		propertyList.push_back(getPropertyName);
		name.erase(name.begin() + 11 ,name.end());
	}

	name.erase(name.begin(), name.end() - 1);
	name = addBool + name;
	lua_getglobal(L2, name.c_str());
	bool getUnlocked = (bool)lua_toboolean(L2, -1);
	lua_remove(L2, -1);

	name.erase(name.begin(), name.end() - 1);
	name = addShowedOnce + name;
	lua_getglobal(L2, name.c_str());
	bool getShowedOnce = (bool)lua_toboolean(L2, -1);
	lua_remove(L2, -1);

	newAchievement = new CAchievements(getName, getTitle, propertyList, getUnlocked, false,getShowedOnce, -1.0) ;
	return newAchievement;
}

CProperties* CLuaScript::getAchievementPropertiesVariables(string name)
{
	CProperties* newProperty;
	string addName = "Name";
	string addTitle = "Title";
	string addValue = "Value";
	string addActive = "Active";
	string addActValue = "ActivationValue";
	string addBool = "Bool";

	name = addName + name;
	lua_getglobal(L2, name.c_str());
	string getName = (string)lua_tostring(L2, -1);
	lua_remove(L2, -1);
	name.erase(name.begin(), name.end() - 1);

	name = addTitle + name;
	lua_getglobal(L2, name.c_str());
	string getTitle = (string)lua_tostring(L2, -1);
	lua_remove(L2, -1);
	name.erase(name.begin(), name.end() - 1);

	name = addValue + name;
	lua_getglobal(L2, name.c_str());
	int getValue = (int)lua_tonumber(L2, -1);
	lua_remove(L2, -1);
	name.erase(name.begin(), name.end() - 1);

	name = addActive + name;
	lua_getglobal(L2, name.c_str());
	string getActive = (string)lua_tostring(L2, -1);
	lua_remove(L2, -1);
	name.erase(name.begin(), name.end() - 1);

	name = addActValue + name;
	lua_getglobal(L2, name.c_str());
	int getActValue = (int)lua_tonumber(L2, -1);
	lua_remove(L2, -1);
	name.erase(name.begin(), name.end() - 1);

	name = addBool + name;
	lua_getglobal(L2, name.c_str());
	bool getBool = (bool)lua_toboolean(L2, -1);
	lua_remove(L2, -1);
	
	newProperty = new CProperties(getName, getTitle,getValue, getActive, getActValue, getBool);
	return newProperty;
}

void CLuaScript::saveAchievementValues()
{
	fstream file;
	file.open("LuaScripts//Achievements.lua", std::ofstream::out, std::ostream::trunc);
	file << "TotalAchievements = " << Application::m_cAchievementList.size() << "\n\n";

	for (unsigned i = 0; i < Application::m_cAchievementList.size(); i++)
	{
		int counter = static_cast<int>(i) + 1;
		Application::m_cAchievementList[i]->Save(file,counter);
	}

	file.close();
}

void CLuaScript::saveAchievementPropertiesValues()
{
	fstream file;
	file.open("LuaScripts//AchievementProperties.lua", std::ofstream::out, std::ostream::trunc);
	file << "TotalProperties  = " << Application::m_cPropertyList.size() << "\n\n";

	for (unsigned i = 0; i < Application::m_cPropertyList.size(); i++)
	{
		int counter = static_cast<int>(i) + 1;
		Application::m_cPropertyList[i]->Save(file, counter);
	}

	file.close();
}

void CLuaScript::saveProfileValues()
{
	fstream file;
	file.open("LuaScripts//Profile.lua", std::ofstream::out, std::ostream::trunc);
	file << "HighestLevelUnlocked = " << Application::m_cProfile->GetHighestLevelUnlocked();

	file.close();
}

void CLuaScript::resetAchievementValues()
{
	fstream file;
	file.open("LuaScripts//Achievements.lua", std::ofstream::out, std::ostream::trunc);
	file << "TotalAchievements = " << Application::m_cAchievementList.size() << "\n\n";

	for (unsigned i = 0; i < Application::m_cAchievementList.size(); i++)
	{
		int counter = static_cast<int>(i) + 1;
		Application::m_cAchievementList[i]->Reset(file, counter);
	}

	file.close();
}

void CLuaScript::resetAchievementPropertiesValues()
{
	fstream file;
	file.open("LuaScripts//AchievementProperties.lua", std::ofstream::out, std::ostream::trunc);
	file << "TotalProperties  = " << Application::m_cPropertyList.size() << "\n\n";

	for (unsigned i = 0; i < Application::m_cPropertyList.size(); i++)
	{
		int counter = static_cast<int>(i) + 1;
		Application::m_cPropertyList[i]->Reset(file, counter);
	}

	file.close();
}

void CLuaScript::resetProfileValues()
{
	fstream file;
	file.open("LuaScripts//Profile.lua", std::ofstream::out, std::ostream::trunc);
	file << "HighestLevelUnlocked = 1";

	file.close();
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