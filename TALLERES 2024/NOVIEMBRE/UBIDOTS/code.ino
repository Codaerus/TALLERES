#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long t = 0;
const char* DEVICE_LABEL = "codaerus";
const char* VARIABLE_LABEL = "ENVIO";
const char* token = "BBUS-qOXOByvvdlqRrf0fMtom82AFZh1LD8";
int i = 0;
void setup() {
  setup_wifi();
  client.setServer("industrial.api.ubidots.com", 1883);
}

void loop() {
  client.connect("ESP",token,"");
  if(millis()-t>5000){
    //{"value": 27}
    int pot1 = i;
    String payload = "{\"value\": " + String(pot1) + "}";
    client.publish ((String("/v1.6/devices/") +  String(DEVICE_LABEL) + "/" + String(VARIABLE_LABEL)).c_str(), payload.c_str());
    t= millis();
    i = i + 10;
  }
}

void setup_wifi(){
  Serial.begin(9600);
  WiFi.begin("MOVISTAR_78A8","NS2ajtQJ7TtDt9m"); //DHCP
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println(WiFi.localIP());
}
