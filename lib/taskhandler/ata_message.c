#include "trk_messageDefinitions.h"
#include "ata_message.h"

trk_MessageCallback msg_callback;
trk_PushMessageCallback msg_pushcallback;

void ata_MessageOpen(trk_MessageCallback MessageCallback, trk_PushMessageCallback PushMessageCallback)
{
   msg_callback = MessageCallback;
   msg_pushcallback = PushMessageCallback;
}

void ata_MessageStackOverflow()
{
   /* Failure Action here */
}
