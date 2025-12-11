import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    id: page2
    color: "white"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Page 2 - Settings"
            font.bold: true
            font.pixelSize: 18
        }

        ComboBox {
            Layout.preferredWidth: 200
            model: ["Low", "Medium", "High"]
            currentIndex: 1
        }

        RowLayout {
            Text {
                text: "Volume:"
            }

            Slider {
                Layout.preferredWidth: 150
                from: 0
                to: 100
                value: 50
            }
        }

        TextField {
            Layout.preferredWidth: 200
            placeholderText: "Enter setting value"
        }
    }
}
