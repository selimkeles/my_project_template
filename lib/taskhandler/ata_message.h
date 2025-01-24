#ifndef MESSAGE_ATA_MESSAGE_H_
#define MESSAGE_ATA_MESSAGE_H_

#include "trk_message.h"

extern trk_MessageCallback msg_callback;
extern trk_PushMessageCallback msg_pushcallback;

extern void ata_MessageOpen(trk_MessageCallback MessageCallback, trk_PushMessageCallback PushMessageCallback);
extern void ata_MessageStackOverflow(void);

#endif /* MESSAGE_ATA_MESSAGE_H_ */
