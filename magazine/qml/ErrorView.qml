import Qt 4.7

Item {
    id: container

    property alias description: iDescription.text


    Text {
        id: iDescription
        text: "Error occurred"
        anchors.centerIn: parent
        visible: true
        color: "Silver"
        font.pointSize: 22;
    }


}
