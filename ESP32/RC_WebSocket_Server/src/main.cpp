// Include the AccelStepper Library
#include <AccelStepper.h> //Version 1.61.0
#include <math.h>
#include <Arduino.h>
#include <WiFi.h>
//#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET 4        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define step constants
#define FULLSTEP 4
#define HALFSTEP 8

// Creates two instances
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper stepper1(FULLSTEP, 2, 16, 4, 17);   // IN1, IN3, IN2, IN4
AccelStepper stepper2(FULLSTEP, 32, 25, 33, 26); //IN1, IN3, IN2, IN4

//Constants
const char *ssid = "";
const char *password = "";

int directionBits[4]; // [0]: Left [1]: Up [2]: Right [3]: Down

//Globals
WebSocketsServer webSocket = WebSocketsServer(80);

// Called when receiving any WebSocket message

void setDirection(char *payload)
{
  if (strcmp(payload, "L0") == 0)
  {
    directionBits[0] = 0;
  }
  else if (strcmp(payload, "L1") == 0)
  {
    directionBits[0] = 1;
  }
  else if (strcmp(payload, "U0") == 0)
  {
    directionBits[1] = 0;
  }
  else if (strcmp(payload, "U1") == 0)
  {
    directionBits[1] = 1;
  }
  else if (strcmp(payload, "R0") == 0)
  {
    directionBits[2] = 0;
  }
  else if (strcmp(payload, "R1") == 0)
  {
    directionBits[2] = 1;
  }
  else if (strcmp(payload, "D0") == 0)
  {
    directionBits[3] = 0;
  }
  else if (strcmp(payload, "D1") == 0)
  {
    directionBits[3] = 1;
  }
  Serial.printf("L:%d U:%d R:%d D:%d\n", directionBits[0], directionBits[1], directionBits[2], directionBits[3]);
}

void onWebSocketEvent_Server(uint8_t num,
                             WStype_t type,
                             uint8_t *payload,
                             size_t length)
{

  // Figure out the type of WebSocket event
  switch (type)
  {
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
    setDirection((char *)payload);

    // Serial.printf((char*)payload);
    webSocket.sendTXT(num, payload);
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

void Motorsteuerung()
{

  if (directionBits[0] == 0 && directionBits[1] == 1 && directionBits[2] == 0 && directionBits[3] == 0) //Geardeaus
  {
    stepper1.setMaxSpeed(500.0);
    stepper2.setMaxSpeed(500.0);
    stepper1.moveTo(-100000);
    stepper2.moveTo(100000);
    stepper1.setSpeed(-500);
    stepper2.setSpeed(500);
    stepper1.run();
    stepper2.run();
  }

  else if (directionBits[0] == 1 && directionBits[1] == 0 && directionBits[2] == 0 && directionBits[3] == 0) //Linkskurve
  {
    stepper1.setMaxSpeed(500.0);
    stepper2.setMaxSpeed(500.0);
    stepper1.moveTo(-100000);
    stepper2.moveTo(-100000);
    stepper1.setSpeed(-500);
    stepper2.setSpeed(-500);
    stepper1.run();
    stepper2.run();
  }

  else if (directionBits[0] == 0 && directionBits[1] == 0 && directionBits[2] == 1 && directionBits[3] == 0) //Rechtskurve
  {
    stepper1.setMaxSpeed(500.0);
    stepper2.setMaxSpeed(500.0);
    stepper1.moveTo(100000);
    stepper2.moveTo(100000);
    stepper1.setSpeed(500);
    stepper2.setSpeed(500);
    stepper1.run();
    stepper2.run();
  }

  else if (directionBits[0] == 0 && directionBits[1] == 0 && directionBits[2] == 0 && directionBits[3] == 1) //Rückwerts
  {
    stepper1.setMaxSpeed(500.0);
    stepper2.setMaxSpeed(500.0);
    stepper1.moveTo(100000);
    stepper2.moveTo(-100000);
    stepper1.setSpeed(500);
    stepper2.setSpeed(-500);
    stepper1.run();
    stepper2.run();
  }

  else if (directionBits[0] == 1 && directionBits[1] == 1 && directionBits[2] == 0 && directionBits[3] == 0) //GrosseLinkskurve
  {
    stepper1.setMaxSpeed(500.0);
    stepper2.setMaxSpeed(250.0);
    stepper1.moveTo(100000);
    stepper2.moveTo(100000);
    stepper1.setSpeed(-500);
    stepper2.setSpeed(250);
    stepper1.run();
    stepper2.run();
  }
  else if (directionBits[0] == 0 && directionBits[1] == 1 && directionBits[2] == 1 && directionBits[3] == 0) //GrosseRechtskurve
  {
    stepper1.setMaxSpeed(250.0);
    stepper2.setMaxSpeed(500.0);
    stepper1.moveTo(100000);
    stepper2.moveTo(100000);
    stepper1.setSpeed(-250);
    stepper2.setSpeed(500);
    stepper1.run();
    stepper2.run();
  }
  else
  {
    stepper1.setCurrentPosition(0);
    stepper2.setCurrentPosition(0);
  }
}

void setup()
{
  // Start Serial port
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  // Clear the buffer
  display.clearDisplay();

  // Connect to access point
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // Print our IP address
  display.clearDisplay();
  display.setTextSize(1); // legt die neu Schriftgöße fest
  display.setTextColor(WHITE);
  display.setCursor(0, 4);
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

  // set the maximum speed, acceleration factor,
  // initial speed and the target position for motor 1
  /*stepper1.setMaxSpeed(500.0);
  stepper1.setAcceleration(1000.0);
  stepper1.setSpeed(0);

  // set the same for motor 2
  stepper2.setMaxSpeed(500.0);
  stepper2.setAcceleration(1000.0);
  stepper2.setSpeed(0);
  */
}

void loop()
{
  // put your main code here, to run repeatedly:
  // Look for and handle WebSocket data
  webSocket.loop();
  Motorsteuerung();
}
