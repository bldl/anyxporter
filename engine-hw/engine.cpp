#include "engine.hpp"

#include "abstract.hpp"

#include <iostream>

namespace engine
{
  void exportData() {
    auto L = my_lua_newstate_smart();
    datasrc::Db db;
    datasrc::open(db);
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
      datasrc::entryToLua(e, L);
      filesys::Bytes b = ""; // xxx
      filesys::NumBytes n = 0; // xxx
      filesys::fileAppend(file, b, n);
    }
  }
} // end namespace engine

