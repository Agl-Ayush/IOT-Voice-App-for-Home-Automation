#include <WiFi.h>
WiFiClient client;
WiFiServer server(80);
const char* ssid = "Redmi 11 Prime 5G";
const char* password = "12345678";
String command =""; // Command received from Android device

int relay3 = 5; // Set Relay Pins
int relay4 = 4;

void setup()
{
 Serial.begin(115200);
 pinMode(relay3,OUTPUT);
 pinMode(relay4, OUTPUT);
 digitalWrite(relay3,HIGH);
 digitalWrite(relay4,HIGH);
 connectWiFi();
 server.begin();
 }

 void loop()
{
 client = server.available();
 if (!client) return;
 command = checkClient ();
 if (command == "r3on" || command == "turn on relay 3”|| command == "relay 3 on")
 digitalWrite(relay3,0);
 else if (command == "r3off"||command == "turn off relay 3"|| command == "relay 3 off")
 digitalWrite(relay3,1);
 else if (command == "r4on" || command == "turn on relay 4"|| command == "relay 4 on")
 digitalWrite(relay4,0);

 else if (command == "r4off" || command == "turn off relay 4"|| command == "relay 4 off")
 digitalWrite(relay4,1);

 else if (command == "allon"||command == "Turn on all devices"||command == "all on")
 digitalWrite(relay3,LOW);
 digitalWrite(relay4,LOW);
 }
 else if (command == "alloff" || command == "Turn off all devices"|| command == "all off")
 {
 digitalWrite(relay3,HIGH);
 digitalWrite(relay4,HIGH);
 }

sendBackEcho(command); // send command echo back to android device
 command = "";
}

 /* connecting WiFi */
void connectWiFi()
{
 Serial.println("Connecting to WIFI");
 WiFi.begin(ssid, password);
 while ((!(WiFi.status() == WL_CONNECTED)))
 {
 delay(300);
 Serial.print("..");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.println("NodeMCU Local IP is : ");
 Serial.print((WiFi.localIP()));
}

 /* check command received from Android Device */
 String checkClient (void)
{
 while(!client.available()) delay(1);
 String request = client.readStringUntil('\r');
 request.remove(0, 5);
 request.remove(request.length()-9,9);
 return request;
}
 /* send command echo back to android device */
 void sendBackEcho(String echo)
{
 client.println("HTTP/1.1 200 OK ");
 client.println("Content-Type: text/html");
 client.println("");

client.ptinln(“<!DOCTYPE HTTML>”);
client.ptinln(“<html>”);
client.ptinln(“<echo>”);
client.ptinln(“</html>”);
client.stop();
delay(1);
}
