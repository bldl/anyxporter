#include "abstract.hpp"

#include "my_nullptr.hpp"

#include <assert.h>

namespace datasrc
{

  void open(Db& db) {
    db = std::move(unique_ptr<QContactManager>
		   (new QContactManager(nullptr)));
  }

  void close(Db& db) {
    db.reset();
  }

#if 0
  void test(Db& outDb) {
    Db db;
    open(db);
    outDb = std::move(db); // cannot assign w/o move
  }
#endif

  void iterator(Db& db, Iter& iter) {
    iter.db = db.get(); // non-owned pointer
    iter.lst = db->contactIds();
    iter.nextIx = 0;
  }

  void atEof(Iter const& iter, bool& res) {
    res = (iter.nextIx >= iter.lst.size());
  }

  void next(Iter& iter, Entry& h) {
    iter.nextIx += 1;
    const QContactLocalId& id = iter.lst[iter.nextIx];
    h = iter.db->contact(id);
  }

  void entryToLua(Entry const& e, LuaState& st) {
    lua_State* const L = st.get();
    lua_createtable(L, 2, 0);
    /*
    lua_pushstring(L, e.lastName);
    lua_setfield(L, -2, "last_name");
    lua_pushstring(L, e.firstName);
    lua_setfield(L, -2, "first_name");
    */
  }

}

