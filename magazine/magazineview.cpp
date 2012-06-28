
#include <QDeclarativeContext>


#include "MagazineView.h"








MagazineView::MagazineView( Engine& engine ) :
        iEngine( engine )
{    
}


MagazineView::~MagazineView()
{
}


void MagazineView::initialize()
{

    iKustomi = new Kustomi;
    iKustomi->m_url = iEngine.url();
    iKustomi->m_image = iEngine.imageFile();

    //rootContext()->setContextProperty( "exposedImageName", iEngine.imageFile() );
    //rootContext()->setContextProperty( "exposedUrl", iEngine.url() );


    rootContext()->setContextProperty( "kustomi", iKustomi );


    setSource( QUrl::fromLocalFile( "magazineView.qml" ) );


    QObject* root = reinterpret_cast<QObject*>( rootObject() );
    QObject::connect( root, SIGNAL( clicked() ), this, SLOT( onClicked() ) );
}


void MagazineView::onClicked()
{
    qDebug( "MagazineView::onClicked exposedUrl" );
    qDebug( iKustomi->url().toAscii() );
    //qDebug( rootContext()->contextProperty( "exposedUrl" ).toString().toAscii() );
    qDebug( "MagazineView::onClicked url" );
    //qDebug( rootContext()->contextProperty( "url" ).toString().toAscii() );
}
