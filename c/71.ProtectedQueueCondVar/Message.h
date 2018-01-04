#ifndef __MESSAGE_H__
#define __MESSAGE_H__


typedef struct Message Message;


Message* MsgCreate(const char* _str);

void MsgUpdate(Message* _msg, const char* _str);

void MsgDestroy(Message* _msg);


#endif /* #ifndef __MESSAGE_H__ */


