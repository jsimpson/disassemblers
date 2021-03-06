#ifndef EMULATOR_8080_H_
#define EMULATOR_8080_H_

#include <stdint.h>

// Registers and register pairs.
enum {
    B  = 0x00,
    C  = 0x01,
    D  = 0x02,
    E  = 0x03,
    H  = 0x04,
    L  = 0x05,
    M  = 0x06,
    A  = 0x07,
    BC = 0x00,
    DE = 0x01,
    HL = 0x02,
    SP = 0x03
};

// Condition code (status) bits.
enum {
    ZERO_BIT      = 1,
    SIGN_BIT      = 1 << 1,
    AUX_CARRY_BIT = 1 << 2,
    PARITY_BIT    = 1 << 3,
    CARRY_BIT     = 1 << 4
};


typedef struct condition_codes
{
    unsigned char s:1;  // sign flag
    unsigned char z:1;  // zero flag
    unsigned char ac:1; // auxillary carry flag
    unsigned char p:1;  // parity flag
    unsigned char cy:1; // carry flag
    unsigned char padding:3;
} condition_codes_t;

typedef struct cpu
{
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char d;
    unsigned char e;
    unsigned char h;
    unsigned char l;
    unsigned short int stack_pointer;
    unsigned short int program_counter;
    unsigned char * memory;
    condition_codes_t condition_codes;
    unsigned char interrupt_enabled;

} cpu_8080_t;

void die(cpu_8080_t * cpu);
void process_condition_bits(cpu_8080_t * cpu, uint16_t value, uint8_t bits);
int process_instruction(cpu_8080_t * cpu);
void load_rom_to_memory(cpu_8080_t * cpu, const char * filename);

#endif /* !EMULATOR_8080_H_ */
