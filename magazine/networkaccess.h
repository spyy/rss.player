#ifndef NETWORKACCESS_H
#define NETWORKACCESS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkProxy>


class QUrl;
class QIODevice;


class NetworkAccess : public QObject
{
    Q_OBJECT
public:
    explicit NetworkAccess( QObject *parent = 0 );
    ~NetworkAccess();

public:
    void fetchAudioFile( QUrl url );
    void fetchRssFile( QUrl url );
    QIODevice& ioDevice();
    QUrl url();

private:
    void setProxy();

signals:
   void audioSignal();
   void rssSignal();
   void downloadSignal( qint64 bytesReceived, qint64 bytesTotal );
   void errorSignal();

public slots: // QNetworkReply
    void  rssFinished();
    void  audioFinished();
    void  downloadProgress( qint64 bytesReceived, qint64 bytesTotal );
    void  error( QNetworkReply::NetworkError code );
    void  metaDataChanged();    

private: // data
    QNetworkReply* iReply;
    QNetworkAccessManager* iManager;
    QNetworkProxy* iProxy;
    QNetworkRequest* iRequest;
};

#endif // NETWORKACCESS_H
