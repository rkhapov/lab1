#include "pitches.h"
#include "button.h"
#include "buzzer.h"

#define R_OUT 6
#define G_OUT 7
#define B_OUT 8

MD_TCS230 colorSensor(S2_OUT, S3_OUT, S0_OUT, S1_OUT);

void setup()
{
    Serial.begin(115200);
    Serial.println("Started!");

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

    colorSensor.getRGB(&rgb);
    print_rgb(rgb);
    set_rgb_led(rgb);
}

void print_rgb(colorData rgb)
{
  Serial.print(rgb.value[TCS230_RGB_R]);
  Serial.print(" ");
  Serial.print(rgb.value[TCS230_RGB_G]);
  Serial.print(" ");
  Serial.print(rgb.value[TCS230_RGB_B]);
  Serial.println();
}
  
void set_rgb_led(colorData rgb)
{
    analogWrite(R_OUT, 255 - rgb.value[TCS230_RGB_R]);
    analogWrite(G_OUT, 255 - rgb.value[TCS230_RGB_G]);
    analogWrite(B_OUT, 255 - rgb.value[TCS230_RGB_B]);
}
