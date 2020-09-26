// Run with:  qhot simple_plasmoid.qml --plugin-path=/usr/lib/qt/qml/org/kde/plasma/components
import QtQuick 2.1
import QtQuick.Controls 2.14
import org.kde.plasma.core 2.0 as PlasmaCore

Rectangle {
    color: PlasmaCore.ColorScope.backgroundColor
    Label {
        id: control
        text: "QML"
        anchors.centerIn: parent
        font.pixelSize: parent.width/text.length
        font.family: PlasmaCore.Theme.defaultFont.family
        color: PlasmaCore.ColorScope.textColor
        renderType: Text.NativeRendering
    }
}