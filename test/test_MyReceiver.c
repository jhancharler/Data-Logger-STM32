#include "unity.h"
#include "MyReceiver.h"
#include "MyCommon.h"
#include "mock_MyUSART.h"
#include "mock_MyGPIO.h"
#include "unity_helper.h"
#include <stdio.h>

void initMyReceiver(void);
void initMyReceiverNoExpectations(void);
ReceiverEcode_e receiveFromUsart(char byte);
ReceiverEcode_e receiveFromUsart_String(char* string);
ReceiverEcode_e receiveFromUsartButUsartNotReady(void);
ReceiverEcode_e initAndReceive(char* string);
ReceiverEcode_e expectReceiveAndEcho(char* receivedByte, Error_Code_e willReturn);

// 10 characters
#define FULL_STRING     "0123456789"
#define EXCESS_STRING   "0123456789abc"

void setUp(void)
{

}

void tearDown(void)
{

}

void test_MyReceiver_Init_WillInitialiseUSARTAndGPIOProperly(void)
{
    MyGPIO expectedStruct =
    {
        .gpio_register = MY_USART_GPIO,
        .pin_mask = (MY_USART_RX | MY_USART_TX),
        .mode = GPIO_ALT,
        .alt_func = MY_USART_ALT,
        .output_type = GPIO_PUSH_PULL,
        .pupd = GPIO_PUPD_UP
    };

    MyGPIO_Init_ExpectAndReturn(&expectedStruct, ECODE_OK);
    MyUSART_Init_ExpectAndReturn(MY_USART, USART_BR_19200, ECODE_OK);

    initMyReceiver();
}

void test_MyReceiver_Receive_WillReadFromUSARTEvenIfNotInitialised(void)
{
    char received = 0;
    expectReceiveAndEcho(&received, ECODE_OK);
}

void test_MyReceiver_GetBuffer_ReceivedCharsAndEmptiedAfterInit(void)
{
    initMyReceiverNoExpectations();

    // empty after init
    char* buf = MyReceiver_GetBuffer();
    TEST_ASSERT_EQUAL_STRING("", buf);

    // not empty after receiving
    ReceiverEcode_e err = receiveFromUsart('a');
    TEST_ASSERT_EQUAL_INT(RCVR_RECEIVED, err);
    buf = MyReceiver_GetBuffer();
    TEST_ASSERT_EQUAL_STRING("a", buf);

    // empty again after init!
    initMyReceiverNoExpectations();
    buf = MyReceiver_GetBuffer();
    TEST_ASSERT_EQUAL_STRING("", buf);
}

void test_MyReceiver_GetBuffer_FillsUpAfter10CharactersAndWillEchoNewline(void)
{
    initMyReceiverNoExpectations();

    // receive a full string
    ReceiverEcode_e err = receiveFromUsart_String(FULL_STRING);
    TEST_ASSERT_EQUAL_INT(RCVR_RECEIVED, err);
    char* buf = MyReceiver_GetBuffer();
    TEST_ASSERT_EQUAL_STRING(FULL_STRING, buf);

    // receive 1 more character. should echo '\n' now
    char readData = 0;  // should pass in a 0
    char passedIn = 'c';
    MyUSART_Read_ExpectAndReturn(MY_USART, &readData, ECODE_OK);
    MyUSART_Read_ReturnThruPtr_readData(&passedIn);
    MyUSART_Write_ExpectAndReturn(MY_USART, '\n', ECODE_OK);

    err = MyReceiver_Receive();
    TEST_ASSERT_EQUAL_INT(RCVR_DONE, err);

    // Buffer shall not have expanded
    buf = MyReceiver_GetBuffer();
    TEST_ASSERT_EQUAL_STRING(FULL_STRING, buf);
}

void test_MyReceiver_Returns_RECEIVED_EvenIfErrorAsLongAsReceivedOnce(void)
{
    initMyReceiverNoExpectations();

    ReceiverEcode_e err = receiveFromUsartButUsartNotReady();
    TEST_ASSERT_EQUAL_INT(RCVR_NOT_RECEIVED, err);

    err = receiveFromUsart('a');
    TEST_ASSERT_EQUAL_INT(RCVR_RECEIVED, err);

    err = receiveFromUsartButUsartNotReady();
    TEST_ASSERT_EQUAL_INT(RCVR_RECEIVED, err);

}

void test_MyReceiver_GetBuffer_FillsUpAfterReceivingReturn(void)
{
    initMyReceiverNoExpectations();

    ReceiverEcode_e err = receiveFromUsart_String("012\n345");
    TEST_ASSERT_EQUAL_INT(RCVR_DONE, err);

    char* buf = MyReceiver_GetBuffer();
    TEST_ASSERT_EQUAL_STRING("012", buf);
}

void test_MyReceiver_Clear_WillEmptyTheInbufAndSetStateToNOTRECEIVED(void)
{
    initMyReceiverNoExpectations();
    receiveFromUsart_String("test");

    MyReceiver_Clear();
    char* buf = MyReceiver_GetBuffer();
    TEST_ASSERT_EQUAL_STRING("", buf);

    ReceiverEcode_e err = receiveFromUsartButUsartNotReady();
    TEST_ASSERT_EQUAL_INT(RCVR_NOT_RECEIVED, err);
}

void test_MyReceiver_AbleToContinueReceivingAfterClearing(void)
{
    initMyReceiverNoExpectations();

    receiveFromUsart_String("DryRun");
    TEST_ASSERT_EQUAL_STRING("DryRun", MyReceiver_GetBuffer());

    MyReceiver_Clear();

    receiveFromUsart_String("NextWord");
    TEST_ASSERT_EQUAL_STRING("NextWord", MyReceiver_GetBuffer());
}


/******************************** Helper Functions *****************/

void initMyReceiver(void)
{
    MyReceiver_Init(MY_USART, MY_USART_GPIO, MY_USART_ALT, MY_USART_RX, MY_USART_TX);
}

void initMyReceiverNoExpectations(void)
{
    MyGPIO_Init_IgnoreAndReturn(ECODE_OK);
    MyUSART_Init_IgnoreAndReturn(ECODE_OK);
    MyReceiver_Init(MY_USART, MY_USART_GPIO, MY_USART_ALT, MY_USART_RX, MY_USART_TX);
}

ReceiverEcode_e receiveFromUsart(char byte)
{
    return expectReceiveAndEcho(&byte, ECODE_OK);
}

// Useful as it shouldn't change what MyReceiver_Receive() will return
ReceiverEcode_e receiveFromUsartButUsartNotReady(void)
{
    char byte = 0;
    return expectReceiveAndEcho(&byte, ECODE_NOT_READY);
}

ReceiverEcode_e receiveFromUsart_String(char* string)
{
    ReceiverEcode_e err = RCVR_NOT_RECEIVED;
    while (*string)
    {
        err = receiveFromUsart(*string);
        if (err != RCVR_RECEIVED)
        {
            break;
        }
        string++;
    }
    return err;
}

ReceiverEcode_e expectReceiveAndEcho(char* receivedByte, Error_Code_e willReturn)
{
    char readData = 0;  // should pass in a 0
    MyUSART_Read_ExpectAndReturn(MY_USART, &readData, willReturn);
    MyUSART_Read_ReturnThruPtr_readData(receivedByte);

    MyUSART_Write_ExpectAndReturn(MY_USART, *receivedByte, ECODE_OK);

    return MyReceiver_Receive();
}

/*
- [x] MyReceiver_Receive will return 0 if received 0 and buffer is empty
- [x] MyReceiver_Receive will continue to return RECEIVED even if uart fails
- [x] MyReceiver clear shall clear the input buffer and reset state to NOT_RECEIVED
- [x] Shall echo back to terminal 
- [x] Also shall write \n automatically when full

- [ ] TODO, no longer use UART. Use the a "singleton" for USART6. Have the transmission
and reception go through that module instead. Let it have unique transmit ability
*/