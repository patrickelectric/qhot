import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.1
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.12

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

    ColorDialog {
        id: colorDialog
        title: "Select background color"
        currentColor: loaderBackground.color
        color: ProvidesSomething.background
        onAccepted: popup.close()
    }

    Popup {
        id: popup
        width: 300
        height: 200
        x: (window.width - width) / 2
        y: (window.height - height) / 2

        onOpenedChanged: content.state = opened ? "opened" : ""
        onClosed: loader.forceActiveFocus()

        Rectangle {
            id: content
            anchors.fill: parent
            color: ProvidesSomething.background

            RowLayout{
                anchors.fill: parent

                Button {
                    Layout.alignment: Qt.AlignCenter
                    text: "background"
                    onClicked: colorDialog.open()
                }
            }

            states: [
                State {
                    name: "opened"
                    PropertyChanges {
                        target: window
                        width: popup.width
                        height: popup.height
                    }
                }
            ]
        }
    }

    Button {
        id: button

        property var error: ""

        anchors.fill: parent
        anchors.margins: 5
        text: "Clicke here!\n Or add item as argument.\n" + error
        onClicked: fileDialog.visible = true
        visible: loader.status === Loader.Null
    }

    Connections {
        target: ProvidesSomething
        onFilePathChanged: {
            var path = ProvidesSomething.filePath + "?t=" + Date.now()
            loader.source = path
        }
    }

    Rectangle {
        id: loaderBackground
        anchors.fill: parent
        color: colorDialog.color
        visible: !button.visible

        Loader {
            id: loader
            focus: true
            Keys.onPressed: {
                if (event.key === Qt.Key_Q && (event.modifiers & Qt.ControlModifier)) {
                    Qt.quit()
                } else if (event.key === Qt.Key_F1 && (event.modifiers & Qt.ControlModifier)) {
                    popup.opened ? popup.close() : popup.open()
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

}
