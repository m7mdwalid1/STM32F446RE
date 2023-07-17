/*******************************************************************************
 * Filename              :   SCB_Program.c
 * Author                :   Mohamemd Waleed Gad
 * Origin Date           :   Jul 17, 2023
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
#include "../Include/SCB_Interface.h"
#include "../Include/SCB_Private.h"
/*==============================================================================================================================================
 *@fn SCB_VoidSetPriorityGroup
 *@brief Setting Priority Group
 *@paramter[in] Local_u8PriorityGroup: Priority Group
 *@retval void
 *==============================================================================================================================================*/
void SCB_VoidSetPriorityGroup(PRIGROUP_t Local_u8PriorityGroup)
{
    /*Setting Priority Group*/
    SCB->AIRCR = Local_u8PriorityGroup;
}
