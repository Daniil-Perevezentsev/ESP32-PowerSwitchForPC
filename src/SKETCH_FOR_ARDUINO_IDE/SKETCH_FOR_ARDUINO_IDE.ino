  
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <DNSServer.h>
#include "WiFiManager.h"

// wifi setup
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PSWD"

// initialization telegramm bot
#define BOT_TOKEN "TOKEN TELEGRAM BOT"
#define SECURE_CHAT_ID "-CHAT ID"
const unsigned long BOT_MTBS = 1000; //mean time between scan messages

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

const int Relay1 = 2;      //power sw   
int Relay1Status = 0;

          


void handleNewMessages(int numNewMessages)
{
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++)
  {
    
    String chat_id = bot.messages[i].chat_id;
    if(chat_id != SECURE_CHAT_ID){
      continue;
    }
    
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if (text == "/on")
    {
      bot.sendMessage(chat_id, "Ваша воля будет исполена", "");
      digitalWrite(Relay1, HIGH);
      delay(500);
      digitalWrite(Relay1, LOW);
      Relay1Status = 0;                  
      bot.sendMessage(chat_id, "Исполнено", "");
    }
    if (text == "/reset")
    {
      bot.sendMessage(chat_id, "Слушаюсь и повинусь", "");
      digitalWrite(Relay1, HIGH);
      delay(5000);
      digitalWrite(Relay1, LOW);
      Relay1Status = 0;                  
      bot.sendMessage(chat_id, "Готово", "");
    }
    if (text == "/status")
    {
      if (Relay1Status)bot.sendMessage(chat_id, "Я всё ещё работаю", "");
      else bot.sendMessage(chat_id, "-", "");
    }

    if (text == "/start")
    {
      String welcome = "Готов вкалывать, " + from_name + ".\n";
      welcome += "Включить-выключить пека.\n\n";
      welcome += "------------------------------\n";
      welcome += "/on : включить|выключить пк\n";
      welcome += "------------------------------\n";
      welcome += "/reset : жесткая перезагрузка\n";
      welcome += "------------------------------\n";
      welcome += "/status : показывает включено или выключено\n";
      welcome += "------------------------------\n";
      bot.sendMessage(chat_id, welcome, "");
    }
  }
}

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(Relay1, OUTPUT);                  // Инициализируем как Выход
  digitalWrite(Relay1, LOW); // initialize pin as off (active LOW)
      secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //reset settings - for testing
  //wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);
  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if(!wifiManager.autoConnect("esp32", "espespesp")) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.restart();

    delay(1000);
  } 

  //if you get here you have connected to the WiFi
  Serial.println(F("WIFIManager connected!"));

  Serial.print(F("IP --> "));
  Serial.println(WiFi.localIP());
  Serial.print(F("GW --> "));
  Serial.println(WiFi.gatewayIP());
  Serial.print(F("SM --> "));
  Serial.println(WiFi.subnetMask());

  Serial.print(F("DNS 1 --> "));
  Serial.println(WiFi.dnsIP(0));

  Serial.print(F("DNS 2 --> "));
  Serial.println(WiFi.dnsIP(1));
  
  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

}

void loop() {
  
if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}
