#include "engine.hpp"

#include "abstract.hpp"
#include "current_config.hrh"

#include <iostream>

namespace engine
{
  void exportData() {
    luastate::LuaState L;
    luastate::init(L);
    filesys::luaLoadFormatter(L);
    datasrc::Db db;
    datasrc::open(db);
    datasrc::Iter iter;
    datasrc::iterator(db, iter);
    filesys::File file;
    filesys::Path path = EXPORT_OUTPUT_FILE;
    filesys::fileOpenTruncate(file, path);
    filesys::Bytes b;
    filesys::luaPreambleToBytes(L, b);
    filesys::fileAppend(file, b);
    for (;;) {
      bool r;
      datasrc::atEof(iter, r);
      if (r) break;
      datasrc::Entry e;
      datasrc::next(iter, e);
      //std::cout << "read entry" << std::endl;
      datasrc::entryToLua(db, e, L);
      filesys::luaEntryToBytes(L, b);
      filesys::fileAppend(file, b);
    }
    filesys::luaPostambleToBytes(L, b);
    filesys::fileAppend(file, b);
  }
} // end namespace engine

