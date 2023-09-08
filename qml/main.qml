import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Dialogs
import QtQuick.Layouts

import QtCharts

import QtQml.Models

import ProvidesSomething

ApplicationWindow {
    id: window
    title: Qt.application.name
    visible: true

    Shortcut {
        context: "ApplicationShortcut"
        sequence: "Ctrl+Meta+Q"
        onActivated: Qt.quit()
    }

    Shortcut {
        context: "ApplicationShortcut"
        sequence: "Ctrl+Meta+F1"
        onActivated: popup.opened ? popup.close() : popup.open()
    }

    Component.onCompleted: {
        window.flags |= Qt.WindowStaysOnTopHint
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        currentFolder: StandardPaths.standardLocations(StandardPaths.HomeLocation)[0]
        onAccepted: {
            print("File selected:", selectedFile)
            loader.source = selectedFile
        }
    }

    ColorDialog {
        id: colorDialog
        title: "Select background color"
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
        visible: loader.status === Loader.Null
        onClicked: fileDialog.visible = true
    }

    Connections {
        target: ProvidesSomething
        function onFilePathChanged() {
            var path = ProvidesSomething.filePath + "?t=" + Date.now()
            loader.source = path
        }
    }

    Rectangle {
        id: loaderBackground
        anchors.fill: parent
        color: colorDialog.selectedColor
        visible: !button.visible

        Loader {
            id: loader
            focus: true
            anchors.fill: parent
            onStatusChanged: {
                if(loader.status === Loader.Error || loader.status === Loader.Null) {
                    button.visible = true
                    button.error = "Failed to load."
                } else {
                    button.visible = false
                    button.error = ""
                    // resize the window to fit the contents if it's larger and gives us implicit size
                    if (item) {
                        if (item.implicitWidth !== "undefined" && item.implicitWidth > window.width)
                            window.width = Math.min(item.implicitWidth, Screen.width)
                        if (item.implicitHeight !== "undefined" && item.implicitHeight > window.height)
                            window.height = Math.min(item.implicitHeight, Screen.height)
                    }
                }
            }
        }
    }

}
