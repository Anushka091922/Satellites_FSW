#include <Arduino_FreeRTOS.h>

#define RED      6
#define YELLOW  7
#define BLUE    8


typedef int TaskProfiler;

TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler BlueLEDProfiler;

TaskHandle_t  blue_Handle,red_Handle, yellow_Handle;

void setup()
{
  Serial.begin(9600);
  xTaskCreate(redLedControllerTask, "RED LED Task",100,NULL,1,&red_Handle);
  xTaskCreate(blueLedControllerTask, "BLUE LED Task", 100, NULL, 1,&blue_Handle);
  xTaskCreate(yellowControllerTask, "YELLOW LED Task", 100,NULL,1,&yellow_Handle);
  
}

void redLedControllerTask(void *pvParameters)
{
  pinMode(RED,OUTPUT);
  while(1)
  {
     RedLEDProfiler++;   //this will increment when the task will run
     Serial.print("RedTask Run Time : ");   //simple print statemnet 
     Serial.println(RedLEDProfiler);
  //  digitalWrite(RED, digitalRead(RED)^1);
    delay(300);
  }
}

void blueLedControllerTask(void *pvParameters)
{
  pinMode(BLUE,OUTPUT);
  while(1)
  {
    BlueLEDProfiler++;
    Serial.print("BlueTask Run Time : ");
    Serial.println(BlueLEDProfiler);
    //digitalWrite(BLUE,digitalRead(BLUE)^1);
    delay(300);
  }
}

void yellowControllerTask(void *pvParameters)
{
  pinMode(YELLOW,OUTPUT);
  while(1)
  {
    YellowLEDProfiler++;
    Serial.print("YellowTask Run Time : ");
    Serial.println(YellowLEDProfiler);
    //digitalWrite(YELLOW,digitalRead(YELLOW)^1);
    
    vTaskPrioritySet(NULL,2);
    delay(300);
  }
}
void loop(){}
