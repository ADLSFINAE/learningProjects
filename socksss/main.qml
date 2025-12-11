import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQml 2.12

ApplicationWindow {
    visible: true
    width: 1024
    height: 768
    title: "Адаптивная панель с выпадающими меню"

    property int checkBoxCount: 3
    property bool thirdExpanded: false
    property bool fourthExpanded: false
    property bool fifthExpanded: false

    // Основной контейнер
    Column {
        anchors.fill: parent
        spacing: 0

        // Основная строка с прямоугольниками
        Row {
            id: mainRow
            width: parent.width
            height: 150
            spacing: 5

            // 1-й прямоугольник (неизменяемый)
            Rectangle {
                id: rect1
                width: 60
                height: parent.height
                color: "lightblue"
                border.color: "gray"

                Text {
                    text: "1"
                    anchors.centerIn: parent
                    font.pointSize: 14
                }
            }

            // 2-й прямоугольник (неизменяемый)
            Rectangle {
                id: rect2
                width: 60
                height: parent.height
                color: "lightgreen"
                border.color: "gray"

                Text {
                    text: "2"
                    anchors.centerIn: parent
                    font.pointSize: 14
                }
            }

            // 3-й прямоугольник (адаптивный)
            Rectangle {
                id: rect3
                height: parent.height
                color: getRect3Color()
                border.color: "gray"
                border.width: 1

                // ПРОСТАЯ ЛОГИКА: проверяем сумму всех ширин
                width: {
                    // Если развернут - квадрат
                    if (thirdExpanded) {
                        return 40
                    }

                    // Вычисляем базовую ширину для Grid
                    var gridNeededWidth = calculateGridNeededWidth()

                    // Рассчитываем ширину 4-го и 5-го
                    var width4 = rect4.width
                    var width5 = rect5.width

                    // Сумма всех ширин с учетом отступов
                    var totalWidth = rect1.width + rect2.width + gridNeededWidth + width4 + width5 + (mainRow.spacing * 4)

                    // Если не помещается и 4-й/5-й уже квадраты
                    if (totalWidth > mainRow.width && width4 <= 40 && width5 <= 40) {
                        return 40  // Сворачиваем 3-й в квадрат
                    }

                    // Если Grid требует много места
                    if (gridNeededWidth > 250) {
                        return Math.min(mainRow.width - rect1.width - rect2.width - (mainRow.spacing * 2),
                                      Math.max(250, gridNeededWidth))
                    }

                    // Нормальный режим
                    var availableWidth = mainRow.width - rect1.width - rect2.width - width4 - width5 - (mainRow.spacing * 4)
                    return Math.max(120, Math.min(250, availableWidth))
                }

                function calculateGridNeededWidth() {
                    var columns = Math.ceil(checkBoxCount / 3)
                    var columnWidth = 100  // минимальная ширина колонки
                    var spacing = 8
                    return columns * columnWidth + (columns - 1) * spacing + 20
                }

                function getRect3Color() {
                    if (thirdExpanded) return "darkorange"
                    if (width <= 40) return "orange"
                    return "lightyellow"
                }

                // НОРМАЛЬНЫЙ РЕЖИМ (Grid)
                Column {
                    visible: !thirdExpanded && parent.width > 40
                    anchors.fill: parent
                    padding: 8
                    spacing: 8

                    Button {
                        text: "Добавить элемент (+)"
                        width: parent.width
                        height: 30

                        onClicked: {
                            checkBoxCount++
                        }
                    }

                    // Grid 3 строки × N столбцов
                    Grid {
                        width: parent.width
                        rows: 3
                        spacing: 8
                        flow: Grid.TopToBottom

                        Repeater {
                            model: checkBoxCount

                            Rectangle {
                                width: Math.max(80, (parent.width - (Math.ceil(checkBoxCount / 3) - 1) * parent.spacing) / Math.ceil(checkBoxCount / 3))
                                height: 30
                                color: index % 2 === 0 ? "#f8f8f8" : "#ffffff"
                                border.color: "lightgray"

                                Row {
                                    spacing: 6
                                    anchors.centerIn: parent

                                    CheckBox {
                                        checked: false
                                        scale: 0.9
                                    }

                                    Text {
                                        text: "Эл. " + (index + 1)
                                        anchors.verticalCenter: parent.verticalCenter
                                        font.pixelSize: 10
                                    }
                                }
                            }
                        }
                    }
                }

                // КВАДРАТ (кликабельный)
                Rectangle {
                    visible: !thirdExpanded && parent.width <= 40
                    anchors.fill: parent
                    color: "orange"

                    Text {
                        text: "3 ▼"
                        anchors.centerIn: parent
                        font.pointSize: 10
                        color: "white"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: thirdExpanded = true
                    }
                }
            }

            // 4-й прямоугольник
            Rectangle {
                id: rect4
                height: parent.height
                color: fourthExpanded ? "coral" : "lightcoral"
                border.color: "gray"
                border.width: 1

                width: {
                    if (fourthExpanded) {
                        return 40
                    }

                    // Простая логика: если не помещается - квадрат
                    var usedWidth = rect1.width + rect2.width + rect3.width + 80 + (mainRow.spacing * 4)  // 80 - предположение для 5-го
                    var available = mainRow.width - usedWidth

                    return available < 80 ? 40 : 80
                }

                // Нормальный режим
                Column {
                    visible: !fourthExpanded && parent.width > 50
                    anchors.fill: parent
                    padding: 8
                    spacing: 8

                    Text {
                        text: "Панель 4"
                        font.bold: true
                        font.pointSize: 12
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Button {
                        text: "Кнопка 1"
                        width: parent.width
                        height: 25
                    }

                    Button {
                        text: "Кнопка 2"
                        width: parent.width
                        height: 25
                    }
                }

                // Квадрат
                Rectangle {
                    visible: !fourthExpanded && parent.width <= 50
                    anchors.fill: parent
                    color: "coral"

                    Text {
                        text: "4 ▼"
                        anchors.centerIn: parent
                        font.pointSize: 12
                        color: "white"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: fourthExpanded = true
                    }
                }
            }

            // 5-й прямоугольник
            Rectangle {
                id: rect5
                height: parent.height
                color: fifthExpanded ? "pink" : "lightpink"
                border.color: "gray"
                border.width: 1

                width: {
                    if (fifthExpanded) {
                        return 40
                    }

                    // Простая логика: если не помещается - квадрат
                    var usedWidth = rect1.width + rect2.width + rect3.width + rect4.width + (mainRow.spacing * 4)
                    var available = mainRow.width - usedWidth

                    return available < 80 ? 40 : 80
                }

                // Нормальный режим
                Column {
                    visible: !fifthExpanded && parent.width > 50
                    anchors.fill: parent
                    padding: 8
                    spacing: 8

                    Text {
                        text: "Панель 5"
                        font.bold: true
                        font.pointSize: 12
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Button {
                        text: "Опция A"
                        width: parent.width
                        height: 25
                    }

                    Button {
                        text: "Опция B"
                        width: parent.width
                        height: 25
                    }
                }

                // Квадрат
                Rectangle {
                    visible: !fifthExpanded && parent.width <= 50
                    anchors.fill: parent
                    color: "pink"

                    Text {
                        text: "5 ▼"
                        anchors.centerIn: parent
                        font.pointSize: 12
                        color: "white"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: fifthExpanded = true
                    }
                }
            }
        }

        // ВЫПАДАЮЩЕЕ ОКНО 3-го
        Rectangle {
            id: expandedContent3
            visible: thirdExpanded
            width: Math.min(500, Math.max(350, rect3.calculateGridNeededWidth() + 40))
            height: Math.min(300, Math.ceil(checkBoxCount / 3) * 35 + 100)
            x: rect1.width + rect2.width + (mainRow.spacing * 2)
            y: 0
            color: "lightyellow"
            border.color: "darkgray"
            border.width: 2
            z: 100

            Column {
                anchors.fill: parent
                padding: 12
                spacing: 12

                Text {
                    text: "Третий элемент (развернуто)"
                    font.bold: true
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "darkblue"
                }

                Button {
                    text: "Добавить элемент (+)"
                    width: parent.width
                    height: 30

                    onClicked: {
                        checkBoxCount++
                    }
                }

                Grid {
                    width: parent.width
                    rows: 3
                    spacing: 8
                    flow: Grid.TopToBottom

                    Repeater {
                        model: checkBoxCount

                        Rectangle {
                            width: Math.max(80, (parent.width - (Math.ceil(checkBoxCount / 3) - 1) * parent.spacing) / Math.ceil(checkBoxCount / 3))
                            height: 30
                            color: index % 2 === 0 ? "#f0f0f0" : "#ffffff"
                            border.color: "lightgray"

                            Row {
                                spacing: 6
                                anchors.centerIn: parent

                                CheckBox {
                                    checked: false
                                    scale: 0.9
                                }

                                Text {
                                    text: "Эл. " + (index + 1)
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.pixelSize: 10
                                }
                            }
                        }
                    }
                }

                Button {
                    text: "▲ Свернуть"
                    width: parent.width
                    height: 30
                    onClicked: thirdExpanded = false
                }
            }
        }

        // ВЫПАДАЮЩЕЕ ОКНО 4-го
        Rectangle {
            id: expandedContent4
            visible: fourthExpanded
            width: 250
            height: 200
            x: rect1.width + rect2.width + rect3.width + (mainRow.spacing * 3)
            y: 0
            color: "lightcoral"
            border.color: "darkgray"
            border.width: 2
            z: 99

            Column {
                anchors.fill: parent
                padding: 12
                spacing: 8

                Text {
                    text: "Панель 4 (развернута)"
                    font.bold: true
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Button {
                    text: "Действие 1"
                    width: parent.width
                    height: 30
                }

                Button {
                    text: "Действие 2"
                    width: parent.width
                    height: 30
                }

                Button {
                    text: "Действие 3"
                    width: parent.width
                    height: 30
                }

                Button {
                    text: "Действие 4"
                    width: parent.width
                    height: 30
                }

                Button {
                    text: "▲ Свернуть"
                    width: parent.width
                    height: 30
                    onClicked: fourthExpanded = false
                }
            }
        }

        // ВЫПАДАЮЩЕЕ ОКНО 5-го
        Rectangle {
            id: expandedContent5
            visible: fifthExpanded
            width: 250
            height: 200
            x: rect1.width + rect2.width + rect3.width + rect4.width + (mainRow.spacing * 4)
            y: 0
            color: "lightpink"
            border.color: "darkgray"
            border.width: 2
            z: 98

            Column {
                anchors.fill: parent
                padding: 12
                spacing: 8

                Text {
                    text: "Панель 5 (развернута)"
                    font.bold: true
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Button {
                    text: "Функция A"
                    width: parent.width
                    height: 30
                }

                Button {
                    text: "Функция B"
                    width: parent.width
                    height: 30
                }

                Button {
                    text: "Функция C"
                    width: parent.width
                    height: 30
                }

                Button {
                    text: "Функция D"
                    width: parent.width
                    height: 30
                }

                Button {
                    text: "▲ Свернуть"
                    width: parent.width
                    height: 30
                    onClicked: fifthExpanded = false
                }
            }
        }

        // Свободное пространство
        Item {
            width: parent.width
            height: parent.height - mainRow.height
                       - (thirdExpanded ? expandedContent3.height : 0)
                       - (fourthExpanded ? expandedContent4.height : 0)
                       - (fifthExpanded ? expandedContent5.height : 0)
        }
    }

    // Информационная панель
    Rectangle {
        width: 350
        height: 180
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        color: "#f8f8f8"
        border.color: "gray"
        border.width: 1

        Column {
            anchors.fill: parent
            padding: 10
            spacing: 5

            Text {
                text: "ПРОСТАЯ ЛОГИКА АДАПТАЦИИ"
                font.bold: true
                font.pixelSize: 12
                color: "darkblue"
            }

            Text {
                text: "Элементов Grid: " + checkBoxCount + " (3 × " + Math.ceil(checkBoxCount / 3) + ")"
                font.pixelSize: 11
            }

            Rectangle {
                width: parent.width
                height: 1
                color: "lightgray"
            }

            Text {
                text: "Сумма ширин всех элементов:"
                font.pixelSize: 10
                color: "darkgreen"
            }

            Text {
                text: rect1.width + " + " + rect2.width + " + " + rect3.width + " + " +
                      rect4.width + " + " + rect5.width + " = " +
                      (rect1.width + rect2.width + rect3.width + rect4.width + rect5.width) + "px"
                font.pixelSize: 10
            }

            Text {
                text: "Ширина окна: " + width + "px"
                font.pixelSize: 10
                color: "darkred"
            }

            Text {
                text: "4-й элемент: " + (rect4.width <= 40 ? "КВАДРАТ" : "нормальный")
                font.pixelSize: 10
                color: rect4.width <= 40 ? "red" : "black"
            }

            Text {
                text: "5-й элемент: " + (rect5.width <= 40 ? "КВАДРАТ" : "нормальный")
                font.pixelSize: 10
                color: rect5.width <= 40 ? "red" : "black"
            }

            Text {
                text: "3-й элемент: " +
                      (thirdExpanded ? "РАЗВЕРНУТ" :
                       (rect3.width <= 40 ? "КВАДРАТ" :
                        "GRID (" + Math.ceil(checkBoxCount / 3) + " столбцов)"))
                font.pixelSize: 10
                color: thirdExpanded ? "green" : (rect3.width <= 40 ? "red" : "black")
            }

            Rectangle {
                width: parent.width
                height: 1
                color: "lightgray"
            }

            Row {
                width: parent.width
                spacing: 5

                Button {
                    text: "Тест: 10 эл."
                    width: (parent.width - parent.spacing * 2) / 3
                    height: 25
                    onClicked: {
                        checkBoxCount = 10
                    }
                }

                Button {
                    text: "Тест: 20 эл."
                    width: (parent.width - parent.spacing * 2) / 3
                    height: 25
                    onClicked: {
                        checkBoxCount = 20
                    }
                }

                Button {
                    text: "Сброс"
                    width: (parent.width - parent.spacing * 2) / 3
                    height: 25
                    onClicked: {
                        checkBoxCount = 3
                        thirdExpanded = false
                        fourthExpanded = false
                        fifthExpanded = false
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        console.log("=== ПРОСТАЯ СИСТЕМА АДАПТАЦИИ ===")
        console.log("Логика: если сумма ширин > ширины окна и 4,5 уже квадраты → сворачиваем 3-й")
    }
}
