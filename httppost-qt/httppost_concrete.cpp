#include "httppost_concrete_p.hpp"

#include <stdlib.h>
#include <string.h>

#include <QDebug>
#include <QFile>
#include <QHttpPart>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>

static QVariant qVarUtf8(char const* const s) {
  return QVariant(QString::fromUtf8(s));
}

namespace httppost
{
  void uploadFile(Path const& p) {
    char* const enabled = getenv("DO_HTTP_POST");
    if (!enabled || (strcmp(enabled, "true") != 0))
      return; // no POSTing requested
    
    QHttpPart filePart; // requires Qt 4.8-up
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, 
		       qVarUtf8("application/octet-stream"));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, 
		       qVarUtf8("form-data; name=\"data\"; filename=\"outfile\""));
    // Content-Transfer-Encoding: binary (not a Qt "known header")
    QFile file(QString::fromUtf8(p));
    file.open(QIODevice::ReadOnly);
    filePart.setBodyDevice(&file);

    QHttpMultiPart multiPart(QHttpMultiPart::FormDataType);
    multiPart.append(filePart);

    QUrl url(QString::fromAscii("http://httpbin.org/post"));
    QNetworkRequest request(url);
    QNetworkAccessManager manager;

    QEventLoop eventLoop;
    LoopQuitter loopQuitter(eventLoop);
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)),
		     &loopQuitter, SLOT(quit(QNetworkReply*)));
    QNetworkReply *reply = manager.post(request, &multiPart);
    reply->setParent(&manager);
    // Calling 'exit' on the 'eventLoop' will have it return.
    // There is also a 'quit' slot on 'eventLoop', which could be signaled instead.
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    qDebug() << reply->error();
    qDebug() << reply->rawHeaderPairs();
  }
}
