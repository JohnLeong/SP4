#include "LuaScript.h"

CLuaScript::CLuaScript(string path)
{
	int s = 0;
	string filepath;

	filepath = "Lua_Script/" + path + ".lua";

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

string CLuaScript::getStringVariable(string name)
{
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
	lua_getglobal(L2, name.c_str());
	if (!lua_isboolean(L2, -1))
	{
		return -1.f;
	}
	float value = (float)lua_toboolean(L2, -1);
	return value;
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