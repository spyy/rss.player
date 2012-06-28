#ifndef ENGINE_H
#define ENGINE_H

#include <QDeclarativeItem>


#include "networkaccess.h"
#include "audio.h"




class Engine : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY( QString imageName READ imageName NOTIFY imageNameChanged )
    Q_PROPERTY( QString url READ url WRITE setUrl NOTIFY urlChanged )
    Q_PROPERTY( QString rssName READ rssName NOTIFY rssChanged )
    Q_PROPERTY( unsigned int bytesTotal READ bytesTotal NOTIFY bytesTotalChanged )
    Q_PROPERTY( unsigned int bytesReceived READ bytesReceived NOTIFY bytesReceivedChanged )
    Q_PROPERTY( QString errorText READ errorText NOTIFY errorTextChanged )

public:
    explicit Engine( QDeclarativeItem* parent = 0 );
    void initialize();

public: // property methods
    QString imageName();
    QString url();
    void setUrl( QString aUrl );
    QString rssName();
    unsigned int bytesTotal();
    unsigned int bytesReceived();
    QString errorText();

public: // invokables
    Q_INVOKABLE void updateRssFeed();
    Q_INVOKABLE void play( QString source );
    Q_INVOKABLE void stop();

signals:
    void imageNameChanged();
    void urlChanged();
    void rssChanged();
    void bytesTotalChanged();
    void bytesReceivedChanged();
    void errorTextChanged();

public slots: // NetworkAccess
    void audioDownloaded();
    void rssDownloaded();
    void downloadSignal( qint64 bytesReceived, qint64 bytesTotal );

private:
    void saveToDisk( QString fileName, QByteArray data );
    QString saveFileName( const QUrl &url );
    QString audioFileExists( const QUrl &url );
    void playOrDownload( const QUrl &url );


private:
    QString iImageName;
    QString iUrl;
    QString iRssName;
    QString iCurrentAudio;

    NetworkAccess* iNetwork;
    Audio* iAudio;

    unsigned int iBytesReceived;
    unsigned int iBytesTotal;

};

#endif // ENGINE_H
