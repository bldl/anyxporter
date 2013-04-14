#include "abstract.hpp"

#include <nullptr.hpp>
#include <assert.h>

namespace datasrc
{

  void open(Db& db) {
    db = new QContactManager(nullptr);
  }

  void close(Db& db) {
    delete db;
  }

  void iterator(Db& db, Iter& iter) {
    iter.db = db; // non-owned pointer
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

}

