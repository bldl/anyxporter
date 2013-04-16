#include "abstract.hpp"

namespace luastate
{
  void init(LuaState& st) {
    st = my_lua_newstate_smart();
  }
}
