


#include <QApplication>
#include <qdeclarative.h>
#include <QDeclarativeView>
#include <QNetworkProxy>



#include "engine.h"



void setApplicationProxy()
{
    QNetworkProxy proxy;
    proxy.setType( QNetworkProxy::HttpProxy );
    proxy.setHostName( "172.16.42.137" );
    proxy.setPort( 8080 );
    QNetworkProxy::setApplicationProxy( proxy );
}



int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );
    app.setApplicationName( "rss player" );

    setApplicationProxy();

    qmlRegisterType<Engine>( "MagazineEngine", 1, 0, "MagazineEngine" );

    QDeclarativeView view;
    view.setSource( QUrl::fromLocalFile( "qml/main.qml" ) );
    view.show();


    return app.exec();
}




