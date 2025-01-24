#include "trk_messageDefinitions.h"
#include "trk_message.h"
#include "trk_messageFunctions.h"
#include "ata_message.h"

#define TRUE 1
#define FALSE 0

#ifndef MAX_MESSAGE_NUMBER
   #define MAX_MESSAGE_NUMBER 50
#endif

#ifndef IMMEDIATE_NEXTCHECK
   #define IMMEDIATE_NEXTCHECK TRUE
#endif

#ifndef HIGH_PRIORITY_MESSAGE_ENABLED
   #define HIGH_PRIORITY_MESSAGE_ENABLED TRUE
#endif

#ifndef PERIODIC_MESSAGE_ENABLED
   #define PERIODIC_MESSAGE_ENABLED FALSE
#endif

#ifndef GOZCU_ENABLED
   #define GOZCU_ENABLED FALSE
#endif

#ifndef START_STOP_ENABLED
   #define START_STOP_ENABLED FALSE
#endif

#define THERE_IS_NO_NEXT_CHECK_MESSAGE 0XFF
#define HUGE_SYSTEM_CLOCK 0x80000000


static trk_8BitProperty trk_MessagesProperties[MAX_MESSAGE_NUMBER];

static trk_MessageCounter_t trk_Messages[MAX_MESSAGE_NUMBER];
unsigned long trk_SystemClock = 0;
static unsigned char trk_MaxMessageCounter = 0;
static unsigned int trk_PauseClockCounter = 0;
static unsigned char trk_PushNonExistingMessageWhilePausingState = TRUE;
#if (GOZCU_ENABLED == TRUE)
static unsigned char trk_1msTimerFired = FALSE;
#endif

#if (IMMEDIATE_NEXTCHECK == TRUE)
static unsigned char trk_NextCheckMessagePointer = THERE_IS_NO_NEXT_CHECK_MESSAGE;
#endif

#if (HIGH_PRIORITY_MESSAGE_ENABLED == TRUE)
static trk_MessageFunction trk_HighPriorityFunction = 0x00;
static unsigned char trk_HighPriorityFunctionIndex = 0;
#endif

#if (START_STOP_ENABLED == TRUE)
static unsigned char trk_Is1msTimerEnabled = TRUE;
#endif

unsigned char trk_GetMaxMessegeCounter(void)
{
   return trk_MaxMessageCounter;
}

void trk_PushNonExistingMessageWhilePausing(unsigned char state)
{
   trk_PushNonExistingMessageWhilePausingState = state;
}

void trk_ReArrangeSystemClock(void)
{
   unsigned char counter;
   if (trk_SystemClock > (HUGE_SYSTEM_CLOCK + msg_ProcessAfter1h))
   {
      trk_SystemClock -= HUGE_SYSTEM_CLOCK;
      for (counter = 0; counter < MAX_MESSAGE_NUMBER; counter++)
      {
         trk_Messages[counter].TimeToProcess -= HUGE_SYSTEM_CLOCK;
      }
   }
}

void trk_FindAndPushMessage(trk_messages message, void *user_data, trk_msgProcessTime ProcessTime)
{
   const trk_MessageFunctions_t *ptr = trk_messageFunctionsArray;
   do
   {
      if (ptr->message == message)
      {
         if (ProcessTime == msg_ProcessInstant)
         {
            ptr->messageFunction(user_data);
         }
         else
         {
            trk_PushMessage(ptr->messageFunction, user_data, ProcessTime);
         }
      }
      ptr++;
   }
   while (ptr->message != msg_LastMessage);
}

unsigned char trk_FindMessagePosition(trk_MessageFunction function)
{
   unsigned char messagepos = 0;
   unsigned char firststoppedfunction = 0xFF;

   while ( (messagepos != MAX_MESSAGE_NUMBER) && 
           ( (trk_Messages[messagepos].messagefunction != 0x0000) || (trk_MessagesProperties[messagepos].isprotected == TRUE) ) && 
           ( (trk_Messages[messagepos].messagefunction != function) || (trk_MessagesProperties[messagepos].stopped == TRUE) ) 
         )
   {
      if ( (trk_MessagesProperties[messagepos].stopped == TRUE) && (firststoppedfunction == 0xFF) &&
           (trk_MessagesProperties[messagepos].isprotected == FALSE) )
      {
         firststoppedfunction = messagepos;
      }
      messagepos++;
   }   
   if (trk_Messages[messagepos].messagefunction == function)
   {
      return messagepos;
   }
   else if (firststoppedfunction != 0xFF)
   {
      return firststoppedfunction;
   }
   return messagepos;
}

#if (HIGH_PRIORITY_MESSAGE_ENABLED == TRUE)
void trk_SetHighPriorityFunction(trk_MessageFunction function)
{
   trk_HighPriorityFunction = function;
   trk_HighPriorityFunctionIndex = trk_FindMessagePosition(function);
}
#endif

unsigned char trk_IsMessagePushed(trk_MessageFunction function)
{
   unsigned char position = trk_FindMessagePosition(function);
   if (trk_Messages[position].messagefunction == function)
   {
      return ( (TRUE) && ((trk_MessagesProperties[position].stopped == FALSE)) );
   }
   else
   {
      return FALSE;
   }
}

unsigned long trk_GetMessageRemainingTime(trk_MessageFunction function)
{
   unsigned char position = trk_FindMessagePosition(function);
   if ( (trk_Messages[position].messagefunction == function) && (trk_MessagesProperties[position].stopped == FALSE) )
   {
      return (trk_Messages[position].TimeToProcess-trk_SystemClock);
   }
   else
   {
      return 0;
   }
}

unsigned char trk_CheckMessage(unsigned char counter)
{
   unsigned long messageRefreshTime;
   trk_MessageFunction messagefunction;
   if (trk_SystemClock >= trk_Messages[counter].TimeToProcess)
   {
      if ( (trk_MessagesProperties[counter].paused == FALSE) && (trk_MessagesProperties[counter].stopped == FALSE) )
      {
         messagefunction = trk_Messages[counter].messagefunction;
         messageRefreshTime = messagefunction(trk_Messages[counter].user_data);
         
         if (messagefunction != trk_Messages[counter].messagefunction)
         {
            // in message function, message array is changed, so don't do anything.
         }
         else if (trk_SystemClock < trk_Messages[counter].TimeToProcess)
         {
            // in message function, this message is pushed again, so don't do anything.
         }
         else if (messageRefreshTime == msg_ProcessStopped)
         {
            trk_MessagesProperties[counter].stopped = TRUE;
            trk_Messages[counter].TimeToProcess = trk_SystemClock + msg_ProcessAfter1m;
            #if (HIGH_PRIORITY_MESSAGE_ENABLED == TRUE)            
            if (counter == trk_HighPriorityFunctionIndex)
            {
               trk_HighPriorityFunction = 0x0000;
            }
            #endif
            #if (PERIODIC_MESSAGE_ENABLED == TRUE)
            trk_MessagesProperties[counter].isperiodic = FALSE;
            #endif
         }
         else if (messageRefreshTime == msg_ProcessPause)
         {
            trk_MessagesProperties[counter].paused = TRUE;
         }
         else 
         {
            if (messageRefreshTime == msg_ProcessNextCheck)
            {
               messageRefreshTime = 0x00;
            }
            #if (PERIODIC_MESSAGE_ENABLED == TRUE)
            if (trk_MessagesProperties[counter].isperiodic == TRUE)
            {
               trk_Messages[counter].TimeToProcess += messageRefreshTime;
            }
            else               
            #endif
            {
               trk_Messages[counter].TimeToProcess = trk_SystemClock + messageRefreshTime;
            }
         }
      }
   }
   return counter;
}

void trk_PushMessage(trk_MessageFunction messagefunction, void *user_data, trk_msgProcessTime ProcessTime)
{
   static unsigned char trk_pushmessagecounter = 0;
   unsigned char trk_messagepos = 0xFF;
   unsigned char trk_pushmessagecountertemporary;
   #if (HIGH_PRIORITY_MESSAGE_ENABLED == TRUE)
   if (ProcessTime == msg_ProcessCheckHighPriorityFunction)
   {
      if (trk_HighPriorityFunction != 0x0000)
      {
         trk_CheckMessage(trk_HighPriorityFunctionIndex);
         return;
      }   
   }
   #endif

   /* if any interrupt which has a pushmessage has been fired during findposition function, a new message position should be found */
   /* Because this messagepos may already been used by the pushmessage fired in the interrupt */
   do
   {
      if (trk_messagepos != 0xFF)
      {
         trk_MessagesProperties[trk_messagepos].isprotected = FALSE; // to clear previous wrong protected message
      }
      trk_pushmessagecountertemporary = trk_pushmessagecounter;
      trk_messagepos = trk_FindMessagePosition(messagefunction);
      trk_MessagesProperties[trk_messagepos].isprotected = TRUE;
   }
   while (trk_pushmessagecountertemporary != trk_pushmessagecounter); 

   trk_pushmessagecounter++;

   if (trk_messagepos == MAX_MESSAGE_NUMBER)
   {
      ata_MessageStackOverflow();
   }
   else
   {
      if (ProcessTime == msg_ProcessStopped)
      {
         if (trk_Messages[trk_messagepos].messagefunction != 0x0000)
         {
            trk_MessagesProperties[trk_messagepos].stopped = TRUE;
            trk_Messages[trk_messagepos].TimeToProcess = trk_SystemClock + msg_ProcessAfter1m;
            #if (HIGH_PRIORITY_MESSAGE_ENABLED == TRUE)            
            if (trk_messagepos == trk_HighPriorityFunctionIndex)
            {
               trk_HighPriorityFunction = 0x0000;
            }
            #endif
            #if (PERIODIC_MESSAGE_ENABLED == TRUE)
            trk_MessagesProperties[trk_messagepos].isperiodic = FALSE;
            #endif
         }
      }
      else if (ProcessTime == msg_ProcessPause)
      {
         if ( (trk_Messages[trk_messagepos].messagefunction == 0x0000) && 
              (trk_PushNonExistingMessageWhilePausingState == TRUE) )
         {
            trk_Messages[trk_messagepos].messagefunction = messagefunction;
            trk_Messages[trk_messagepos].user_data = user_data;
            trk_Messages[trk_messagepos].TimeToProcess = trk_SystemClock;
         }
         trk_MessagesProperties[trk_messagepos].paused = TRUE;
      }
      else if (ProcessTime == msg_ProcessResume)
      {
         if (trk_Messages[trk_messagepos].messagefunction != 0x0000)
         {
            trk_MessagesProperties[trk_messagepos].paused = FALSE;
         }
      }   
      #if (HIGH_PRIORITY_MESSAGE_ENABLED == TRUE)
      else if (ProcessTime == msg_ProcessAsHighPriority)
      {
         trk_SetHighPriorityFunction(messagefunction);
      }
      #endif
      #if (PERIODIC_MESSAGE_ENABLED == TRUE)
      else if (ProcessTime == msg_ProcessAsPeriodic)
      {
         trk_MessagesProperties[trk_messagepos].isperiodic = TRUE;
      }
      #endif
      #if (START_STOP_ENABLED == TRUE)
      else if (ProcessTime == msg_ProcessStart1msTimer)
      {
         trk_Is1msTimerEnabled = TRUE;
      }
      else if (ProcessTime == msg_ProcessStop1msTimer)
      {
         trk_Is1msTimerEnabled = FALSE;
      }
      #endif
      else
      {

         trk_Messages[trk_messagepos].messagefunction = messagefunction;
         trk_Messages[trk_messagepos].user_data = user_data;
         trk_MessagesProperties[trk_messagepos].paused = FALSE;
         trk_MessagesProperties[trk_messagepos].stopped = FALSE;
         
         if (ProcessTime == msg_ProcessNextCheck)
         {
            ProcessTime = 0;
            #if (IMMEDIATE_NEXTCHECK == TRUE)            
            trk_NextCheckMessagePointer = trk_messagepos;
            #endif
         }

         trk_Messages[trk_messagepos].TimeToProcess = trk_SystemClock + ProcessTime;
      }

      if (trk_messagepos > trk_MaxMessageCounter)
      {
         trk_MaxMessageCounter = trk_messagepos;
      }
   }
   trk_MessagesProperties[trk_messagepos].isprotected = FALSE;
}

void trk_IncreasePausedMessagesProcessTime(void)
{
   unsigned char messagepos = 0;
   while ( (messagepos != MAX_MESSAGE_NUMBER) && (trk_Messages[messagepos].messagefunction != 0x0000) )
   {
      if (trk_MessagesProperties[messagepos].paused == TRUE)
      {
         trk_Messages[messagepos].TimeToProcess += trk_PauseClockCounter;
      }
      messagepos++;
   }   
}

void trk_Fire1msTimer(void)
{
   #if (GOZCU_ENABLED == TRUE)      
   if (trk_1msTimerFired == TRUE)
   #endif
   {
      #if (START_STOP_ENABLED == TRUE)
      if (trk_Is1msTimerEnabled == TRUE)
      #endif
      {
         trk_SystemClock += msg_ProcessAfter1ms;
         trk_PauseClockCounter += msg_ProcessAfter1ms;
         if (trk_PauseClockCounter >= msg_ProcessAfter1ms * 10)
         {
            trk_IncreasePausedMessagesProcessTime();
            trk_ReArrangeSystemClock();
            trk_PauseClockCounter = 0;
         }
         #if (GOZCU_ENABLED == TRUE)      
         trk_1msTimerFired = FALSE;
         ata_SetSystemClock(trk_SystemClock);
         #endif
      }
   }
}

void trk_ProcessMessages(unsigned long ProcessTime)
{
   static unsigned char counter = 0;

   do
   { 
      #if (IMMEDIATE_NEXTCHECK == TRUE)      
      if (trk_NextCheckMessagePointer != THERE_IS_NO_NEXT_CHECK_MESSAGE)
      {
         counter = trk_NextCheckMessagePointer;
         trk_NextCheckMessagePointer = THERE_IS_NO_NEXT_CHECK_MESSAGE;
      }
      #endif

      #if (HIGH_PRIORITY_MESSAGE_ENABLED == TRUE)
      if (trk_HighPriorityFunction != 0x0000)
      {
         trk_CheckMessage(trk_HighPriorityFunctionIndex);
      }
      #endif

      if (counter >= MAX_MESSAGE_NUMBER)
      {
         counter = 0;
         #if (GOZCU_ENABLED == TRUE)
         trk_Fire1msTimer();
         #endif
      }
      
      if (trk_Messages[counter].messagefunction != 0x0000)
      {
         counter = trk_CheckMessage(counter);
         counter++;
         if (trk_Messages[counter].messagefunction == 0x0000)
         {
            counter = 0;
            #if (GOZCU_ENABLED == TRUE)
            trk_Fire1msTimer();
            #endif
         }
      }
      else
      {
         counter = 0;
         #if (GOZCU_ENABLED == TRUE)
         trk_Fire1msTimer();
         #endif
      }
   }
   #if (GOZCU_ENABLED == TRUE)   
   while ((ProcessTime == msg_ProcessForever) && (drv_getShouldStop() == 0));
   #else
   while (ProcessTime == msg_ProcessForever);
   #endif   
   
}

void trk_Message(trk_messages message, void *user_data, trk_msgProcessTime ProcessTime)
{
   if (message == msg_1msTimer)
   {
      #if (GOZCU_ENABLED == TRUE)      
      trk_1msTimerFired = TRUE;
      #else
      trk_Fire1msTimer();
      #endif
   }
   else if (message == msg_ProcessMessages)
   {
      trk_ProcessMessages(ProcessTime);
   }
   else
   {
      trk_FindAndPushMessage(message,user_data,ProcessTime);
   }
}


void trk_KillAllMessages(void)
{
   unsigned char counter;
   for (counter = 0; counter < MAX_MESSAGE_NUMBER; counter++)
   {
      trk_Messages[counter].messagefunction = 0x0000;
   }
   #if (HIGH_PRIORITY_MESSAGE_ENABLED == TRUE)
   trk_HighPriorityFunction = 0x0000;
   #endif
}

void trk_MessageInit(void)
{
   ata_MessageOpen(&trk_Message, &trk_PushMessage);
   trk_KillAllMessages();
}

void trk_StopMessage(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessStopped);
}

void trk_PushMessage1ms(trk_MessageFunction messagefunction, void *user_data)
{
   trk_PushMessage(messagefunction, user_data, msg_ProcessAfter1ms);
}

void trk_PushMessage1msNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1ms);
}
void trk_PushMessage2msNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1ms*2);
}
void trk_PushMessage3msNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1ms*3);
}
void trk_PushMessage4msNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1ms*4);
}
void trk_PushMessage5msNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1ms*5);
}
void trk_PushMessage10msNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1ms*10);
}
void trk_PushMessage500msNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1ms*500);
}

void trk_PushMessage1secNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1s);
}
void trk_PushMessage2secNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1s*2);
}
void trk_PushMessage3secNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1s*3);
}
void trk_PushMessage4secNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1s*4);
}
void trk_PushMessage5secNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1s*5);
}
void trk_PushMessage10secNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1s*10);
}

void trk_PushMessage1mNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1m);
}
void trk_PushMessage2mNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1m*2);
}
void trk_PushMessage3mNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1m*3);
}

void trk_PushMessage4mNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1m*4);
}
void trk_PushMessage5mNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1m*5);
}
void trk_PushMessage10mNullUserData(trk_MessageFunction messagefunction)
{
   trk_PushMessage(messagefunction, 0x00, msg_ProcessAfter1m*10);
}

void trk_PushMessageNullUserData(trk_MessageFunction messagefunction, trk_msgProcessTime ProcessTime)
{
   trk_PushMessage(messagefunction, 0x00, ProcessTime);
}

void trk_SynchroniseMessage(trk_MessageFunction messagefunction, unsigned long SynchronisationTime)
{
   unsigned char messagepos = trk_FindMessagePosition(messagefunction);
   if (messagepos < MAX_MESSAGE_NUMBER)
   {
      trk_Messages[messagepos].TimeToProcess = ((trk_SystemClock / SynchronisationTime) + 1) * SynchronisationTime;
   }
}

