import Qt 4.7






Item {
    id: container   
    property alias url: textInput.text

    signal update
    signal listen


    Item {
        id: row1
        width: parent.width
        height: 40
        anchors.left: parent.left
        anchors.top: parent.top
        TextInput {
            id: textInput
            width: row1.width - 10
            anchors.centerIn: row1
            font.pointSize: 22
            horizontalAlignment: TextInput.AlignLeft
            cursorVisible: true
        }
    }

    Item {
        id: row2
        width: parent.width
        height: 40
        anchors.left: parent.left
        anchors.top: row1.bottom
        PodcastButton {
            width: parent.width - 10
            anchors.centerIn: parent
            text: "Update"
            onClicked: {
                console.debug("onClicked")
                container.update()
            }
        }
    }

    Item {
        id: row3
        width: parent.width
        height: 40
        anchors.left: parent.left
        anchors.top: row2.bottom
        PodcastButton {
            width: parent.width - 10
            anchors.centerIn: parent
            text: "Listen"
            onClicked: {
                console.debug("onClicked")
                container.listen()
            }
        }
    }

}
