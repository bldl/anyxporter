#include "abstract.hpp"

#include <assert.h>

namespace datasrc
{

  void open(Db& db) {}

  void close(Db& db) {}

  void iterator(Db& db, Iter& iter) {}

  void atEof(Iter const& iter, bool& res) { res = true; }

  void next(Iter& iter, Entry& h) {
    assert(false && "iteration past end");
  }

}

