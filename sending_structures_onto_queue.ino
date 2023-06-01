#include <Arduino_FreeRTOS.h>
#include "queue.h"


typedef int TaskProfiler;

TaskProfiler SenderProfiler;
TaskProfiler receiverProfiler;

typedef enum
{
  eSender1,
  eSender2,
}DataSource_t;

typedef struct
{
  uint8_t ucValue;
  DataSource_t eDataSource;
}Data_t;


static const Data_t xStructToSend[2]=
{
  {100,eSender1},
  {50,eSender2}
};


QueueHandle_t xQueue;
void setup()
{  
   Serial.begin(9600);
   xQueue = xQueueCreate(3,sizeof(Data_t));

   xTaskCreate(vSenderTask,"Sender Task 1", 100,&(xStructToSend[0]),2,NULL);
   xTaskCreate(vSenderTask,"Sender Task 2", 100,&(xStructToSend[1]),2,NULL);

   xTaskCreate(vReceiverTask,"Receiver Task", 100,NULL,1,NULL);   
   
}


void vSenderTask (void *pvParameters)
{
  BaseType_t xStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  while(1)
  {
     xStatus  = xQueueSend(xQueue,pvParameters,xTicksToWait);
     if(xStatus != pdPASS)
     {
      Serial.println("Could not send to the queue ");
     }
  }
}

void vReceiverTask(void *ovParameters)
{
  Data_t xReceivedStructure;
  BaseType_t xStatus;

   while(1)
   {
       xStatus = xQueueReceive(xQueue,&xReceivedStructure,0);
       if(xStatus == pdPASS)
       {
        if(xReceivedStructure.eDataSource  == eSender1)
        {
          Serial.print("Thi is from sender 1  : ");
          Serial.println(xReceivedStructure.ucValue);
        }
        else
        {
          Serial.print("This is from sender 2 : ");
          Serial.println(xReceivedStructure.ucValue);
        }
       }
      else
      Serial.println("Could not receive data from the queue");
   }
}
void loop(){}

