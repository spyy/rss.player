#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>
#include <Phonon/Path>
#include <Phonon/MediaSource>


class Audio : public QObject
{
    Q_OBJECT
public:
    explicit Audio( QObject *parent = 0 );
    ~Audio();

public: // new functions    
    void play( QString fileName );
    void stop();

signals:

public slots:
    void stateChanged( Phonon::State newstate, Phonon::State oldstate );

private:
    Phonon::MediaObject* iMediaObject;
    Phonon::AudioOutput* iAudioOutput;
    Phonon::Path iPath;
    Phonon::MediaSource* iMediaSource;

};

#endif // AUDIO_H
