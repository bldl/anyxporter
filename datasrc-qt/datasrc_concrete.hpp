#ifndef __datasrc_concrete_hpp__
#define __datasrc_concrete_hpp__

#include <QContactManager>
#include <QList>
#include <QListIterator>

QT_USE_NAMESPACE
QTM_USE_NAMESPACE

// Qt Mobility based data source.
namespace datasrc {
// xxx this probably should be QScopedPointer
  typedef QContactManager* Db;

  struct Iter {
    QContactManager* db;
    QList<QContactLocalId> lst;
    int nextIx;
  };

  typedef QContact Entry;
}

#endif /* __datasrc_concrete_hpp__ */

