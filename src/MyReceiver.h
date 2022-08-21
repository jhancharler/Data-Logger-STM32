#ifndef MY_RECEIVER_H_INCLUDED
#define MY_RECEIVER_H_INCLUDED

#define NOT_RECEIVED 0
#define RECEIVED 1
#define DONE 2

int MyReceiver_Receive(void);
void MyReceiver_Clear(void);
char* MyReceiver_GetBuffer(void);

#endif