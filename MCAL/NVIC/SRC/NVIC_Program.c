/*******************************************************************************
 * Filename              :   NVIC_Program.c
 * Author                :   Mohamemd Waleed Gad
 * Origin Date           :   Jul 7, 2023
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
#include "../../../LIB/ErrorType.h"
#include "../Include/NVIC_Interface.h"
#include "../Include/NVIC_Private.h"
/*==============================================================================================================================================
 *@fn NVIC_voidEnableInterrupt
 *@brief Enabling the interrupt
 *@paramter[in] uint8_t IRQ_Number : the number of the interrupt
 *@retval void
 *==============================================================================================================================================*/
void NVIC_voidEnableInterrupt(IRQ_Number_t IRQ_Number)
{
    uint8_t RegNum = IRQ_Number / 32;
    uint8_t BitNum = IRQ_Number % 32;
    NVIC->ISER[RegNum] = (1 << BitNum);
}

/*==============================================================================================================================================
 *@fn NVIC_voidDisableInterrupt
 *@brief Disabling the interrupt
 *@paramter[in] uint8_t IRQ_Number : the number of the interrupt
 *@retval void
 *==============================================================================================================================================*/
void NVIC_voidDisableInterrupt(IRQ_Number_t IRQ_Number)
{
    uint8_t RegNum = IRQ_Number / 32;
    uint8_t BitNum = IRQ_Number % 32;
    NVIC->ICER[RegNum] = (1 << BitNum);
}
/*==============================================================================================================================================
 *@fn NVIC_voidSetBendingFlag
 *@brief Disabling the interrupt
 *@paramter[in] uint8_t IRQ_Number : the number of the interrupt
 *@retval void
 *==============================================================================================================================================*/

void NVIC_voidSetBendingFlag(IRQ_Number_t IRQ_Number)
{
    uint8_t RegNum = IRQ_Number / 32;
    uint8_t BitNum = IRQ_Number % 32;
    NVIC->ISPR[RegNum] = (1 << BitNum);
}
/*==============================================================================================================================================
 *@fn NVIC_voidClearBendingFlag
 *@brief Disabling the interrupt
 *@paramter[in] uint8_t IRQ_Number : the number of the interrupt
 *@retval void
 *==============================================================================================================================================*/
void NVIC_voidClearBendingFlag(IRQ_Number_t IRQ_Number)
{
    uint8_t RegNum = IRQ_Number / 32;
    uint8_t BitNum = IRQ_Number % 32;
    NVIC->ICPR[RegNum] = (1 << BitNum);
}
/*==============================================================================================================================================
 *@fn NVIC_u8GetActiveFlag
 *@brief Disabling the interrupt
 *@paramter[in] uint8_t IRQ_Number : the number of the interrupt
 *@retval uint8_t : the state of the interrupt
 *==============================================================================================================================================*/

uint8_t NVIC_u8GetActiveFlag(IRQ_Number_t IRQ_Number)
{
    uint8_t RegNum = IRQ_Number / 32;
    uint8_t BitNum = IRQ_Number % 32;
    return ((NVIC->IABR[RegNum] >> BitNum) & 1);
}

/*==============================================================================================================================================
 *@fn NVIC_voidSetPriority
 *@brief Setting the priority of the interrupt
 *@paramter[in] uint8_t IRQ_Number : the number of the interrupt
 *@paramter[in] uint8_t Copy_u8Priority : the priority of the interrupt
 *@retval void
 *==============================================================================================================================================*/
void NVIC_voidSetPriority(IRQ_Number_t IRQ_Number, uint8_t Copy_u8Priority)
{
    NVIC->IPR[IRQ_Number] = Copy_u8Priority;
}
