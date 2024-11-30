#include <LiquidCrystal.h>

// Initialize the LCD ith the pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 13;
const int buttonPin = 7;
int buttonState = 0;

long duration;
int distance;

// List of common TV sizes
String tvSizes[] = {
  "24 inch Monitor", 
  "27 inch Monitor",
  "32 inch Monitor",
  "43 inch TV     ",
  "50 inch TV     ",
  "55 inch TV     ",
  "65 inch TV     ", 
  "75 inch TV     ",
  "85 inch TV     "
};

// List of the average viewing distance for each TV size
int viewDistance[] = {
  75, // 24 in
  83, // 27 in
  113, // 32 in
  135, // 43 in
  158, // 50 in
  170, // 55 in
  200, // 65 in
  230, // 75 in
  260 // 85 in
};

float margin = 1.2;
int currentTV = 0;

int counter = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distance = duration * 0.034 / 2;

 lcd.setCursor(0, 0); // Sets the cursor at the beginning of the LCD screen
  lcd.print("Distance: ");
  lcd.print(distance); 
  lcd.print(" cm ");

  // LED lights up if within optimal viewing range of the selected TV
  if (distance > viewDistance[currentTV] / margin && distance < viewDistance[currentTV] * margin) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // Read buton
  buttonState = digitalRead(buttonPin);

  // Button to toggle through the TV sizes and print on LCD
  if (buttonState == HIGH) {
    lcd.setCursor(0, 1); 
    lcd.print(tvSizes[counter]); 
    currentTV = counter;

    counter++;
    if (counter == sizeof(tvSizes)/sizeof(tvSizes[0])) {
      counter = 0;
    }
    delay(500);
  }

  delay(100); // Wait for half a second before the next measurement
}
