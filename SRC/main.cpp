/**
 * @file main.cpp
 * @brief Control a servo motor based on ultrasonic distance detection.
 * * When an object is detected within a certain range, the servo moves
 * by a specified number of degrees.
 */

#include <Arduino.h>
#include <ESP32Servo.h>

// --- Configuration ---
const int trigPin = 2;    ///< Trigger pin of the HC-SR04
const int echoPin = 15;   ///< Echo pin of the HC-SR04
const int servoPin = 13;  ///< Signal pin of the Servo

/** * @brief Adjust these values to change the behavior
 */
const int detectionThreshold = 30; ///< Distance in cm to trigger the movement
const int baseAngle = 0;           ///< Starting position of the servo
const int movementDegrees = 25;    ///< How many degrees to move (the "few degrees")

Servo myServo;

/**
 * @brief Initializes sensors and servo settings.
 */
void setup() {
    Serial.begin(115200);
    
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // ESP32 Specific Servo Setup
    ESP32PWM::allocateTimer(0);
    myServo.setPeriodHertz(50); 
    myServo.attach(servoPin, 500, 2400);
    
    myServo.write(baseAngle);
    Serial.println("System online. Waiting for motion...");
}

/**
 * @brief Reads distance and moves the servo if an object is within threshold.
 */
void loop() {
    // 1. Trigger the ultrasonic pulse
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // 2. Measure the time it takes for the sound to return
    long duration = pulseIn(echoPin, HIGH);

    // 3. Convert time to distance in centimeters
    int distance = duration * 0.034 / 2;

    // Debugging: View distance in Serial Monitor
    if (distance > 0 && distance < 400) {
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
    }

    // 4. Action Logic
    /**
     * If something is closer than detectionThreshold, move to (base + movementDegrees).
     * Otherwise, stay at/return to baseAngle.
     */
    if (distance > 0 && distance < detectionThreshold) {
        myServo.write(baseAngle + movementDegrees); 
        Serial.println("Object detected! Moving servo.");
        delay(500); // Keep it moved for a short duration
    } else {
        myServo.write(baseAngle);
    }

    delay(100); // Stability delay
}
