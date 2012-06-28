import Qt 4.7

Item {
    id: container   

    property string url
    property string title
    property string episodeSource
    signal subscribe
    signal play
    signal stop
    signal back


    RssModel {
         id: rssModel
         source: "http://www.nelonen.fi/rss/podcasts/5"
     }


     Component {
         id: highlightBar
         Rectangle {
             width: container.width
             height: container.height
             color: "silver"
             y: episodes.currentItem.y;
         }
     }

     Item {
         id: titleRect
         width: container.width
         height: 50
         anchors.left: parent.left
         anchors.top: parent.top
         Text {
             color: "silver"
             font.pointSize: 22
             anchors.centerIn: parent
             text: "Herätkää"
         }

     }

     Item {
         id: episodesRect
         width: container.width
         height: container.height - titleRect.height - controlRect.height - progressbarRect.height
         anchors.left: parent.left
         anchors.top: titleRect.bottom

         ListView {
             id: episodes
             anchors.fill: parent
             model: rssModel
             highlightFollowsCurrentItem: true
             focus: true
             highlight: highlightBar
             keyNavigationWraps: false
             delegate: EpisodeItem {
                 title: model.title;
                 description: model.description
                 url: model.url
                 type: model.type
                 link: model.link
             }
             spacing: 3
         }
     }

     Item {
         id: progressbarRect
         width: container.width
         height: 25
         anchors.left: parent.left
         anchors.top: episodesRect.bottom
         ProgressBar {
             id: progressbar
             width: parent.width
             height: parent.height
             visible: false
             color: "silver"
             secondColor: "silver"

             NumberAnimation on value {
                 id: progressAnimation
                 duration: 9000
                 from: 0
                 to: 100
                 //loops: 0
                 running: false

             }
         }
     }

     Item {
         id: controlRect
         width: container.width
         height: 50
         anchors.left: parent.left
         anchors.top: progressbarRect.bottom

         Row {
             anchors.fill: parent

             Rectangle {
                 color: "silver"
                 width: container.width / 4
                 height: parent.height
                 border.color: "darkgray"
                 border.width: 2
                 Text {
                     anchors.fill: parent
                     text: "<<"
                     color: "Black"
                     font.bold: true
                     font.pointSize: 22
                     verticalAlignment: Text.AlignVCenter
                     horizontalAlignment: Text.AlignHCenter
                 }
                 MouseArea {
                     anchors.fill: parent
                     onClicked: {
                         progressbar.visible = false
                         progressbar.value = 0
                         episodes.decrementCurrentIndex()
                     }
                 }
             }

             Rectangle {
                 color: "silver"
                 width: container.width / 4
                 height: parent.height
                 border.color: "darkgray"
                 border.width: 2
                 Text {
                     id: playText
                     anchors.fill: parent
                     text: "Play"
                     color: "Black"
                     font.bold: true
                     font.pointSize: 22
                     verticalAlignment: Text.AlignVCenter
                     horizontalAlignment: Text.AlignHCenter
                 }
                 MouseArea {
                     anchors.fill: parent
                     onClicked: {
                         progressbar.visible = true
                         container.episodeSource = episodes.currentItem.url
                         playText.text == "Play" ? container.play() : container.stop()
                         playText.text == "Play" ? playText.text = "Stop" : playText.text = "Play"
                     }
                 }
             }

             Rectangle {
                 color: "silver"
                 width: container.width / 4
                 height: parent.height
                 border.color: "darkgray"
                 border.width: 2
                 Text {
                     anchors.fill: parent
                     text: "Back"
                     color: "Black"
                     font.bold: true
                     font.pointSize: 22
                     verticalAlignment: Text.AlignVCenter
                     horizontalAlignment: Text.AlignHCenter
                 }
                 MouseArea {
                     anchors.fill: parent
                     onClicked: container.back()
                 }
             }

             Rectangle {
                 color: "silver"
                 width: container.width / 4
                 height: parent.height
                 border.color: "darkgray"
                 border.width: 2
                 Text {
                     anchors.fill: parent
                     text: ">>"
                     color: "Black"
                     font.bold: true
                     font.pointSize: 22
                     verticalAlignment: Text.AlignVCenter
                     horizontalAlignment: Text.AlignHCenter
                 }
                 MouseArea {
                     anchors.fill: parent
                     onClicked: {
                         progressbar.visible = false
                         progressbar.value = 0
                         episodes.incrementCurrentIndex()
                     }
                 }
             }
         }

     }


}
