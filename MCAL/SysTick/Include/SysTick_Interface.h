/*******************************************************************************
 * Filename              :   SysTick_Interface.h
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
#ifndef SYSTICK_INCLUDE_SYSTICK_INTERFACE_H_
#define SYSTICK_INCLUDE_SYSTICK_INTERFACE_H_

void SysTick_Delay_ms(uint32_t Copy_u32Time_ms);
void SysTick_Delay_us(uint32_t Copy_u32Time_us);


#endif /* SYSTICK_INCLUDE_SYSTICK_INTERFACE_H_ */
