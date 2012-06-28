import Qt 4.7


Item {
    id: container
    height: buttonText.paintedHeight + 2
    width: 400
    signal clicked
    property alias text: buttonText.text


    Rectangle {
        id: button
        color: "silver"
        anchors.fill: parent
        border.color: "darkgray"
        border.width: 3
        radius: 10

        Text {
            id: buttonText
            color: "black"
            anchors.horizontalCenter: parent.horizontalCenter
            style: Text.Normal
            font.pointSize: 22
            font.family: "Arial"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: container.clicked()
            }
    }

}
