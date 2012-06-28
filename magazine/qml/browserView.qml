import Qt 4.7
import QtWebKit 1.0

Item {
    id: container
    width: parent.width
    height: parent.height

    property string addUrl: "add.html"
    property string manualUrl: "manual.html"
    property string resolvedUrl: Qt.resolvedUrl(manualUrl)

    signal clicked
    property string url


    WebView {
        id: web
        url: container.addUrl
        anchors.fill: parent

        onLoadFailed: {
            console.debug("onLoadFailed")
            console.debug(url)
        }
        onLoadFinished:  {
            console.debug("onLoadFinished")
            console.debug(url)
            //url == container.resolvedUrl ? button.visible = true : button.visible = true
        }
        onLoadStarted: {
            console.debug("onLoadStarted")
            console.debug(url)
        }

    }

    InputButton {
        id: button
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        width: container.width - 10
        btnText: "Search"
        visible: true

        onClicked: {
            container.url = "http://" + urlText
            web.visible = false
            container.clicked()

        }
    }


}
