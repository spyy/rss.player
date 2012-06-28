
QT += declarative network xml phonon


SOURCES += main.cpp
SOURCES += rssparser.cpp
SOURCES += engine.cpp
SOURCES += networkaccess.cpp
SOURCES += audio.cpp

OTHER_FILES += qml/main.qml \
    qml/ErrorView.qml
OTHER_FILES += qml/RssModel.qml
OTHER_FILES += qml/MagazineView.qml
OTHER_FILES += qml/EpisodeView.qml
OTHER_FILES += qml/PodcastButton.qml
OTHER_FILES += qml/InputButton.qml
OTHER_FILES += qml/EpisodeItem.qml
OTHER_FILES += qml/DownloadingView.qml
OTHER_FILES += qml/ProgressBar.qml

OTHER_FILES += rss.xml


HEADERS += engine.h
HEADERS += rssparser.h
HEADERS += networkaccess.h
HEADERS += audio.h
