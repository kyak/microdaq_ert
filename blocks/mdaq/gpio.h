/* gpio.h -- GPIO driver for MicroDAQ device
 *
 * Copyright (C) 2013 Embedded Solutions
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */


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


void GPIO_init(void);
uint32_t GPIO_getBank( GPIO_Bank_t bank);
int16_t GPIO_setDir(GPIO_PinNumber_t pinNumber, GPIO_PortDir_t direction);
int16_t GPIO_getInput(GPIO_PinNumber_t pinNumber);
int16_t GPIO_getOutput(GPIO_PinNumber_t pinNumber);
int16_t GPIO_setOutput(GPIO_PinNumber_t pinNumber, GPIO_PinStatus_t output);
int16_t GPIO_getLastSetOutput(GPIO_PinNumber_t pinNumber);
int16_t GPIO_setEdgeTrigger(GPIO_PinNumber_t pinNumber, GPIO_EdgeType_t edgeType);
int16_t GPIO_clrEdgeTrigger(GPIO_PinNumber_t pinNumber, GPIO_EdgeType_t edgeType);

#endif /* GPIO_H */

