/*
  4n27
  led
  1 - anodo
  2 - catodo
  transistor
  4 - coleor
  5 - emissor
  6 - case
*/
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include <ESP8266WiFi.h>
#include <SocketIOClient.h>//#include <SocketIOsocket.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>

#define evento "/post/dispositivo/"
#define serial "lampada001"
#define debugar true
#define luz D2

void Atuar(String);
void Debug(String);
void Estado(String);
void Valor(String);

int valor_luminosidade;

SocketIOClient socket;

char host[] = "api.saiot.ect.ufrn.br";
int port = 80;

extern String RID;
extern String Rname;

unsigned long previousMillis = 0;
long interval = 5000;
unsigned long lastreply = 0;
unsigned long lastsend = 0;

String JSON;
StaticJsonBuffer<100> jsonBuffer;


void setup() {
  analogWriteFreq(120);

  pinMode(luz, OUTPUT);

  Serial.begin(115200);

  delay(10);

  Serial.flush();

  WiFiManager wifis;
  wifis.autoConnect();

  /*
     configuração para OTA
  */
  // Port defaults to 8266
  ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname(serial);

  // No authentication by default  ArduinoOTA.setPassword((const char *)"123");
  //ArduinoOTA.setPassword();

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");

  /// emit reinicio
  JsonObject& root = jsonBuffer.createObject();
  root["serial"] = serial;  //  root["time"] = 1351824120;   //  JsonArray& data = root.createNestedArray("data");  //  data.add(double_with_n_digits(48.756080, 6));  //  data.add(double_with_n_digits(2.302038, 6));
  root.printTo(JSON);

  // We start by connecting to a WiFi network

  if (!socket.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }
  if (socket.connected())
  {
    Serial.println("\n\n\n\n\nConectou no servidor\n\n\n");
    socket.emit("/post/dispositivo/", JSON);
  }
  socket.on("atuar", Atuar);
  socket.on("debug", Debug);
  socket.on("estado", Estado);
  socket.on("valor", Valor);
}// end Setup

void loop() {
  delay(10);
  socket.monitor();
  ArduinoOTA.handle();
}
