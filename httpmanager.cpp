#include "httpmanager.h"
#include "global.h"
#include "qnetworkaccessmanager.h"
#include "qnetworkreply.h"
#include "qnetworkrequest.h"

HttpManager::~HttpManager()
{

}

HttpManager::HttpManager()
{
    connect(this,&HttpManager::signal_http_finish,this,&HttpManager::slots_http_finish);
}

void HttpManager::PostHttpRequest(QUrl url, QJsonObject json, RequestId request_id, Modules modules)
{
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(data.length()));

    auto self  = shared_from_this();
    QNetworkReply *reply = _manager.post(request,data);
    connect(reply,&QNetworkReply::finished,[self,reply,request_id,modules](){
        //处理错误情况
        if(reply->error() != QNetworkReply::NoError){
            qDebug() << reply->errorString();
            //发送信号通知完成
            emit self->signal_http_finish(request_id,"",ErrorCodes::ERR_NETWORK,modules);
            reply->deleteLater();
            return;
        }

        //无错误
        QString res = reply->readAll();
        //发送信号通知完成
        emit self->signal_http_finish(request_id,res,ErrorCodes::SUCCESS,modules);
        reply->deleteLater();
        return;
    });

}

void HttpManager::slots_http_finish(RequestId id, QString res, ErrorCodes err, Modules modules)
{
    if(modules == Modules::REGISTERMOD)
    {
        //发送信号通知指定模块http的响应结束了
        emit signal_http_finish(id,res,err,modules);
    }
}
