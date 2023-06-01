#include <Arduino_FreeRTOS.h>

#define RED     6
#define BLUE    8
#define YELLOW  7

typedef int TaskProfiler;

TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler BlueLEDProfiler;
// how we can actually chnage the priority of the task when the task is already created 
TaskHandle_t blue_Handle,red_Handle,yellow_handle;   //second code line part 

void setup()
{
  xTaskCreate(redLedControllerTask,"RED LED Task",100,NULL,3,NULL);
  xTaskCreate(blueLedControllerTask,"BLUE LED Task", 100, NULL,3,NULL);
  xTaskCreate(yellowLedControllerTask,"YELLOW LED Task", 100, NULL,3,NULL);  
}


void redLedControllerTask(void *pvParameters)
{
  pinMode(RED,OUTPUT);  //pin the led 
  while(1)
  {
   digitalWrite(RED,digitalRead(RED)^1);   //to toggle red we are using this 
  }
}

void blueLedControllerTask(void *pvParameters)
{
  pinMode(BLUE,OUTPUT);
  while(1)
  {
   digitalWrite(BLUE,digitalRead(BLUE)^1); 
  }
}

void yellowLedControllerTask(void *pvParameters)
{
  pinMode(YELLOW,OUTPUT);
  while(1)
  {
    digitalWrite(YELLOW,digitalRead(YELLOW)^1);
    vTaskPrioritySet (red_Handle,2); //after yellow is toggle we will set the priority of the rd as 2. and we are also introsucing the delay of 
    // some time 
    delay(50);  //delay to see the change 
  }
}

void loop(){}

