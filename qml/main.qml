import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.1
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3

import ProvidesSomething 1.0

ApplicationWindow {
    id: window

    minimumWidth: 300
    minimumHeight: 150

    title: "QHot"
    visible: true

    Component.onCompleted: {
        window.flags |= Qt.WindowStaysOnTopHint | Qt.WindowTitleHint
    }

    Shortcut {
        context: "ApplicationShortcut"
        sequence: "Ctrl+Q"
        onActivated: Qt.quit()
    }

    Shortcut {
        context: "ApplicationShortcut"
        sequence: "ALT+F1"
        onActivated: popup.opened ? popup.close() : popup.open()
    }

    Shortcut {
        property int currentVisibility: 0

        function toggleVisibility() {
            ++currentVisibility;
            switch (currentVisibility) {
            case 0:
                return Window.AutomaticVisibility
            case 1:
                return Window.Maximized
            case 2:
                currentVisibility = -1
                return Window.FullScreen
            }
        }

        context: "ApplicationShortcut"
        sequence: "ALT+F2"
        onActivated: window.visibility = toggleVisibility()
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            print("File selected:", fileDialog.fileUrl)
            ProvidesSomething.filePath = fileDialog.fileUrl
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

    Item {
        id: stateContainer
        state: {
            if (popup.opened) {
                return "popupOpened"
            } else if (loader.status === Loader.Ready) {
                return "itemLoaded"
            }

            return ""
        }

        states: [
            State {
                name: "popupOpened"
                PropertyChanges {
                    target: window
                    width: popup.width
                    height: popup.height
                }
            },
            State {
                name: "itemLoaded"
                PropertyChanges {
                    target: window
                    width: loader.item.width
                    height: loader.item.height
                }
            }
        ]
    }
}
