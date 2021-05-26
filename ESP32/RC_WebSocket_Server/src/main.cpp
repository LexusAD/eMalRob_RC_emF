#include <Arduino.h>
// #include <WiFi.h>
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Constants
const char* ssid = "";
const char* password = "";

int directionBits[4]; // [0]: Left [1]: Up [2]: Right [3]: Down


//Globals
WebSocketsServer webSocket = WebSocketsServer(80);

// Called when receiving any WebSocket message

void setDirection(char *payload){
      if (strcmp(payload,"L0") == 0)
      {
        directionBits[0] = 0;
      }
      else if (strcmp(payload,"L1") == 0)
      {
        directionBits[0] = 1;
      }
      else if (strcmp(payload,"U0") == 0)
      {
        directionBits[1] = 0;
      }
      else if (strcmp(payload,"U1") == 0)
      {
        directionBits[1] = 1;
      }
      else if (strcmp(payload,"R0") == 0)
      {
        directionBits[2] = 0;
      }
      else if (strcmp(payload,"R1") == 0)
      {
        directionBits[2] = 1;
      }
      else if (strcmp(payload,"D0") == 0)
      {
        directionBits[3] = 0;
      }
      else if (strcmp(payload,"D1") == 0)
      {
        directionBits[3] = 1;
      }
      Serial.printf("L:%d U:%d R:%d D:%d\n",directionBits[0],directionBits[1],directionBits[2],directionBits[3]);
}



void onWebSocketEvent_Server(uint8_t num,
                      WStype_t type,
                      uint8_t * payload,
                      size_t length) {

  // Figure out the type of WebSocket event
  switch(type) {
    // Client has disconnected
    case WStype_DISCONNECTED:
      Serial.printf("Disconnected!", num);
      break;

    // New client has connected
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("Connection from ", num);
        Serial.println(ip.toString());
      }
      break;

    // Echo text message back to client
    case WStype_TEXT:
      //Serial.printf("%s\n",payload);
      setDirection((char*)payload);

      // Serial.printf((char*)payload);
      webSocket.sendTXT(num,payload);
      break;

    // For everything else: do nothing
    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
    default:
      break;
  }
}

/*void onWebSocketEvent_Client(WStype_t type, uint8_t * payload, size_t length)
{
  int i = 0; //counter
  webSocket.sendTXT("Test!");
  Serial.print("onWebSocketEvent wurde getriggert.  Länge: ");
  Serial.print(length);
  Serial.print("   Typ: ");
  Serial.println(type);
  if(length > 0)
  {
  if(type == WStype_TEXT)
  {
  display.clearDisplay(); 
  display.setTextSize(1); // legt die neu Schriftgöße fest 
  display.setTextColor(WHITE);
  display.setCursor(0,4);
  for(i = 0; i < length; i++)
  display.print(payload[i]);
  display.display();
  webSocket.sendTXT("Alles gut");
  }
  else
  {
  display.clearDisplay(); 
  display.setTextSize(2); // legt die neu Schriftgöße fest 
  display.setTextColor(WHITE);
  display.setCursor(0,4);
  for(i = 0; i < length; i++)
  display.print(payload[i]);
  display.display();
  webSocket.sendTXT("Falscher Typ :|");
  }
  }
}*/

void setup() {

  // Start Serial port
  Serial.begin(115200);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Clear the buffer
  display.clearDisplay();

  // Connect to access point
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }

  // Print our IP address
  display.clearDisplay(); 
  display.setTextSize(1); // legt die neu Schriftgöße fest 
  display.setTextColor(WHITE);
  display.setCursor(0,4);
  Serial.println("Connected!");
  Serial.print("My IP address: ");
  display.println("Connected!");
  display.println("My IP address: ");
  Serial.println(WiFi.localIP());
  display.print(WiFi.localIP());
  display.display();
  // Start WebSocket server and assign callback
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent_Server);
  //webSocket.setReconnectInterval(5000); //reconnect versuch alle 5s
}

void loop() {

  // Look for and handle WebSocket data
  webSocket.loop();
}
