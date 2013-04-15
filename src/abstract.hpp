#ifndef __abstract_hpp__
#define __abstract_hpp__

/* Implementation specific. 
   Must define concrete datatypes.
*/
#include "datasrc_concrete.hpp"
#include "filesys_concrete.hpp"
#include "my_lua.h"

// Lua stack objects are used as the common IR. Hence this definition
// is the same for all our concepts.
typedef LuaStateSmart LuaState;

namespace datasrc
{
  void open(Db& db);
  void close(Db& db);
  void iterator(Db& db, Iter& iter);
  void atEof(Iter const& iter, bool& res);
  void next(Iter& iter, Entry& h);

  // Data source and entry format tend to be coupled,
  // so we have this as part of the concept.
  void entryToLua(Entry const& e, LuaState& st);
}

namespace filesys
{
  void fileOpenTruncate(File& f, Path const& p);
  void fileCreateTempFile(File& f);
  void fileClose(File& f);
  void fileAppend(File& f, Bytes const& s);
}

/*
// We need temp file support for this and other output options. Must fileClose before sending, but closing must not delete, dtor should do that.
namespace btobexpush
{
  void btObexPushFile(Path const& f);
}
*/

#endif /* __abstract_hpp__ */
