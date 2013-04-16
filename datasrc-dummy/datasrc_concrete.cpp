#include "abstract.hpp"

#include <assert.h>

// A dummy data source.
namespace datasrc
{

  void open(Db& /*db*/) {}

  void close(Db& /*db*/) {}

  void iterator(Db& /*db*/, Iter& /*iter*/) {}

  void atEof(Iter const& /*iter*/, bool& res) { res = true; }

  void next(Iter& /*iter*/, Entry& /*h*/) {
    assert(false && "iteration past end");
  }

  void entryToLua(Db const& /*db*/, Entry const& e, LuaState& st) {
    lua_State* const L = st.get();
    lua_createtable(L, 0, 0);
  }

}

