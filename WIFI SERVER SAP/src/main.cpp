#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#define ledPin 2

// // Set these to your desired credentials. yourAP yourPassword
// const char *ssid = "KTEK_HOST";
// const char *password = "12345678";  // must be atleast 8 character 

#define ssid "KTEK_HOST"
#define password "12345678"

WebServer server(80);


void led_home();
void led_client_on();
void led_client_off();
void no_page();

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.println();
  Serial.println("Configuring access point...");

  server.close();
  delay(100);
  WiFi.mode(WIFI_AP);
  WiFi.disconnect();
  delay(500);

  // Custom IP configuration (optional)
  IPAddress local_ip(192, 168, 1, 1);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0); // 254 allowed users
  // IPAddress subnet(255, 255, 255, 0); // 2 allowed users

  WiFi.softAPConfig(local_ip, gateway, subnet);  // Set custom IP
  // ..................................... (END Custom IP Configuration)

  WiFi.softAP(ssid, password); // Start AP
  // WiFi.softAP(ssid, password, 1, 0, 4);  // max 4 devices (default)

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);  // Should print 192.168.1.1

  server.on("/", led_home);
  server.on("/ledon", led_client_on);
  server.on("/ledoff", led_client_off);
  server.onNotFound(no_page);
  server.begin();
  Serial.println("SERVER STARTED.......");
}

void loop() {
  server.handleClient();
}

String get_html(char s){
  String htmlCode = "<!DOCTYPE html><html>";

  switch (s) {
  case 'O': {
      htmlCode += "<h2>LED IS TURN ON</h2>";
    htmlCode += "<p>Turn Led OFF <a href=\"ledoff\">here</a></p>";
    break;}

    case 'F': {
    htmlCode += "<h2>LED IS TURN OFF</h2>";
    htmlCode += "<p>Turn Led ON <a href=\"ledon\">here</a></p>";
    break;}

    default:{
    htmlCode += "<h2>Welcome KTEK</h2>";
    htmlCode += "<p>Turn Led ON <a href=\"ledon\">here</a></p>";
    htmlCode += "<p>Turn Led OFF <a href=\"ledoff\">here</a></p>";
    }
  }

  // htmlCode += "<p>Turn Led ON <a href=\"ledon\">here</a></p>";
  htmlCode += "</html>";
  
  return htmlCode;
}

void led_home(){
  digitalWrite(ledPin, LOW);
  Serial.println("Index");
  server.send(200, "text/html", get_html('A'));  // it suppose to have it's own page
}

void led_client_on(){
  digitalWrite(ledPin, HIGH);
  Serial.println("Page ON");
  server.send(200, "text/html", get_html('O'));  // it suppose to have it's own page
}

void led_client_off(){
  digitalWrite(ledPin, LOW);
  Serial.println("Page OFF");
  server.send(200, "text/html", get_html('F'));  // it suppose to have it's own page
}

void no_page(){
  digitalWrite(ledPin, LOW);
  Serial.println("no Page");
  server.send(404, "text/plan", "no page");
}
