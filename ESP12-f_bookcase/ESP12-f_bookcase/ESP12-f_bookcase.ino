/*
  Bookcase

  Use MQTT protocol and 74HC595 through ESP12-f to control 11 LEDs.
  You need to set your WiFi and MQTT client name you want.

  modified 16 Apr 2021
  by TNTInMinecraft
  modified 20 Jan 2023
  by TNTInMinecraft
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// set device name and place
String DeviceName = "bookcase";
String Place = "bedroom";

// 74hc595
int BitPin = 12;   // Latch pin (STCP)
int ClockPin = 13;  // Clock pin (SHCP)
int DataPin = 14;   // Data pin (DS)

// WiFi
const char *ssid = "***"; // WiFi name
const char *password = "***";  // WiFi password

// MQTT Broker
const char *mqtt_broker = "***";
const char *topic = "esp12-f";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // set out pin to 74hc595
  pinMode(BitPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  pinMode(DataPin, OUTPUT);

  Serial.begin(115200);
  
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi.");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to the WiFi network.IP addrress: ");
  Serial.println(WiFi.localIP());

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
  
  // publish and subscribe
  client.publish(topic, "hello");
  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
  String message;
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    message = message + (char) payload[i];
  }
  Serial.println(message);
  light_control(message); // set light state
  Serial.println("-----------------------");
}

void light_control(String message) {
  // cut message
  int j = 0;
  int bit_data[16] = {1};
  for (int i = 0; i < message.length(); i++) {
    if (message[i] == ',') {
      j++;
    } else {
      bit_data[j] = bit_data[j] * 10 + (message[i] - '0');
    }
  }
  message = "";

  // output light state
  digitalWrite(BitPin, LOW);
  for (int i = 15; i >= 0; i--) {
    digitalWrite(DataPin, bit_data[i]);
    digitalWrite(ClockPin, HIGH);
    digitalWrite(ClockPin, LOW);
  }
  digitalWrite(BitPin, HIGH);
}

void loop() {
  client.loop();
}
