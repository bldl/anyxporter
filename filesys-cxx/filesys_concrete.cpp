#include "abstract.hpp"

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
    int err = luaL_loadfile(L, "lua-src/mock_convert.lua");
    if (err) {
      char const* const cs = lua_tostring(L, -1);
      std::string errString(cs);
      lua_pop(L, 1);
      throw std::runtime_error(errString);
    }
    // Evaluate loaded chunk.
    lua_call(L, 0, 0);
  }

  void luaToBytes(LuaState& st, Bytes& s) {
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

