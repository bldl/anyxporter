#include "engine.hpp"

#include "abstract.hpp"

using datasrc::Db;
using datasrc::Iter;
using datasrc::Entry;

namespace engine
{
  void exportData() {
    Db db;
    datasrc::open(db); // xxx does magnolia expect a dtor for a type?
    Iter iter;
    datasrc::iterator(db, iter);
    for (;;) {
      bool r;
      datasrc::atEof(iter, r);
      if (r) break;
      Entry e;
      datasrc::next(iter, e);
    }
    datasrc::close(db); // xxx must ensure this gets called, or if we have a dtor do not need this at all
  }
} // end namespace engine

