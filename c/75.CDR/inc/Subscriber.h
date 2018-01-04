#ifndef __SUBSCRIBER_H__
#define __SUBSCRIBER_H__


typedef struct Subscriber Subscriber;


Subscriber* SubscriberCreate();

int SubscriberAddOutgoingCallInNetwork(Subscriber* _subscriber, unsigned int _duration);
int SubscriberAddIncomigCallInNetwork(Subscriber* _subscriber, unsigned int _duration);
int SubscriberAddOutgoingSmsInNetwork(Subscriber* _subscriber, unsigned int _dummyArg);
int SubscriberAddIncomingSmsInNetwork(Subscriber* _subscriber, unsigned int _dummyArg);

int SubscriberAddOutgoingCallOutNetwork(Subscriber* _subscriber, unsigned int _duration);
int SubscriberAddIncomigCallOutNetwork(Subscriber* _subscriber, unsigned int _duration);
int SubscriberAddOutgoingSmsOutNetwork(Subscriber* _subscriber, unsigned int _dummyArg);
int SubscriberAddIncomingSmsOutNetwork(Subscriber* _subscriber, unsigned int _dummyArg);

int SubscriberAddToDownloaded(Subscriber* _subscriber, double _megabytes);
int SubscriberAddToUploaded(Subscriber* _subscriber, double _megabytes);

void SubscriberDestroy(Subscriber* _subscriber);

int SubscriberWriteToString(Subscriber* _subscriber, char* _buf);
void SubscriberPrint(Subscriber* _subscriber);


#endif /* #ifndef __SUBSCRIBER_H__ */

