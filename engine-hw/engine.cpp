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
    filesys::File file;
    filesys::Path path = "outfile";
    filesys::fileOpenTruncate(file, path);
    for (;;) {
      bool r;
      datasrc::atEof(iter, r);
      if (r) break;
      datasrc::Entry e;
      datasrc::next(iter, e);
      std::cout << "read entry" << std::endl;
      filesys::Bytes b = ""; // xxx
      filesys::NumBytes n = 0; // xxx
      filesys::fileAppend(file, b, n);
    }
    filesys::fileClose(file);
    datasrc::close(db); // xxx must ensure this gets called, or if we have a dtor do not need this at all
  }
} // end namespace engine

