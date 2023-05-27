/*******************************************************************************
 * Filename              :   GPIO_Program.c
 * Author                :   Mohamemd Waleed Gad
 * Origin Date           :   May 5, 2023
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
#include "../../../LIB/ErrorType.h"
#include "../../../LIB/STM32F446.h"
#include "../Include/GPIO_Interface.h"
#include "../Include/GPIO_Private.h"

static GPIO_RegDef_t *GPIO_PORT[GPIO_PREPHIRAL_NUM] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};
/*==============================================================================================================================================
 * Function Definitions
 *==============================================================================================================================================*/
/***********************************************************
 *@fn GPIO_u8PinInit
 *@brief the function initializes the GPIO pin according to the input paramters
 *@paramter[in] PinConfig : initializaton values of the pin
 *@retval ErrorStatus
 */
uint8_t GPIO_u8PinInit(const Pin_Config_t *PinConfig)
{
	uint8_t Local_u8ErrorStatus = OK;
	if (PinConfig != NULL)
	{
		if (((PinConfig->Port) <= PORTH) && ((PinConfig->PinNum) <= PIN15))
		{
			/*select GPIO mode: INPUT , OUTPUT , ANALOG , ALT FUNC */
			(GPIO_PORT[PinConfig->Port]->MODER) &= ~(TWO_BIT_MASK << ((PinConfig->PinNum) * TWO_PIN_ACCESS));
			(GPIO_PORT[PinConfig->Port]->MODER) |= ((PinConfig->Mode) << ((PinConfig->PinNum) * TWO_PIN_ACCESS));

			/*Select Gpio Pull state : PU , PD , NO PULL*/
			(GPIO_PORT[PinConfig->Port]->PUPDR) &= ~(TWO_BIT_MASK << ((PinConfig->PinNum) * TWO_PIN_ACCESS));
			(GPIO_PORT[PinConfig->Port]->PUPDR) |= ((PinConfig->PullType) << ((PinConfig->PinNum) * TWO_PIN_ACCESS));

			/*Select Output type & output speed in case of general purpose output or alternate function */
			if ((PinConfig->Mode) == Output || (PinConfig->Mode) == Alternate_func)
			{
				(GPIO_PORT[PinConfig->Port]->OTYPER) &= ~(ONE_BIT_MASK << (PinConfig->PinNum));
				(GPIO_PORT[PinConfig->Port]->OTYPER) |= ((PinConfig->PullType) << (PinConfig->PinNum));

				(GPIO_PORT[PinConfig->Port]->OSPEEDR) &= ~(TWO_BIT_MASK << (PinConfig->PinNum) * TWO_PIN_ACCESS);
				(GPIO_PORT[PinConfig->Port]->OSPEEDR) |= ((PinConfig->PullType) << (PinConfig->PinNum) * TWO_PIN_ACCESS);
				if ((PinConfig->Mode) == Alternate_func)
				{
					if ((PinConfig->PinNum) <= PIN7)
					{
						(GPIO_PORT[PinConfig->Port]->AFRL[0]) &= ~(FOUR_BIT_MASK << (PinConfig->PinNum) * FOUR_PIN_ACCESS);
						(GPIO_PORT[PinConfig->Port]->AFRL[0]) |= ((PinConfig->ALtFunc) << (PinConfig->PinNum) * FOUR_PIN_ACCESS);
					}
					else if ((PinConfig->PinNum) > PIN7)
					{
						(GPIO_PORT[PinConfig->Port]->AFRL[1]) &= ~(FOUR_BIT_MASK << (PinConfig->PinNum) * FOUR_PIN_ACCESS);
						(GPIO_PORT[PinConfig->Port]->AFRL[1]) |= ((PinConfig->ALtFunc) << (PinConfig->PinNum) * FOUR_PIN_ACCESS);
					}
				}
			}
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else
	{
		Local_u8ErrorStatus = NULL_PTR_ERR;
	}
	return Local_u8ErrorStatus;
}
/***********************************************************
 *@fn GPIO_u8SetPinValue
 *@brief the function output a certain value on an output pin
 *@paramter[in] Port : the port number , get options @Port_t enum
 *@paramter[in] PinNum : the pin number , get options @PinNum enum
 *@paramter[in] PinVal : the output value , get options @PinVal enum
 *@retval ErrorStatus
 */
uint8_t GPIO_u8SetPinValue(PORT_t Port, Pin_t PinNum, PinVal_t PinVal)
{
	uint8_t Local_u8ErrorStatus = OK;
	if ((Port <= PORTH) && (PinNum <= PIN15))
	{
		if (PinVal == PinLow)
		{
			GPIO_PORT[Port]->ODR &= ~(ONE_BIT_MASK << PinNum);
		}
		else if (PinVal == PinHigh)
		{
			GPIO_PORT[Port]->ODR |= (ONE_BIT_MASK << PinNum);
		}
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;
}
/*==============================================================================================================================================
 *@fn  GPIO_u8TogglePinValue
 *@brief  the function toggles the value of a certain pin
 *@paramter[in] Port : the port number , get options @Port_t enum
 *@paramter[in] PinNum : the pin number , get options @PinNum enum
 *@retval ErrorStatus
 *==============================================================================================================================================*/
uint8_t GPIO_u8TogglePinValue(PORT_t Port, Pin_t PinNum)
{
	uint8_t Local_u8ErrorStatus = OK;
	if ((Port <= PORTH) && (PinNum <= PIN15))
	{
		GPIO_PORT[Port]->ODR ^= (ONE_BIT_MASK << PinNum);
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;
}
/*==============================================================================================================================================
 *@fn  GPIO_u8ReadPinValue
 *@brief  the function reads the value of a certain pin
 *@paramter[in] Port : the port number , get options @Port_t enum
 *@paramter[in] PinNum : the pin number , get options @PinNum enum
 *@paramter[out] PinVal : the output value , get options @PinVal enum
 *@retval ErrorStatus
 *==============================================================================================================================================*/
uint8_t GPIO_u8ReadPinValue(PORT_t Port, Pin_t PinNum, PinVal_t *PinVal)
{
	uint8_t Local_u8ErrorStatus = OK;
	if ((Port <= PORTH) && (PinNum <= PIN15))
	{
		*PinVal = ((GPIO_PORT[Port]->IDR) >> PinNum & (ONE_BIT_MASK));
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;
}
