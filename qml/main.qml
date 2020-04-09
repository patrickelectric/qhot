import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.1
import QtQuick.Dialogs 1.3

import QtCharts 2.3

import QtGraphicalEffects 1.0

import QtQml.Models 2.2

import ProvidesSomething 1.0

ApplicationWindow {
    id: window
    title: "QHot"
    visible: true

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
        text: "Clicke here!\n Or add item as argument.\n" + error
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 5
        onClicked: {
            fileDialog.visible = true
        }

        property var error: ""
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
        focus: true
        anchors.fill: parent

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
