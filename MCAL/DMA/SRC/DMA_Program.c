/*******************************************************************************
 * Filename              :   DMA_Program.c
 * Author                :   Mohamemd Waleed Gad
 * Origin Date           :   Aug 6, 2023
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
#include "../Include/DMA_Interface.h"
#include "../Include/DMA_Private.h"
/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION
 *==============================================================================================================================================*/
/* Array Of Pointers To Functions To Hold The Address Of The Call Back Function */
static void (*DMA1_PTR[Streams_Num][Interrupts_Num])(void) = {NULL};
static void (*DMA2_PTR[Streams_Num][Interrupts_Num])(void) = {NULL};
/* Array Of Pointers To DMA Registers */
static DMA_Reg_t *DMA[2] = {DMA1, DMA2};

/*==============================================================================================================================================
 * FUNCTION DEFINITION
 *==============================================================================================================================================*/

/*==============================================================================================================================================
 *@fn DMA_ClearInterruptFlag
 *@brief  Clearing Interrupt Flag Of A Specific Stream
 *@paramter[in]  Local_u8DMA_Number: This parameter is used to determine the DMA number
 *@paramter[in]  Local_u8ChannelNumber: This parameter is used to determine the channel number
 *@paramter[in]  Local_u8Flag: This parameter is used to determine the flag to be cleared
 *@retval  void
 *==============================================================================================================================================*/
void DMA_ClearInterruptFlag(DMA_Number_t Local_u8DMA_Number, DMA_Stream_t Local_u8Stream_Number, DMA_Flag_t Local_u8Flag)
{
	/* Local Variable To Hold Register Number */
	uint8_t Local_u8RegNum = Local_u8Stream_Number / 4;

	/* Clearing Interrupt Flag Of A Given Stream */
	DMA[Local_u8DMA_Number]->IFCR[Local_u8RegNum] |= (1 << (Local_u8Stream_Number + Local_u8Flag));
}
/*==============================================================================================================================================
 *@fn  DMA_Init
 *@brief This function is used to initialize a specific channel
 *@paramter[in] DMA_CONFIG: This parameter is used to determine the channel configuration
 *@retval void
 *==============================================================================================================================================*/
void DMA_Init(DMA_ChannelConfig_t *DMA_CONFIG)
{
	/* Channel Selection */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR &= ~(ThreeBitMasking << CHSEL);
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR |= ((DMA_CONFIG->ChannelSelection) << CHSEL);

	/*Setting Channel Priority*/
	DMA_SetStreamPriority(DMA_CONFIG);

	/* Setting memory data size */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR &= ~(TwoBitMasking << MSIZE);
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR |= ((DMA_CONFIG->MeomryDataSize) << MSIZE);

	/* Setting Periphral data size */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR &= ~(TwoBitMasking << PSIZE);
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR |= ((DMA_CONFIG->PeripheralDataSize) << PSIZE);

	/* Setting memory increment mode */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR &= ~(OneBitMasking << MINC);
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR |= ((DMA_CONFIG->MeomryIncreamentMode) << MINC);

	/* Setting Periphral increment mode */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR &= ~(OneBitMasking << PINC);
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR |= ((DMA_CONFIG->PeripheralIncreamentMode) << MINC);

	/* Setting data transfer direction */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR &= ~(TwoBitMasking << DIR);
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR |= ((DMA_CONFIG->DataDirection) << DIR);

	/* Seeting peripheral flow controller */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR &= ~(OneBitMasking << PFCTRL);
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR |= ((DMA_CONFIG->FlowController) << PFCTRL);
}

/*==============================================================================================================================================
 *@fn  DMA_SetStreamPriority
 *@brief  This function is used to set the priority of a Stream
 *@paramter[in] DMA_CONFIG: This parameter is used to determine the channel configuration
 *@retval void
 *==============================================================================================================================================*/

void DMA_SetStreamPriority(DMA_ChannelConfig_t *DMA_CONFIG)
{
	/*Setting Channel Priority*/
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR &= ~(TwoBitMasking << PL);
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR |= (DMA_CONFIG->PriorityLevel << PL);
}
/*==============================================================================================================================================
 *@fn  DMA_SetStreamInteruptConfig
 *@brief  This function is used to set the interrupt configuration of a specific channel
 *@paramter[in] DMA_CONFIG: This parameter is used to determine the channel configuration
 *@retval void
 *==============================================================================================================================================*/
void DMA_SetStreamInteruptConfig(DMA_ChannelConfig_t *DMA_CONFIG)
{
	/* Configuring DMA Interrupts */
	/* Clearing Interrupts Bits */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR &= ~(FourBitMasking << DMEIE);
	/* Setting Direct Mode Error Interrupt  */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR |= ((DMA_CONFIG->InteruptFlagsConfig->DirectModeErrorInterrupt) << DMEIE);
	/* Setting Transfer Error Interrupt */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR |= ((DMA_CONFIG->InteruptFlagsConfig->TransferErrorInterrupt) << TEIE);
	/* Setting Half Transfer Interrupt */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR |= ((DMA_CONFIG->InteruptFlagsConfig->HalfTransferInterrupt) << HTIE);
	/* Setting Transfer Complete Interrupt */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR |= ((DMA_CONFIG->InteruptFlagsConfig->TransferCompleteInterrupt) << TCIE);
}
/*==============================================================================================================================================
 *@fn  DMA_StartTransfer
 *@brief  This function is used to start a transfer of a specific channel with polling
 *@paramter[in] DMA_CONFIG: This parameter is used to determine the channel configuration
 *@paramter[in] Local_u32SourceAddress: This parameter is used to determine the source address
 *@paramter[in] Local_u32DestinationAddress: This parameter is used to determine the destination address
 *@paramter[in] Local_u16DataLength: This parameter is used to determine the data length
 *@retval void
 *==============================================================================================================================================*/
void DMA_StartTransfer(DMA_ChannelConfig_t *DMA_CONFIG, uint32_t Local_u32SourceAddress, uint32_t Local_u32DestinationAddress, uint16_t Local_u16DataLength)
{
	if (DMA_CONFIG->DataDirection == MeomryToMeomry || DMA_CONFIG->DataDirection == PeripheralToMeomry)
	{
		/* Setting Source Address */
		DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SPAR = Local_u32SourceAddress;
		/* Setting Destination Address */
		DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SM0AR = Local_u32DestinationAddress;
	}
	else if (DMA_CONFIG->DataDirection == MeomryToPeripheral)
	{
		/* Setting Source Address */
		DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SM0AR = Local_u32SourceAddress;
		/* Setting Destination Address */
		DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SPAR = Local_u32DestinationAddress;
	}
	/* Setting Data Length */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SNDTR = Local_u16DataLength;
	/* Enabling Stream */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR &= ~((OneBitMasking) << EN);
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR |= ((OneBitMasking) << EN);
	/* Waiting For Transfer Complete Flag */
	while (DMA_CheckingInterruptFlagSource(DMA_CONFIG->DMA_Number, DMA_CONFIG->StreamNumber, TCIF) == 0)
		;
}
/*==============================================================================================================================================
 *@fn  DMA_StartTransfer_IT
 *@brief  This function is used to start a transfer of a specific channel with interrupt
 *@paramter[in] DMA_CONFIG: This parameter is used to determine the channel configuration
 *@paramter[in] Local_u32SourceAddress: This parameter is used to determine the source address
 *@paramter[in] Local_u32DestinationAddress: This parameter is used to determine the destination address
 *@paramter[in] Local_u16DataLength: This parameter is used to determine the data length
 *@retval void
 *==============================================================================================================================================*/
void DMA_StartTransfer_IT(DMA_ChannelConfig_t *DMA_CONFIG, uint32_t Local_u32SourceAddress, uint32_t Local_u32DestinationAddress, uint16_t Local_u16DataLength)
{
	if (DMA_CONFIG->DataDirection == MeomryToMeomry || DMA_CONFIG->DataDirection == PeripheralToMeomry)
	{
		/* Setting Source Address */
		DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SPAR = Local_u32SourceAddress;
		/* Setting Destination Address */
		DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SM0AR = Local_u32DestinationAddress;
	}
	else if (DMA_CONFIG->DataDirection == MeomryToPeripheral)
	{
		/* Setting Source Address */
		DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SM0AR = Local_u32SourceAddress;
		/* Setting Destination Address */
		DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SPAR = Local_u32DestinationAddress;
	}
	/* Setting Data Length */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SNDTR = Local_u16DataLength;
	/* Configuring DMA Interrupts */
	DMA_SetStreamInteruptConfig(DMA_CONFIG);
	/* Enabling Stream */
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR &= ~((OneBitMasking) << EN);
	DMA[DMA_CONFIG->DMA_Number]->STREAM[DMA_CONFIG->StreamNumber]->SCR |= ((OneBitMasking) << EN);
}
/*==============================================================================================================================================
 *@fn  DMA_CheckingInterruptFlagSource
 *@brief  This function is used to check the interrupt flag source of a specific channel
 *@paramter[in] DMA_Number: This parameter is used to determine the DMA number
 *@paramter[in] StreamNumber: This parameter is used to determine the stream number
 *@paramter[in] Local_u8Flag: This parameter is used to determine the interrupt flag
 *@retval uint8_t: This return value is used to determine the interrupt flag source
 *==============================================================================================================================================*/
uint8_t DMA_CheckingInterruptFlagSource(DMA_Number_t DMA_Number, DMA_Stream_t StreamNumber, DMA_Flag_t Local_u8Flag)
{
	uint8_t FlagSource = 0;
	/* Local Variable To Hold Register Number */
	uint8_t Local_u8RegNum = (StreamNumber) / 4;
	/* Checking Interrupt Flag Source*/
	FlagSource = 1 & (DMA[DMA_Number]->ISR[Local_u8RegNum] >> (StreamNumber + Local_u8Flag));
	return FlagSource;
}

/*==============================================================================================================================================
 *@fn  DMA_SetCallBack
 *@brief  This function is used to set the callback function of a specific channel
 *@paramter[in] DMA_CONFIG: This parameter is used to determine the channel configuration
 *@paramter[in] Local_DMA_CallBack: This parameter is used to determine the callback function
 *@paramter[in] Local_u8Flag: This parameter is used to determine the interrupt flag source
 *@retval void
 *==============================================================================================================================================*/
void DMA_SetCallBack(DMA_ChannelConfig_t *DMA_CONFIG, void (*Local_DMA_CallBack)(void), DMA_Flag_t Local_u8Flag)
{
	if (DMA_CONFIG->DMA_Number == DMA_1)
	{
		DMA1_PTR[DMA_CONFIG->StreamNumber][Local_u8Flag] = Local_DMA_CallBack;
	}
	else if (DMA_CONFIG->DMA_Number == DMA_2)
	{
		DMA2_PTR[DMA_CONFIG->StreamNumber][Local_u8Flag] = Local_DMA_CallBack;
	}
}

/*==============================================================================================================================================
 * IRQ Handlers
 *==============================================================================================================================================*/
/*==============================================================================================================================================
 *@fn  DMA1_Stream0_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA1 Stream0
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA1_Stream0_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_0, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_0, TCIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_0][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_0, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_0, HTIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_0][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_0, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_0, TEIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_0][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_0, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_0, FEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_0][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_0, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_0, DMEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_0][DMEIF]();
	}
}
/*==============================================================================================================================================
 *@fn  DMA1_Stream1_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA1 Stream1
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA1_Stream1_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_1, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_1, TCIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_1][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_1, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_1, HTIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_1][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_1, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_1, TEIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_1][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_1, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_1, FEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_1][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_1, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_1, DMEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_1][DMEIF]();
	}
}
/*==============================================================================================================================================
 *@fn  DMA1_Stream2_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA1 Stream2
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA1_Stream2_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_2, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_2, TCIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_2][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_2, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_2, HTIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_2][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_2, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_2, TEIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_2][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_2, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_2, FEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_2][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_2, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_2, DMEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_2][DMEIF]();
	}
}
/*==============================================================================================================================================
 *@fn  DMA1_Stream3_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA1 Stream3
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA1_Stream3_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_3, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_3, TCIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_3][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_3, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_3, HTIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_3][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_3, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_3, TEIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_3][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_3, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_3, FEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_3][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_3, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_3, DMEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_3][DMEIF]();
	}
}
/*==============================================================================================================================================
 *@fn  DMA1_Stream4_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA1 Stream4
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA1_Stream4_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_4, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_4, TCIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_4][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_4, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_4, HTIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_4][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_4, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_4, TEIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_4][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_4, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_4, FEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_4][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_4, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_4, DMEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_4][DMEIF]();
	}
}
/*==============================================================================================================================================
 *@fn  DMA1_Stream5_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA1 Stream5
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA1_Stream5_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_5, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_5, TCIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_5][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_5, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_5, HTIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_5][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_5, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_5, TEIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_5][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_5, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_5, FEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_5][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_5, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_5, DMEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_5][DMEIF]();
	}
}
/*==============================================================================================================================================
 *@fn  DMA1_Stream6_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA1 Stream6
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA1_Stream6_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_6, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_6, TCIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_6][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_6, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_6, HTIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_6][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_6, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_6, TEIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_6][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_6, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_6, FEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_6][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_6, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_6, DMEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_6][DMEIF]();
	}
}
/*==============================================================================================================================================
 *@fn  DMA1_Stream7_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA1 Stream7
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA1_Stream7_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_7, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_7, TCIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_7][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_7, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_7, HTIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_7][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_7, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_7, TEIF);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_7][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_7, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_7, FEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_7][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_1, DMA_STREAM_7, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_1, DMA_STREAM_7, DMEIE);
		/* Calling Callback Function */
		DMA1_PTR[DMA_STREAM_7][DMEIF]();
	}
}
/*==============================================================================================================================================
 *@fn  DMA2_Stream0_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA2 Stream0
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA2_Stream0_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_0, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_0, TCIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_0][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_0, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_0, HTIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_0][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_0, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_0, TEIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_0][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_0, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_0, FEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_0][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_0, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_0, DMEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_0][DMEIF]();
	}
}
/*==============================================================================================================================================
 *@fn  DMA2_Stream1_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA2 Stream1
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA2_Stream1_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_1, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_1, TCIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_1][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_1, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_1, HTIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_1][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_1, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_1, TEIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_1][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_1, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_1, FEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_1][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_1, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_1, DMEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_1][DMEIF]();
	}
}
/*==============================================================================================================================================
 *@fn  DMA2_Stream2_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA2 Stream2
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA2_Stream2_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_2, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_2, TCIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_2][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_2, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_2, HTIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_2][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_2, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_2, TEIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_2][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_2, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_2, FEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_2][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_2, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_2, DMEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_2][DMEIF]();
	}
}
/*==============================================================================================================================================
 *@fn  DMA2_Stream3_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA2 Stream3
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA2_Stream3_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_3, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_3, TCIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_3][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_3, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_3, HTIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_3][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_3, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_3, TEIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_3][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_3, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_3, FEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_3][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_3, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_3, DMEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_3][DMEIF]();
	}
}
/*==============================================================================================================================================
 *@fn  DMA2_Stream4_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA2 Stream4
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA2_Stream4_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_4, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_4, TCIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_4][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_4, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_4, HTIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_4][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_4, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_4, TEIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_4][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_4, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_4, FEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_4][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_4, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_4, DMEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_4][DMEIF]();
	}
}
/*==============================================================================================================================================
 *@fn  DMA2_Stream5_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA2 Stream5
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA2_Stream5_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_5, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_5, TCIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_5][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_5, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_5, HTIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_5][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_5, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_5, TEIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_5][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_5, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_5, FEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_5][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_5, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_5, DMEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_5][DMEIF]();
	}
}
/*==============================================================================================================================================
 *@fn  DMA2_Stream6_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA2 Stream6
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA2_Stream6_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_6, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_6, TCIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_6][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_6, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_6, HTIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_6][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_6, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_6, TEIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_6][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_6, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_6, FEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_6][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_6, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_6, DMEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_6][DMEIF]();
	}
}
/*==============================================================================================================================================
 *@fn  DMA2_Stream7_IRQHandler
 *@brief  This function is used to handle the interrupt of DMA2 Stream7
 *@paramter[in] void
 *@retval void
 *==============================================================================================================================================*/
void DMA2_Stream7_IRQHandler(void)
{
	/* Checking Interrupt Flag Source*/
	/* Transfer Complete */
	if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_7, TCIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_7, TCIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_7][TCIF]();
	}
	/* Half Transfer Complete */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_7, HTIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_7, HTIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_7][HTIF]();
	}
	/* Transfer Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_7, TEIF))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_7, TEIF);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_7][TEIF]();
	}
	/* FIFO Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_7, FEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_7, FEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_7][FIEF]();
	}
	/* Direct Mode Error */
	else if (DMA_CheckingInterruptFlagSource(DMA_2, DMA_STREAM_7, DMEIE))
	{
		/* Clearing Interrupt Flag */
		DMA_ClearInterruptFlag(DMA_2, DMA_STREAM_7, DMEIE);
		/* Calling Callback Function */
		DMA2_PTR[DMA_STREAM_7][DMEIF]();
	}
}
