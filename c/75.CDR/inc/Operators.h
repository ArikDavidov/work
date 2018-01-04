#ifndef __OPERATORS_H__
#define __OPERATORS_H__

#include "CDR.h"
#include "Operator.h"


typedef struct Operators Operators;

typedef enum OperatorsResult {
	OPERATORS_SUCCESS = 0,
	OPERATORS_UNINITIALIZED_ERROR, 		/**< Uninitialized Operators error	*/
	OPERATORS_KEY_NULL_ERROR, 			/**< Key was null 					*/
	OPERATORS_KEY_DUPLICATE_ERROR, 		/**< Duplicate key error 			*/
	OPERATORS_KEY_NOT_FOUND_ERROR, 		/**< Key not found 					*/
	OPERATORS_ALLOCATION_ERROR,			/**< Allocation error 	 			*/
	OPERATORS_INV_ARG_ERROR				/**< Out parameter was null			*/
} OperatorsResult;


Operators* OperatorsCreate();
Operator* OperatorsGetOperator(Operators* _operators, const Cdr* _cdr);
Operator* OperatorsFindOperator(Operators* _operators, const char* _mccMnc);
OperatorsResult OperatorsProcess(Operators* _operators, const Cdr* _cdr);
void OperatorsWrite(Operators* _operators);
void OperatorsDestroy(Operators* _operators);

void OperatorsWriteOperatorToString(Operators* _operators, char* _partyOperator,
									Operator* _operator, char* _buf);
void OperatorsPrintAllOperator(Operators* _operators);
//void OperatorsPrint(Operators* _operators);

#endif /* #ifndef __OPERATOR_H__ */

