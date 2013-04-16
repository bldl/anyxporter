#include "abstract.hpp"

#include "my_nullptr.hpp"

#include <QDebug>
#include <assert.h>

// Qt Mobility based data source.
namespace datasrc
{

  void open(Db& db) {
    db = std::move(unique_ptr<QContactManager>
		   (new QContactManager(nullptr)));
    #ifndef QT_NO_DEBUG
    // informative to view 'x' in debugger
    auto x = db->detailDefinitions();
    //qDebug() << x;
    #endif
  }

  void close(Db& db) {
    db.reset();
  }

#if 0
  void test(Db& outDb) {
    Db db;
    open(db);
    outDb = std::move(db); // cannot assign w/o move
  }
#endif

  void iterator(Db& db, Iter& iter) {
    iter.db = db.get(); // non-owned pointer
    iter.lst = db->contactIds();
    iter.nextIx = 0;
  }

  void atEof(Iter const& iter, bool& res) {
    res = (iter.nextIx >= iter.lst.size());
  }

  void next(Iter& iter, Entry& h) {
    const QContactLocalId& id = iter.lst[iter.nextIx];
    h = iter.db->contact(id);
    iter.nextIx += 1;
  }

  void entryToLua(Db const& /*db*/, Entry const& e, LuaState& st) {
    lua_State* const L = st.get();
    QList<QContactDetail> ds = e.details();
    lua_createtable(L, 0, ds.size());
    for (QList<QContactDetail>::const_iterator it = ds.constBegin(); 
	 it != ds.constEnd();
	 ++it) {
      QContactDetail const& d = *it;
      QString const n = d.definitionName();
      QByteArray asciiKey = n.toAscii();
      char const* const key = asciiKey.data();
      QByteArray uniValue = n.toUtf8(); //xxx want value actually
      char const* const value = uniValue.data();
      lua_pushstring(L, value);
      lua_setfield(L, -2, key);
    }

    /*
      // Shows possible details, not entry details.
    lua_State* const L = st.get();
    lua_createtable(L, 0, defs.size());
    QMap<QString, QContactDetailDefinition> defs = db->detailDefinitions();
    QMap<QString, QContactDetailDefinition>::const_iterator it = 
      defs.constBegin();
    while (it != defs.constEnd()) {
      QByteArray asciiKey = it.key().toAscii();
      char const* const key = asciiKey.data();
      QByteArray uniValue = it.key().toUtf8(); //xxx want value actually
      char const* const value = uniValue.data();
      lua_pushstring(L, value);
      lua_setfield(L, -2, key);
      ++it;
    }
    */
  }

}

