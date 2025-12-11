import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    id: page3
    color: "white"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 15

        Text {
            text: "Settings Page"
            font.bold: true
            font.pixelSize: 20
            color: "#2c3e50"
        }

        ComboBox {
            Layout.preferredWidth: 250
            model: ["English", "Russian", "French", "German"]
            currentIndex: 0
        }

        TextField {
            Layout.preferredWidth: 250
            placeholderText: "Email address"
            validator: RegExpValidator { regExp: /\S+@\S+\.\S+/ }
        }

        CheckBox {
            text: "Enable notifications"
            checked: true
        }

        Button {
            text: "Save Settings"
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
