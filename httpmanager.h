#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H


#include "global.h"
#include "qjsonobject.h"
#include "singleton.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <memory>
#include <share.h>

//CRTP技术
class HttpManager:public QObject,public Singleton<HttpManager>,public std::enable_shared_from_this<HttpManager>
{
    Q_OBJECT
public:
    ~HttpManager();
private:
    friend class Singleton<HttpManager>;
    HttpManager();
    QNetworkAccessManager _manager;
    void PostHttpRequest(QUrl url,QJsonObject json, RequestId request_id, Modules modules);

private slots:
    void slots_http_finish(RequestId id, QString res, ErrorCodes err, Modules modules);
signals:
    void signal_http_finish(RequestId id, QString res, ErrorCodes err, Modules modules);
    void signal_module_finish(RequestId id, QString res, ErrorCodes err);
};

#endif // HTTPMANAGER_H
