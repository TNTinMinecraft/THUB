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
int BitPin = 12;    // Latch pin (STCP)
int ClockPin = 13;  // Clock pin (SHCP)
int DataPin = 14;   // Data pin (DS)

// WiFi
const char *ssid = "***";         // WiFi name
const char *password = "***";  // WiFi password

// MQTT Broker
const char *mqtt_broker = "192.168.31.153";
const char *topic = "esp8266";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

// LED_bit
int bit_data[16] = { 1 };

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

  // set client name
  String UpData = "THUB." + DeviceName + "." + Place + String(WiFi.macAddress()) + ".online";
  byte pubSiz = UpData.length() + 1;
  char pubmsg[pubSiz];

  // publish and subscribe
  UpData.toCharArray(pubmsg, pubSiz);
  client.publish(topic, pubmsg);
  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
  String message;
  String in_message[8] = { "" };
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];
  }
  Serial.println(message);
  int j = 0;
  for (int i = 0; i < message.length(); i++) {
    if (message[i] == '.') {
      j++;
    } else {
      in_message[j] = in_message[j] + char(message[i]);
    }
  }
  if (in_message[0].compareTo("THUB") && in_message[1].compareTo(DeviceName) && in_message[2].compareTo(Place) && in_message[3].compareTo(WiFi.macAddress())) {
    if (in_message[4] == "bit") {
      cut_message(in_message[5]);  // cut message
      light_control();
    } else if (in_message[4] == "mode") {
      light_control();
    }
  }
  // debug
  debug_LED();
  Serial.println("-----------------------");
}

void cut_message(String cut_message) {
  int j = 0;
  for (int i = 0; i < cut_message.length(); i++) {
    if (cut_message[i] == ',') {
      j++;
    } else {
      bit_data[j] = bit_data[j] * 10 + (cut_message[i] - '0');
    }
  }
  cut_message = "";
}

void modes(String in_mode) {
  if (in_mode.compareTo("all_off")) {
    for (int i = 0; i < 16; i++) {
      bit_data[i] = 0;
    }
  } else if (in_mode.compareTo("all_on")) {
    for (int i = 0; i < 16; i++) {
      bit_data[i] = 1;
    }
  } else if (in_mode.compareTo("on_up")) {
    for (int i = 0; i < 16; i++) {
      bit_data[i] = 1;
      i++;
      bit_data[i] = 1;
      delay(500);
    }
  }
}

void light_control() {
  // output light state
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
