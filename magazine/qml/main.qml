import Qt 4.7
import MagazineEngine 1.0


Item {
    id: container
    width: diver.width
    height: diver.height
    property string url: "http://www.nelonen.fi/rss/podcasts/3"


    MagazineEngine {
         id: engine
         url: "http://www.nelonen.fi/rss/podcasts/3"
         onUrlChanged: console.debug("urlChanged")
         onRssChanged: {
             console.debug("onRssChanged")
             downloadingView.visible = false
             magazineView.visible = true
         }
         onBytesReceivedChanged: console.debug("onBytesReceivedChanged")
         onBytesTotalChanged: console.debug("onBytesTotalChanged")
     }

    Image {
        id: diver
        source: "content/diver.bmp"
        visible: true
    }


    MagazineView {
        id: magazineView
        width: container.width
        height: container.height
        url: engine.url
        visible: true
        onUpdate: {
            engine.url = magazineView.url
            engine.updateRssFeed()
            magazineView.visible = false
            downloadingView.visible = true
        }
        onListen: {
            episodeView.url = engine.rssName
            magazineView.visible = false
            downloadingView.visible = false
            episodeView.visible = true
        }
    }

    DownloadingView {
        id: downloadingView
        width: container.width
        height: container.height
        visible: false        
    }

    ErrorView {
        id: errorView
        width: container.width
        height: container.height
        visible: false
    }


    EpisodeView {
        id: episodeView
        width: container.width
        height: container.height
        visible: false        
        onPlay: {
            console.debug("onPlay")
            console.debug(episodeView.episodeSource)
            engine.play(episodeView.episodeSource)
        }
        onStop: {
            console.debug("onStop")
            engine.stop()
        }
        onBack: {
            console.debug("onBack")
            downloadingView.visible = false
            episodeView.visible = false
            magazineView.visible = true
        }
    }

}
