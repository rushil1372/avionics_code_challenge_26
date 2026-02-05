#include "i2c.h"
#include <stdint.h>
#include <stdio.h>

// Simulated register storage for testing 
static uint8_t simulated_registers[256] = {0};
static int initialized = 0;

static void init_simulated_registers(void)
{
    if (!initialized) {
        // WHO_AM_I
        simulated_registers[0x0F] = 0x3D;
        
        // Default CTRL_REG1: OM=00, DO=100 (10Hz)
        simulated_registers[0x20] = 0x10;
        
        // Default CTRL_REG2: FS=00 (4 G) 
        simulated_registers[0x21] = 0x00;
        
        // Default CTRL_REG3: MD=11 - power-down
        simulated_registers[0x22] = 0x03;
        
        // Default INT_CFG 
        simulated_registers[0x30] = 0xE8;
        
        // Simulate some magnetic field data 
        simulated_registers[0x28] = 0x12;  // X low 
        simulated_registers[0x29] = 0x34;  // X high 
        simulated_registers[0x2A] = 0x56;  // Y low 
        simulated_registers[0x2B] = 0x78;  // Y high 
        simulated_registers[0x2C] = 0x9A;  // Z low 
        simulated_registers[0x2D] = 0xBC;  // Z high 
        
        initialized = 1;
    }
}

status_t i2c_read(
    uint8_t bus_address,
    uint8_t register_address,
    uint16_t length,
    uint8_t *buffer)
{
    init_simulated_registers();
    
    printf(
        "read [%d] bytes from bus [0x%02X] for register [0x%02X]\n",
        length,
        bus_address,
        register_address);
    
    // Read from simulated registers 
    for (size_t i = 0; i < length; ++i) {
        buffer[i] = simulated_registers[(register_address + i) & 0xFF];
    }
    
    return STATUS_OK;
}
status_t i2c_write(
    uint8_t bus_address,
    uint8_t register_address,
    uint16_t length,
    uint8_t *buffer)
{
    init_simulated_registers();
    
    printf(
        "write [%d] bytes to bus [0x%02X] for register [0x%02X]: ",
        length,
        bus_address,
        register_address);
    
    // Write to simulated registers 
    for (size_t i = 0; i < length; ++i) {
        simulated_registers[(register_address + i) & 0xFF] = buffer[i];
        printf("0x%02X ", buffer[i]);
    }
    printf("\n");
    
    return STATUS_OK;
}
