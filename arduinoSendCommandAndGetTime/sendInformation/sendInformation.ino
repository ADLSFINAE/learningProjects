void setup() {
  Serial.begin(9600); // Инициализация UART
  pinMode(LED_BUILTIN, OUTPUT); // Встроенный светодиод
}

// Функция, которая генерирует данные для отправки
String generateData() {
  int sensorValue = analogRead(A0); // Читаем аналоговый датчик (для примера)
  return "Data: " + String(sensorValue) + "|Time: " + String(millis());
}

bool testsActive = false; // Флаг активности тестов

void loop() {
  // Проверка входящих команд
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n'); // Читаем команду
    command.trim(); // Удаляем лишние символы
    
    if (command == "START") {
      testsActive = true;
      Serial.println("TESTING STARTED"); // Подтверждение начала
      digitalWrite(LED_BUILTIN, HIGH); // Включаем светодиод
      
      // Основной цикл отправки данных
      while(testsActive) {
        delay(200);
        String response = generateData();
        Serial.println(response);
        
        // Проверка команды STOP во время задержки
          if(Serial.available()) {
            String stopCommand = Serial.readStringUntil('\n');
            stopCommand.trim();
            delay(200);
            if(stopCommand == "STOP") {
              testsActive = false;
              break;
            }
          }
        
      }
      delay(200);
      digitalWrite(LED_BUILTIN, LOW); // Выключаем светодиод
      Serial.println("TESTING STOPPED"); // Подтверждение остановки
    }
    else if (command == "STOP") {
      testsActive = false; // На случай, если STOP пришел вне цикла
      Serial.println("STOP COMMAND RECEIVED");
    }
  }
}