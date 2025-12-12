import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle {
    id: page5
    color: "white"
    
    // Модель данных для таблицы
    ListModel {
        id: tableModel
        ListElement { name: "John Smith"; department: "IT"; salary: "5000"; status: "Active" }
        ListElement { name: "Alice Johnson"; department: "HR"; salary: "4500"; status: "Active" }
        ListElement { name: "Bob Williams"; department: "Sales"; salary: "4800"; status: "On Leave" }
        ListElement { name: "Carol Davis"; department: "Marketing"; salary: "5200"; status: "Active" }
        ListElement { name: "David Miller"; department: "IT"; salary: "4700"; status: "Active" }
        ListElement { name: "Eva Wilson"; department: "Finance"; salary: "5500"; status: "Inactive" }
        ListElement { name: "Frank Moore"; department: "Sales"; salary: "4900"; status: "Active" }
        ListElement { name: "Grace Taylor"; department: "HR"; salary: "4600"; status: "Active" }
        ListElement { name: "Henry Anderson"; department: "IT"; salary: "5100"; status: "On Leave" }
        ListElement { name: "Irene Thomas"; department: "Marketing"; salary: "5300"; status: "Active" }
    }
    
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15
        
        Text {
            text: "Employee Table"
            font.bold: true
            font.pixelSize: 24
            color: "#2c3e50"
            Layout.alignment: Qt.AlignHCenter
        }
        
        // Панель управления
        RowLayout {
            Layout.fillWidth: true
            spacing: 10
            
            Button {
                text: "Add Row"
                onClicked: {
                    tableModel.append({
                        "name": "New Employee",
                        "department": "New Dept",
                        "salary": "0",
                        "status": "Active"
                    })
                }
            }
            
            Button {
                text: "Remove Selected"
                onClicked: {
                    if (tableView.currentRow >= 0) {
                        tableModel.remove(tableView.currentRow)
                    }
                }
            }
            
            Item { Layout.fillWidth: true } // Spacer
            
            TextField {
                id: searchField
                placeholderText: "Search..."
                Layout.preferredWidth: 200
                onTextChanged: filterModel()
            }
        }
        
        // Таблица
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#f8f9fa"
            border.color: "#dee2e6"
            radius: 5
            
            ListView {
                id: tableView
                anchors.fill: parent
                anchors.margins: 1
                clip: true
                model: tableModel
                boundsBehavior: Flickable.StopAtBounds
                
                // Заголовок таблицы
                header: Rectangle {
                    width: tableView.width
                    height: 40
                    color: "#343a40"
                    
                    Row {
                        anchors.fill: parent
                        spacing: 1
                        
                        Repeater {
                            model: ["Name", "Department", "Salary ($)", "Status"]
                            
                            Rectangle {
                                width: index === 0 ? 200 : 150
                                height: 40
                                color: "transparent"
                                
                                Text {
                                    anchors.centerIn: parent
                                    text: modelData
                                    color: "white"
                                    font.bold: true
                                }
                                
                                // Разделитель
                                Rectangle {
                                    anchors.right: parent.right
                                    width: 1
                                    height: parent.height
                                    color: "#495057"
                                    visible: index < 3
                                }
                            }
                        }
                    }
                }
                
                // Элемент таблицы
                delegate: Rectangle {
                    width: tableView.width
                    height: 40
                    color: index % 2 === 0 ? "#ffffff" : "#f8f9fa"
                    
                    Row {
                        anchors.fill: parent
                        spacing: 1
                        
                        // Ячейка 1: Name
                        Rectangle {
                            width: 200
                            height: 40
                            color: "transparent"
                            
                            TextField {
                                anchors.fill: parent
                                anchors.margins: 5
                                text: name
                                verticalAlignment: Text.AlignVCenter
                                onEditingFinished: tableModel.setProperty(index, "name", text)
                            }
                        }
                        
                        // Ячейка 2: Department
                        Rectangle {
                            width: 150
                            height: 40
                            color: "transparent"
                            
                            ComboBox {
                                anchors.fill: parent
                                anchors.margins: 5
                                model: ["IT", "HR", "Sales", "Marketing", "Finance", "Admin"]
                                currentIndex: model.indexOf(department)
                                onActivated: tableModel.setProperty(index, "department", currentText)
                            }
                        }
                        
                        // Ячейка 3: Salary
                        Rectangle {
                            width: 150
                            height: 40
                            color: "transparent"
                            
                            SpinBox {
                                anchors.fill: parent
                                anchors.margins: 5
                                from: 0
                                to: 100000
                                stepSize: 100
                                value: parseInt(salary)
                                onValueModified: tableModel.setProperty(index, "salary", value.toString())
                            }
                        }
                        
                        // Ячейка 4: Status
                        Rectangle {
                            width: 150
                            height: 40
                            color: "transparent"
                            
                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 5
                                spacing: 5
                                
                                Rectangle {
                                    width: 12
                                    height: 12
                                    radius: 6
                                    color: getStatusColor(status)
                                }
                                
                                ComboBox {
                                    Layout.fillWidth: true
                                    model: ["Active", "Inactive", "On Leave"]
                                    currentIndex: model.indexOf(status)
                                    onActivated: tableModel.setProperty(index, "status", currentText)
                                }
                            }
                        }
                    }
                    
                    MouseArea {
                        anchors.fill: parent
                        onClicked: tableView.currentIndex = index
                    }
                }
                
                // Выделение текущей строки
                highlight: Rectangle {
                    color: "#e3f2fd"
                    radius: 3
                }
                highlightFollowsCurrentItem: true
                currentIndex: -1
            }
            
            // Полоса прокрутки
            ScrollBar {
                id: verticalScrollBar
                width: 10
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                policy: ScrollBar.AlwaysOn
                visible: tableView.contentHeight > tableView.height
            }
        }
        
        // Статистика
        RowLayout {
            Layout.fillWidth: true
            spacing: 20
            
            Rectangle {
                Layout.fillWidth: true
                height: 80
                color: "#e8f4fd"
                radius: 5
                
                Column {
                    anchors.centerIn: parent
                    spacing: 5
                    
                    Text {
                        text: tableModel.count
                        font.bold: true
                        font.pixelSize: 24
                        color: "#2196F3"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    
                    Text {
                        text: "Total Employees"
                        font.pixelSize: 12
                        color: "#666"
                    }
                }
            }
            
            Rectangle {
                Layout.fillWidth: true
                height: 80
                color: "#e8f5e9"
                radius: 5
                
                Column {
                    anchors.centerIn: parent
                    spacing: 5
                    
                    Text {
                        text: tableModel.count - getInactiveCount()
                        font.bold: true
                        font.pixelSize: 24
                        color: "#4CAF50"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    
                    Text {
                        text: "Active Employees"
                        font.pixelSize: 12
                        color: "#666"
                    }
                }
            }
            
            Rectangle {
                Layout.fillWidth: true
                height: 80
                color: "#fff3e0"
                radius: 5
                
                Column {
                    anchors.centerIn: parent
                    spacing: 5
                    
                    Text {
                        text: calculateAverageSalary() + "$"
                        font.bold: true
                        font.pixelSize: 24
                        color: "#FF9800"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    
                    Text {
                        text: "Average Salary"
                        font.pixelSize: 12
                        color: "#666"
                    }
                }
            }
        }
    }
    
    // Функция для получения цвета статуса
    function getStatusColor(status) {
        switch(status) {
            case "Active": return "#4CAF50";
            case "Inactive": return "#f44336";
            case "On Leave": return "#FF9800";
            default: return "#757575";
        }
    }
    
    // Функция для фильтрации
    function filterModel() {
        // В этом простом примере фильтрация не реализована
        // В реальном приложении можно использовать ProxyModel
    }
    
    // Функция для подсчета неактивных сотрудников
    function getInactiveCount() {
        var count = 0;
        for (var i = 0; i < tableModel.count; i++) {
            if (tableModel.get(i).status === "Inactive") {
                count++;
            }
        }
        return count;
    }
    
    // Функция для расчета средней зарплаты
    function calculateAverageSalary() {
        if (tableModel.count === 0) return 0;
        
        var total = 0;
        for (var i = 0; i < tableModel.count; i++) {
            total += parseInt(tableModel.get(i).salary);
        }
        return Math.round(total / tableModel.count);
    }
}
