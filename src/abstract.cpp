#include "abstract.hpp"

namespace luastate
{
  void init(LuaState& st) {
    // GCC 4.4.5 silently fails to assign if we try to assign.
    // Let us explicitly swap.
    // (Recent versions are okay with assign, too, realizing it
    // is a move.)
    st.swap(my_lua_newstate_smart());
  }
}
