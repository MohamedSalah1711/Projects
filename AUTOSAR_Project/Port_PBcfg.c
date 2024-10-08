/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION           (1U)
#define PORT_PBCFG_SW_MINOR_VERSION           (0U)
#define PORT_PBCFG_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION   (3U)

#include "Port.h"

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Port_Init Function */
const Port_ConfigType Port_PinConfig=
{ 
    PORT_A, PORT_PIN0, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_A, PORT_PIN1, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_A, PORT_PIN2, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_A, PORT_PIN3, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_A, PORT_PIN4, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_A, PORT_PIN5, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_A, PORT_PIN6, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_A, PORT_PIN7, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    
    PORT_B, PORT_PIN0, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_B, PORT_PIN1, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_B, PORT_PIN2, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_B, PORT_PIN3, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_B, PORT_PIN4, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_B, PORT_PIN5, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_B, PORT_PIN6, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_B, PORT_PIN7, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,    
      
    PORT_C, PORT_PIN0, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_C, PORT_PIN1, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_C, PORT_PIN2, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_C, PORT_PIN3, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_C, PORT_PIN4, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_C, PORT_PIN5, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_C, PORT_PIN6, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_C, PORT_PIN7, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,    

    PORT_E, PORT_PIN0, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_E, PORT_PIN1, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_E, PORT_PIN2, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_E, PORT_PIN3, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_E, PORT_PIN4, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_E, PORT_PIN5, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,

    PORT_F, PORT_PIN0, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_F, PORT_PIN1, OUTPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO, /*LED*/
    PORT_F, PORT_PIN2, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_F, PORT_PIN3, INPUT, NO_PULLUP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO,
    PORT_F, PORT_PIN4, INPUT, PULL_UP, STD_LOW, ON, Changeable,PORT_PIN_MODE_DIO, /*SW*/
    
    
};