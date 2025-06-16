#ifndef PINS_H
#define PINS_H

// T-Echo Pin Definitions

// E-Paper Display (SPI)
#define EPD_MOSI     3
#define EPD_CLK      2
#define EPD_CS       30
#define EPD_DC       28
#define EPD_RESET    29
#define EPD_BUSY     4

// LoRa SX1262 (SPI)
#define LORA_MOSI    3
#define LORA_MISO    1
#define LORA_SCLK    2
#define LORA_CS      24
#define LORA_DIO1    33
#define LORA_BUSY    32
#define LORA_RST     23

// GPS L76K (UART)
#define GPS_RX_PIN   15
#define GPS_TX_PIN   13
#define GPS_WAKEUP_PIN 12
#define GPS_PPS_PIN  16

// I2C Bus (BME280 sensor)
#define I2C_SDA      26
#define I2C_SCL      27

// Power Management
#define VBAT_PIN     31
#define CHARGE_PIN   17

// User Interface
#define BUTTON_PIN   11
#define TOUCH_PIN    14

// LEDs
#define LED_PIN      LED_BUILTIN

// Buzzer (if available)
#define BUZZER_PIN   -1  // Not available on T-Echo

#endif // PINS_H 