/*******************************************************************************
 * Filename              :   GPIO_Interface.h
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
#ifndef GPIO_GPIO_INTERFACE_H_
#define GPIO_GPIO_INTERFACE_H_

typedef enum
{
	PORTA=0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
	PORTH
}PORT_t;
typedef enum
{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}Pin_t;

typedef enum
{
	Input=0,
	Output,
	Alternate_func,
	Analog
}Mode_t;
typedef enum
{
	LOW=0,
	MEDIUM,
	FAST,
	HIGH
}OutputSpeed_t;
typedef enum
{
	PUSH_PULL=0,
	OPEN_DRAIN
}Output_Type_t;
typedef enum
{
	AF0=0,
	AF1,
	AF2,
	AF3 ,
	AF4 ,
	AF5 ,
	AF6 ,
	AF7 ,
	AF8 ,
	AF9 ,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}Alt_Func_t;

typedef enum
{
	NOPULL=0,
	PULLUP,
	PULLDOWN
}PullUpDown_t;

typedef enum
{
	PinLow,
	PinHigh
}PinVal_t;

typedef struct
{
	PORT_t Port;
	Pin_t PinNum;
	Mode_t Mode;
	OutputSpeed_t Speed;
	Output_Type_t OutputType;
	PullUpDown_t PullType;
	Alt_Func_t ALtFunc;
}Pin_Config_t;
/*==============================================================================================================================================
 * Function Declarations
 *==============================================================================================================================================*/
/***********************************************************
 *@fn GPIO_u8PinInit
 *@brief the function initializes the GPIO pin according to the input paramters
 *@paramter[in] PinConfig : initializaton values of the pin
 *@retval ErrorStatus
 */
uint8_t GPIO_u8PinInit(const Pin_Config_t * PinConfig);
/***********************************************************
 *@fn GPIO_u8SetPinValue
 *@brief the function output a certain value on an output pin
 *@paramter[in] Port : the port number , get options @Port_t enum
 *@paramter[in] PinNum : the pin number , get options @PinNum enum
 *@paramter[in] PinVal : the output value , get options @PinVal enum
 *@retval ErrorStatus
 */
uint8_t GPIO_u8SetPinValue(PORT_t Port ,Pin_t PinNum,PinVal_t PinVal);
/*==============================================================================================================================================
 *@fn  GPIO_u8TogglePinValue
 *@brief  the function toggles the value of a certain pin
 *@paramter[in] Port : the port number , get options @Port_t enum
 *@paramter[in] PinNum : the pin number , get options @PinNum enum
 *@retval ErrorStatus
*==============================================================================================================================================*/
uint8_t GPIO_u8TogglePinValue(PORT_t Port ,Pin_t PinNum);
/*==============================================================================================================================================
 *@fn  GPIO_u8ReadPinValue
 *@brief  the function reads the value of a certain pin
 *@paramter[in] Port : the port number , get options @Port_t enum
 *@paramter[in] PinNum : the pin number , get options @PinNum enum
 *@paramter[out] PinVal : the output value , get options @PinVal enum
 *@retval ErrorStatus
*==============================================================================================================================================*/
uint8_t GPIO_u8ReadPinValue(PORT_t Port ,Pin_t PinNum,PinVal_t* PinVal);






#endif /* GPIO_GPIO_INTERFACE_H_ */
