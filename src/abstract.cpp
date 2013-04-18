#include "abstract.hpp"

#include "my_platform.h"

namespace luastate
{
  void init(LuaState& st) {
    // GCC 4.4.5 silently fails to assign if we try to assign,
    // causing a std::bad_function_call at runtime.
    // Let us explicitly swap.
    // (Recent versions are okay with assign, too, realizing it
    // is a move, but we can be explicit.)
#if (defined(__GNUC__) && (GCC_VERSION <= 40405))
    st.swap(my_lua_newstate_smart());
#else
    st = std::move(my_lua_newstate_smart());
#endif
  }
}
