#include "engine.hpp"

#include "abstract.hpp"

using datasrc::Db;
using datasrc::Seq;
using datasrc::Entry;

namespace engine
{
  void exportData() {
    Db db;
    datasrc::open(db); // xxx does magnolia expect a dtor for a type?
    Seq seq;
    datasrc::makeSeq(db, seq);
    for (;;) {
      bool r;
      datasrc::isEmpty(seq, r);
      if (r) break;
      Entry e;
      datasrc::head(seq, e);
      Seq tmp = seq;
      datasrc::tail(tmp, seq);
    }
    datasrc::close(db); // xxx must ensure this gets called, or if we have a dtor do not need this at all
  }
} // end namespace engine

