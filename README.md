# ESP32-PowerSwitchForPC

## О проекте</br>
Это устройство позволяет включать/выключать/перезагружать ваш PC удаленно с помощью:
- ESP32
- Telegram bot
- NPN-транзисторы 2n2222

Данный функционал был реализован с помощью физического замыкания через</br>транзисторы контактов  **POWER SW** и **RESET SW**.

В качестве микрокотроллера был выбран ESP32.</br>
 Он имеет встроенный WiFi что позволяет подключаться к глобальной сети интернет. Так же он</br> обладает высокой производительность за относительно малую цену.

 Почему не esp8266? Потому что.

 ## Инструкции:</br>
 [Создание телеграмм бота](https://github.com/Daniil-Perevezentsev/ESP32-PowerSwitchForPC/blob/main/src/doc/creating%20telegram%20bot.md)</br>
 [Настройкa WiFiManager](https://github.com/Daniil-Perevezentsev/ESP32-PowerSwitchForPC/blob/main/src/doc/esp32%20wifi%20connection%20setup.md)

 ## Библиотеки из этого проекта:</br>
[WiFi.h для работы c ESP32](https://github.com/espressif/arduino-esp32)</br>
[WiFiClientSecure.h](https://github.com/espressif/arduino-esp32)</br>
[UniversalTelegramBot.h](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot)</br>
[WiFiManager.h](https://github.com/tzapu/WiFiManager)</br>
[ArduinoJson](https://github.com/bblanchon/ArduinoJson)</br>

 ## Схема Easyeda

|   |  |
| ------------- | ------------- |
| POWER SW  | GPIO17  |
| RESET SW  | GPIO16  |
| Питание  | 3.3v |

![](https://github.com/Daniil-Perevezentsev/ESP32-PowerSwitchForPC/blob/main/src/doc/picture/Schematic.png?raw=true)

## 3Д-модель Easyeda
![](https://github.com/Daniil-Perevezentsev/ESP32-PowerSwitchForPC/blob/main/src/doc/picture/3D-model.PNG?raw=true)

## Контакты
[TG](https://t.me/Rondo4R)

## Авторы
Перевезенцев Даниил </br>
Лисицкий Максим