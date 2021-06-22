#include <AccelStepper.h> //Version 1.61.0
#include <math.h>
#include <Arduino.h>
#include <WiFi.h>
//#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SET_BIT(x,n) ((x |= 1UL << n))
#define CLEAR_BIT(x,n) (x &= ~(1UL << n))
#define CHECK_BIT(x,n) ((x >> n) & 1U)

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

uint8_t directionBits = 0;// first 4 bits LSB->MSB: [0]: Left [1]: Up [2]: Right [3]: Down 

//Globals
WebSocketsServer webSocket = WebSocketsServer(80);

// Called when receiving any WebSocket message

void setDirection(char *payload)
{
  if (strcmp(payload, "L0") == 0)
  {
    CLEAR_BIT(directionBits,0)
  }
  else if (strcmp(payload, "L1") == 0)
  {
    SET_BIT(directionBits,0)
  }
  else if (strcmp(payload, "U0") == 0)
  {
    CLEAR_BIT(directionBits,1)
  }
  else if (strcmp(payload, "U1") == 0)
  {
    SET_BIT(directionBits,1)
  }
  else if (strcmp(payload, "R0") == 0)
  {
    CLEAR_BIT(directionBits,2)
  }
  else if (strcmp(payload, "R1") == 0)
  {
    SET_BIT(directionBits,2)
  }
  else if (strcmp(payload, "D0") == 0)
  {
    CLEAR_BIT(directionBits,3)
  }
  else if (strcmp(payload, "D1") == 0)
  {
    SET_BIT(directionBits,3)
  }
  Serial.printf("L:%d U:%d R:%d D:%d\n", CHECK_BIT(directionBits,0),CHECK_BIT(directionBits,1),CHECK_BIT(directionBits,2),CHECK_BIT(directionBits,3));
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

  if (directionBits == 0x02) //Geardeaus //0010 -> 0x02
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

  else if (directionBits == 0x01) //Linkskurve //0001 -> 0x01
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

  else if (directionBits == 0x04) //Rechtskurve //0100->0x04
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

  else if (directionBits == 0x08) //Rückwerts //1000->0x08
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

  else if (directionBits == 0x03) //GrosseLinkskurve //0011->0x03
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
  else if (directionBits == 0x06) //GrosseRechtskurve //0110-> 0x06
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
