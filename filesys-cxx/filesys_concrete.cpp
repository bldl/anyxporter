#include "abstract.hpp"

#include "current_config.hrh"

#include <stdexcept>

#include <assert.h>

using std::ios_base;

namespace filesys
{
  void fileOpenTruncate(File& f, Path const& p) {
    f.open(p, ios_base::out | ios_base::trunc | ios_base::binary);
  }

  void fileClose(File& f) {
    f.close();
  }

  void fileAppend(File& f, Bytes const& s) {
    f.write(s.data(), s.size());
  }

  void luaLoadFormatter(LuaState& st) {
    lua_State* const L = st.get();

    int err = luaL_loadfile(L, LUA_USER_SCRIPT_PATHNAME);
    if (err) {
      lua_pop(L, 1); // error string

      err = luaL_loadfile(L, LUA_SCRIPT_PATH LUA_EXPORT_SCRIPT);
      if (err) {
	char const* const cs = lua_tostring(L, -1);
	std::string errString(cs);
	lua_pop(L, 1);
	throw std::runtime_error(errString);
      }
    }

    // Evaluate loaded chunk.
    lua_call(L, 0, 0);
  }

  static void luaGetString(LuaState& st, Bytes& s, char const* n) {
    lua_State* const L = st.get();
    lua_getglobal(L, n);
    if (lua_isnil(L, -1)) {
      s = std::string();
      lua_pop(L, 1);
    } else if (lua_isstring(L, -1)) {
      size_t len;
      char const* const cs = lua_tolstring(L, -1, &len);
      assert(cs && "Lua was supposed to get a string");
      s = std::string(cs, len);
      lua_pop(L, 1);
    } else if (lua_isfunction(L, -1)) {
      lua_call(L, 0, 1); // require exactly one result
      if (!lua_isstring(L, -1))
	throw std::runtime_error
	  ("pre/postamble function must produce a string value");
      size_t len;
      char const* const cs = lua_tolstring(L, -1, &len);
      assert(cs && "Lua was supposed to get a string");
      s = std::string(cs, len);
      lua_pop(L, 1);
    } else {
      throw std::runtime_error
	("pre/postamble must be a string or function");
    }
  }

  void luaPreambleToBytes(LuaState& st, Bytes& s) {
    return luaGetString(st, s, "preamble_string");
  }

  void luaPostambleToBytes(LuaState& st, Bytes& s) {
    return luaGetString(st, s, "postamble_string");
  }

  void luaEntryToBytes(LuaState& st, Bytes& s) {
    lua_State* const L = st.get();
    lua_getglobal(L, "entry_to_string");
    if (lua_isnil(L, -1))
      throw std::runtime_error
      ("'entry_to_string' undefined");
    if (!lua_isfunction(L, -1))
      throw std::runtime_error
      ("'entry_to_string' must be a function");
    lua_insert(L, -2); // swap
    lua_call(L, 1, 1); // require exactly one result
    if (!lua_isstring(L, -1))
      throw std::runtime_error
	("'entry_to_string' must produce a string value");
    size_t len;
    char const* const cs = lua_tolstring(L, -1, &len);
    assert(cs && "Lua was supposed to get a string");
    s = std::string(cs, len);
    lua_pop(L, 1);
  }
}

