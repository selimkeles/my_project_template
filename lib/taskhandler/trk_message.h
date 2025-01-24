#ifndef __TRK_MESSAGE_H__
#define __TRK_MESSAGE_H__

#include "trk_messageDefinitions.h"

#ifdef DEFINED_PROCESS_TIME
#define msg_ProcessStopped 0x01
#define msg_ProcessInstant 0x03
#define msg_ProcessForever 0x05
#define msg_ProcessPause 0x07
#define msg_ProcessResume 0x09
#define msg_ProcessAsHighPriority 0x0B
#define msg_ProcessCheckHighPriorityFunction 0x0D
#define msg_ProcessNextCheck 0x0F
#define msg_ProcessAsPeriodic 0x11
#define msg_ProcessStop1msTimer 0x13
#define msg_ProcessStart1msTimer 0x15
#define msg_ProcessAfter1ms ((unsigned long)0x02)
#define msg_ProcessAfter1s ((unsigned long)msg_ProcessAfter1ms * 1000)
#define msg_ProcessAfter2s ((unsigned long)msg_ProcessAfter1s * 2)
#define msg_ProcessAfter3s ((unsigned long)msg_ProcessAfter1s * 3)
#define msg_ProcessAfter5s ((unsigned long)msg_ProcessAfter1s * 5)
#define msg_ProcessAfter10s ((unsigned long)msg_ProcessAfter1s * 10)
#define msg_ProcessAfter1m ((unsigned long)msg_ProcessAfter1s * (unsigned long)60)
#define msg_ProcessAfter1h ((unsigned long)msg_ProcessAfter1m * (unsigned long)60)

typedef unsigned long trk_msgProcessTime;

#else

typedef enum
{
   msg_ProcessStopped = 0x01,
   msg_ProcessInstant = 0x03,
   msg_ProcessForever = 0x05,
   msg_ProcessPause = 0x07,
   msg_ProcessResume = 0x09,
   msg_ProcessAsHighPriority = 0x0B,
   msg_ProcessCheckHighPriorityFunction = 0x0D,
   msg_ProcessNextCheck = 0x0F,
   msg_ProcessAsPeriodic = 0x11,
   msg_ProcessStop1msTimer = 0x13,
   msg_ProcessStart1msTimer = 0x15,
   msg_ProcessAfter1ms = 0x02,
   msg_ProcessAfter1s = msg_ProcessAfter1ms * 1000,
   msg_ProcessAfter1m = (unsigned long)msg_ProcessAfter1s * (unsigned long)60,
   msg_ProcessAfter1h = (unsigned long)msg_ProcessAfter1m * (unsigned long)60
} trk_msgProcessTime;
#endif

typedef struct
{
   unsigned char paused:1;
   unsigned char stopped:1;
   unsigned char isprotected:1;
   unsigned char isperiodic:1;
   unsigned char reserved:4;
} trk_8BitProperty;

typedef unsigned long (*trk_MessageFunction)(void* user_data);


typedef void (*trk_MessageCallback)(trk_messages message, void* user_data, trk_msgProcessTime ProcessTime);
typedef void (*trk_PushMessageCallback)(trk_MessageFunction messagefunction, void *user_data, trk_msgProcessTime ProcessTime);

typedef struct trk_MessageFunctions_t
{
   trk_messages message;
   trk_MessageFunction messageFunction;
}trk_MessageFunctions_t;


typedef struct trk_MessageCounter_t
{
   trk_MessageFunction messagefunction;
   unsigned long TimeToProcess;
   void *user_data;
}trk_MessageCounter_t;

extern void trk_Fire1msTimer(void);
extern void trk_PushMessage(trk_MessageFunction messagefunction, void *user_data, trk_msgProcessTime ProcessTime);
extern void trk_Message(trk_messages message, void *user_data, trk_msgProcessTime ProcessTime);
extern void trk_MessageInit(void);
extern void trk_SetHighPriorityFunction(trk_MessageFunction function);
extern void trk_ReArrangeSystemClock(void);
extern void trk_KillAllMessages(void);
extern void trk_StopMessage(trk_MessageFunction messagefunction);
extern void trk_PushMessage1ms(trk_MessageFunction messagefunction, void *user_data);
extern void trk_SynchroniseMessage(trk_MessageFunction messagefunction, unsigned long SynchronisationTime);
extern void trk_PushMessage1msNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage1secNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessageNullUserData(trk_MessageFunction messagefunction, trk_msgProcessTime ProcessTime);
extern void trk_PushNonExistingMessageWhilePausing(unsigned char state);
extern unsigned char trk_IsMessagePushed(trk_MessageFunction function);
extern unsigned long trk_GetMessageRemainingTime(trk_MessageFunction function);
extern unsigned char trk_GetMaxMessegeCounter(void);
extern unsigned long trk_SystemClock;
extern void trk_PushMessage2secNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage3secNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage4secNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage5secNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage10secNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage2msNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage3msNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage4msNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage5msNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage10msNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage500msNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage1mNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage2mNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage3mNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage4mNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage5mNullUserData(trk_MessageFunction messagefunction);
extern void trk_PushMessage10mNullUserData(trk_MessageFunction messagefunction);


#endif
