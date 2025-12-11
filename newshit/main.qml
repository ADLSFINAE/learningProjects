import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Dynamic Pages Application")

    // Пример данных
    property var buttonTitles: ["Page 1", "Page 2", "Settings", "About"]
    property var buttonWidths: [100, 100, 120, 100]

    // Текущий выбранный индекс
    property int currentPageIndex: 0

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // Панель с кнопками
        Rectangle {
            Layout.fillWidth: true
            height: 60
            color: "#f0f0f0"

            Row {
                anchors.centerIn: parent
                spacing: 10

                Repeater {
                    model: buttonTitles.length

                    CustomButton {
                        width: buttonWidths[index]
                        text: buttonTitles[index]
                        isSelected: currentPageIndex === index

                        onClicked: {
                            currentPageIndex = index
                        }
                    }
                }
            }
        }

        // Область для отображения страниц
        StackLayout {
            id: pageContainer
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: currentPageIndex

            // Page 1
            Page1 {}

            // Page 2
            Page2 {}

            // Page 3 (Settings)
            Page3 {}

            // Page 4 (About)
            Page4 {}
        }
    }
}
