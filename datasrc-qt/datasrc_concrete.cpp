#include "abstract.hpp"

#include <nullptr.hpp>
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

}

