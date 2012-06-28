import Qt 4.7

Item {
    id: container
    height: episodeName.paintedHeight + 2
    width: 400

    property string type
    property string description
    property alias title: episodeName.text
    property string url
    property string link

    signal clicked(string itemInfo)
    property int fontPointSize: 18


    Item {
        height: container.height
        anchors.left: parent.left
        width: container.width

        Text {
            id: episodeName
            color: "white"
            anchors.fill: parent
            anchors.leftMargin: 5
            style: Text.Normal
            font.pointSize: fontPointSize
            text: "empty"
        }

        MouseArea {
             anchors.fill: parent
             //onPressed: autoRepeatClicks.start()
         }
    }

}
