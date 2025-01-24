#ifndef APP_TRK_MESSAGEDEFINITIONS_H_
#define APP_TRK_MESSAGEDEFINITIONS_H_

#define DEFINED_PROCESS_TIME

typedef enum trk_messages
{
   msg_FirstMessage = 0x00,   //default message
   msg_ProcessMessages,       //default message
   msg_1msTimer,              //default message
   msg_KeyPressed,
   msg_ProgramManagerNextStep,
   msg_DoorSocketReconnect,
   msg_Error,
   
   msg_LastMessage            //default message
} trk_messages;

#endif
