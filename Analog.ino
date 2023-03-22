#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "AC1200";            //add your network name
const char* password = "Tplink@123";    //change your password

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  server.begin();

  // Display the IP address in the serial monitor
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client");
    float voltage = (analogRead(A0) * 3.3) / 1024.0;
    String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html style='background-image: url(\"https://calchip.com/wp-content/uploads/2022/06/opacity-36.png\"); height :100vh;background-size: cover; background-repeat: no-repeat;'>\r\n";
    response += "<body>\r\n";
    response += "<div style='display: flex; align-items: center; justify-content: center; height: 100vh;'>\r\n";
    response += "<div style='background-color: #FFF; padding: 40px; border-radius: 20px; display: flex; flex-direction: column; align-items: center;'>\r\n";
    response += "<div style='background-color: navy; width: 100%; height: 150px; border-radius: 20px 20px 0 0; display: flex; align-items: center; justify-content: center;'>\r\n";
    response += "<h1 style='color: #FFFF00; text-align: center; font-size: 48px; margin: 0;'>ESP8266 Analog Input</h1>\r\n";
    response += "</div>\r\n";
    response += "<p style='font-size: 36px; text-align: center; color: #000;'>Analog Input Voltage: " + String(voltage, 2) + "V</p>\r\n";
    response += "<div style='flex-grow: 1;'></div>\r\n";
    response += "<div style='text-align: center;'><a href='https://www.linkedin.com/in/josephpeter-j' style='font-size: 24px;'>Linked In Profile</a></div>";
    response += "</div>\r\n";
    response += "</div>\r\n";

    response += "</body>\r\n";
    response += "</html>\r\n";
    client.print(response);
    delay(1);
    Serial.println("Client disconnected");
  }
}
