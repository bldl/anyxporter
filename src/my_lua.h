#ifndef __my_lua_h__
#define __my_lua_h__

/*
  Note that any shared library is likely to use 'longjmp' for
  non-local returns, meaning that C++ exceptions thrown from bindings
  would be a problem. Better build our own copy of Lua if we want to
  use throwing bindings. Or if building for a target that does not
  have Lua, of course. Currently we require no custom bindings as we
  only use Lua for pure computation (text processing).

  Examples:

  lua_State* L = luaL_newstate();
  ...
  lua_close(L);

  lua_State* L = my_lua_newstate();
  ...
  lua_close(L);

  auto L = my_lua_newstate_smart();
  ...
  L.reset();

  {
  auto L = my_lua_newstate_smart();
  ...
  }

  // Can load any pure Lua routines from a file.
  // (Packaging and deployment are a hassle then, though.)
  int err = luaL_loadfile(L, filename); // 0 on success
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

  /** Includes all "approved" libraries. Sets panic handler to a
      throwing one, so if using from C code that requires cleanup,
      make sure to protect any subsequent operations that might
      panic. */
  lua_State* my_lua_newstate();

  void my_lua_openlibs(lua_State* L);

#ifdef __cplusplus
} /* extern "C" */
#endif

#ifdef __cplusplus
#include <functional>
#include <memory>

#include "my_auto_ptr.hpp"

class LuaPanic {}; // exception

/** Panic handler function that throws LuaPanic. Of course you can
    only catch such panics in C++ code. */
int atpanic_throw(lua_State* L);

lua_State* my_lua_newstate_throwing();

typedef void (lua_deleter_t)(lua_State*);

typedef auto_ptr_op<lua_State, lua_deleter_t> LuaStateSmart;

LuaStateSmart my_lua_newstate_smart();

void my_lua_newstate_set_smart(LuaStateSmart& ptr);
#endif

#endif /* __my_lua_h__ */
