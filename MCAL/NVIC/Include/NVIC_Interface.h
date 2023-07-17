/*******************************************************************************
 * Filename              :   NVIC_Interface.h
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
#ifndef NVIC_INCLUDE_NVIC_INTERFACE_H_
#define NVIC_INCLUDE_NVIC_INTERFACE_H_

typedef enum
{
    WWDG_IRQNumber = 0,
    PVD_IRQNumber,
    TAMP_STAMP_IRQNumber,
    RTC_WKUP_IRQNumber,
    FLASH_IRQNumber,
    RCC_IRQNumber,
    EXTI0_IRQNumber,
    EXTI1_IRQNumber,
    EXTI2_IRQNumber,
    EXTI3_IRQNumber,
    EXTI4_IRQNumber,
    DMA1_Stream0_IRQNumber,
    DMA1_Stream1_IRQNumber,
    DMA1_Stream2_IRQNumber,
    DMA1_Stream3_IRQNumber,
    DMA1_Stream4_IRQNumber,
    DMA1_Stream5_IRQNumber,
    DMA1_Stream6_IRQNumber,
    ADC_IRQNumber,
    CAN1_TX_IRQNumber,
    CAN1_RX0_IRQNumber,
    CAN1_RX1_IRQNumber,
    CAN1_SCE_IRQNumber,
    EXTI9_5_IRQNumber,
    TIM1_BRK_TIM9_IRQNumber,
    TIM1_UP_TIM10_IRQNumber,
    TIM1_TRG_COM_TIM11_IRQNumber,
    TIM1_CC_IRQNumber,
    TIM2_IRQNumber,
    TIM3_IRQNumber,
    TIM4_IRQNumber,
    I2C1_EV_IRQNumber,
    I2C1_ER_IRQNumber,
    I2C2_EV_IRQNumber,
    I2C2_ER_IRQNumber,
    SPI1_IRQNumber,
    SPI2_IRQNumber,
    USART1_IRQNumber,
    USART2_IRQNumber,
    USART3_IRQNumber,
    EXTI15_10_IRQNumber,
    RTC_Alarm_IRQNumber,
    OTG_FS_WKUP_IRQNumber,
    TIM8_BRK_TIM12_IRQNumber,
    TIM8_UP_TIM13_IRQNumber,
    TIM8_TRG_COM_TIM14_IRQNumber,
    TIM8_CC_IRQNumber,
    DMA1_Stream7_IRQNumber,
    FMC_IRQNumber,
    SDIO_IRQNumber,
    TIM5_IRQNumber,
    SPI3_IRQNumber,
    UART4_IRQNumber,
    UART5_IRQNumber,
    TIM6_DAC_IRQNumber,
    TIM7_IRQNumber,
    DMA2_Stream0_IRQNumber,
    DMA2_Stream1_IRQNumber,
    DMA2_Stream2_IRQNumber,
    DMA2_Stream3_IRQNumber,
    DMA2_Stream4_IRQNumber,
    CAN2_TX_IRQNumber = 63,
    CAN2_RX0_IRQNumber,
    CAN2_RX1_IRQNumber,
    CAN2_SCE_IRQNumber,
    OTG_FS_IRQNumber,
    DMA2_Stream5_IRQNumber,
    DMA2_Stream6_IRQNumber,
    DMA2_Stream7_IRQNumber,
    USART6_IRQNumber,
    I2C3_EV_IRQNumber,
    I2C3_ER_IRQNumber,
    OTG_HS_EP1_OUT_IRQNumber,
    OTG_HS_EP1_IN_IRQNumber,
    OTG_HS_WKUP_IRQNumber,
    OTG_HS_IRQNumber,
    DCMI_IRQNumber,
    FPU_IRQNumber = 81,
    SPI4_IRQNumber = 84,
    SAI1_IRQNumber = 87,
    SAI2_IRQNumber = 91,
    QUADSPI_IRQNumber,
    HDMI_IRQNumber,
    SPDIF_RX_IRQNumber,
    FMPI2C1_EV_IRQNumber,
    FMPI2C1_ER_IRQNumber,
} IRQ_Number_t;
/*==============================================================================================================================================
 *@fn NVIC_voidEnableInterrupt
 *@brief Enabling the interrupt
 *@paramter[in] uint8_t IRQ_Number : the number of the interrupt
 *@retval void
 *==============================================================================================================================================*/
void NVIC_voidEnableInterrupt(IRQ_Number_t IRQ_Number);

/*==============================================================================================================================================
 *@fn NVIC_voidDisableInterrupt
 *@brief Disabling the interrupt
 *@paramter[in] uint8_t IRQ_Number : the number of the interrupt
 *@retval void
 *==============================================================================================================================================*/
void NVIC_voidDisableInterrupt(IRQ_Number_t IRQ_Number);
/*==============================================================================================================================================
 *@fn NVIC_voidSetBendingFlag
 *@brief Setting the bending flag of the interrupt
 *@paramter[in] uint8_t IRQ_Number : the number of the interrupt
 *@retval void
 *==============================================================================================================================================*/

void NVIC_voidSetBendingFlag(IRQ_Number_t IRQ_Number);
/*==============================================================================================================================================
 *@fn NVIC_voidClearBendingFlag
 *@brief Clearing the bending flag of the interrupt
 *@paramter[in] uint8_t IRQ_Number : the number of the interrupt
 *@retval void
 *==============================================================================================================================================*/
void NVIC_voidClearBendingFlag(IRQ_Number_t IRQ_Number);
/*==============================================================================================================================================
 *@fn NVIC_u8GetActiveFlag
 *@brief Getting the state of the interrupt
 *@paramter[in] uint8_t IRQ_Number : the number of the interrupt
 *@retval uint8_t : the state of the interrupt
 *==============================================================================================================================================*/
uint8_t NVIC_u8GetActiveFlag(IRQ_Number_t IRQ_Number);
/*==============================================================================================================================================
 *@fn NVIC_voidSetPriority
 *@brief Setting the priority of the interrupt
 *@paramter[in] uint8_t IRQ_Number : the number of the interrupt
 *@paramter[in] uint8_t Copy_u8Priority : the priority of the interrupt
 *@retval void
 *==============================================================================================================================================*/
void NVIC_voidSetPriority(IRQ_Number_t IRQ_Number, uint8_t Copy_u8Priority);
#endif /* NVIC_INCLUDE_NVIC_INTERFACE_H_ */
