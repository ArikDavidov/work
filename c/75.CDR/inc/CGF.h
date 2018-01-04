#ifndef __CFG_H__
#define __CFG_H__

#include "Processor.h"


typedef enum CFGResult {
	CFG_SUCCESS = 0,
	CFG_UNINITIALIZED_ERROR, 		/**< Uninitialized CFG error 	*/
	CFG_KEY_NULL_ERROR, 			/**< Key was null 				*/
	CFG_KEY_DUPLICATE_ERROR, 		/**< Duplicate key error 		*/
	CFG_KEY_NOT_FOUND_ERROR, 		/**< Key not found 				*/
	CFG_ALLOCATION_ERROR,			/**< Allocation error 	 		*/
	CFG_INV_ARG_ERROR				/**< Out parameter was null		*/
} CFGResult;


void CgfSubscriberRetrieveQuery(Processor* _processor, char* _buf);
void CgfOperatorRetrieveQuery(Processor* _processor, char* _buf);


/*
CFGResult CgfAllSubscribersReport(CFG* _cfg, FILE* _fp);
CFGResult CgfAllOperatorsReport(CFG* _cfg, FILE* _fp);
*/

#endif /* #ifndef __CFG_H__ */

