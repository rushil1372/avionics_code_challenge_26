#include "lis3mdl.h"
#include "i2c.h"
#include <stdio.h>

int main(void)
{
    lis3mdl_device_t magnetometer;
    lis3mdl_full_scale_t full_scale;
    lis3mdl_odr_t odr;
    int16_t x, y, z;
    status_t status;

    printf("=== LIS3MDL Magnetometer Driver Test ===\n\n");

    printf("1. Initializing device...\n");
    status = lis3mdl_init(&magnetometer, LIS3MDL_ADDR_LOW);
    if (status == STATUS_OK) {
        printf("   Device initialized successfully!\n\n");
    } else {
        printf("   Device initialization failed!\n");
        return -1;
    }

    printf("2. Getting full-scale configuration...\n");
    status = lis3mdl_get_full_scale(&magnetometer, &full_scale);
    if (status == STATUS_OK) {
        printf("   Current full-scale: ");
        switch (full_scale) {
            case LIS3MDL_FS_4_GAUSS:
                printf("±4 gauss\n\n");
                break;
            case LIS3MDL_FS_8_GAUSS:
                printf("±8 gauss\n\n");
                break;
            case LIS3MDL_FS_12_GAUSS:
                printf("±12 gauss\n\n");
                break;
            case LIS3MDL_FS_16_GAUSS:
                printf("±16 gauss\n\n");
                break;
        }
    }

    printf("3. Setting full-scale to ±12 gauss...\n");
    status = lis3mdl_set_full_scale(&magnetometer, LIS3MDL_FS_12_GAUSS);
    if (status == STATUS_OK) {
        printf("   Full-scale set successfully!\n\n");
    }

    printf("4. Getting output data rate...\n");
    status = lis3mdl_get_odr(&magnetometer, &odr);
    if (status == STATUS_OK) {
        printf("   Current ODR: ");
        switch (odr) {
            case LIS3MDL_ODR_0_625_HZ:
                printf("0.625 Hz\n\n");
                break;
            case LIS3MDL_ODR_1_25_HZ:
                printf("1.25 Hz\n\n");
                break;
            case LIS3MDL_ODR_2_5_HZ:
                printf("2.5 Hz\n\n");
                break;
            case LIS3MDL_ODR_5_HZ:
                printf("5 Hz\n\n");
                break;
            case LIS3MDL_ODR_10_HZ:
                printf("10 Hz\n\n");
                break;
            case LIS3MDL_ODR_20_HZ:
                printf("20 Hz\n\n");
                break;
            case LIS3MDL_ODR_40_HZ:
                printf("40 Hz\n\n");
                break;
            case LIS3MDL_ODR_80_HZ:
                printf("80 Hz\n\n");
                break;
        }
    }

    printf("5. Setting output data rate to 20 Hz...\n");
    status = lis3mdl_set_odr(&magnetometer, LIS3MDL_ODR_20_HZ);
    if (status == STATUS_OK) {
        printf("   ODR set successfully!\n\n");
    }

    printf("6. Enabling interrupt pin...\n");
    status = lis3mdl_set_interrupt_enable(&magnetometer, false);
    if (status == STATUS_OK) {
        printf("   Interrupt enabled successfully!\n\n");
    }

    printf("7. Reading X-axis data...\n");
    status = lis3mdl_read_axis(&magnetometer, LIS3MDL_AXIS_X, &x);
    if (status == STATUS_OK) {
        printf("   X-axis: %d (raw ADC value)\n\n", x);
    }

    printf("8. Reading all axes (X, Y, Z)...\n");
    status = lis3mdl_read_xyz(&magnetometer, &x, &y, &z);
    if (status == STATUS_OK) {
        printf("   X: %d\n", x);
        printf("   Y: %d\n", y);
        printf("   Z: %d\n\n", z);
    }

    printf("9. Disabling interrupt pin...\n");
    status = lis3mdl_set_interrupt_enable(&magnetometer, false);
    if (status == STATUS_OK) {
        printf("   Interrupt disabled successfully!\n\n");
    }

    printf("=== Test Complete ===\n");

    return 0;
}
