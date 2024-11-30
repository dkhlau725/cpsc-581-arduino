#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 13;
const int buttonPin = 7;
int buttonState = 0;

long duration;
int distance;

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

int viewDistance[] = {
  75, // 24in
  83, // 27in
  113, // 32in
  135, // 43in
  158, // 50in
  170, // 55in
  200, // 65in
  230, // 75in
  260 // 85in
};

float margin = 1.2;
int currentTV = 0;

int counter = 0;

void setup() {
  lcd.begin(16, 2);
  
  // Set pin modes
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

  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distance = duration * 0.034 / 2;

 lcd.setCursor(0, 0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("Distance: "); // Prints string "Distance" on the LCD
  lcd.print(distance); // Prints the distance value from the sensor
  lcd.print(" cm ");

  // LED lights up depending on range
  if (distance > viewDistance[currentTV] / margin && distance < viewDistance[currentTV] * margin) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  buttonState = digitalRead(buttonPin);

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
