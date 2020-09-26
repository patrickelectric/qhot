// To generate/update .qm file: lrelease translation_pt_BR.ts
// Run with: qhot translation.qml --translation=translation_pt.qm
import QtQuick 2.1
import QtQuick.Controls 2.14

Rectangle {
    color: "darkgray"
    anchors.fill: parent
    ListView {
        anchors.fill: parent
        model: [
            {
                object: qsTr("car"),
                color: qsTr("white")
            },
            {
                object: qsTr("apple"),
                color: qsTr("red")
            },
            {
                object: qsTr("table"),
                color: qsTr("gray")
            }
        ]
        delegate: Label {
            id: control
            font.pixelSize: parent.width * 1.5 / text.length
            color: "black"
            text: qsTr("%1 is %2").arg(modelData.object).arg(modelData.color)
        }
    }
}