#include "srcdsControl.h"
#include <lua.hpp>
#include <iostream>
using namespace std;

// https://gist.github.com/Youka/2a6e69584672f7cb0331
// https://forums.alliedmods.net/showthread.php?t=287902

#define LUA_SRCDSCONTROL "SRCDSControl"

// meta

static int srcdscontrol_new(lua_State* L) {
	*reinterpret_cast<SRCDSControl**>(lua_newuserdata(L, sizeof(SRCDSControl*))) = new SRCDSControl();
	luaL_setmetatable(L, LUA_SRCDSCONTROL);
	return 1;
}

static int srcdscontrol_gc(lua_State* L) {
	delete* reinterpret_cast<SRCDSControl**>(lua_touserdata(L, 1));
	return 0;
}

// methods

static int srcdscontrol_start(lua_State* L) {
	(*reinterpret_cast<SRCDSControl**>(luaL_checkudata(L, 1, LUA_SRCDSCONTROL)))->Start(luaL_checkstring(L, 2), luaL_checkstring(L, 3));
	return 0;
}

static int srcdscontrol_read(lua_State* L) {
	lua_pushstring(L, (*reinterpret_cast<SRCDSControl**>(luaL_checkudata(L, 1, LUA_SRCDSCONTROL)))->ReadText(luaL_checkinteger(L, 2), luaL_checkinteger(L, 2)).c_str());
	return 1;
}

static int srcdscontrol_write(lua_State* L) {
	lua_pushboolean(L, (*reinterpret_cast<SRCDSControl**>(luaL_checkudata(L, 1, LUA_SRCDSCONTROL)))->WriteText(luaL_checkstring(L, 2)));
	return 1;
}

static void register_srcdscontrol(lua_State* L) {
	lua_register(L, LUA_SRCDSCONTROL, srcdscontrol_new);
	luaL_newmetatable(L, LUA_SRCDSCONTROL);
	lua_pushcfunction(L, srcdscontrol_gc); lua_setfield(L, -2, "__gc");
	lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
	lua_pushcfunction(L, srcdscontrol_start); lua_setfield(L, -2, "start");
	lua_pushcfunction(L, srcdscontrol_read); lua_setfield(L, -2, "read");
	lua_pushcfunction(L, srcdscontrol_write); lua_setfield(L, -2, "write");
	lua_pop(L, 1);
}