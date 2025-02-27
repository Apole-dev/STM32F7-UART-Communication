#ifndef LORA_ENUMS
#define LORA_ENUMS

#include <stdbool.h>
#include <stdint.h>

enum PARITY_STATE {
    PARITY_8N1 = 0b00,  // 8N1 (No parity)
    PARITY_8O1 = 0b01,  // 8O1 (Odd parity)
    PARITY_8E1 = 0b10   // 8E1 (Even parity)
};

enum BAUD_RATE {
    BAUD_1200   = 0b000,
    BAUD_2400   = 0b001,
    BAUD_4800   = 0b010,
    BAUD_9600   = 0b011,
    BAUD_19200  = 0b100,
    BAUD_38400  = 0b101,
    BAUD_57600  = 0b110,
    BAUD_115200 = 0b111
};

enum AIR_DATA_RATE {
    AIR_RATE_0_3K = 0b000,  // 0.3 kbps
    AIR_RATE_1_2K = 0b001,  // 1.2 kbps
    AIR_RATE_2_4K = 0b010,  // 2.4 kbps
    AIR_RATE_4_8K = 0b011,  // 4.8 kbps
    AIR_RATE_9_6K = 0b100,  // 9.6 kbps
    AIR_RATE_19_2K = 0b101  // 19.2 kbps
};

enum WIRLESS_WAKE_TIME {
    WAKE_250MS  = 0b000,  // 250 ms
    WAKE_500MS  = 0b001,  // 500 ms
    WAKE_750MS  = 0b010,  // 750 ms
    WAKE_1000MS = 0b011,  // 1000 ms
    WAKE_1250MS = 0b100,  // 1250 ms
    WAKE_1500MS = 0b101,  // 1500 ms
    WAKE_1750MS = 0b110,  // 1750 ms
    WAKE_2000MS = 0b111   // 2000 ms
};

enum TRANSMISSION_POWER {
    POWER_30DBM = 0b00,  // 30 dBm
    POWER_27DBM = 0b01,  // 27 dBm
    POWER_24DBM = 0b10,  // 24 dBm
    POWER_21DBM = 0b11   // 21 dBm
};

#endif // !LORA_ENUMS
