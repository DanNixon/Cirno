#ifndef _TILDA_PINS_H
#define _TILDA_PINS_H

// Test pads
#define TP4                   (22u) //D22
#define TP5                   (79u)
#define TP6                   (78u) //SS3
#define TP7                   (80u)
#define TP8                   (83u)
#define TP9                   (81u)
#define TP10                  (23u) //D23
#define TP11                  (16u) //Serial2 TXD
#define TP12                  (17u) //Serial2 RXD
#define TP15                  (14u) //Serial3 TXD
#define TP16                  (15u) //Serial3 RXD
#define TP20                  (29u) //SCREEN_LEFT
#define TP21                  (46u) //SCREEN_RIGHT
#define TP22                  (51u) //D51
#define TP23                  (64u) //A64
#define TP24                  (63u) //A63
#define TP25                  (33u) //D33
#define TP26                  (32u) //D32
#define TP27                  (96u) //UOTGVOBOF

// GLCD
#define LCD_CS                BOARD_SPI_SS2
#define LCD_POWER             (40u)
#define LCD_BACKLIGHT         (35u)
#define LCD_BACKLIGHT_ON      HIGH
#define LCD_BACKLIGHT_OFF     LOW
#define LCD_A0                (38u)
#define LCD_RESET             (34u)

// MCP73831 v0.2+
#define MCP_STAT              (62u)

// RGB LED's
#define LED1_BLUE             (37u)
#define LED1_GREEN            (39u)
#define LED1_RED              (41u)
#define LED2_BLUE             (82u)
#define LED2_GREEN            (44u)
#define LED2_RED              (45u)

// SD socket
#define SD_CS                 BOARD_SPI_SS1
#define SD_CARD_DECTECT       (36u)

// Flash
#define FLASH_CS              BOARD_SPI_SS0
#define FLASH_HOLD            (49u)

// IMU (MPU & HMC)
#define MPU_INT               (31u)
#define HMC_DRDY              (30u)

// Radio (SRF)
#define SRF_SLEEP             (61u)
#define SRF_AT_COMMAND        (43u)

// IR
#define IR_TX_PWM             (6u)
#define IR_RX                 (42u)

// Buttons
#define BUTTON_LIGHT          (60u)
#define BUTTON_SCREEN_RIGHT   (46u)
#define BUTTON_SCREEN_LEFT    (29u)
#define BUTTON_A              (48u)
#define BUTTON_B              (47u)
#define BUTTON_UP             (27u)
#define BUTTON_RIGHT          (25u)
#define BUTTON_DOWN           (26u)
#define BUTTON_LEFT           (28u)
#define BUTTON_CENTER         (24u)

// PMIC
#define VBATT_MON             A11
#define PMIC_ENOTG            (96u)
#define PMIC_VUSBGD           (64u)
#define PMIC_FAULT            (63u)
#define PMIC_CHRG             (62u)
#define PMIC_ILIM1            (51u)
#define PMIC_ILIM0            (50u)

// Piezo
#define PIEZO                 (66u)
#define PIEZO_PWM             (111u)

#endif //_TILDA_PINS_H
