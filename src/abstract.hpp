#ifndef __abstract_hpp__
#define __abstract_hpp__

/* Implementation specific. 
   Must define concrete datatypes.
*/
#include "datasrc_concrete.hpp"
#include "filesys_concrete.hpp"

namespace datasrc
{
  void open(Db& db);
  void close(Db& db);
  void iterator(Db& db, Iter& iter);
  void atEof(Iter const& iter, bool& res);
  void next(Iter& iter, Entry& h);
  //  void pushAsLuaObj(const Entry& e, script::Vm& vm);
  //  void toString(script::Vm& vm, text::String& s);
}

namespace dataout
{
  void fileOpenTruncate(File& f, Path const& p);
  void fileCreateTempFile(File& f);
  void fileClose(File& f);
  void fileAppend(File& f, Bytes const& s, NumBytes const& n);
  void btObexPushFile(File& f);
}

#endif /* __abstract_hpp__ */
