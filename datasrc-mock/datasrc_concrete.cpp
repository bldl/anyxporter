#include "abstract.hpp"

#include "my_nullptr.hpp"

#include <assert.h>

// A mock data source.
namespace datasrc
{

  static const Entry data[] = {
    {"Fisk", "Ben"},
    {"Murdock", "Wilson"},
    {"Natchios", "Matthew"},
    {"Nelson", "Elektra"},
    {"Urich", "Franklin"},
    {nullptr, nullptr}
  };

  void open(Db& /*db*/) {}

  void close(Db& /*db*/) {}

  void iterator(Db& /*db*/, Iter& iter) {
    iter = 0;
  }

  void atEof(Iter const& iter, bool& res) { 
    res = (data[iter].lastName == nullptr);
  }

  void next(Iter& iter, Entry& h) {
    assert(data[iter].lastName && "iteration past end");
    h = data[iter];
    iter++;
  }

  void entryToLua(Entry const& e, LuaState& st) {
    lua_State* const L = st.get();
    lua_createtable(L, 2, 0);
    lua_pushstring(L, e.lastName);
    lua_setfield(L, -2, "last_name");
    lua_pushstring(L, e.firstName);
    lua_setfield(L, -2, "first_name");
  }

}

