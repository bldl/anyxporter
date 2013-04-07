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
  void makeSeq(Db& db, Seq& seq);
  void isEmpty(const Seq& seq, bool& res);
  void head(const Seq& seq, Entry& h);
  void tail(const Seq& seq, Seq& t);
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
