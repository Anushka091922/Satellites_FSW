#include <Arduino_FreeRTOS.h>

#define RED    6
#define YELLOW 7
#define BLUE   8

typedef int TaskProfiler;

TaskProfiler  RedLEDProfiler;
TaskProfiler  YellowLEDProfiler;
TaskProfiler  BlueLEDProfiler;

void setup()  //we have just created the setup function 
{
  Serial.begin(9600);
  xTaskCreate(redLedControllerTask,   //created the task . and first argument is the task function
              "Red LED Task",
              100,   // decide between 100 to 128.we can not assign zero or null value to this 
              NULL,   // parameter passing 
              1,      // priority .higher the number higher the priority . we can not assign zero or null value to this
              NULL     // task hondo 
              );
 xTaskCreate(blueLedControllerTask,
             "Blue LED Task",
             100,
             NULL,
             1,
             NULL);
 xTaskCreate(yellowLedControllerTask,
             "Yellow LED Task",
             100,
             NULL,
             1,
             NULL
             );
}

void redLedControllerTask(void *pvParameters)  //void_name of the task function
{
  pinMode(RED,OUTPUT);   //for printing . name of the pin and output 

  while(1)
  {
   Serial.println("This is RED"); 
  }
}

void blueLedControllerTask(void *pvParameters)
{
    pinMode(BLUE,OUTPUT);
    while(1)
    {
     Serial.print("This is BLUE");
    }
}

void yellowLedControllerTask(void *pvParameters)
{
   pinMode(YELLOW,OUTPUT);
  while(1)
  {
   Serial.println("This is YELLOW");
  }
}

void loop()
{}
// althought we are not using the void loop we will always have to include that in our code .'
//  so here basically as we have given the same priority to all the tasks then 
//  the two tasks can now access the computer . but we can simply make use of the semaphores to actually allow 
// only one task to access the cpu 
