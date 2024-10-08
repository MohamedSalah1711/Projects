#ifndef PORT_REGS_H
#define PORT_REGS_H

#include "Std_Types.h"

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C

/*Mask for diffreint mode*/
#define CAN0_MASK_PF0_PF3 0x00000003
#define CAN0_MASK 0x00000008 
#define GPIO_ADC_MASK 0x0000000F
#define GPT_MASK 0x00000007 
#define WDG_MASK 0x00000007 
#define PWM0_MASK 0x00000004
#define PWM1_MASK 0x00000005
#define NMI_MASK 0x00000008 
#define USB_MASK 0x00000008 
#define UART0_MASK 0x00000002 
#define UART1_MASK 0x00000001 
/* RCC Registers */
#define SYSCTL_REGCGC2_REG        		(*((volatile uint32 *)0x400FE108))

#endif /* PORT_REGS_H */