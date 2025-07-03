#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

bool fanState = false;
bool lightState = false;
String doorStatus = "Closed";
String fanStatus = "OFF";
String lightStatus = "OFF";

// Sound sensor pins and clap logic

unsigned long lastClapTime = 0;
int clapCount = 0;

// OLED config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins
const int trigPin = 9;
const int echoPin = 8;
const int servoPin = 10;
const int ldrPin = A0;
const int soundSensorPin = 7;
const int lightLED = 6;
const int fanLED = 5;

Servo myServo;

// For clap control

unsigned long lastSoundTime = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(soundSensorPin, INPUT);
  pinMode(lightLED, OUTPUT);
  pinMode(fanLED, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(0);  // Door closed

  // OLED init
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while(1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Multi-Sensory System");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  checkUltrasonic();
  checkLDR();
  checkSound();
  updateOLED();
  delay(100);
}


void checkUltrasonic() {
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  if (distance > 0 && distance < 5) {
    myServo.write(90);
    doorStatus = "Opened";

  } else {
    myServo.write(0);
    doorStatus = "Closed";

  }
}


void checkLDR() {
  int ldrValue = analogRead(ldrPin);

  if (ldrValue > 300) {
    digitalWrite(lightLED, HIGH);
    lightState = true;
    lightStatus = "ON";
    delay(1000);

  } else {
    digitalWrite(lightLED, LOW);
    lightState = false;
    lightStatus = "OFF";

  }
}


void checkSound() {
  int soundVal = digitalRead(soundSensorPin);
  unsigned long currentTime = millis();

  if (soundVal == HIGH) {
    if (currentTime - lastClapTime < 800) {
      clapCount++;
    } else {
      clapCount = 1;
    }
    lastClapTime = currentTime;

    if (clapCount == 4) {
      fanState = !fanState;
      digitalWrite(fanLED, fanState);
      fanStatus = fanState ? "ON" : "OFF";
      clapCount = 0;
    }
  }
}


void updateOLED() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.println("Multi-Sensory System");
  display.println("---------------------");
  display.print("Door: "); display.println(doorStatus);
  display.print("Light: "); display.println(lightStatus);
  display.print("Fan: "); display.println(fanStatus);

  display.display();
}





void doorAnimation(bool open) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println(open ? "Door Opening" : "Door Closing");

  display.drawRect(30, 20, 60, 30, WHITE);  // Room

  if (open) {
    for (int i = 0; i < 20; i += 5) {
      display.drawLine(90, 20, 90 - i, 50, WHITE); // Swing door
      display.display();
      delay(100);
      display.clearDisplay();
      display.drawRect(30, 20, 60, 30, WHITE);
    }
  } else {
    display.drawLine(90, 20, 90, 50, WHITE); // Door closed
    display.display();
    delay(300);
  }
}







