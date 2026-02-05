#ifndef LIS3MDL_HEADER_H
#define LIS3MDL_HEADER_H

#include "i2c.h"
#include <stdint.h>
#include <stdbool.h>

// LIS3MDL I2C Address options based on SDO/SA1 pin 
#define LIS3MDL_ADDR_LOW    0x1C  // SDO/SA1 connected to GND 
#define LIS3MDL_ADDR_HIGH   0x1E  // SDO/SA1 connected to Vdd

// Register Addresses 
#define LIS3MDL_WHO_AM_I    0x0F
#define LIS3MDL_CTRL_REG1   0x20
#define LIS3MDL_CTRL_REG2   0x21
#define LIS3MDL_CTRL_REG3   0x22
#define LIS3MDL_STATUS_REG  0x27
#define LIS3MDL_OUT_X_L     0x28
#define LIS3MDL_OUT_X_H     0x29
#define LIS3MDL_OUT_Y_L     0x2A
#define LIS3MDL_OUT_Y_H     0x2B
#define LIS3MDL_OUT_Z_L     0x2C
#define LIS3MDL_OUT_Z_H     0x2D
#define LIS3MDL_INT_CFG     0x30
#define LIS3MDL_INT_SRC     0x31

// WHO_AM_I register value 
#define LIS3MDL_WHO_AM_I_VALUE  0x3D

// Full-scale configuration 
typedef enum {
    LIS3MDL_FS_4_GAUSS  = 0x00,  // 4 gauss
    LIS3MDL_FS_8_GAUSS  = 0x01,  // 8 gauss 
    LIS3MDL_FS_12_GAUSS = 0x02,  // 12 gauss 
    LIS3MDL_FS_16_GAUSS = 0x03   // 16 gauss 
} lis3mdl_full_scale_t;

// Output Data Rate configuration 
typedef enum {
    LIS3MDL_ODR_0_625_HZ = 0x00,  // 0.625 Hz
    LIS3MDL_ODR_1_25_HZ  = 0x01,  // 1.25 Hz
    LIS3MDL_ODR_2_5_HZ   = 0x02,  // 2.5 Hz
    LIS3MDL_ODR_5_HZ     = 0x03,  // 5 Hz 
    LIS3MDL_ODR_10_HZ    = 0x04,  // 10 Hz 
    LIS3MDL_ODR_20_HZ    = 0x05,  // 20 Hz 
    LIS3MDL_ODR_40_HZ    = 0x06,  // 40 Hz 
    LIS3MDL_ODR_80_HZ    = 0x07   // 80 Hz
} lis3mdl_odr_t;

// Axis selection
typedef enum {
    LIS3MDL_AXIS_X = 0,
    LIS3MDL_AXIS_Y = 1,
    LIS3MDL_AXIS_Z = 2
} lis3mdl_axis_t;

// Device structure 
typedef struct {
    uint8_t i2c_address;
    lis3mdl_full_scale_t full_scale;
    lis3mdl_odr_t odr;
} lis3mdl_device_t;

/**
 * @brief Initialize the LIS3MDL device
 * 
 * @param dev Pointer to device structure
 * @param i2c_address I2C address of the device
 * @return status_t STATUS_OK on success, STATUS_ERROR on failure
 */
status_t lis3mdl_init(lis3mdl_device_t *dev, uint8_t i2c_address);

/**
 * @brief Get the full-scale configuration
 * 
 * @param dev Pointer to device structure
 * @param full_scale Pointer to store the full-scale value
 * @return status_t STATUS_OK on success, STATUS_ERROR on failure
 */
status_t lis3mdl_get_full_scale(lis3mdl_device_t *dev, lis3mdl_full_scale_t *full_scale);

/**
 * @brief Set the full-scale configuration
 * 
 * @param dev Pointer to device structure
 * @param full_scale Full-scale value to set
 * @return status_t STATUS_OK on success, STATUS_ERROR on failure
 */
status_t lis3mdl_set_full_scale(lis3mdl_device_t *dev, lis3mdl_full_scale_t full_scale);

/**
 * @brief Get the output data rate
 * 
 * @param dev Pointer to device structure
 * @param odr Pointer to store the output data rate
 * @return status_t STATUS_OK on success, STATUS_ERROR on failure
 */
status_t lis3mdl_get_odr(lis3mdl_device_t *dev, lis3mdl_odr_t *odr);

/**
 * @brief Set the output data rate
 * 
 * @param dev Pointer to device structure
 * @param odr Output data rate to set
 * @return status_t STATUS_OK on success, STATUS_ERROR on failure
 */
status_t lis3mdl_set_odr(lis3mdl_device_t *dev, lis3mdl_odr_t odr);

/**
 * @brief Enable or disable the interrupt pin
 * 
 * @param dev Pointer to device structure
 * @param enable true to enable, false to disable
 * @return status_t STATUS_OK on success, STATUS_ERROR on failure
 */
status_t lis3mdl_set_interrupt_enable(lis3mdl_device_t *dev, bool enable);

/**
 * @brief Read the output data of a specified axis
 * 
 * @param dev Pointer to device structure
 * @param axis Axis to read (X, Y, or Z)
 * @param data Pointer to store the 16-bit output data
 * @return status_t STATUS_OK on success, STATUS_ERROR on failure
 */
status_t lis3mdl_read_axis(lis3mdl_device_t *dev, lis3mdl_axis_t axis, int16_t *data);

/**
 * @brief Read all three axes at once
 * 
 * @param dev Pointer to device structure
 * @param x Pointer to store X-axis data
 * @param y Pointer to store Y-axis data
 * @param z Pointer to store Z-axis data
 * @return status_t STATUS_OK on success, STATUS_ERROR on failure
 */
status_t lis3mdl_read_xyz(lis3mdl_device_t *dev, int16_t *x, int16_t *y, int16_t *z);

#endif
