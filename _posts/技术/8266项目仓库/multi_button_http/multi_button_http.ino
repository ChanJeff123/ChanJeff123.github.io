#include <ESP8266WiFi.h>
# define d1_pin 5//D1
# define d2_pin 4//D2
# define d3_pin 0//D3
# define d4_pin 13//D7
# define d5_pin 2//板载LED low为亮  也是D4引脚

const char* ssid = "main";
const char* password = "12312311";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(d1_pin, OUTPUT);//D1
  pinMode(d2_pin, OUTPUT);//D2
  pinMode(d3_pin, OUTPUT);//D3
  pinMode(d4_pin, OUTPUT);//D7
  pinMode(d5_pin, OUTPUT);//板载
  digitalWrite(d1_pin, LOW);
  digitalWrite(d2_pin, LOW);
  digitalWrite(d3_pin, LOW);
  digitalWrite(d4_pin, LOW);
  digitalWrite(d5_pin, HIGH);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request


  if (request.indexOf("/light1on") > 0)  {
    digitalWrite(d1_pin, HIGH);

  }
  if (request.indexOf("/light1off") > 0)  {
    digitalWrite(d1_pin, LOW);

  }

  if (request.indexOf("/light2on") > 0)  {
    digitalWrite(d2_pin, HIGH);

  }
  if (request.indexOf("/light2off") > 0)  {
    digitalWrite(d2_pin, LOW);

  }
  if (request.indexOf("/light3on") > 0)  {
    digitalWrite(d3_pin, HIGH);

  }
  if (request.indexOf("/light3off") > 0)  {
    digitalWrite(d3_pin, LOW);

  }
  if (request.indexOf("/light4on") > 0)  {
    digitalWrite(d4_pin, HIGH);
  }
  if (request.indexOf("/light4off") > 0)  {
    digitalWrite(d4_pin, LOW);
  }
  if (request.indexOf("/light5on") > 0)  {
    digitalWrite(d5_pin, LOW);
  }
  if (request.indexOf("/light5off") > 0)  {
    digitalWrite(d5_pin, HIGH);
  }
  // Set ledPin according to the request
  //digitalWrite(ledPin, value);

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
  client.println("</head>");
  client.println("<body bgcolor = \"#f7e6ec\">");
  client.println("<hr/><hr>");
  client.println("<h4><center> Jeff Nodemcu Controller </center></h4>");
  client.println("<hr/><hr>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("Device 1 [D1]");
  client.println("<a href=\"/light1on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/light1off\"\"><button>Turn Off </button></a><br />");
  client.println("</center>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("Device 2 [D2]");
  client.println("<a href=\"/light2on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/light2off\"\"><button>Turn Off </button></a><br />");
  client.println("</center>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("Device 3 [D3]");
  client.println("<a href=\"/light3on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/light3off\"\"><button>Turn Off </button></a><br />");
  client.println("</center>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("Device 4 [D7]");
  client.println("<a href=\"/light4on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/light4off\"\"><button>Turn Off </button></a><br />");
  client.println("</center>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("Device 5 [borad]");
  client.println("<a href=\"/light5on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/light5off\"\"><button>Turn Off </button></a><br />");
  client.println("</center>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("<table border=\"5\">");
  client.println("<tr>");
  if (digitalRead(d1_pin))
  {
    client.print("<td>Light 1 is ON</td>");
  }
  else
  {
    client.print("<td>Light 1 is OFF</td>");
  }
  client.println("<br />");
  if (digitalRead(d2_pin))
  {
    client.print("<td>Light 2 is ON</td>");
  }
  else
  {
    client.print("<td>Light 2 is OFF</td>");
  }
  client.println("</tr>");
  client.println("<tr>");
  if (digitalRead(d3_pin))
  {
    client.print("<td>Light 3 is ON</td>");
  }
  else
  {
    client.print("<td>Light 3 is OFF</td>");
  }
  if (digitalRead(d4_pin))
  {
    client.print("<td>Light 4 is ON</td>");
  }
  else
  {
    client.print("<td>Light 4 is OFF</td>");
  }
  if (digitalRead(d5_pin))
  {
    client.print("<td>Light 5 is OFF</td>");
  }
  else
  {
    client.print("<td>Light 5 is ON</td>");
  }
  client.println("</tr>");
  client.println("</table>");
  client.println("</center>");
  client.println("</html>");
  delay(1);
  Serial.println("Client disConnected");
  Serial.println("");
}
