#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_OFF)

/* Number of the configured PINS */
#define PORT_CONFIGURED_PINS              (43U)

/* Pre-compile option to enable/disable the use of Port_SetPinDirection function */
#define PORT_SET_PIN_DIRECTION_API              (STD_ON)

/* Pre-compile option to enable/disable the use of Port_SetPinMode function */
#define PORT_SET_PIN_MODE_API                   (STD_ON)

   

/*******************************************************************************
 *                              Port Pins Index                                *
 *******************************************************************************/
#define PORTA_PA0                        (0U)
#define PORTA_PA1                        (1U)
#define PORTA_PA2                        (2U)
#define PORTA_PA3                        (3U)
#define PORTA_PA4                        (4U)
#define PORTA_PA5                        (5U)
#define PORTA_PA6                        (6U)
#define PORTA_PA7                        (7U)
#define PORTB_PB0                        (8U)
#define PORTB_PB1                        (9U)
#define PORTB_PB2                        (10U)
#define PORTB_PB3                        (11U)
#define PORTB_PB4                        (12U)
#define PORTB_PB5                        (13U)
#define PORTB_PB6                        (14U)
#define PORTB_PB7                        (15U)
#define PORTC_PC0                        (16U) 
#define PORTC_PC1                        (17U) 
#define PORTC_PC2                        (18U) 
#define PORTC_PC3                        (19U)
#define PORTC_PC4                        (20U)
#define PORTC_PC5                        (21U)
#define PORTC_PC6                        (22U)
#define PORTC_PC7                        (23U)
#define PORTD_PD0                        (24U)
#define PORTD_PD1                        (25U)
#define PORTD_PD2                        (26U)
#define PORTD_PD3                        (27U)
#define PORTD_PD4                        (28U)
#define PORTD_PD5                        (29U)
#define PORTD_PD6                        (30U)
#define PORTD_PD7                        (31U)
#define PORTE_PE0                        (32U)
#define PORTE_PE1                        (33U)
#define PORTE_PE2                        (34U)
#define PORTE_PE3                        (35U)
#define PORTE_PE4                        (36U)
#define PORTE_PE5                        (37U)
#define PORTF_PF0                        (38U)  
#define PORTF_PF1                        (39U)
#define PORTF_PF2                        (40U)
#define PORTF_PF3                        (41U)
#define PORTF_PF4                        (42U)
#define JTAG_PIN1                       PORTC_PC0
#define JTAG_PIN2                       PORTC_PC1
#define JTAG_PIN3                       PORTC_PC2
#define JTAG_PIN4                       PORTC_PC3
#define NMI_PIN1                        PORTF_PF0
#define NMI_PIN2                        PORTD_PD7
#define UNLOCK_VALUE                    0x4C4F434B

/*******************************************************************************
 *                             PORTs                                           *
 *******************************************************************************/

#define PORT_A                            (0U)
#define PORT_B                            (1U)
#define PORT_C                            (2U)
#define PORT_D                            (3U)
#define PORT_E                            (4U)
#define PORT_F                            (5U)

/*******************************************************************************
 *                              PORTs  Pins                                    *
 *******************************************************************************/

#define PORT_PIN0                            (0U)
#define PORT_PIN1                            (1U)
#define PORT_PIN2                            (2U)
#define PORT_PIN3                            (3U)
#define PORT_PIN4                            (4U)
#define PORT_PIN5                            (5U)
#define PORT_PIN6                            (6U)
#define PORT_PIN7                            (7U)

#endif /* PORT_CFG_H */