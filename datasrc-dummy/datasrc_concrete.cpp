#include "abstract.hpp"

namespace datasrc
{

  void open(Db& db) {}

  void close(Db& db) {}

  void makeSeq(Db& db, Seq& seq) {}

  void isEmpty(const Seq& seq, bool& r) { r = true; }

  void head(const Seq& seq, Entry& h) {}

  void tail(const Seq& seq, Seq& t) {}

}

