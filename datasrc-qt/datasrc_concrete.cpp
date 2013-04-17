#include "abstract.hpp"

#include "my_nullptr.hpp"

#include <QDebug>

#include <assert.h>
#include <stdexcept>

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
#if 1
    lua_State* const L = st.get();
    QList<QContactDetail> ds = e.details();
    lua_createtable(L, 0, ds.size());
    for (QList<QContactDetail>::const_iterator dit = ds.constBegin(); 
	 dit != ds.constEnd(); ++dit) {
      QContactDetail const& d = *dit;
      if (d.isEmpty())
	continue;
      QMap<QString, QVariant> const vm = d.variantValues();
      lua_createtable(L, 0, vm.size());
      for (QMap<QString, QVariant>::const_iterator vit = vm.constBegin();
	   vit != vm.constEnd(); ++vit) {
	QString vn = vit.key(); // always in Latin1 range
	QVariant vv = vit.value();
	if (vv.canConvert<QString>()) {
	  QString const s = vv.toString();
	  lua_pushstring(L, s.toUtf8().data());
	  lua_setfield(L, -2, vn.toUtf8().data());
	} else {
	  throw std::runtime_error
	    (std::string("Unsupported type: ") + vv.typeName());
	}
      }
      QString const dn = d.definitionName();
      lua_setfield(L, -2, dn.toUtf8().data());
    }
#elif 0
    // Shows entry definition names, not actual data.
    lua_State* const L = st.get();
    QList<QContactDetail> ds = e.details();
    lua_createtable(L, 0, ds.size());
    for (QList<QContactDetail>::const_iterator it = ds.constBegin(); 
	 it != ds.constEnd(); ++it) {
      QContactDetail const& d = *it;
      QString const n = d.definitionName();
      QByteArray baKey = n.toUtf8(); // always in Latin1 range
      char const* const key = baKey.data();
      QByteArray baValue = n.toUtf8(); //xxx want value actually
      char const* const value = baValue.data();
      lua_pushstring(L, value);
      lua_setfield(L, -2, key);
    }
#else
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
#endif
  }

}

