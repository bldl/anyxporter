#ifndef __abstract_hpp__
#define __abstract_hpp__

/* Implementation specific. 
   Must define concrete datatypes.
*/
#include "datasrc_concrete.hpp"
#include "filesys_concrete.hpp"
#include "my_lua.h"

namespace luastate
{
  typedef LuaStateSmart LuaState;

  void init(LuaState& st);
}

namespace datasrc
{
  typedef luastate::LuaState LuaState;

  void open(Db& db);
  void close(Db& db);
  void iterator(Db& db, Iter& iter);
  void atEof(Iter const& iter, bool& res);
  void next(Iter& iter, Entry& h);

  // Data source and entry format tend to be coupled,
  // so we have this as part of the concept.
  void entryToLua(Db const& db, Entry const& e, LuaState& st);
}

namespace filesys
{
  typedef luastate::LuaState LuaState;

  void luaLoadFormatter(LuaState& st);
  void luaPreambleToBytes(LuaState& st, Bytes& s);
  void luaPostambleToBytes(LuaState& st, Bytes& s);
  void luaEntryToBytes(LuaState& st, Bytes& s);
  void fileOpenTruncate(File& f, Path const& p);
  //void fileCreateTempFile(File& f);
  void fileClose(File& f);
  void fileAppend(File& f, Bytes const& s);
}

#endif /* __abstract_hpp__ */
