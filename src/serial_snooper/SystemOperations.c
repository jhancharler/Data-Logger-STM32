#include "SystemOperations.h"
#include "MySD.h"
#include "stm32f3xx_hal.h"
#include "DataHolder.h"
#include "FileNameIterator.h"

#define STATUS_INIT_FAIL (1 << 0)
#define STATUS_TIMESTAMP (1 << 1)

static uint8_t previousData;
static uint32_t lastTimeFlushed;
static uint8_t status;
static uint8_t bLogFileIsOpen = 0;
static uint8_t timestampThisLine(uint8_t thisByte);

int SystemOperations_Init(void)
{
    status = STATUS_TIMESTAMP;
    lastTimeFlushed = 0;
    bLogFileIsOpen = 0;

    FileNameIterator_init();

    return SO_SUCCESS;
}   

void SystemOperations_OpenLogFile(void)
{
    // get size of file
    uint32_t dataSize = DH_GetOpenedFileSize();
    // find out if we have data to handle
    uint8_t bThereIsNewDataToHandle = DH_IsThereNewData();
    // open new file if the current one is too large
    uint8_t bMaxFileSizeReached = (dataSize >= MAX_FILE_SIZE);
    uint8_t bLowerBoundaryFileSizeReached = (dataSize >= FILE_SIZE_LOWER_THRESHOLD);
    // open new file earlier if system has no new data to handle
    uint8_t bOpenNewFileEarly = (bLowerBoundaryFileSizeReached && !bThereIsNewDataToHandle);
    // or open a file if none is open
    if (!bLogFileIsOpen || bMaxFileSizeReached || bOpenNewFileEarly)
    {
        // get new file name
        const char* fileName = DH_GetFileName();

        // open file
        FRESULT err = MySD_Init(fileName);

        if (err == FR_OK)
        {
            bLogFileIsOpen = 1;
        }
        else
        {
            bLogFileIsOpen = 0;
        }
    }
}

void SystemOperations_WriteSD(void)
{
    // Write to SD card from a circular buffer
    // Parse each letter one by one and determine if
    // need to also write a timestamp.
    if (DH_IsThereNewData())
    {
        // get top item from circular buffer
        uint8_t val = DH_GetLatestData();
        // parse it (determine if need to timestamp)
        if (timestampThisLine(val))
        {
            // write timestamp
            const char* ts = DH_GetTimestampString();
            MySD_WriteString(ts);
            status &= ~STATUS_TIMESTAMP;
        }
        // write data to SD card
        MySD_Write(&val, 1);
        previousData = val;
    }
}

void SystemOperations_FlushSD(void)
{
    // Device may be unplugged at any moment.
    // Flush every so often so no data is lost.
    uint32_t tNow = HAL_GetTick();
    if (tNow >= (lastTimeFlushed + FLUSH_TIME_MS))
    {
        MySD_Flush();
        lastTimeFlushed = tNow;
    }
}


// Should behave like the "auto" setting on Teraterm
// Should timestamp the first ever character
// Then will timestamp the first character
// after a line feed.
// A line feed is either: CR, LF, CRLF, LFCR
static uint8_t timestampThisLine(uint8_t thisByte)
{
    uint8_t ret = 0;
    if (status & STATUS_TIMESTAMP)
    {
        ret = 1;
    }
    if (previousData == '\n')
    {
        if (thisByte != '\r')
        {
            // If previously received LF and this
            // new line is not CR...
            ret = 1;
        }
        else
        {
            status |= STATUS_TIMESTAMP; // ts the next one
        }
    }
    if (previousData == '\r')
    {
        if (thisByte != '\n')
        {
            // If previously received CR and this
            // new line is not LF...
            ret = 1;
        }
        else
        {
            status |= STATUS_TIMESTAMP; // ts the next one
        }
    }
    return ret;
}
