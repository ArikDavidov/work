#ifndef __SUBSCRIBERS_H__
#define __SUBSCRIBERS_H__

#include "CDR.h"
#include "Subscriber.h"


typedef struct Subscribers Subscribers;

typedef enum SubscribersResult {
	SUBSCRIBERS_SUCCESS = 0,
	SUBSCRIBERS_UNINITIALIZED_ERROR, 		/**< Uninitialized Subscribers error	*/
	SUBSCRIBERS_KEY_NULL_ERROR,				/**< Key was null 						*/
	SUBSCRIBERS_KEY_DUPLICATE_ERROR, 		/**< Duplicate key error 				*/
	SUBSCRIBERS_KEY_NOT_FOUND_ERROR, 		/**< Key not found 						*/
	SUBSCRIBERS_ALLOCATION_ERROR,			/**< Allocation error 	 				*/
	SUBSCRIBERS_INV_ARG_ERROR				/**< Out parameter was null				*/
} SubscribersResult;


Subscribers* SubscribersCreate();
Subscriber* SubscribersFindSubscriber(Subscribers* _subscribers, const char* _msisdn);
SubscribersResult SubscribersProcess(Subscribers* _subscribers, const Cdr* _cdr);
void SubscribersDestroy(Subscribers* _subscribers);

void SubscribersWrite(Subscribers* _subscribers);
void SubscribersWriteSubscriberToString(Subscribers* _subscribers, char* _msisdn,
										Subscriber* _subscriber, char* _buf);
void SubscribersPrint(Subscribers* _subscriber);


#endif /* #ifndef __SUBSCRIBERS_H__ */










