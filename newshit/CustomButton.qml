import QtQuick 2.12

Item {
    id: root

    property alias text: buttonText.text
    property int buttonWidth: 100
    property int buttonHeight: 40
    property bool isSelected: false

    signal clicked()

    width: buttonWidth
    height: buttonHeight

    Rectangle {
        id: buttonRect
        anchors.fill: parent
        color: root.isSelected ? "#4CAF50" : "#2196F3"
        radius: 5

        Text {
            id: buttonText
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: 14
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: root.clicked()
        }
    }
}
