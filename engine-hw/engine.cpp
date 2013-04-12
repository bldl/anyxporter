#include "engine.hpp"

#include "abstract.hpp"

#include <iostream>

namespace engine
{
  void exportData() {
    datasrc::Db db;
    datasrc::open(db); // xxx does magnolia expect a dtor for a type?
    datasrc::Iter iter;
    datasrc::iterator(db, iter);
    dataout::File file;
    dataout::Path path = "outfile";
    dataout::fileOpenTruncate(file, path);
    for (;;) {
      bool r;
      datasrc::atEof(iter, r);
      if (r) break;
      datasrc::Entry e;
      datasrc::next(iter, e);
      std::cout << "read entry" << std::endl;
      dataout::Bytes b = ""; // xxx
      dataout::NumBytes n = 0; // xxx
      dataout::fileAppend(file, b, n);
    }
    dataout::fileClose(file);
    datasrc::close(db); // xxx must ensure this gets called, or if we have a dtor do not need this at all
  }
} // end namespace engine

