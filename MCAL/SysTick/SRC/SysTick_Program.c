/*******************************************************************************
 * Filename              :   SysTick_Program.c
 * Author                :   Mohamemd Waleed Gad
 * Origin Date           :   May 11, 2023
 * Version               :   1.0.0
 * Compiler              :   GCC ARM Embedded Toolchain
 * Target                :
 * Notes                 :   None
 **
 *******************************************************************************/
/************************ SOURCE REVISION LOG *********************************
 *
 *    Date    Version   Author             Description
 *  14/10/20   1.0.0   Mohamemd Waleed   Initial Release.
 *
 *******************************************************************************/
#include <stdint.h>
#include "../../../LIB/STM32F446.h"
#include "../Include/SysTick_Interface.h"
#include "../Include/SysTick_Private.h"

void SysTick_Delay_ms(uint32_t Copy_u32Time_ms)
{
	/*Store Reload Value*/
	SysTick->SYST_RVR = (Copy_u32Time_ms * 2000);
	/*Select SysTick Source*/
	SysTick->SYST_CSR &= ~(1 << SYST_CSR_CLKSOURCE);
	/*Enable SysTick*/
	SysTick->SYST_CSR |= (1 << SYST_CSR_ENABLE);
	/*Wait Until Count Flag Set*/
	while (((SysTick->SYST_CSR) & (1 << SYST_CSR_COUNTFLAG)) == 0)	;
	/*disable SysTick*/
	SysTick->SYST_CSR &= ~(1 << SYST_CSR_ENABLE);
}
void SysTick_Delay_us(uint32_t Copy_u32Time_us)
{
	/*Store Reload Value*/
	SysTick->SYST_RVR = (Copy_u32Time_us);
	/*Select SysTick Source*/
	SysTick->SYST_CSR &= ~(1 << SYST_CSR_CLKSOURCE);
	/*Enable SysTick*/
	SysTick->SYST_CSR |= (1 << SYST_CSR_ENABLE);
	/*Wait Until Count Flag Set*/
	while (((SysTick->SYST_CSR) & (1 << SYST_CSR_COUNTFLAG)) == 0)	;
	/*disable SysTick*/
	SysTick->SYST_CSR &= ~(1 << SYST_CSR_ENABLE);
}

