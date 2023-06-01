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
uint32_t resume_monitor;
bool  _suspended = false;

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
   digitalWrite(RED,digitalRead(RED)^1);
    RedLEDProfiler++;
    Serial.print("RED Run Time : ");
    Serial.println(RedLEDProfiler);
   vTaskDelay(10);
  }
}

void blueLedControllerTask(void *pvParameters)
{
    pinMode(BLUE,OUTPUT);
    while(1)
    {
      digitalWrite(BLUE,digitalRead(BLUE)^1);
      BlueLEDProfiler++;
      Serial.print("BLUE Run Time :");
      Serial.println(BlueLEDProfiler);
             suspend_monitor++;

      if(suspend_monitor>=30)
      {
        _suspended = true;
         suspend_monitor =0;
         
        vTaskSuspend(NULL);
        
      }

      vTaskDelay(10);
    }
}

void yellowLedControllerTask(void *pvParameters)
{
   pinMode(YELLOW,OUTPUT);
  while(1)
  {

    digitalWrite(YELLOW,digitalRead(YELLOW)^1);
    YellowLEDProfiler++;
    Serial.print("YELLOW Run Time : ");
    Serial.println(YellowLEDProfiler);
    Serial.println(" ");

    vTaskDelay(10);
     if(_suspended)
     {
      resume_monitor++;
      if(resume_monitor >=10)
       {
        vTaskResume(blue_Handle);
        resume_monitor =0;
        _suspended =false;
       }
     }
  }
}

void loop()
{}

