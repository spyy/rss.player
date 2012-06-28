

#include <QNetworkRequest>
#include <QUrl>


#include "networkaccess.h"



NetworkAccess::NetworkAccess( QObject* parent ) :
    QObject( parent )

{    

    iManager = new QNetworkAccessManager( this );

    //setProxy();

    iReply = 0;

    iRequest = new QNetworkRequest;
    iRequest->setRawHeader( "User-Agent", "Spy 1.0" );
}

NetworkAccess::~NetworkAccess()
{
    delete iProxy;
    delete iRequest;
}

void NetworkAccess::fetchAudioFile( QUrl url )
{
    qDebug( "NetworkAccess::fetchAudioFile" );

    iRequest->setUrl( url );
    iReply = iManager->get( *iRequest );

    connect( iReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    connect( iReply, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
    connect( iReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));    
    connect( iReply, SIGNAL(finished()), this, SLOT(audioFinished()));    
}

void NetworkAccess::fetchRssFile( QUrl url )
{
    qDebug( "NetworkAccess::fetchRssFile" );
    qDebug( url.toString().toAscii() );

    iRequest->setUrl( url );
    iReply = iManager->get( *iRequest );

    connect( iReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    connect( iReply, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
    connect( iReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));        
    connect( iReply, SIGNAL(finished()), this, SLOT(rssFinished()));
}

QIODevice& NetworkAccess::ioDevice()
{
    return *iReply;
}

QUrl NetworkAccess::url()
{
    return iRequest->url();
}

void NetworkAccess::setProxy()
{
    iProxy = new QNetworkProxy;
    iProxy->setType( QNetworkProxy::HttpProxy );
    iProxy->setHostName( "172.16.42.137" );
    iProxy->setPort( 8080 );
    iManager->setProxy( *iProxy );
}

void NetworkAccess::rssFinished()
{
    qDebug( "NetworkAccess::rssFinished" );

    QUrl url = iReply->url();
    if ( iReply->error() )
    {
        qDebug("Download of %s failed: %s\n",url.toEncoded().constData(),qPrintable(iReply->errorString()));
    }
    else
    {
        emit rssSignal();
    }

    iReply->deleteLater();
}

void NetworkAccess::audioFinished()
{
    qDebug( "NetworkAccess::audioFinished" );

    QUrl url = iReply->url();
    if ( iReply->error() )
    {
        qDebug("Download of %s failed: %s\n",url.toEncoded().constData(),qPrintable(iReply->errorString()));
    }
    else
    {
        emit audioSignal();
    }

    iReply->deleteLater();
}

void NetworkAccess::downloadProgress( qint64 bytesReceived, qint64 bytesTotal )
{
    qDebug( "NetworkAccess::downloadProgress" );

    emit downloadSignal( bytesReceived, bytesTotal );
}

void NetworkAccess::error( QNetworkReply::NetworkError code )
{
    qDebug( "NetworkAccess::error: %d", code );
    emit errorSignal();
}

void NetworkAccess::metaDataChanged()
{
    qDebug( "NetworkAccess::metaDataChanged" );

    const QList<QNetworkReply::RawHeaderPair> &pairs = iReply->rawHeaderPairs();
    for ( int i=0; i < pairs.count(); i++ )
    {
        QByteArray first = pairs.at(i).first;
        QByteArray second = pairs.at(i).second;
        //qDebug( "%s : %s", first.data(), second.data() );
    }
}




