#include "my_lua.h"

int atpanic_throw(lua_State *L) {
  (void)L;
  throw LuaPanic();
  return 0;
}

// xxx for production builds should be more selective, can say edit source to exclude things
extern "C"
void my_lua_openlibs(lua_State* L) {
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

std::unique_ptr<lua_State, lua_deleter_t> my_lua_newstate_smart() {
  std::unique_ptr<lua_State, lua_deleter_t> 
    p(my_lua_newstate_throwing(), lua_close);
  return p;
}
