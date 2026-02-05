# LIS3MDL Magnetometer Device Driver

A C device driver for the LIS3MDL 3-axis digital magnetometer sensor.

## Features

- Get/Set full-scale configuration
- Get/Set output data rate
- Enable/Disable interrupt pin
- Read single and multiple axes data (X, Y, or Z)

## Files

- `lis3mdl.h` - Driver header file with API definitions
- `lis3mdl.c` - Driver implementation
- `i2c.h` - I2C interface definition
- `i2c.c` - I2C stub implementation
- `test_lis3mdl.c` - Example program demonstrating driver usage
- `Makefile` - Build configuration

## Building

```bash
make
```

## Running the Test

```bash
./test_lis3mdl
```

## Usage Example

```
./test_lis3mdl 
=== LIS3MDL Magnetometer Driver Test ===

1. Initializing device...
read [1] bytes from bus [0x1C] for register [0x0F]
write [1] bytes to bus [0x1C] for register [0x22]: 0x00 
read [1] bytes from bus [0x1C] for register [0x21]
read [1] bytes from bus [0x1C] for register [0x20]
   Device initialized successfully!

2. Getting full-scale configuration...
read [1] bytes from bus [0x1C] for register [0x21]
   Current full-scale: ±4 gauss

3. Setting full-scale to ±12 gauss...
read [1] bytes from bus [0x1C] for register [0x21]
write [1] bytes to bus [0x1C] for register [0x21]: 0x40 
   Full-scale set successfully!

4. Getting output data rate...
read [1] bytes from bus [0x1C] for register [0x20]
   Current ODR: 10 Hz

5. Setting output data rate to 20 Hz...
read [1] bytes from bus [0x1C] for register [0x20]
write [1] bytes to bus [0x1C] for register [0x20]: 0x14 
   ODR set successfully!

6. Enabling interrupt pin...
read [1] bytes from bus [0x1C] for register [0x30]
write [1] bytes to bus [0x1C] for register [0x30]: 0xE8 
   Interrupt enabled successfully!

7. Reading X-axis data...
read [2] bytes from bus [0x1C] for register [0xA8]
   X-axis: 0 (raw ADC value)

8. Reading all axes (X, Y, Z)...
read [6] bytes from bus [0x1C] for register [0xA8]
   X: 0
   Y: 0
   Z: 0

9. Disabling interrupt pin...
read [1] bytes from bus [0x1C] for register [0x30]
write [1] bytes to bus [0x1C] for register [0x30]: 0xE8 
   Interrupt disabled successfully!

=== Test Complete ===
```

## API Reference

### Initialization

```c
status_t lis3mdl_init(lis3mdl_device_t *dev, uint8_t i2c_address);
```

### Full-Scale Configuration

```c
status_t lis3mdl_get_full_scale(lis3mdl_device_t *dev, lis3mdl_full_scale_t *full_scale);
status_t lis3mdl_set_full_scale(lis3mdl_device_t *dev, lis3mdl_full_scale_t full_scale);
```

Options: LIS3MDL_FS_4_GAUSS, LIS3MDL_FS_8_GAUSS, LIS3MDL_FS_12_GAUSS, LIS3MDL_FS_16_GAUSS

### Output Data Rate

```c
status_t lis3mdl_get_odr(lis3mdl_device_t *dev, lis3mdl_odr_t *odr);
status_t lis3mdl_set_odr(lis3mdl_device_t *dev, lis3mdl_odr_t odr);
```

Options: LIS3MDL_ODR_0_625_HZ through LIS3MDL_ODR_80_HZ

### Interrupt Control

```c
status_t lis3mdl_set_interrupt_enable(lis3mdl_device_t *dev, bool enable);
```

Options: True, False

### Data Reading

```c
// Read single axis
status_t lis3mdl_read_axis(lis3mdl_device_t *dev, lis3mdl_axis_t axis, int16_t *data);

// Read all three axes (more efficient)
status_t lis3mdl_read_xyz(lis3mdl_device_t *dev, int16_t *x, int16_t *y, int16_t *z);
```

## References

- LIS3MDL Datasheet : Rev 7 (Rel: 05-Dec-2023)
- AN4602 Application note : Rev 1 (17-Dec-2014)
