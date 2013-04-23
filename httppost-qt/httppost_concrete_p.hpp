#ifndef __httppost_concrete_p_hpp__
#define __httppost_concrete_p_hpp__

#include "httppost_concrete.hpp"

#include <QtCore/qglobal.h> // for QT_USE_NAMESPACE

QT_USE_NAMESPACE

#include <QEventLoop>
#include <QNetworkReply>
#include <QObject>

/* Could create a more generic handler with lambdas,
   but 'moc' cannot cope with template params, so
   must explicitly specialize for QNetworkReply*
   in C++ source code. */
class LoopQuitter : public QObject
{
  Q_OBJECT
private:
  QEventLoop& m_loop;
public:
  LoopQuitter(QEventLoop& loop) : m_loop(loop) {}
public slots:
  void quit(QNetworkReply*) { m_loop.exit(); }
};

#endif /* __httppost_concrete_p_hpp__ */

