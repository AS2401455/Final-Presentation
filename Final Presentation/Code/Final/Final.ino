#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "DC_Motor.h"

#define TEMP_SENSOR_PIN A1 // Analog pin for LM35
#define BUTTON_PIN A0      // Analog pin for LCD Shield buttons

int desiredTemperature = 25; // Default desired temperature
int currentTemperature = 0;  // Current temperature read from the sensor
int motorSpeed = 0;          // Motor speed for AC

void setup() {
    LCD_Init();                     // Initialize LCD
    DC_Init();                      // Initialize Motor
    pinMode(TEMP_SENSOR_PIN, INPUT); // LM35 connected to A1
    LCD_Clear();
    LCD_String_xy(0, 0, "SHAHIN'S AC"); // Static text on the screen
}

int readTemperature() {
    int analogValue = analogRead(TEMP_SENSOR_PIN);
    return (analogValue * 5.0 / 1023.0) * 100; // Convert LM35 output to Celsius
}

void updateMotorSpeed() {
    if (currentTemperature > desiredTemperature) {
        motorSpeed = 255; // Max speed to cool down
        DC_Start(0, DIRECTION_CW, motorSpeed);
    } else if (currentTemperature < desiredTemperature) {
        motorSpeed = 0; // Turn off the motor if below desired temperature
        DC_Stop(0);
    }
}

int readButton() {
    int buttonValue = analogRead(BUTTON_PIN);
    if (buttonValue < 50) return 1;    // SELECT
    if (buttonValue < 200) return 2;  // LEFT
    if (buttonValue < 400) return 3;  // DOWN
    if (buttonValue < 600) return 4;  // UP
    if (buttonValue < 800) return 5;  // RIGHT
    return 0; // No button pressed
}

void loop() {
    currentTemperature = readTemperature(); // Read temperature from sensor

    // Read buttons
    int button = readButton();
    if (button == 4) { // UP button increases desired temperature
        desiredTemperature++;
        _delay_ms(200); // Debounce delay
    }
    if (button == 3) { // DOWN button decreases desired temperature
        desiredTemperature--;
        _delay_ms(200); // Debounce delay
    }

    updateMotorSpeed(); // Update motor speed based on temperature

    // Display on LCD
    LCD_String_xy(1, 0, "Temp:");
    char tempStr[5];
    sprintf(tempStr, "%dC", currentTemperature);
    LCD_String(tempStr);

    LCD_String_xy(1, 10, "Set:");
    char desiredTempStr[5];
    sprintf(desiredTempStr, "%dC", desiredTemperature);
    LCD_String(desiredTempStr);

    _delay_ms(500); // Refresh delay
}

