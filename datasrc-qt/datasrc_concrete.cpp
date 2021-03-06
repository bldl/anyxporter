#include "abstract.hpp"

#include "my_nullptr.hpp"

#include <QDebug>
//#include <QImage> // requires QtGui library

#include <assert.h>
#include <stdexcept>

// Qt Mobility based data source.
namespace datasrc
{

  void open(Db& db) {
    db.reset(new QContactManager(nullptr));
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

  static void pushStringList(lua_State* const L, QStringList const& ss)
  {
    lua_createtable(L, ss.size(), 0);
    int slix = 1;
    for (QList<QString>::const_iterator sit = ss.constBegin();
	 sit != ss.constEnd(); ++sit, ++slix) {
      QString const& s = *sit;
      lua_pushstring(L, s.toUtf8().data());
      lua_rawseti(L, -2, slix);
    }
  }

  void entryToLua(Db const& /*db*/, Entry const& e, LuaState& st) {
#if 1
    lua_State* const L = st.get();
    QList<QContactDetail> ds = e.details();
    lua_createtable(L, ds.size(), 0);
    int dlix = 1; // syntax does not allow this, too, in 'for' init
    for (QList<QContactDetail>::const_iterator dit = ds.constBegin(); 
	 dit != ds.constEnd(); ++dit, ++dlix) {
      QContactDetail const& d = *dit;
      if (d.isEmpty())
	continue;
      { // QMap -> table, and push
	QMap<QString, QVariant> const vm = d.variantValues();
	lua_createtable(L, 0, vm.size());
	for (QMap<QString, QVariant>::const_iterator vit = 
	       vm.constBegin();
	     vit != vm.constEnd(); ++vit) {
	  QString vn = vit.key(); // always in Latin1 range
	  QVariant vv = vit.value();
	  if (vv.canConvert<QString>()) {
	    QString const s = vv.toString();
	    lua_pushstring(L, s.toUtf8().data());
	    lua_setfield(L, -2, vn.toUtf8().data());
	  } else if (vv.canConvert<QStringList>()) {
	    QStringList const ss = vv.toStringList();
	    pushStringList(L, ss); // as new array of string
	    lua_setfield(L, -2, vn.toUtf8().data());
	  } else if (vv.type() == QVariant::Image) {
	    lua_pushstring(L, "[QImage]");
	    /*
	    // We could probably save any images.
	    QImage const img = vv.value<QImage>(QVariant::Image);
	    lua_pushstring(L, img.text().toUtf8().data());
	    */
	    lua_setfield(L, -2, vn.toUtf8().data());
	  } else {
	    throw std::runtime_error
	      (std::string("Unsupported type: ") + vv.typeName());
	  }
	}
	// definitionName
	QString const dn = d.definitionName();
	lua_pushstring(L, dn.toUtf8().data());
	lua_setfield(L, -2, "DefinitionName");
	// contexts
	QStringList const ctxLst = d.contexts();
	if (!ctxLst.isEmpty()) {
	  //qDebug() << ctxLst; // none in Qt Simulator mock data
	  pushStringList(L, ctxLst);
	  lua_setfield(L, -2, "Contexts");
	}
      }
      lua_rawseti(L, -2, dlix);
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

