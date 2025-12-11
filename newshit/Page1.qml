import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    id: page1
    color: "white"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Page 1 - User Information"
            font.bold: true
            font.pixelSize: 18
        }

        ComboBox {
            Layout.preferredWidth: 200
            model: ["Option 1", "Option 2", "Option 3"]
            currentIndex: 0
        }

        TextField {
            Layout.preferredWidth: 200
            placeholderText: "Enter your name"
        }

        Text {
            text: "Welcome to Page 1"
            color: "#666"
        }
    }
}
