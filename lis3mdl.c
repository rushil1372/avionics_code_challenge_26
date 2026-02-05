#include "lis3mdl.h"
#include <stddef.h>

// Bit masks for CTRL_REG1 
#define LIS3MDL_CTRL_REG1_DO_MASK   0x1C  // DO - bits 2 3 4
#define LIS3MDL_CTRL_REG1_DO_SHIFT  2

// Bit masks for CTRL_REG2 
#define LIS3MDL_CTRL_REG2_FS_MASK   0x60  // FS - bits 5 6
#define LIS3MDL_CTRL_REG2_FS_SHIFT  5

// Bit masks for CTRL_REG3 
#define LIS3MDL_CTRL_REG3_MD_MASK   0x03  // MD - bits 0 1

// Bit masks for INT_CFG 
#define LIS3MDL_INT_CFG_IEN         0x01  // Interrupt enable bit

// Operating mode - Continuous conversion - REG3
#define LIS3MDL_MODE_CONTINUOUS     0x00

status_t lis3mdl_init(lis3mdl_device_t *dev, uint8_t i2c_address)
{
    uint8_t who_am_i;
    uint8_t ctrl_reg;
    status_t status;

    if (dev == NULL) {
        return STATUS_ERROR;
    }

    dev->i2c_address = i2c_address;

    status = i2c_read(dev->i2c_address, LIS3MDL_WHO_AM_I, 1, &who_am_i);
    if (status != STATUS_OK || who_am_i != LIS3MDL_WHO_AM_I_VALUE) {
        return STATUS_ERROR;
    }

    ctrl_reg = LIS3MDL_MODE_CONTINUOUS;
    status = i2c_write(dev->i2c_address, LIS3MDL_CTRL_REG3, 1, &ctrl_reg);
    if (status != STATUS_OK) {
        return STATUS_ERROR;
    }

    status = lis3mdl_get_full_scale(dev, &dev->full_scale);
    if (status != STATUS_OK) {
        return STATUS_ERROR;
    }

    status = lis3mdl_get_odr(dev, &dev->odr);
    if (status != STATUS_OK) {
        return STATUS_ERROR;
    }

    return STATUS_OK;
}

// Get the full scale configuration
status_t lis3mdl_get_full_scale(lis3mdl_device_t *dev, lis3mdl_full_scale_t *full_scale)
{
    uint8_t ctrl_reg2;
    status_t status;

    if (dev == NULL || full_scale == NULL) {
        return STATUS_ERROR;
    }

    status = i2c_read(dev->i2c_address, LIS3MDL_CTRL_REG2, 1, &ctrl_reg2);
    if (status != STATUS_OK) {
        return STATUS_ERROR;
    }

    *full_scale = (lis3mdl_full_scale_t)((ctrl_reg2 & LIS3MDL_CTRL_REG2_FS_MASK) >> LIS3MDL_CTRL_REG2_FS_SHIFT);
    dev->full_scale = *full_scale;

    return STATUS_OK;
}

// Set the full scale configuration
status_t lis3mdl_set_full_scale(lis3mdl_device_t *dev, lis3mdl_full_scale_t full_scale)
{
    uint8_t ctrl_reg2;
    status_t status;

    if (dev == NULL || full_scale > LIS3MDL_FS_16_GAUSS) {
        return STATUS_ERROR;
    }

    status = i2c_read(dev->i2c_address, LIS3MDL_CTRL_REG2, 1, &ctrl_reg2);
    if (status != STATUS_OK) {
        return STATUS_ERROR;
    }

    ctrl_reg2 &= ~LIS3MDL_CTRL_REG2_FS_MASK;
    ctrl_reg2 |= (full_scale << LIS3MDL_CTRL_REG2_FS_SHIFT);

    status = i2c_write(dev->i2c_address, LIS3MDL_CTRL_REG2, 1, &ctrl_reg2);
    if (status != STATUS_OK) {
        return STATUS_ERROR;
    }

    dev->full_scale = full_scale;

    return STATUS_OK;
}

// Get the output data rate
status_t lis3mdl_get_odr(lis3mdl_device_t *dev, lis3mdl_odr_t *odr)
{
    uint8_t ctrl_reg1;
    status_t status;

    if (dev == NULL || odr == NULL) {
        return STATUS_ERROR;
    }

    status = i2c_read(dev->i2c_address, LIS3MDL_CTRL_REG1, 1, &ctrl_reg1);
    if (status != STATUS_OK) {
        return STATUS_ERROR;
    }

    *odr = (lis3mdl_odr_t)((ctrl_reg1 & LIS3MDL_CTRL_REG1_DO_MASK) >> LIS3MDL_CTRL_REG1_DO_SHIFT);
    dev->odr = *odr;

    return STATUS_OK;
}

// Set the output data rate
status_t lis3mdl_set_odr(lis3mdl_device_t *dev, lis3mdl_odr_t odr)
{
    uint8_t ctrl_reg1;
    status_t status;

    if (dev == NULL || odr > LIS3MDL_ODR_80_HZ) {
        return STATUS_ERROR;
    }

    status = i2c_read(dev->i2c_address, LIS3MDL_CTRL_REG1, 1, &ctrl_reg1);
    if (status != STATUS_OK) {
        return STATUS_ERROR;
    }

    ctrl_reg1 &= ~LIS3MDL_CTRL_REG1_DO_MASK;
    ctrl_reg1 |= (odr << LIS3MDL_CTRL_REG1_DO_SHIFT);

    status = i2c_write(dev->i2c_address, LIS3MDL_CTRL_REG1, 1, &ctrl_reg1);
    if (status != STATUS_OK) {
        return STATUS_ERROR;
    }

    dev->odr = odr;

    return STATUS_OK;
}

// Enable or disable interrupt pin
status_t lis3mdl_set_interrupt_enable(lis3mdl_device_t *dev, bool enable)
{
    uint8_t int_cfg;
    status_t status;

    if (dev == NULL) {
        return STATUS_ERROR;
    }

    status = i2c_read(dev->i2c_address, LIS3MDL_INT_CFG, 1, &int_cfg);
    if (status != STATUS_OK) {
        return STATUS_ERROR;
    }

    if (enable) {
        int_cfg |= LIS3MDL_INT_CFG_IEN;
    } else {
        int_cfg &= ~LIS3MDL_INT_CFG_IEN;
    }

    status = i2c_write(dev->i2c_address, LIS3MDL_INT_CFG, 1, &int_cfg);
    if (status != STATUS_OK) {
        return STATUS_ERROR;
    }

    return STATUS_OK;
}

// Read output of specified axis
status_t lis3mdl_read_axis(lis3mdl_device_t *dev, lis3mdl_axis_t axis, int16_t *data)
{
    uint8_t buffer[2];
    uint8_t reg_address;
    status_t status;

    if (dev == NULL || data == NULL) {
        return STATUS_ERROR;
    }

    switch (axis) {
        case LIS3MDL_AXIS_X:
            reg_address = LIS3MDL_OUT_X_L;
            break;
        case LIS3MDL_AXIS_Y:
            reg_address = LIS3MDL_OUT_Y_L;
            break;
        case LIS3MDL_AXIS_Z:
            reg_address = LIS3MDL_OUT_Z_L;
            break;
        default:
            return STATUS_ERROR;
    }

    // Read two bytes from register
    status = i2c_read(dev->i2c_address, reg_address | 0x80, 2, buffer);
    if (status != STATUS_OK) {
        return STATUS_ERROR;
    }

    // Combine low and high bytes into 16-bit signed value
    *data = (int16_t)((buffer[1] << 8) | buffer[0]);

    return STATUS_OK;
}

// Read all axis data together
status_t lis3mdl_read_xyz(lis3mdl_device_t *dev, int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t buffer[6];
    status_t status;

    if (dev == NULL || x == NULL || y == NULL || z == NULL) {
        return STATUS_ERROR;
    }

    status = i2c_read(dev->i2c_address, LIS3MDL_OUT_X_L | 0x80, 6, buffer);
    if (status != STATUS_OK) {
        return STATUS_ERROR;
    }

    // Combine low and high bytes for each axis
    *x = (int16_t)((buffer[1] << 8) | buffer[0]);
    *y = (int16_t)((buffer[3] << 8) | buffer[2]);
    *z = (int16_t)((buffer[5] << 8) | buffer[4]);

    return STATUS_OK;
}
