
#include <QFile>
#include <QFileInfo>
#include <QDir>

#include "engine.h"


Engine::Engine( QDeclarativeItem* parent ) :
    QDeclarativeItem( parent )
{
    iImageName = "diver.bmp";
    iRssName = "rss.xml";
    iNetwork = 0;

    initialize();
}

void Engine::initialize()
{
    iNetwork = new NetworkAccess( this );
    iAudio = new Audio( this );

    connect( iNetwork, SIGNAL(audioSignal()), this, SLOT(audioDownloaded()) );
    connect( iNetwork, SIGNAL(rssSignal()), this, SLOT(rssDownloaded()) );
    connect( iNetwork, SIGNAL(downloadSignal(qint64,qint64)), this, SLOT(downloadSignal(qint64,qint64)) );
}

QString Engine::imageName()
{

    // res = QDir::currentPath() + "/content/" + iImageName;
    return iImageName;
}

QString Engine::url()
{
    return iUrl;
}

void Engine::setUrl( QString aUrl )
{
    iUrl = aUrl;
}

QString Engine::rssName()
{    
    return  QDir::currentPath() + "/download/" + iRssName;
}

unsigned int Engine::bytesTotal()
{
    return iBytesTotal;
}

unsigned int Engine::bytesReceived()
{
    return iBytesReceived;
}

QString Engine::errorText()
{
    return QString();
}

void Engine::updateRssFeed()
{
    qDebug( "Engine::updateRssFeed" );

    iNetwork->fetchRssFile( iUrl );
}

void Engine::play( QString source )
{
    qDebug( "Engine::play" );

    playOrDownload( QUrl( source ) );
}

void Engine::stop()
{
    qDebug( "Engine::stop" );

    iAudio->stop();
}


void Engine::audioDownloaded()
{
    qDebug( "Engine::audioDownloaded" );

    QString fileName = saveFileName( iNetwork->url() );
    QString audioFile = QDir::currentPath() + "/download/" + fileName;
    QByteArray data = iNetwork->ioDevice().readAll();

    saveToDisk( audioFile, data );
    iAudio->play( audioFile );
}

void Engine::rssDownloaded()
{
    qDebug( "Engine::rssDownloaded" );

    QByteArray data = iNetwork->ioDevice().readAll();
    saveToDisk( rssName(), data );

    emit rssChanged();
}

void Engine::downloadSignal( qint64 bytesReceived, qint64 bytesTotal )
{
    qDebug("Engine::downloadSignal");

    unsigned int received = bytesReceived / 100;
    unsigned int total = bytesTotal / 100;

    if ( total != iBytesTotal )
    {
        iBytesTotal = total;
        emit bytesTotalChanged();
    }

    if ( received != iBytesReceived )
    {
        iBytesReceived = received;
        emit bytesReceivedChanged();
    }
}


void Engine::saveToDisk( QString fileName, QByteArray data )
{
    qDebug( "Engine::saveToDisk" );

    QFile file( fileName );

    if ( ! file.open( QIODevice::WriteOnly ) )
    {
        qDebug( "Could not open for writing: %s", qPrintable( file.errorString() ) );
    }
    else
    {
        file.write( data );
        file.close();
    }
}

QString Engine::saveFileName( const QUrl &url )
{
    qDebug( "Engine::saveFileName" );

    QString path = url.path();
    QString basename = QFileInfo( path ).fileName();

    if ( basename.isEmpty() )
    {
        basename = "download";
    }

    return basename;
}

QString Engine::audioFileExists( const QUrl &url )
{
    qDebug( "Engine::audioFileExists" );

    QString fileName = saveFileName( url );
    QString file = QDir::currentPath() + "/download/" + fileName;
    return QFile::exists( file ) ? file : QString();
}

void Engine::playOrDownload( const QUrl &url )
{
    qDebug( "Engine::playOrDownload" );

    QString audioFile = audioFileExists( url );
    if ( audioFile.isNull() )
    {
        iBytesReceived = 0;
        iBytesTotal = 0;
        iNetwork->fetchAudioFile( url );
    }
    else
    {
        iAudio->play( audioFile );
    }
}


