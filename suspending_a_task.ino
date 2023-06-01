#include <Arduino_FreeRTOS.h>

#define RED    6
#define YELLOW 7
#define BLUE   8

typedef int TaskProfiler;

TaskProfiler  RedLEDProfiler;
TaskProfiler  YellowLEDProfiler;
TaskProfiler  BlueLEDProfiler;

TaskHandle_t blue_Handle, red_Handle,yellow_Handle;
uint32_t suspend_monitor;

void setup()
{
  Serial.begin(9600);
  xTaskCreate(redLedControllerTask,
              "Red LED Task",
              100,
              NULL,
              1,
              &red_Handle
              );
 xTaskCreate(blueLedControllerTask,
             "Blue LED Task",
             100,
             NULL,
             1,
             &blue_Handle);
 xTaskCreate(yellowLedControllerTask,
             "Yellow LED Task",
             100,
             NULL,
             1,
             &yellow_Handle
             );
}

void redLedControllerTask(void *pvParameters)
{
  pinMode(RED,OUTPUT);

  while(1)
  {
   // digitalWrite(RED,digitalRead(RED)^1);
    RedLEDProfiler++;
    Serial.print("RED Run Time : ");
    Serial.println(RedLEDProfiler);
   vTaskDelay(100);
  }
}

void blueLedControllerTask(void *pvParameters)
{
    pinMode(BLUE,OUTPUT);
    while(1)
    {
     // digitalWrite(BLUE,digitalRead(BLUE)^1);
      BlueLEDProfiler++;
      Serial.print("BLUE Run Time :");
      Serial.println(BlueLEDProfiler);
     
      if(suspend_monitor>=7)
      {
        vTaskSuspend(yellow_Handle);
      }

      vTaskDelay(100);
    }
}

void yellowLedControllerTask(void *pvParameters)
{
   pinMode(YELLOW,OUTPUT);
  while(1)
  {
       suspend_monitor++;

   // digitalWrite(YELLOW,digitalRead(YELLOW)^1);
    YellowLEDProfiler++;
    Serial.print("YELLOW Run Time : ");
    Serial.println(YellowLEDProfiler);
    vTaskDelay(100);
  }
}

void loop()
{}

