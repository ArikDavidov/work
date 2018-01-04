#ifndef __OPERATOR_H__
#define __OPERATOR_H__


typedef struct Operator Operator;


Operator* OperatorCreate();
int  OperatorAddCallToOutgoing(Operator* _operator, unsigned int _duration);
int  OperatorAddCallToIncoming(Operator* _operator, unsigned int _duration);
int  OperatorAddSmsToOutgoing(Operator* _operator);
int  OperatorAddSmsToIncoming(Operator* _operator);
void OperatorDestroy(Operator* _operator);

int OperatorWriteToString(Operator* _operator, char* _buf);
void OperatorPrint(Operator* _operator);
/*void OperatorWrite(Operator* _operator);*/

#endif /* #ifndef __OPERATOR_H__ */


