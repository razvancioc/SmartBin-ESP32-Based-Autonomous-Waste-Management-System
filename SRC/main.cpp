#include <Arduino.h>
#include <Servo.h>

// Define pins for Arduino Uno
const int trigPin = 2;
const int echoPin = 3;
const int servoPin = 9;

// Adjustable parameters
const int detectionThreshold = 30; // Distance in cm
const int baseAngle = 90;          // Idle position (base angle)
const int movementDegrees = -90;  // How many degrees to move

Servo myServo;

void setup() {
    Serial.begin(9600); // Standard baud rate for Uno
    
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    myServo.attach(servoPin);
    myServo.write(baseAngle);
    
    Serial.println("System initialized on Arduino Uno. Waiting for movement...");
}

void loop() {
    // 1. Generate the pulse (Trigger)
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // 2. Read the time (Echo)
    long duration = pulseIn(echoPin, HIGH);
    
    // 3. Calculate distance in cm
    int distance = duration * 0.034 / 2;
    
    // Print to terminal for debugging
    if (distance > 0 && distance < 1000) {
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
    }
    
    // 4. Action logic
    if (distance > 0 && distance < detectionThreshold) {
        myServo.write(baseAngle + movementDegrees); 
        Serial.println("Object detected! Servo activated.");
        delay(1000); // Keep it moved for a moment
    } else {
        myServo.write(baseAngle);
    }
    
    delay(500); // Pause for stability
}
