 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed Salah
 ******************************************************************************/
#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Port_PinTypee * Port_ChannelsPtr = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;
uint8 index=0;
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
void Port_Init( const Port_ConfigType* ConfigPtr ){
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
		     PORT_E_PARAM_POINTER);
	}
	else
        {       
          /*Do Nothing*/
        }
#endif
	

    Port_Status= PORT_INITIALIZED;
    Port_ChannelsPtr = ConfigPtr->PinType;
    for(index=ZERO; index<PORT_CONFIGURED_PINS;index++){
      
      volatile uint32 * PortReg_Ptr = NULL_PTR; /*Pointer Point to Base Adress*/
      volatile uint32 delay = 0;
      switch(Port_ChannelsPtr[index].Port_Num){
      
      case PORT_A:
        PortReg_Ptr=(volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
        break;
      case PORT_B:
        PortReg_Ptr=(volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
        break;
      case PORT_C:
        PortReg_Ptr=(volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
        break;
      case PORT_D:
        PortReg_Ptr=(volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
        break;
      case PORT_E:
        PortReg_Ptr=(volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
        break;
      case PORT_F:
        PortReg_Ptr=(volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
        break;
        
      
      }
          /* Enable clock for PORT and allow time for clock to start*/
       SYSCTL_REGCGC2_REG |= (1<<Port_ChannelsPtr[index].Port_Num);
       delay = SYSCTL_REGCGC2_REG;
       if( ((Port_ChannelsPtr[index].Port_Num == 3) && (Port_ChannelsPtr[index].Pin_Num == 7)) || ((Port_ChannelsPtr[index].Port_Num == 5) && (Port_ChannelsPtr[index].Pin_Num == 0)) ) /* PD7 or PF0 */
    {
        *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_LOCK_REG_OFFSET) = UNLOCK_VALUE;                     /* Unlock the GPIOCR register */   
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_COMMIT_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
    }
    else if( (Port_ChannelsPtr[index].Port_Num == 2) && (Port_ChannelsPtr[index].Pin_Num <= 3) ) /* PC0 to PC3 */
    {
        /* Do Nothing ...  this is the JTAG pins */
    }
    else
    {
        /* Do Nothing ... No need to unlock the commit register for this pin */
    } 
         CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num); /*Disable Analog Functionality*/ 
         SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num); /*Enable Digital Functionality*/
         SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num); /*Enable Alternate Functionality*/
    
         switch(Port_ChannelsPtr[index].Mode){
         
         case PORT_PIN_MODE_ADC:
           
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num); /* Disable Alternative functionality*/
           *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) &= ~(GPIO_ADC_MASK << ( Port_ChannelsPtr[index].Pin_Num* 4));/* Clear the PMCx bits for this pin */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num); /*Enable Analog*/
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num); /*Disable Digital*/
           break;
         
         case PORT_PIN_MODE_CAN:
           if((Port_ChannelsPtr[index].Port_Num == PORT_F) && (Port_ChannelsPtr[index].Pin_Num == PORT_PIN0)||((Port_ChannelsPtr[index].Port_Num == PORT_F) && (Port_ChannelsPtr[index].Pin_Num == PORT_PIN3))){
             
             *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (CAN0_MASK_PF0_PF3 << (Port_ChannelsPtr[index].Pin_Num * 4));
           }else{
             
             *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (CAN0_MASK << (Port_ChannelsPtr[index].Pin_Num * 4));
             
           }
           break;
         
         case PORT_PIN_MODE_DIO:
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num); /*Enable Alternate Functionality*/
              *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) &= ~(GPIO_ADC_MASK << ( Port_ChannelsPtr[index].Pin_Num* 4));  
         break;
         case PORT_PIN_MODE_DIO_GPT:
              *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (GPT_MASK << (Port_ChannelsPtr[index].Pin_Num * 4));
           break;
           
         case PORT_PIN_MODE_DIO_WDG:
              *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (WDG_MASK << (Port_ChannelsPtr[index].Pin_Num * 4));  
           break;
         case PORT_PIN_MODE_PWM:
              *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (PWM0_MASK << (Port_ChannelsPtr[index].Pin_Num * 4));
           break;
         
         case PORT_PIN_MODE_NMI :
              *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (NMI_MASK << (Port_ChannelsPtr[index].Pin_Num* 4));   
           break;         
         case PORT_PIN_MODE_DIO_USP :
              *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (USB_MASK << (Port_ChannelsPtr[index].Pin_Num* 4));     /* SET the PMCx bits for this pin */
           break;  
           case PORT_PIN_MODE_UART:
        if((Port_ChannelsPtr[index].Port_Num ==PORT_C && Port_ChannelsPtr[index].Pin_Num == PORT_PIN4) || (Port_ChannelsPtr[index].Port_Num ==PORT_C && Port_ChannelsPtr[index].Pin_Num == PORT_PIN5))
        {
      *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (UART0_MASK << ( Port_ChannelsPtr[index].Pin_Num* 4));      /* SET the PMCx bits for this pin */
        }
        else
      {
        *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (UART1_MASK << ( Port_ChannelsPtr[index].Pin_Num* 4));      /* SET the PMCx bits for this pin */
      }
      break; 
         }     
         
         switch(Port_ChannelsPtr[index].direction){
         case INPUT:
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_DIR_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num);
           if(Port_ChannelsPtr[index].initial_value == STD_HIGH)
        {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_DATA_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_DATA_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
           break;
           
         case OUTPUT:
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_DIR_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        
        if(Port_ChannelsPtr[index].resistor == PULL_UP)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
        }
        else if(Port_ChannelsPtr[index].resistor == PULL_DOWN)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
        }
           break;
            
         }  
         
    }

}

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
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction ){

  volatile uint32 * PortReg_Ptr = NULL_PTR; /* point to the required Port Registers base address */
 volatile boolean error=FALSE;
 #if (PORT_DEV_ERROR_DETECT == STD_ON)
   	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_STD, PORT_E_UNINIT);
		error = TRUE;
	}
else
	{
		/* No Action Required */
	}

if( Port_ChannelsPtr[Pin].DirectionChangeable == OFF){
          /* Check if the direction is changable or not*/
          Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		     PORT_SET_PIN_DIRECTION_STD  , PORT_E_DIRECTION_UNCHANGEABLE );
        }
          else 
          {
            /* No Action Required */
          }
          
#endif
switch(Port_ChannelsPtr[Pin].Port_Num)
    {
        case  0: PortReg_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  1: PortReg_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  2: PortReg_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  3: PortReg_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  4: PortReg_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  5: PortReg_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }
     if(Direction == OUTPUT)
    {
	SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_DIR_REG_OFFSET) , Port_ChannelsPtr[Pin].Pin_Num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        
        if(Port_ChannelsPtr[Pin].initial_value == STD_HIGH)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_DATA_REG_OFFSET) , Port_ChannelsPtr[Pin].Pin_Num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_DATA_REG_OFFSET) , Port_ChannelsPtr[Pin].Pin_Num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
    }
     else if(Direction == INPUT)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_DIR_REG_OFFSET) , Port_ChannelsPtr[Pin].Pin_Num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        
        if(Port_ChannelsPtr[Pin].resistor == PULL_UP)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_ChannelsPtr[Pin].Pin_Num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
        }
        else if(Port_ChannelsPtr[Pin].resistor == PULL_DOWN)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_ChannelsPtr[Pin].Pin_Num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_ChannelsPtr[Pin].Pin_Num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_ChannelsPtr[Pin].Pin_Num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
        }
   

    } else{
    }
     }
      
                                

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
void Port_RefreshPortDirection( void ){ 
  
  volatile boolean error=FALSE;
   
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
   	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_REFRESH_PORT_DIRECTION_STD, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif


        
          
           for(index=ZERO; index<PORT_CONFIGURED_PINS;index++){
      if( Port_ChannelsPtr[index].DirectionChangeable == OFF){
          /* Check if the direction is changable or not*/
          Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		     PORT_SET_PIN_DIRECTION_STD  , PORT_E_DIRECTION_UNCHANGEABLE );
        }
          else 
          {
            /* No Action Required */
          }
      volatile uint32 * PortReg_Ptr = NULL_PTR; /*Pointer Point to Base Adress*/
      volatile uint32 delay = 0;
      switch((Port_ChannelsPtr[index].Port_Num)){
      
      case PORT_A:
        PortReg_Ptr=(volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
        break;
      case PORT_B:
        PortReg_Ptr=(volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
        break;
      case PORT_C:
        PortReg_Ptr=(volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
        break;
      case PORT_D:
        PortReg_Ptr=(volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
        break;
      case PORT_E:
        PortReg_Ptr=(volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
        break;
      case PORT_F:
        PortReg_Ptr=(volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
        break;
        
      
      }
          /* Enable clock for PORT and allow time for clock to start*/
       SYSCTL_REGCGC2_REG |= (1<<Port_ChannelsPtr[index].Port_Num);
       delay = SYSCTL_REGCGC2_REG;
       if( ((Port_ChannelsPtr[index].Port_Num == 3) && (Port_ChannelsPtr[index].Pin_Num == 7)) || ((Port_ChannelsPtr[index].Port_Num == 5) && (Port_ChannelsPtr[index].Pin_Num == 0)) ) /* PD7 or PF0 */
    {
        *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_LOCK_REG_OFFSET) = UNLOCK_VALUE;                     /* Unlock the GPIOCR register */   
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_COMMIT_REG_OFFSET) , Port_ChannelsPtr->Pin_Num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
    }
    else if( (Port_ChannelsPtr[index].Port_Num == 2) && (Port_ChannelsPtr[index].Pin_Num <= 3) ) /* PC0 to PC3 */
    {
        /* Do Nothing ...  this is the JTAG pins */
    }
    else
    {
        /* Do Nothing ... No need to unlock the commit register for this pin */
    } 
 
    if(Port_ChannelsPtr[index].DirectionChangeable==ON){
      if(Port_ChannelsPtr[index].direction == OUTPUT)
				{
					/* Set the corresponding bit in the GPIODIR register to configure it as output pin */
					SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_DIR_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num);
				}
				else if(Port_ChannelsPtr[index].direction == INPUT)
				{
					/* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
					CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_DIR_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num);
				}
				else
				{	/* Do Nothing */  }
    
    
    
    
    
    
    
    }else{
      
      /* Do Nothing */ 
        }
      
    
    }
}

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
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
	#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* check if the input configuration pointer is not a NULL_PTR */
		if(versioninfo == NULL_PTR)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
		}
		else
		{	/* Do Nothing */	}

		/* Check if the Driver is initialized before using this function */
		if(Port_Status == PORT_NOT_INITIALIZED)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_UNINIT);
		}
		else
		{	/* Do Nothing */	}
	#endif

		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
}
#endif


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
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode ){
#if (PORT_DEV_ERROR_DETECT == STD_ON)
		/* Check if the Driver is initialized before using this function */
		if(Port_Status == PORT_NOT_INITIALIZED)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_STD, PORT_E_UNINIT);
		}
		else
		{	/* Do Nothing */	}

		/* check if incorrect Port Pin ID passed */
		if(Pin >= PORT_CONFIGURED_PINS)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_STD, PORT_E_PARAM_PIN);
		}
		else
		{	/* Do Nothing */	}

		/* check if the Port Pin Mode passed not valid */
		if(Mode > PORT_PIN_MODE_NMI)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_STD, PORT_E_PARAM_INVALID_MODE);
		}
		else
		{	/* Do Nothing */	}

		/* check if the API called when the mode is unchangeable */
		if(Port_ChannelsPtr[Pin].ModeChangeable == NOT_Changeable)
		{
			Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_STD, PORT_E_MODE_UNCHANGEABLE);
		}
		else
		{	/* Do Nothing */	}
	#endif

volatile uint32 * PortReg_Ptr = NULL_PTR; /*Pointer Point to Base Adress*/
 switch(Port_ChannelsPtr[Pin].Port_Num)
    {
        case  0: PortReg_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  1: PortReg_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  2: PortReg_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  3: PortReg_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  4: PortReg_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  5: PortReg_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }
         switch(Mode){
         
         case PORT_PIN_MODE_ADC:
           
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num); /* Disable Alternative functionality*/
           *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) &= ~(GPIO_ADC_MASK << ( Port_ChannelsPtr[index].Pin_Num* 4));/* Clear the PMCx bits for this pin */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num); /*Enable Analog*/
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num); /*Disable Digital*/
           break;
         
         case PORT_PIN_MODE_CAN:
           if((Port_ChannelsPtr[index].Port_Num == PORT_F) && (Port_ChannelsPtr[index].Pin_Num == PORT_PIN0)||((Port_ChannelsPtr[index].Port_Num == PORT_F) && (Port_ChannelsPtr[index].Pin_Num == PORT_PIN3))){
             
             *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (CAN0_MASK_PF0_PF3 << (Port_ChannelsPtr[index].Pin_Num * 4));
           }else{
             
             *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (CAN0_MASK << (Port_ChannelsPtr[index].Pin_Num * 4));
             
           }
           break;
         
         case PORT_PIN_MODE_DIO:
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_ChannelsPtr[index].Pin_Num); /*Enable Alternate Functionality*/
              *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) &= ~(GPIO_ADC_MASK << ( Port_ChannelsPtr[index].Pin_Num* 4));  
         break;
         case PORT_PIN_MODE_DIO_GPT:
              *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (GPT_MASK << (Port_ChannelsPtr[index].Pin_Num * 4));
           break;
           
         case PORT_PIN_MODE_DIO_WDG:
              *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (WDG_MASK << (Port_ChannelsPtr[index].Pin_Num * 4));  
           break;
         case PORT_PIN_MODE_PWM:
              *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (PWM0_MASK << (Port_ChannelsPtr[index].Pin_Num * 4));
           break;
         
         case PORT_PIN_MODE_NMI :
              *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (NMI_MASK << (Port_ChannelsPtr[index].Pin_Num* 4));   
           break;         
         case PORT_PIN_MODE_DIO_USP :
              *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (USB_MASK << (Port_ChannelsPtr[index].Pin_Num* 4));     /* SET the PMCx bits for this pin */
           break;  
           case PORT_PIN_MODE_UART:
        if((Port_ChannelsPtr[index].Port_Num ==PORT_C && Port_ChannelsPtr[index].Pin_Num == PORT_PIN4) || (Port_ChannelsPtr[index].Port_Num ==PORT_C && Port_ChannelsPtr[index].Pin_Num == PORT_PIN5))
        {
      *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (UART0_MASK << ( Port_ChannelsPtr[index].Pin_Num* 4));      /* SET the PMCx bits for this pin */
        }
        else
      {
        *(volatile uint32 *)((volatile uint8 *)PortReg_Ptr + PORT_CTL_REG_OFFSET) |= (UART1_MASK << ( Port_ChannelsPtr[index].Pin_Num* 4));      /* SET the PMCx bits for this pin */
      }
      break; 
         }     







}
