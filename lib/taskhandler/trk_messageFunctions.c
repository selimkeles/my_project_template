#include "trk_message.h"
#include "trk_messageDefinitions.h"
#include "trk_messageFunctions.h"

const trk_MessageFunctions_t *trk_messageFunctionsArray = trk_messageFunctionsArraySource;

const trk_MessageFunctions_t trk_messageFunctionsArraySource[] =
{
   // {msg_ProgramManagerNextStep, &trk_NextStep},
   // {msg_KeyPressed, &trk_KeyPressed},
   {msg_LastMessage, &trk_ProcessNull}

};

unsigned long trk_ProcessNull(void *user_data)
{
   return msg_ProcessStopped;
}


