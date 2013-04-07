#ifndef __abstract_hpp__
#define __abstract_hpp__

namespace text
{
}

// Implementation specific. Must define concrete datatypes.
#include "datasrc_concrete.hpp"

namespace datasrc
{
  void open(Db& db);
  void close(Db& db);
  void iterator(Db& db, Iter& iter);
  void atEof(const Iter& iter, bool& res);
  void next(Iter& iter, Entry& h);
  //  void pushAsLuaObj(const Entry& e, script::Vm& vm);
  //  void toString(script::Vm& vm, text::String& s);
}

namespace dataout
{
  void fileOpenTruncate();
  void fileCreateTempFile();
  void fileClose();
  void fileAppend();
  void btObexPushFile();
}

#endif /* __abstract_hpp__ */
