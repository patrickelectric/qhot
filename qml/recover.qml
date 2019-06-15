import QtQuick 2.12

Text {
    id: infoText
    text: "Magic"
    anchors.centerIn: parent
    state: 'null'

    states: [
        State {
            name: "error"
            PropertyChanges {
                target: infoText
                text: "FAILED TO LOAD ITEM."
            }
        },
        State {
            name: "null"
            PropertyChanges {
                target: infoText
                text: "Add item as argument<br>Or drop it here!"
            }
        }
    ]
}
