#include <Arduino.h>
#include <MD_TCS230.h>

#include "button.h"

#define  S0_OUT  2
#define  S1_OUT  3
#define  S2_OUT  4
#define  S3_OUT  5

#define R_OUT 6
#define G_OUT 7
#define B_OUT 8

#define R_CONTROL_PIN 9
#define G_CONTROL_PIN 10
#define B_CONTROL_PIN 11

MD_TCS230 colorSensor(S2_OUT, S3_OUT, S0_OUT, S1_OUT);

bool rEnabled = true;
bool gEnabled = true;
bool bEnabled = true;

Button rButton(R_CONTROL_PIN);
Button gButton(G_CONTROL_PIN);
Button bButton(B_CONTROL_PIN);

void setup()
{
    Serial.begin(115200);
    Serial.println("Started!");

    sensorData whiteCalibration;
    whiteCalibration.value[TCS230_RGB_R] = 0;
    whiteCalibration.value[TCS230_RGB_G] = 0;
    whiteCalibration.value[TCS230_RGB_B] = 0;

    sensorData blackCalibration;
    blackCalibration.value[TCS230_RGB_R] = 0;
    blackCalibration.value[TCS230_RGB_G] = 0;
    blackCalibration.value[TCS230_RGB_B] = 0;

    colorSensor.begin();
    colorSensor.setDarkCal(&blackCalibration);
    colorSensor.setWhiteCal(&whiteCalibration);

    pinMode(R_OUT, OUTPUT);
    pinMode(G_OUT, OUTPUT);
    pinMode(B_OUT, OUTPUT);
}

void loop() 
{
    colorData rgb;
    colorSensor.read();
    while (!colorSensor.available());

    if (rButton.wasPressed()){
      rEnabled = !rEnabled;
    }

    if (gButton.wasPressed()) {
      gEnabled = !gEnabled;
    }

    if (bButton.wasPressed()){
      bEnabled = !bEnabled;
    }
    
    colorSensor.getRGB(&rgb); 
    set_rgb_led(rgb);
}

void set_rgb_led(colorData rgb)
{
    if (rEnabled) {
      analogWrite(R_OUT, 255 - rgb.value[TCS230_RGB_R]);
    }
    else {
      analogWrite(R_OUT, 255);
    }


    if (gEnabled) {
      analogWrite(G_OUT, 255 - rgb.value[TCS230_RGB_G]);
    }
    else {
      analogWrite(G_OUT, 255);
    }


    if (bEnabled) {
      analogWrite(B_OUT, 255 - rgb.value[TCS230_RGB_B]);
    }
    else {
      analogWrite(B_OUT, 255);
    }
}
