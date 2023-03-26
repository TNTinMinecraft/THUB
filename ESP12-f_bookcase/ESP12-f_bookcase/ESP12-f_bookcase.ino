/*
  Bookcase

  Use MQTT protocol and 74HC595 through ESP12-f to control 11 LEDs.
  You need to set your WiFi and MQTT client name you want.

  modified 16 Apr 2021
  by TNTInMinecraft
  modified 20 Jan 2023
  by TNTInMinecraft
  Change mqtt from THUB to Json 26 Mar 2023
  by TNTInMinecraft
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// set device name and place
String DeviceName = "bookcase";
String Place = "bedroom";

// 74hc595
int BitPin = 12;    // Latch pin (STCP)
int ClockPin = 13;  // Clock pin (SHCP)
int DataPin = 14;   // Data pin (DS)

// WiFi
const char *ssid = "***";         // WiFi name
const char *password = "***";  // WiFi password
String MAC = "";

// MQTT Broker
const char *mqtt_broker = "192.168.31.153";
const char *topic = "esp8266";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

// LED_bit
int bit_data[16] = {1};

WiFiClient espClient;
PubSubClient client(espClient);

// set json memory
StaticJsonDocument<200> mqtt_json;

void setup() {  
  // set out pin to 74hc595
  pinMode(BitPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  pinMode(DataPin, OUTPUT);

  Serial.begin(115200);

  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi.");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to the WiFi network IP addrress: ");
  Serial.println(WiFi.localIP());
  MAC = WiFi.macAddress();

  //set mqtt client name
  String client_id = "THUB." + DeviceName + "." + Place + "." + String(WiFi.macAddress());
  Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());

  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Public emqx mqtt broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  // set client name
  char pubmsg[100];
  mqtt_json["id"] = MAC;
  mqtt_json["device"] = DeviceName;
  mqtt_json["place"] = Place;
  serializeJson(mqtt_json, pubmsg, sizeof(pubmsg));
  client.publish(topic, pubmsg);
  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
  String message;

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];
  }

  Serial.println(message);

  // deserialize json
  DeserializationError error = deserializeJson(mqtt_json, message);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  // judgement id and modes
  if (mqtt_json["id"] == MAC) {
    if (mqtt_json["modes"] == "default") {
      Serial.println(String(mqtt_json["data"]));
      modes_control(mqtt_json["data"]);
    } else if (mqtt_json["modes"] == "bit") {
      for (int i = 0; i < 16; i++){
        bit_data[i] = mqtt_json["data"][i];
      }
    } else {
      return;
    }
    light_control();
  }

  // debug
  debug_LED();
  Serial.println("-----------------------");
}

void modes_control(const char* in_mode) {
  if (in_mode == "all_off") {
    for (int i = 0; i < 16; i++) {
      bit_data[i] = 0;
    }
  } else if (in_mode == "all_on") {
    for (int i = 0; i < 16; i++) {
      bit_data[i] = 1;
    }
  } else if (in_mode == "on_up") {
    for (int i = 0; i < 16; i++) {
      bit_data[i] = 1;
      i++;
      bit_data[i] = 1;
      delay(500);
    }
  }
}

// output light state
void light_control() {
  digitalWrite(BitPin, LOW);
  for (int i = 15; i >= 0; i--) {
    digitalWrite(DataPin, bit_data[i]);
    digitalWrite(ClockPin, HIGH);
    digitalWrite(ClockPin, LOW);
  }
  digitalWrite(BitPin, HIGH);
}

void debug_LED(){
  for (int i = 0; i <= 16; i++) {
    Serial.print(bit_data[i]);
    Serial.print(",");
  }
  Serial.println("");
}

void loop() {
  client.loop();
}
