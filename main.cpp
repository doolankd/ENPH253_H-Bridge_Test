#include "Arduino.h"
#include <Wire.h>
#define MOTOR_A1 PB_8
#define MOTOR_A2 PB_9
#define MOTOR_B1 PB_6
#define MOTOR_B2 PB_7
#define POTENTIOMETER PA0

#define PWMFREQ 2000


//below is library for OLED display board
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


volatile int varyDuty = 0;
volatile int varyDuty2 = 0;
volatile int vd = 0;
volatile int vd2 = 0;

void setup() {
  /*
  // Displays Adafruit logo by default. call clearDisplay immediately if you don't want this.
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  */
  delay(2000);

  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);
  pinMode(POTENTIOMETER, INPUT);
}

void loop() {
  varyDuty = analogRead(POTENTIOMETER);
  vd = varyDuty;

  if (varyDuty > 530) {
    vd2 = 0;
    vd = vd - 530;
  } else {
      if (varyDuty < 490) {
        vd2 = 490 - varyDuty;
        vd = 0;
      } else {
        vd = 0;
        vd2 = 0;
      }
  }

  //pwm_start(MOTOR_A, PWM_FREQUENCY,vd * 4,RESOLUTION_10B_COMPARE_FORMAT);
  //pwm_start(MOTOR_B, PWM_FREQUENCY,vd2 * 4,RESOLUTION_10B_COMPARE_FORMAT);

  pwm_start(MOTOR_A1, PWM_FREQUENCY,vd * 3.75,RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_A2, PWM_FREQUENCY,vd2 * 3.75,RESOLUTION_10B_COMPARE_FORMAT);

  pwm_start(MOTOR_B1, PWM_FREQUENCY,vd * 3.75,RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_B2, PWM_FREQUENCY,vd2 * 3.75,RESOLUTION_10B_COMPARE_FORMAT);
/*
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("arbitrary duty");
  display.println(vd);
  display.setCursor(0,15);
  display.println("arbitrary duty2");
  display.println(vd2);
  display.display();
  */

  delay(300);
};
