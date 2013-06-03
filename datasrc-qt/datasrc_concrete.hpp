#ifndef __datasrc_concrete_hpp__
#define __datasrc_concrete_hpp__

#include "my_smart_ptr.hpp"

#include <QContactManager>
#include <QList>
#include <QListIterator>

QT_USE_NAMESPACE
QTM_USE_NAMESPACE

// Qt Mobility based data source.
namespace datasrc {
  /*
    A QContactManager is not copyable due to its IO nature. What this
    means for Magnolia is perhaps that any ADT implementations that
    are non-copyable must be annotated as such. The compiler must then
    reorganize code in function bodies to avoid temporary copies of
    such values. Passing in such a value as an 'obs' argument is okay,
    as that does not cause ownership changes. Returning such a value
    by assigning to an 'out' param is okay, provided that std::move is
    used, and that afterwards only the param is referred to, and not
    any moved local variable. A unique_ptr is consistent with these
    semantics, and does ensure cleanup of locals that are not moved
    out or explicitly deleted.
  */
  typedef UNIQUE_PTR<QContactManager> Db;

  struct Iter {
    QContactManager* db;
    QList<QContactLocalId> lst;
    int nextIx;
  };

  typedef QContact Entry;
}

#endif /* __datasrc_concrete_hpp__ */

