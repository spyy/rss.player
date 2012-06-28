#ifndef MAGAZINEVIEW_H
#define MAGAZINEVIEW_H


#include <QDeclarativeView>


#include "engine.h"



class Kustomi : public QObject
 {
     Q_OBJECT
     Q_PROPERTY( QString imageName READ imageName NOTIFY imageNameChanged )
     Q_PROPERTY( QString url READ url WRITE setUrl NOTIFY urlChanged )


 public:
     Kustomi() : m_image( " " ), m_url( " " ) {}

     QString imageName() const { return m_image; }

     QString url() const { return m_url; }
     void setUrl(const QString &c) { m_url = c; }


     //Q_INVOKABLE void clearChart();

 signals:
     void urlChanged();
     void imageNameChanged();

 public:
     QString m_image;
     QString m_url;
 };



class MagazineView : public QDeclarativeView
{
    Q_OBJECT
    Q_PROPERTY(QString diver READ diverImage)

public:
    MagazineView( Engine& engine );
    ~MagazineView();

public: // properties
    QString diverImage() const { return iDiver; }

public: // new functions
    void initialize();

signals:

public slots:

    void onClicked();


private:
    Engine& iEngine;
    QString iDiver;
    Kustomi* iKustomi;

};


#endif
