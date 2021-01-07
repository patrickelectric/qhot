import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.1
import QtQuick.Dialogs 1.3

import ProvidesSomething 1.0

ApplicationWindow {
    id: window
    title: "QHot"
    visible: true

    Component.onCompleted: {
        window.flags |= Qt.WindowStaysOnTopHint
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            print("File selected:", fileDialog.fileUrl)
            loader.source = fileDialog.fileUrl
        }
    }

    Button {
        id: button

        property var error: ""

        anchors.fill: parent
        anchors.margins: 5
        text: "Clicke here!\n Or add item as argument.\n" + error
        onClicked: fileDialog.visible = true

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
        anchors.fill: parent
        focus: true
        Keys.onPressed: {
            if (event.key === Qt.Key_F4 && (event.modifiers & Qt.AltModifier)) {
                Qt.quit()
            }
        }
        onStatusChanged: {
            if(loader.status === Loader.Error || loader.status === Loader.Null) {
                button.visible = true
                button.error = "Failed to load."
            } else {
                button.visible = false
                button.error = ""
            }
        }
    }
}
