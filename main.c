#ifdef WIN32
#include <windows.h>
#else
#include <stdlib.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "hidapi.h"
#include <stdint.h>
#define MAX_STR 255
#include <locale.h>
#include <string.h>
#include <wchar.h>

int main(int argc, char* argv[])
{
    int res;
    unsigned char buf[65];
    wchar_t w_str[MAX_STR];
    hid_device *handle;

    // Initialize the hidapi library
    res = hid_init();
    if(res != 0) {
        printf("hid_init failed!\n");
        return -1;
    }

    // Open the device using the VID, PID,
    // and optionally the Serial number.
    handle = hid_open(0x0483, 0x5750, NULL);
    if(handle == NULL) {
        printf("hid_open failed!\n");
        return -2;
    }

    // Read the Manufacturer String
    hid_get_manufacturer_string(handle, w_str, MAX_STR);
    wprintf(L"Manufacturer String: %s\n", w_str);

    // Read the Product String
    hid_get_product_string(handle, w_str, MAX_STR);
    wprintf(L"Product String: %s\n", w_str);

    // Read the Serial Number String
    hid_get_serial_number_string(handle, w_str, MAX_STR);
    wprintf(L"Serial Number String: (%d) %s\n", w_str[0], w_str);

    // Read Indexed String 1
    hid_get_indexed_string(handle, 1, w_str, MAX_STR);
    wprintf(L"Indexed String 1: %s\n", w_str);

    //return 0;
    for (int j = 0; j < 100000; ++j) {
        // Read requested state
        memset(buf,0,sizeof(buf));
        res = hid_read(handle, buf+1, 64);
        if(res == -1 || res == 0) {
            //printf("hid_read error.\n");
            continue;
            //break;
        }
        // Print out the returned buffer.
        printf("report %d length %d, %s\n",j, res, (char *)buf+1);
        fflush(stdout);
        buf[0] = 0;
        res = hid_write(handle,buf,65);
        if(res == -1) {
            printf("hid_write error.\n");
            break;
        }
    }

    hid_close(handle);

    // Finalize the hidapi library
    hid_exit();

    return 0;
}