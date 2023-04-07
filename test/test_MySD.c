#include "unity.h"
#include "MySD.h"
#include "fakeff.h"
#include "fakefilesystem.h"
#include "fake_led.h"
#include "string.h"

static const BYTE g_Mode = FA_WRITE | FA_READ | FA_OPEN_APPEND;

void setUp(void)
{
    // Close the module to reset internal state variables
    MySD_Close();
    fakeLed_reset();
}

void tearDown(void)
{
}

void test_OpenLogFileMountsAndOpensAFileAndLedIsOn(void)
{
    //given
    TEST_ASSERT_FALSE(fakefilesystem_fileExists("file"));
    //when
    FRESULT err = MySD_Init("file");
    // then
    TEST_ASSERT_EQUAL_INT(FR_OK, err);
    TEST_ASSERT_TRUE(fakefilesystem_fileExists("file"));
    TEST_ASSERT_TRUE(fakeLed_isOn());
}

#if 0
void test_init_sd_when_all_ok(void)
{
    FATFS FatFs = { 0 };
    FIL file = { 0 };

    f_mount_ExpectAndReturn(&FatFs, "", 1, FR_OK);
    f_open_ExpectAndReturn(&file, "testFile.txt", g_Mode, FR_OK);
    led_init_Expect();
    led_on_Expect();

    FRESULT err = MySD_Init("testFile.txt");

    TEST_ASSERT_EQUAL_INT(FR_OK, err);
}

void test_init_sd_when_no_mount(void)
{
    FATFS FatFs = { 0 };

    f_mount_ExpectAndReturn(&FatFs, "", 1, FR_NOT_READY);

    FRESULT err = MySD_Init("testFile.txt");

    TEST_ASSERT_EQUAL_INT(FR_NOT_READY, err);
}

void test_init_sd_when_open_fails(void)
{
    FATFS FatFs = { 0 };
    FIL file = { 0 };

    f_mount_ExpectAndReturn(&FatFs, "", 1, FR_OK);
    f_open_ExpectAndReturn(&file, "testFile.txt", g_Mode, FR_NOT_READY);

    FRESULT err = MySD_Init("testFile.txt");

    TEST_ASSERT_EQUAL_INT(FR_NOT_READY, err);
}

void test_init_sd_twice_closes_file_opens_another(void)
{
    FIL file = { 0 };

    // The first call:
    f_mount_IgnoreAndReturn(FR_OK);
    f_open_IgnoreAndReturn(FR_OK);
    led_init_Ignore();
    led_on_Ignore();

    MySD_Init("testFile.txt");

    f_mount_StopIgnore();
    f_open_StopIgnore();

    // The second call:
    f_close_ExpectAndReturn(&file, FR_OK);
    f_open_ExpectAndReturn(&file, "testFile2.txt", g_Mode, FR_OK);
    
    FRESULT err = MySD_Init("testFile2.txt");

    TEST_ASSERT_EQUAL_INT(FR_OK, err);
}

void test_close_sd(void)
{
    FIL file = { 0 };
    f_close_ExpectAndReturn(&file, FR_OK);
    f_mount_ExpectAndReturn(NULL, "", 0, FR_OK);
    MySD_Close();
}

void test_write_sd_string_all_bytes_written_correctly(void)
{
    FIL file = { 0 };
    char buf[] = "test buffer";
    int len = strlen(buf);
    unsigned int bytesWrote = 0;

    f_write_ExpectAndReturn(&file, buf, len, &bytesWrote, FR_OK);
    led_toggle_Expect();

    FRESULT err = MySD_WriteString(buf);
    TEST_ASSERT_EQUAL_INT(FR_OK, err);
}

void test_write_sd_calls_fats_toggles_led(void)
{
    const uint8_t buflen = 6;
    FIL file = { 0 };
    char buf[6] = {0, 5, 6, 7, 8, 1};
    unsigned int bytesWrote = 0;

    f_write_ExpectAndReturn(&file, buf, buflen, &bytesWrote, FR_OK);
    led_toggle_Expect();

    FRESULT err = MySD_Write(buf, buflen);
    TEST_ASSERT_EQUAL_INT(FR_OK, err);
}

void test_write_sd_fails_doesnt_toggle_led(void)
{
    const uint8_t buflen = 6;
    FIL file = { 0 };
    char buf[6] = {0, 5, 6, 7, 8, 1};
    unsigned int bytesWrote = 0;

    f_write_ExpectAndReturn(&file, buf, buflen, &bytesWrote, FR_DISK_ERR);

    FRESULT err = MySD_Write(buf, buflen);
    TEST_ASSERT_EQUAL_INT(FR_DISK_ERR, err);
}

void test_write_string_fails_doesnt_toggle_led(void)
{
    FIL file = { 0 };
    char buf[] = "test buffer";
    int len = strlen(buf);
    unsigned int bytesWrote = 0;

    f_write_ExpectAndReturn(&file, buf, len, &bytesWrote, FR_DISK_ERR);

    FRESULT err = MySD_WriteString(buf);
    TEST_ASSERT_EQUAL_INT(FR_DISK_ERR, err);
}

void test_mysd_flush(void)
{
    FIL file = { 0 };

    f_sync_ExpectAndReturn(&file, FR_OK);

    FRESULT err = MySD_Flush();
    TEST_ASSERT_EQUAL_INT(FR_OK, err);
}

void test_mysd_size(void)
{    
    FIL file = { 0 };
    // funny hack to get around encapsulating the FIL object
    FIL fileWithSize = { 0 };   
    fileWithSize.obj.objsize = 33;


    f_mount_IgnoreAndReturn(0);
    f_open_ExpectAndReturn(&file, 
        "filename", g_Mode, FR_OK);
    // here's the hack, the encapsulated file will now
    // have a size of 33
    f_open_ReturnMemThruPtr_fp(&fileWithSize, sizeof(FIL));
    led_init_Ignore();
    led_on_Ignore();

    FRESULT err = MySD_Init("filename");

    FSIZE_t size = MySD_getOpenedFileSize();

    TEST_ASSERT_EQUAL(33, size);
}

void test_read_ok(void)
{
    const uint8_t buflen = 6;
    FIL file = { 0 };
    char buf[6] = {0, 5, 6, 7, 8, 1};
    unsigned int bytesRead = 0;

    f_read_ExpectAndReturn(&file, buf, buflen, &bytesRead, FR_OK);

    FRESULT err = MySD_Read(buf, buflen);
    TEST_ASSERT_EQUAL_INT(FR_OK, err);
}

#endif

/*

- [x] Init will mount SD card then open a file for writing
- [x] Init again will not mount again and will close
    the open file and open a new one
- [x] Write will write to the end of that file
    - Write without init will return error
    - A successful write will return 0
- [x] Close file shall close the file and unmount SD
    - Even if mount failed, will do the unmount routine
    - Even if file not opened, will close

*/
