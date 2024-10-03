 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Salah
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
* for example Siemens Industry Software's ID = 0x001F :)*/
#define PORT_VENDOR_ID    (0x001F)

/* Port Module Id */

#define PORT_MODULE_ID (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)
#define ZERO 0


/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h" 

/* AUTOSAR Version checking between Dio_Cfg.h and Dio.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_Cfg.h and Dio.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

   
/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/

/* Service ID for PORT Init */
#define PORT_INIT_SID (uint8)0x00

/* Service ID for PORT Set Pin Direction */
#define PORT_SET_PIN_DIRECTION_STD (uint8)0x01   

/* Service ID for PORT Refresh Port Direction */
#define PORT_REFRESH_PORT_DIRECTION_STD (uint8)0x02   
   
/* Service ID for PORT GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID       (uint8)0x03
   
/* Service ID for PORT Set Pin Mode */
#define PORT_SET_PIN_MODE_STD (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
   
/* DET code to report Invalid Port Pin ID */
#define PORT_E_PARAM_PIN (uint8)0x0A
   
/* DET code to report Port Pin Not Changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE (uint8)0x0B

/* DET code to report API Port_init Called With Wrong Parameter */
#define PORT_E_PARAM_CONFIG (uint8)0x0C

/* DET code to report API Port_SetPinMode Called When Mode Is Unchangeable */
#define PORT_E_MODE_UNCHANGEABLE (uint8)0x0E
#define PORT_E_PARAM_INVALID_MODE (uint8)0x0D

/* DET code to report API Service Without Module Initialization */
#define PORT_E_UNINIT (uint8)0x0F

/* DET code to report API Called With Null Pointer */
#define PORT_E_PARAM_POINTER (uint8)0x10

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
/*Description : Type definition for Port_PinType used by the PORT APIs.*/   
typedef uint8 Port_PinType;
 
/*enum for input and output pin during runtime*/
typedef enum
{
    INPUT,OUTPUT
}Port_PinDirectionType;    
/* Description: Descripton mode of pins */ 
typedef uint8 Port_PinModeType;
   
/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    NO_PULLUP,PULL_UP,PULL_DOWN
}Port_InternalResistor;   
/* Description: Enum to hold PIN direction */
typedef enum
{
    NOT_Changeable,Changeable
}Port_PinModeChangeable;

/* Description: Enum to hold PIN direction */
typedef enum
{
    OFF,ON
}Port_PinDirectionChangeable;
/* Port pin mode from mode list for use with Port_Init() function */
typedef enum
{
	PORT_PIN_MODE_ADC,
	PORT_PIN_MODE_CAN,
	PORT_PIN_MODE_DIO,
	PORT_PIN_MODE_DIO_GPT,
	PORT_PIN_MODE_DIO_WDG,
	PORT_PIN_MODE_PWM,
        PORT_PIN_MODE_DIO_USP,
        PORT_PIN_MODE_UART,
	PORT_PIN_MODE_SPI,
        PORT_PIN_MODE_NMI,
}PortPinInitialMode;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. PORTA, PORTB, PORTC, PORTD, PORTE or PORTF
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
        5. initial value in output case     
        6. direction changeable in runtime or not     
        7. mode changeable in runtime or not   
        8. mode of each pin
 */
typedef struct 
{
    uint8 Port_Num; 
    uint8 Pin_Num; 
    Port_PinDirectionType direction;
    Port_InternalResistor resistor;
    uint8 initial_value;
    Port_PinDirectionChangeable DirectionChangeable;
    Port_PinModeChangeable ModeChangeable;
    PortPinInitialMode Mode;
}Port_PinTypee;

/* Data Structure required for initializing the Port Driver */
typedef struct Port_ConfigType
{
	Port_PinTypee PinType[PORT_CONFIGURED_PINS];
} Port_ConfigType;

/*******************************************************************************
*                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function initialize ALL ports and port pins with the configuration set pointed to by the parameter ConfigPtr.
************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr );

/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Port Pin ID numberm,Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Sets the port pin direction during runtime.
************************************************************************************/
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Nonreentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Refreshes port direction .
 shall exclude those port pins from refreshing that are configured as ‘pin direction changeable during runtime.
************************************************************************************/
void Port_RefreshPortDirection( void );

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Nonreentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo
* Return value: None
* Description: Function to Returns the version information of this module.
************************************************************************************/
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );

/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Port Pin ID number,New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the port pin mode of the referenced pin during runtime.
************************************************************************************/
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /*PORT.h*/
