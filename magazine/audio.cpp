#include <Phonon/MediaSource>

#include "audio.h"


Audio::Audio( QObject *parent ) :
    QObject( parent )
{
    iMediaObject = new Phonon::MediaObject( this );    
    iAudioOutput = new Phonon::AudioOutput( Phonon::MusicCategory, this );
    iPath = Phonon::createPath( iMediaObject, iAudioOutput );
    iMediaSource = 0;

    connect( iMediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(stateChanged(Phonon::State,Phonon::State)));
}

Audio::~Audio()
{
    delete iMediaSource;    
}

/*
void Audio::play( QIODevice* ioDevice )
{
    if ( iIODevice )
    {
        iIODevice->deleteLater();
        iIODevice = 0;
    }
    delete iMediaSource;

    qDebug("isSequential : %d",ioDevice->isSequential());

    iIODevice = ioDevice;
    iMediaSource = new Phonon::MediaSource( iIODevice );

    iMediaObject->setCurrentSource( *iMediaSource );
    iMediaObject->play();
}
*/

void Audio::play( QString fileName )
{
    qDebug( "Audio::play" );

    delete iMediaSource;

    iMediaSource = new Phonon::MediaSource( fileName );

    iMediaObject->setCurrentSource( *iMediaSource );
    iMediaObject->play();
}

void Audio::stop()
{
    qDebug( "Audio::stop" );

    iMediaObject->stop();
}

void Audio::stateChanged( Phonon::State newstate, Phonon::State /*oldstate*/ )
{
    switch ( newstate )
    {
    case Phonon::LoadingState:
        qDebug( "Phonon::LoadingState" );
        break;
    case Phonon::StoppedState:
        qDebug( "Phonon::StoppedState" );
        break;
    case Phonon::PlayingState:
        qDebug( "Phonon::PlayingState" );
        break;
    case Phonon::BufferingState:
        qDebug( "Phonon::BufferingState" );
        break;
    case Phonon::PausedState:
        qDebug( "Phonon::PausedState" );
        break;
    case Phonon::ErrorState:
        qDebug( "Phonon::ErrorState: %s", iMediaObject->errorString().toAscii().data() );
        break;
    default:
        qDebug( "Phonon::Unknown" );
        break;
    }
}
