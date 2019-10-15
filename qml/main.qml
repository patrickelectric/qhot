import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.13

import ProvidesSomething 1.0

ApplicationWindow {
    id: window
    title: "QHot"
    visible: true

    DropArea {
        id: dropArea
        anchors.fill: parent
        keys: ["text/plain"]
        onEntered: print('entered')
        onDropped: {
            // Only get the first file
            ProvidesSomething.filePath = drop.text.split('\n')[0]
        }
    }

    Connections {
        target: ProvidesSomething
        onFilePathChanged: {
            var path = ProvidesSomething.filePath + "?t=" + Date.now()
            loader.source = path
        }
    }

    Loader {
        id: loader
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: pathLayout.bottom
        property var recoverSource: "qrc:/recover.qml"
        source: recoverSource

        onStatusChanged: {
            if(loader.status === Loader.Error) {
                loader.source = recoverSource
                loader.item.state = "error"
            } else if(loader.status === Loader.Null) {
                loader.source = recoverSource
                loader.item.state = "null"
            }
        }
    }

    RowLayout {
        id: pathLayout
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        TextEdit {
            id: pathEdit
            Layout.fillWidth: true
            text: "POTATO"
            onEditingFinished: {
                ProvidesSomething.filePath = text
            }
        }
        Button {
            id: pathEditButton
            text: "ok!"
            onClicked: {
                ProvidesSomething.filePath = pathEdit.text
            }
        }
    }
}
