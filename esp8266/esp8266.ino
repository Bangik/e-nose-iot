#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLoqVVYVDV"
#define BLYNK_DEVICE_NAME "esp arduino2"
#define BLYNK_AUTH_TOKEN "QpkRo2AATmP6Fj2btaTQkskDVLA0Yhw_"

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Murni Fotocopy";
char pass[] = "Sudahdiganti7";
char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;
const char* fingerprint = "D8 F3 33 1C 03 51 B8 09 14 20 E0 84 4F B3 69 3F 41 D1 EA 1C";

double MQ4;
double MQ136;
double MQ137;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimer);
}

String splitString(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void kirimDataKeServer(){
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  client->setFingerprint(fingerprint);
  // client->setInsecure();
  HTTPClient https;

  String postData;
  //Post Data
  postData = "{\"mq4\":";
  postData += MQ4;
  postData += ",\"mq136\":";
  postData += MQ136;
  postData += ",\"mq137\": ";
  postData += MQ137;
  postData += "}";
  
  https.begin(*client, "https://e-nose.bangik.live/insert.php");
  https.addHeader("Content-Type", "application/json");
      
  int httpCode = https.POST(postData);   //Send the request
  if (httpCode < 0) {
    Serial.printf("[HTTP] ... failed, error: %s\n", https.errorToString(httpCode).c_str());
  }
  const String& payload = https.getString();    //Get the response payload
  
  Serial.print("https code : ");
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println("payload : " + payload);    //Print request response payload
  Serial.println("post data " + postData);
      
  https.end();
}

void myTimer() 
{
  Blynk.virtualWrite(V0,  MQ4);
  Blynk.virtualWrite(V1,  MQ136);
  Blynk.virtualWrite(V2,  MQ137);
  kirimDataKeServer();
}

void loop() {
  if(Serial.available()){
    String msg = "";
    while(Serial.available()){
      msg += char(Serial.read());
      delay(1);
    }
    
    MQ4 = splitString(msg, ';', 0).toDouble();
    MQ136 = splitString(msg, ';', 1).toDouble();
    MQ137 = splitString(msg, ';', 2).toDouble();
  }

  Blynk.run(); 
  timer.run();
}