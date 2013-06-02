#include "my_lua.h"

int atpanic_throw(lua_State *L) {
  (void)L;
  throw LuaPanic();
  return 0;
}

extern "C"
void my_lua_openlibs(lua_State* L) {
  // we edited source of the original to exclude things,
  // but only get those changes if compile from source;
  // could copy/paste modified version over here
  luaL_openlibs(L);
}

extern "C"
lua_State* my_lua_newstate() {
  lua_State* L = luaL_newstate();
  if (L) {
    // luaL_openlibs already may cause a panic, and we must somehow
    // catch it here (rather than 'exit'), but we better not throw
    // from a C function.
    lua_atpanic(L, atpanic_throw);

    try {
      my_lua_openlibs(L);
    } catch (const LuaPanic& ex) {
      lua_close(L);
      return NULL;
    }
  }
  return L;
}

lua_State* my_lua_newstate_throwing() {
  lua_State* L = my_lua_newstate();
  if (!L) throw std::bad_alloc();
  lua_atpanic(L, atpanic_throw);
  try {
    my_lua_openlibs(L);
  } catch (...) {
    lua_close(L);
    throw;
  }
  return L;
}

LuaStateSmart my_lua_newstate_smart() {
  return LuaStateSmart(my_lua_newstate_throwing(), &lua_close);
}

void my_lua_newstate_set_smart(LuaStateSmart& ptr) {
  ptr.set(my_lua_newstate_throwing(), &lua_close);
}

