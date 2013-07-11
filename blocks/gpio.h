#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define GPIO_BASE               0x01E26000

#define GPIO_PCR                ( *( volatile uint32_t* )( GPIO_BASE + 0x04 ) )
#define GPIO_BINTEN             ( *( volatile uint32_t* )( GPIO_BASE + 0x08 ) )

/* For GPIO[0:31] */
#define GPIO_DIR_BASE           ( 0x10 )   // Direction Cntl
#define GPIO_OUT_DATA_BASE      ( 0x14 )   // Output data
#define GPIO_SET_DATA_BASE      ( 0x18 )   // Set data
#define GPIO_CLR_DATA_BASE      ( 0x1C )   // Clear data
#define GPIO_IN_DATA_BASE       ( 0x20 )   // Input data
#define GPIO_SET_RIS_TRIG_BASE  ( 0x24 )   // Set rising edge intr
#define GPIO_CLR_RIS_TRIG_BASE  ( 0x28 )   // Clear rising edge intr
#define GPIO_SET_FAL_TRIG_BASE  ( 0x2C )   // Set falling edge intr
#define GPIO_CLR_FAL_TRIG_BASE  ( 0x30 )   // Clear falling edge intr
#define GPIO_INSTAT_BASE        ( 0x34 )   // Intr status
/* Offset between GPIO registers */
#define GPIO_BASE_OFFSET        ( 0x28 )

/* Base address of GPIO register */
#define GPIO_01_BASE            ( GPIO_BASE + GPIO_DIR_BASE )
#define GPIO_23_BASE            ( GPIO_01_BASE + GPIO_BASE_OFFSET )
#define GPIO_45_BASE            ( GPIO_23_BASE + GPIO_BASE_OFFSET )
#define GPIO_67_BASE            ( GPIO_45_BASE + GPIO_BASE_OFFSET )

/* Pointer to address of GPIO direction register */
#define GPIO_01_DIR         ( *(volatile uint32_t*) (GPIO_01_BASE) )
#define GPIO_23_DIR         ( *(volatile uint32_t*) (GPIO_23_BASE) )
#define GPIO_45_DIR         ( *(volatile uint32_t*) (GPIO_45_BASE) )
#define GPIO_67_DIR         ( *(volatile uint32_t*) (GPIO_67_BASE) )

/* Base address of GPIO set rising edge interrupt register */
#define GPIO_01_ADDR_SET_RIS_TRIG    ( GPIO_BASE + GPIO_SET_RIS_TRIG_BASE )
#define GPIO_23_ADDR_SET_RIS_TRIG    ( GPIO_01_ADDR_SET_RIS_TRIG + GPIO_BASE_OFFSET )
#define GPIO_45_ADDR_SET_RIS_TRIG    ( GPIO_23_ADDR_SET_RIS_TRIG + GPIO_BASE_OFFSET )
#define GPIO_67_ADDR_SET_RIS_TRIG    ( GPIO_45_ADDR_SET_RIS_TRIG + GPIO_BASE_OFFSET )

/* Pointer to address of GPIO set rising edge interrupt register */
#define GPIO_01_SET_RIS_TRIG         ( *(volatile uint32_t*) (GPIO_01_ADDR_SET_RIS_TRIG) )
#define GPIO_23_SET_RIS_TRIG         ( *(volatile uint32_t*) (GPIO_23_ADDR_SET_RIS_TRIG) )
#define GPIO_45_SET_RIS_TRIG         ( *(volatile uint32_t*) (GPIO_45_ADDR_SET_RIS_TRIG) )
#define GPIO_67_SET_RIS_TRIG         ( *(volatile uint32_t*) (GPIO_67_ADDR_SET_RIS_TRIG) )

/* Base address of GPIO set rising edge interrupt register */
#define GPIO_01_ADDR_CLR_RIS_TRIG    ( GPIO_BASE + GPIO_CLR_RIS_TRIG_BASE )
#define GPIO_23_ADDR_CLR_RIS_TRIG    ( GPIO_01_ADDR_CLR_RIS_TRIG + GPIO_BASE_OFFSET )
#define GPIO_45_ADDR_CLR_RIS_TRIG    ( GPIO_23_ADDR_CLR_RIS_TRIG + GPIO_BASE_OFFSET )
#define GPIO_67_ADDR_CLR_RIS_TRIG    ( GPIO_45_ADDR_CLR_RIS_TRIG + GPIO_BASE_OFFSET )

/* Pointer to address of GPIO set rising edge interrupt register */

#define GPIO_01_CLR_RIS_TRIG         ( *(volatile uint32_t*) (GPIO_01_ADDR_CLR_RIS_TRIG) )
#define GPIO_23_CLR_RIS_TRIG         ( *(volatile uint32_t*) (GPIO_23_ADDR_CLR_RIS_TRIG) )
#define GPIO_45_CLR_RIS_TRIG         ( *(volatile uint32_t*) (GPIO_45_ADDR_CLR_RIS_TRIG) )
#define GPIO_67_CLR_RIS_TRIG         ( *(volatile uint32_t*) (GPIO_67_ADDR_CLR_RIS_TRIG) )

/* Base address of GPIO set falling edge interrupt register */
#define GPIO_01_ADDR_SET_FAL_TRIG    ( GPIO_BASE + GPIO_SET_FAL_TRIG_BASE )
#define GPIO_23_ADDR_SET_FAL_TRIG    ( GPIO_01_ADDR_SET_FAL_TRIG + GPIO_BASE_OFFSET )
#define GPIO_45_ADDR_SET_FAL_TRIG    ( GPIO_23_ADDR_SET_FAL_TRIG + GPIO_BASE_OFFSET )
#define GPIO_67_ADDR_SET_FAL_TRIG    ( GPIO_45_ADDR_SET_FAL_TRIG + GPIO_BASE_OFFSET )

/* Pointer to address of GPIO set falling edge interrupt register */
#define GPIO_01_SET_FAL_TRIG         ( *(volatile uint32_t*) (GPIO_01_ADDR_SET_FAL_TRIG) )
#define GPIO_23_SET_FAL_TRIG         ( *(volatile uint32_t*) (GPIO_23_ADDR_SET_FAL_TRIG) )
#define GPIO_45_SET_FAL_TRIG         ( *(volatile uint32_t*) (GPIO_45_ADDR_SET_FAL_TRIG) )
#define GPIO_67_SET_FAL_TRIG         ( *(volatile uint32_t*) (GPIO_67_ADDR_SET_FAL_TRIG) )

/* Base address of GPIO set rising edge interrupt register */
#define GPIO_01_ADDR_CLR_FAL_TRIG    ( GPIO_BASE + GPIO_CLR_FAL_TRIG_BASE )
#define GPIO_23_ADDR_CLR_FAL_TRIG    ( GPIO_01_ADDR_CLR_FAL_TRIG + GPIO_BASE_OFFSET )
#define GPIO_45_ADDR_CLR_FAL_TRIG    ( GPIO_23_ADDR_CLR_FAL_TRIG + GPIO_BASE_OFFSET )
#define GPIO_67_ADDR_CLR_FAL_TRIG    ( GPIO_45_ADDR_CLR_FAL_TRIG + GPIO_BASE_OFFSET )


/* Pointer to address of GPIO set rising edge interrupt register */
#define GPIO_01_CLR_FAL_TRIG         ( *(volatile uint32_t*) (GPIO_01_ADDR_CLR_FAL_TRIG) )
#define GPIO_23_CLR_FAL_TRIG         ( *(volatile uint32_t*) (GPIO_23_ADDR_CLR_FAL_TRIG) )
#define GPIO_45_CLR_FAL_TRIG         ( *(volatile uint32_t*) (GPIO_45_ADDR_CLR_FAL_TRIG) )
#define GPIO_67_CLR_FAL_TRIG         ( *(volatile uint32_t*) (GPIO_67_ADDR_CLR_FAL_TRIG) )


/* Sys cfg registers */
#define SYS_BASE            0x01C14000

#define KICK0R              ( *(volatile uint32_t*)(SYS_BASE + 0x038) )
#define KICK1R              ( *(volatile uint32_t*)(SYS_BASE + 0x03c) )

#define PINMUX0             ( *(volatile uint32_t*)(SYS_BASE + 0x120) )
#define PINMUX1             ( *(volatile uint32_t*)(SYS_BASE + 0x124) )
#define PINMUX2             ( *(volatile uint32_t*)(SYS_BASE + 0x128) )
#define PINMUX3             ( *(volatile uint32_t*)(SYS_BASE + 0x12C) )
#define PINMUX4             ( *(volatile uint32_t*)(SYS_BASE + 0x130) )
#define PINMUX5             ( *(volatile uint32_t*)(SYS_BASE + 0x134) )
#define PINMUX6             ( *(volatile uint32_t*)(SYS_BASE + 0x138) )
#define PINMUX7             ( *(volatile uint32_t*)(SYS_BASE + 0x13C) )
#define PINMUX8             ( *(volatile uint32_t*)(SYS_BASE + 0x140) )
#define PINMUX9             ( *(volatile uint32_t*)(SYS_BASE + 0x144) )
#define PINMUX10            ( *(volatile uint32_t*)(SYS_BASE + 0x148) )
#define PINMUX11            ( *(volatile uint32_t*)(SYS_BASE + 0x14C) )
#define PINMUX12            ( *(volatile uint32_t*)(SYS_BASE + 0x150) )
#define PINMUX13            ( *(volatile uint32_t*)(SYS_BASE + 0x154) )
#define PINMUX14            ( *(volatile uint32_t*)(SYS_BASE + 0x158) )
#define PINMUX15            ( *(volatile uint32_t*)(SYS_BASE + 0x15C) )
#define PINMUX16            ( *(volatile uint32_t*)(SYS_BASE + 0x160) )
#define PINMUX17            ( *(volatile uint32_t*)(SYS_BASE + 0x164) )
#define PINMUX18            ( *(volatile uint32_t*)(SYS_BASE + 0x168) )
#define PINMUX19            ( *(volatile uint32_t*)(SYS_BASE + 0x16C) )
/* Offset between MUX registers */
#define MUX_REG_OFFSET      ( 0x0004 )


/********************* EXPORTED DEFINE MACROS (#, ##)*************************/



/******************************************************************************
************************ EXPORTED TYPE DECLARATIONS ***************************
******************************************************************************/

/********************************* ENUMS *************************************/

typedef enum
{
    PIN0                  = 0x00,
    PIN1                  = 0x01,
    PIN2                  = 0x02,
    PIN3                  = 0x03,
    PIN4                  = 0x04,
    PIN5                  = 0x05,
    PIN6                  = 0x06,
    PIN7                  = 0x07,
    PIN8                  = 0x08,
    PIN9                  = 0x09,
    PIN10                 = 0x0A,
    PIN11                 = 0x0B,
    PIN12                 = 0x0C,
    PIN13                 = 0x0D,
    PIN14                 = 0x0E,
    PIN15                 = 0x0F
} GPIO_BankPin_t;

typedef enum
{
    GPIO_BANK0            = 0,
    GPIO_BANK1            = 0x10,
    GPIO_BANK2            = 0x20,
    GPIO_BANK3            = 0x30,
    GPIO_BANK4            = 0x40,
    GPIO_BANK5            = 0x50,
    GPIO_BANK6            = 0x60,
    GPIO_BANK7            = 0x70
} GPIO_Bank_t;

typedef enum
{
/* 16 pins of Bank 0 */
    GP0_0            = (GPIO_BANK0 | PIN0),
    GP0_1            = (GPIO_BANK0 | PIN1),
    GP0_2            = (GPIO_BANK0 | PIN2),
    GP0_3            = (GPIO_BANK0 | PIN3),
    GP0_4            = (GPIO_BANK0 | PIN4),
    GP0_5            = (GPIO_BANK0 | PIN5),
    GP0_6            = (GPIO_BANK0 | PIN6),
    GP0_7            = (GPIO_BANK0 | PIN7),
    GP0_8            = (GPIO_BANK0 | PIN8),
    GP0_9            = (GPIO_BANK0 | PIN9),
    GP0_10           = (GPIO_BANK0 | PIN10),
    GP0_11           = (GPIO_BANK0 | PIN11),
    GP0_12           = (GPIO_BANK0 | PIN12),
    GP0_13           = (GPIO_BANK0 | PIN13),
    GP0_14           = (GPIO_BANK0 | PIN14),
    GP0_15           = (GPIO_BANK0 | PIN15),

/* 16 pins of Bank 1 */
    GP1_0            = (GPIO_BANK1 | PIN0),
    GP1_1            = (GPIO_BANK1 | PIN1),
    GP1_2            = (GPIO_BANK1 | PIN2),
    GP1_3            = (GPIO_BANK1 | PIN3),
    GP1_4            = (GPIO_BANK1 | PIN4),
    GP1_5            = (GPIO_BANK1 | PIN5),
    GP1_6            = (GPIO_BANK1 | PIN6),
    GP1_7            = (GPIO_BANK1 | PIN7),
    GP1_8            = (GPIO_BANK1 | PIN8),
    GP1_9            = (GPIO_BANK1 | PIN9),
    GP1_10           = (GPIO_BANK1 | PIN10),
    GP1_11           = (GPIO_BANK1 | PIN11),
    GP1_12           = (GPIO_BANK1 | PIN12),
    GP1_13           = (GPIO_BANK1 | PIN13),
    GP1_14           = (GPIO_BANK1 | PIN14),
    GP1_15           = (GPIO_BANK1 | PIN15),

/* 16 pins of Bank 2 */
    GP2_0            = (GPIO_BANK2 | PIN0),
    GP2_1            = (GPIO_BANK2 | PIN1),
    GP2_2            = (GPIO_BANK2 | PIN2),
    GP2_3            = (GPIO_BANK2 | PIN3),
    GP2_4            = (GPIO_BANK2 | PIN4),
    GP2_5            = (GPIO_BANK2 | PIN5),
    GP2_6            = (GPIO_BANK2 | PIN6),
    GP2_7            = (GPIO_BANK2 | PIN7),
    GP2_8            = (GPIO_BANK2 | PIN8),
    GP2_9            = (GPIO_BANK2 | PIN9),
    GP2_10           = (GPIO_BANK2 | PIN10),
    GP2_11           = (GPIO_BANK2 | PIN11),
    GP2_12           = (GPIO_BANK2 | PIN12),
    GP2_13           = (GPIO_BANK2 | PIN13),
    GP2_14           = (GPIO_BANK2 | PIN14),
    GP2_15           = (GPIO_BANK2 | PIN15),

/* 16 pins of Bank 3 */
    GP3_0            = (GPIO_BANK3 | PIN0),
    GP3_1            = (GPIO_BANK3 | PIN1),
    GP3_2            = (GPIO_BANK3 | PIN2),
    GP3_3            = (GPIO_BANK3 | PIN3),
    GP3_4            = (GPIO_BANK3 | PIN4),
    GP3_5            = (GPIO_BANK3 | PIN5),
    GP3_6            = (GPIO_BANK3 | PIN6),
    GP3_7            = (GPIO_BANK3 | PIN7),
    GP3_8            = (GPIO_BANK3 | PIN8),
    GP3_9            = (GPIO_BANK3 | PIN9),
    GP3_10           = (GPIO_BANK3 | PIN10),
    GP3_11           = (GPIO_BANK3 | PIN11),
    GP3_12           = (GPIO_BANK3 | PIN12),
    GP3_13           = (GPIO_BANK3 | PIN13),
    GP3_14           = (GPIO_BANK3 | PIN14),
    GP3_15           = (GPIO_BANK3 | PIN15),

/* 16 pins of Bank 4 */
    GP4_0            = (GPIO_BANK4 | PIN0),
    GP4_1            = (GPIO_BANK4 | PIN1),
    GP4_2            = (GPIO_BANK4 | PIN2),
    GP4_3            = (GPIO_BANK4 | PIN3),
    GP4_4            = (GPIO_BANK4 | PIN4),
    GP4_5            = (GPIO_BANK4 | PIN5),
    GP4_6            = (GPIO_BANK4 | PIN6),
    GP4_7            = (GPIO_BANK4 | PIN7),
    GP4_8            = (GPIO_BANK4 | PIN8),
    GP4_9            = (GPIO_BANK4 | PIN9),
    GP4_10           = (GPIO_BANK4 | PIN10),
    GP4_11           = (GPIO_BANK4 | PIN11),
    GP4_12           = (GPIO_BANK4 | PIN12),
    GP4_13           = (GPIO_BANK4 | PIN13),
    GP4_14           = (GPIO_BANK4 | PIN14),
    GP4_15           = (GPIO_BANK4 | PIN15),

/* 16 pins of Bank 5 */
    GP5_0            = (GPIO_BANK5 | PIN0),
    GP5_1            = (GPIO_BANK5 | PIN1),
    GP5_2            = (GPIO_BANK5 | PIN2),
    GP5_3            = (GPIO_BANK5 | PIN3),
    GP5_4            = (GPIO_BANK5 | PIN4),
    GP5_5            = (GPIO_BANK5 | PIN5),
    GP5_6            = (GPIO_BANK5 | PIN6),
    GP5_7            = (GPIO_BANK5 | PIN7),
    GP5_8            = (GPIO_BANK5 | PIN8),
    GP5_9            = (GPIO_BANK5 | PIN9),
    GP5_10           = (GPIO_BANK5 | PIN10),
    GP5_11           = (GPIO_BANK5 | PIN11),
    GP5_12           = (GPIO_BANK5 | PIN12),
    GP5_13           = (GPIO_BANK5 | PIN13),
    GP5_14           = (GPIO_BANK5 | PIN14),
    GP5_15           = (GPIO_BANK5 | PIN15),

/* 16 pins of Bank 6 */
    GP6_0            = (GPIO_BANK6 | PIN0),
    GP6_1            = (GPIO_BANK6 | PIN1),
    GP6_2            = (GPIO_BANK6 | PIN2),
    GP6_3            = (GPIO_BANK6 | PIN3),
    GP6_4            = (GPIO_BANK6 | PIN4),
    GP6_5            = (GPIO_BANK6 | PIN5),
    GP6_6            = (GPIO_BANK6 | PIN6),
    GP6_7            = (GPIO_BANK6 | PIN7),
    GP6_8            = (GPIO_BANK6 | PIN8),
    GP6_9            = (GPIO_BANK6 | PIN9),
    GP6_10           = (GPIO_BANK6 | PIN10),
    GP6_11           = (GPIO_BANK6 | PIN11),
    GP6_12           = (GPIO_BANK6 | PIN12),
    GP6_13           = (GPIO_BANK6 | PIN13),
    GP6_14           = (GPIO_BANK6 | PIN14),
    GP6_15           = (GPIO_BANK6 | PIN15),

    /* 16 pins of Bank 7 */
    GP7_0            = (GPIO_BANK7 | PIN0),
    GP7_1            = (GPIO_BANK7 | PIN1),
    GP7_2            = (GPIO_BANK7 | PIN2),
    GP7_3            = (GPIO_BANK7 | PIN3),
    GP7_4            = (GPIO_BANK7 | PIN4),
    GP7_5            = (GPIO_BANK7 | PIN5),
    GP7_6            = (GPIO_BANK7 | PIN6),
    GP7_7            = (GPIO_BANK7 | PIN7),
    GP7_8            = (GPIO_BANK7 | PIN8),
    GP7_9            = (GPIO_BANK7 | PIN9),
    GP7_10           = (GPIO_BANK7 | PIN10),
    GP7_11           = (GPIO_BANK7 | PIN11),
    GP7_12           = (GPIO_BANK7 | PIN12),
    GP7_13           = (GPIO_BANK7 | PIN13),
    GP7_14           = (GPIO_BANK7 | PIN14),
    GP7_15           = (GPIO_BANK7 | PIN15)

} GPIO_PinNumber_t;

typedef enum
{
    GPIO_OUTPUT              = 0,
    GPIO_INPUT               = 1,
    GPIO_DEFAULT             = GPIO_INPUT
} GPIO_PortDir_t;

typedef enum
{
    GPIO_LOW            = 0,
    GPIO_HIGH           = 1
} GPIO_PinStatus_t;

typedef enum
{
    GPIO_RISING_EDGE    = 0,
    GPIO_FALLING_EDGE   = 1
} GPIO_EdgeType_t;

typedef enum
{
    MUX_FUNC_DEFAULT    = 0x00,     /* Pin tri-stated */
    MUX_FUNC_4          = 0x01,     /* b0001          */
    MUX_FUNC_3          = 0x02,     /* b0010          */
    MUX_FUNC_2          = 0x04,     /* b0100          */
    MUX_FUNC_1          = 0x08      /* b1000          */
} MUX_PinFunc_t;

typedef enum
{
    EMB_WE              = 28,
    EMB_RAS             = 24,
    EMB_CAS             = 20,
    EMB_CS0             = 16,
    EMB_CLK             = 12,
    EMB_SDCKE           = 8,
    EMU0                = 4,
    RTCK                = 0
} MUX_Mux0CtrlNibble_t;

typedef enum
{
    EMB_A5              = 28,
    EMB_A4              = 24,
    EMB_A3              = 20,
    EMB_A2              = 16,
    EMB_A1              = 12,
    EMB_A0              = 8,
    EMB_BA0             = 4,
    EMB_BA1             = 0
} MUX_Mux1CtrlNibble_t;

typedef enum
{
    EMB_D31             = 28,
    EMB_A12             = 24,
    EMB_A11             = 20,
    EMB_A10             = 16,
    EMB_A9              = 12,
    EMB_A8              = 8,
    EMB_A7              = 4,
    EMB_A6              = 0
} MUX_Mux2CtrlNibble_t;

typedef enum
{
    EMB_D23             = 28,
    EMB_D24             = 24,
    EMB_D25             = 20,
    EMB_D26             = 16,
    EMB_D27             = 12,
    EMB_D28             = 8,
    EMB_D29             = 4,
    EMB_D30             = 0
} MUX_Mux3CtrlNibble_t;

typedef enum
{
    EMB_WE_DQM3         = 28,
    EMB_D16             = 24,
    EMB_D17             = 20,
    EMB_D18             = 16,
    EMB_D19             = 12,
    EMB_D20             = 8,
    EMB_D21             = 4,
    EMB_D22             = 0
} MUX_Mux4CtrlNibble_t;

typedef enum
{
    EMB_D6              = 28,
    EMB_D5              = 24,
    EMB_D4              = 20,
    EMB_D3              = 16,
    EMB_D2              = 12,
    EMB_D1              = 8,
    EMB_D0              = 4,
    EMB_WE_DQM2         = 0
} MUX_Mux5CtrlNibble_t;

typedef enum
{
    EMB_D14             = 28,
    EMB_D13             = 24,
    EMB_D12             = 20,
    EMB_D11             = 16,
    EMB_D10             = 12,
    EMB_D9              = 8,
    EMB_D8              = 4,
    EMB_D7              = 0
} MUX_Mux6CtrlNibble_t;

typedef enum
{
    SPI0_SCS            = 28,
    SPI0_ENA            = 24,
    SPI0_CLK            = 20,
    SPI0_SIMO0          = 16,
    SPI0_SOMI0          = 12,
    EMB_WE_DQM0         = 8,
    EMB_WE_DQM1         = 4,
    EMB_D15             = 0
} MUX_Mux7CtrlNibble_t;

typedef enum
{
    SPI1_ENA            = 28,
    AXR1_11             = 24,
    AXR1_10             = 20,
    UART0_TXD           = 16,
    UART0_RXD           = 12,
    SPI1_CLK            = 8,
    SPI1_SIMO0          = 4,
    SPI1_SOMI0          = 0
} MUX_Mux8CtrlNibble_t;

typedef enum
{
    AFSR0               = 28,
    ACLKR0              = 24,
    AHCLKR0             = 20,
    AFSX0               = 16,
    ACLKX0              = 12,
    AHCLKX0             = 8,
    USB0_DRVVBUS        = 4,
    SPI1_SCS0           = 0
} MUX_Mux9CtrlNibble_t;

typedef enum
{
    AXR0_6              = 28,
    AXR0_5              = 24,
    AXR0_4              = 20,
    AXR0_3              = 16,
    AXR0_2              = 12,
    AXR0_1              = 8,
    AXR0_0              = 4,
    AMUTE0              = 0
} MUX_Mux10CtrlNibble_t;

typedef enum
{
    AFSX1               = 28,
    ACLKX1              = 24,
    AHCLKX1             = 20,
    AXR0_11             = 16,
    UART1_TXD           = 12,
    UART1_RXD           = 8,
    AXR0_8              = 4,
    AXR0_7              = 0
} MUX_Mux11CtrlNibble_t;

typedef enum
{
    AXR1_3              = 28,
    AXR1_2              = 24,
    AXR1_1              = 20,
    AXR1_0              = 16,
    AMUTE1              = 12,
    AFSR1               = 8,
    ACLKR1              = 4,
    AHCLKR1             = 0
} MUX_Mux12CtrlNibble_t;

typedef enum
{
    EMA_D1              = 28,
    EMA_D0              = 24,
    AXR1_9              = 20,
    AXR1_8              = 16,
    AXR1_7              = 12,
    AXR1_6              = 8,
    AXR1_5              = 4,
    AXR1_4              = 0
} MUX_Mux13CtrlNibble_t;

typedef enum
{
    EMA_D9              = 28,
    EMA_D8              = 24,
    EMA_D7              = 20,
    EMA_D6              = 16,
    EMA_D5              = 12,
    EMA_D4              = 8,
    EMA_D3              = 4,
    EMA_D2              = 0
} MUX_Mux14CtrlNibble_t;

typedef enum
{
    EMA_A1              = 28,
    EMA_A0              = 24,
    EMA_D15             = 20,
    EMA_D14             = 16,
    EMA_D13             = 12,
    EMA_D12             = 8,
    EMA_D11             = 4,
    EMA_D10             = 0
} MUX_Mux15CtrlNibble_t;

typedef enum
{
    EMA_A9              = 28,
    EMA_A8              = 24,
    EMA_A7              = 20,
    EMA_A6              = 16,
    EMA_A5              = 12,
    EMA_A4              = 8,
    EMA_A3              = 4,
    EMA_A2              = 0
} MUX_Mux16CtrlNibble_t;

typedef enum
{
    EMA_CAS             = 28,
    EMA_SDCKE           = 24,
    EMA_CLK             = 20,
    EMA_BA0             = 16,
    EMA_BA1             = 12,
    EMA_A12             = 8,
    EMA_A11             = 4,
    EMA_A10             = 0
} MUX_Mux17CtrlNibble_t;

typedef enum
{
    EMA_WE_DQM0         = 28,
    EMA_WE_DQM1         = 24,
    EMA_OE              = 20,
    EMA_CS3             = 16,
    EMA_CS2             = 12,
    EMA_CS0             = 8,
    EMA_WE              = 4,
    EMA_RAS             = 0
} MUX_Mux18CtrlNibble_t;

typedef enum
{
    MUX19_RES1          = 28,
    MUX19_RES2          = 24,
    MUX19_RES3          = 20,
    MUX19_RES4          = 16,
    MUX19_RES5          = 12,
    MUX19_RES6          = 8,
    MUX19_RES7          = 4,
    EMA_WAIT            = 0
} MUX_Mux19CtrlNibble_t;

typedef enum
{
    MUX_0               = 0x00,
    MUX_1               = 0x01,
    MUX_2               = 0x02,
    MUX_3               = 0x03,
    MUX_4               = 0x04,
    MUX_5               = 0x05,
    MUX_6               = 0x06,
    MUX_7               = 0x07,
    MUX_8               = 0x08,
    MUX_9               = 0x09,
    MUX_10              = 0x0a,
    MUX_11              = 0x0b,
    MUX_12              = 0x0c,
    MUX_13              = 0x0d,
    MUX_14              = 0x0e,
    MUX_15              = 0x0f,
    MUX_16              = 0x10,
    MUX_17              = 0x11,
    MUX_18              = 0x12,
    MUX_19              = 0x13
} MUX_Mux_t;


void GPIO_init(void);
int16_t GPIO_setDir(GPIO_PinNumber_t pinNumber, GPIO_PortDir_t direction);
int16_t GPIO_getInput(GPIO_PinNumber_t pinNumber);
int16_t GPIO_getOutput(GPIO_PinNumber_t pinNumber);
int16_t GPIO_setOutput(GPIO_PinNumber_t pinNumber, GPIO_PinStatus_t output);
int16_t GPIO_getLastSetOutput(GPIO_PinNumber_t pinNumber);
int16_t GPIO_setEdgeTrigger(GPIO_PinNumber_t pinNumber, GPIO_EdgeType_t edgeType);
int16_t GPIO_clrEdgeTrigger(GPIO_PinNumber_t pinNumber, GPIO_EdgeType_t edgeType);

void MUX_init(void);
int16_t MUX_setPinFunc(MUX_Mux_t muxReg, uint8_t pinOffset, MUX_PinFunc_t newFunc);



#endif /* GPIO_H */

