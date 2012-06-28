import Qt 4.7

Item {
    id: container
    height: podcastName.paintedHeight + 2
    width: 400
    property alias itemName: podcastName.text
    property string itemUrl
    signal clicked

    Item {
        height: container.height
        anchors.left: parent.left
        width: container.width

        Text {
            id: podcastName
            color: "white"
            anchors.fill: parent
            anchors.leftMargin: 5
            style: Text.Normal
            font.pointSize: 22
            font.family: "Arial"
            text: "Hei mualima"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                container.clicked()
                console.debug("click")
            }
        }
    }


}



