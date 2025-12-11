import QtQuick 2.12
import QtQuick.Layouts 1.12

Rectangle {
    id: page4
    color: "white"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 15

        Text {
            text: "About Application"
            font.bold: true
            font.pixelSize: 24
            color: "#34495e"
        }

        Text {
            text: "Version: 1.0.0\n\nThis is a sample application demonstrating dynamic page switching with QML."
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            color: "#7f8c8d"
        }

        Text {
            text: "Features:"
            font.bold: true
            font.pixelSize: 16
        }

        Text {
            text: "• Dynamic button creation\n• Page switching\n• Form elements\n• Custom components"
            font.pixelSize: 14
            color: "#2c3e50"
        }
    }
}
