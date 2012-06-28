import Qt 4.7

Item {
    id: container
    width: 400
    height: button.height
    signal clicked
    property int fontPointSize: 22
    property alias inputText: textInput.text
    property alias btnText: buttonText.text


    TextInput {
        id: textInput
        width: container.width / 10 * 8
        anchors.left: parent.left
        font.pointSize: container.fontPointSize
        horizontalAlignment: TextInput.AlignLeft
        cursorVisible: true
    }


    Rectangle {
        id: button
        color: "darkgray"
        anchors.right: parent.right
        width: container.width / 5
        height: buttonText.paintedHeight

        Text {
            id: buttonText
            x: 0
            y: 0
            color: "black"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: fontPointSize
            anchors.fill: parent
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.debug( "inputItem" )
                container.clicked()
            }

        }
    }


}


