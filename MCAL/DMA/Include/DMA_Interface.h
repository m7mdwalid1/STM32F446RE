/*******************************************************************************
 * Filename              :   DMA_Interface.h
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
#ifndef DMA_INCLUDE_DMA_INTERFACE_H_
#define DMA_INCLUDE_DMA_INTERFACE_H_

typedef enum
{
    DMA_1 = 0, // DMA 1
    DMA_2      // DMA 2
} DMA_Number_t;
typedef enum
{
    DMA_STREAM_0 = 0,  // DMA Stream 0
    DMA_STREAM_1 = 6,  // DMA Stream 1
    DMA_STREAM_2 = 16, // DMA Stream 2
    DMA_STREAM_3 = 22, // DMA Stream 3
    DMA_STREAM_4 = 0,  // DMA Stream 4
    DMA_STREAM_5 = 6,  // DMA Stream 5
    DMA_STREAM_6 = 16, // DMA Stream 6
    DMA_STREAM_7 = 22  // DMA Stream 7
} DMA_Stream_t;

typedef enum
{
    FIEF = 0,  // FIFO error interrupt flag
    DMEIF = 2, // Direct mode error interrupt flag
    TEIF,      // Transfer error interrupt flag
    HTIF,      // Half transfer interrupt flag
    TCIF       // Transfer complete interrupt flag

} DMA_Flag_t;

typedef enum
{
    CH0 = 0, // Channel 0
    CH1,     // Channel 1
    CH2,     // Channel 2
    CH3,     // Channel 3
    CH4,     // Channel 4
    CH5,     // Channel 5
    CH6,     // Channel 6
    CH7      // Channel 7
} DMA_ChannelSelection_t;
typedef enum
{
    SingleTransfer = 0, // Single Transfer
    INCR4 = 1,          // Incremental 4
    INCR8 = 2,          // Incremental 8
    INCR16 = 3          // Incremental 16
} DMA_BrustTransfer_t;
typedef enum
{
    Meomry0 = 0, // Meomry 0 (addressed by the DMA_SxM0AR pointer)
    Meomry1 = 1  // Meomry 1 (addressed by the DMA_SxM1AR pointer)
} DMA_CT_t;
/*typedef enum
{

} DMA_DoubleBufferMode_t;*/
typedef enum
{
    Low = 0,  // Low
    Medium,   // Medium
    High,     // High
    VeryHigh, // Very High
} DMA_Priority_t;
typedef enum
{
    LinkedTO_PSIZE = 0, // Linked to PSIZE
    FixedTO_4Bytes,     // Fixed to 4 bytes
} DMA_PeripheralIncrement_t;
typedef enum
{
    BYTE = 0, // Byte
    HALFWORD, // Half Word
    WORD      // Word
} DMA_DataSize_t;
typedef enum
{
    Increament_DISABLE = 0, // Disable Pointer Increament
    Increament_ENABLE,      // Enable Pointer Increament
} DMA_IncreamentMode_t;
typedef enum
{
    Disable = 0, // Disable
    Enable,      // Enable
} DMA_InitialState_t;
typedef enum
{
    PeripheralToMeomry = 0, // Peripheral to Meomry
    MeomryToPeripheral,     // Meomry to Peripheral
    MeomryToMeomry,         // Meomry to Meomry
} DMA_DataDirection_t;
typedef enum
{
    DMAFlowController = 0,    // DMA Flow Controller
    PeripheralFlowController, // Peripheral Flow Controller
} DMA_FlowController_t;
typedef struct
{
    DMA_InitialState_t TransferCompleteInterrupt; // Transfer Complete Interrupt
    DMA_InitialState_t HalfTransferInterrupt;     // Half Transfer Interrupt
    DMA_InitialState_t TransferErrorInterrupt;    // Transfer Error Interrupt
    DMA_InitialState_t DirectModeErrorInterrupt;  // Direct Mode Error Interrupt
    DMA_InitialState_t FIFOErrorInterrupt;        // FIFO Error Interrupt
} DMA_InteruptConfig_t;
typedef struct
{
    DMA_Number_t DMA_Number;                       // DMA Number
    DMA_Stream_t StreamNumber;                     // Stream Number
    DMA_ChannelSelection_t ChannelSelection;       // Channel Selection
    DMA_BrustTransfer_t MeomryTransferBrust;       // Meomry Transfer Brust
    DMA_BrustTransfer_t PeripheralTransferBrust;   // Peripheral Transfer Brust
                                                   //  DMA_DoubleBufferMode_t DoubleBufferMod;        // Double Buffer Mode
    DMA_Priority_t PriorityLevel;                  // Priority Level
    DMA_PeripheralIncrement_t PeripheralIncrement; // Peripheral Increment
    DMA_DataSize_t MeomryDataSize;                 // Meomry Data Size
    DMA_DataSize_t PeripheralDataSize;             // Peripheral Data Size
    DMA_IncreamentMode_t MeomryIncreamentMode;     // Meomry Increament Mode
    DMA_IncreamentMode_t PeripheralIncreamentMode; // Peripheral Increament Mode
    DMA_InitialState_t CircularMode;               // Circular Mode
    DMA_DataDirection_t DataDirection;             // Data Direction
    DMA_FlowController_t FlowController;           // Flow Controller
    DMA_InteruptConfig_t *InteruptFlagsConfig;     // Interupt Flags Config
} DMA_ChannelConfig_t;
/*==============================================================================================================================================
 * Function Declarations
 *==============================================================================================================================================*/

/*==============================================================================================================================================
 *@fn DMA_ClearInterruptFlag
 *@brief  This function is used to clear the interrupt flag of a specific channel
 *@paramter[in]  Local_u8DMA_Number: This parameter is used to determine the DMA number
 *@paramter[in]  Local_u8ChannelNumber: This parameter is used to determine the channel number
 *@paramter[in]  Local_u8Flag: This parameter is used to determine the flag to be cleared
 *@retval  void
 *==============================================================================================================================================*/
void DMA_ClearInterruptFlag(DMA_Number_t Local_u8DMA_Number, DMA_Stream_t Local_u8Stream_Number, DMA_Flag_t Local_u8Flag);

/*==============================================================================================================================================
 *@fn  DMA_Init
 *@brief This function is used to initialize a specific channel
 *@paramter[in] DMA_CONFIG: This parameter is used to determine the channel configuration
 *@retval void
 *==============================================================================================================================================*/
void DMA_Init(DMA_ChannelConfig_t *DMA_CONFIG);

/*==============================================================================================================================================
 *@fn  DMA_SetChannelPriority
 *@brief  This function is used to set the priority of a Stream
 *@paramter[in] DMA_CONFIG: This parameter is used to determine the channel configuration
 *@retval void
 *==============================================================================================================================================*/

void DMA_SetStreamPriority(DMA_ChannelConfig_t *DMA_CONFIG);
/*==============================================================================================================================================
 *@fn  DMA_SetStreamInteruptConfig
 *@brief  This function is used to set the interrupt configuration of a specific channel
 *@paramter[in] DMA_CONFIG: This parameter is used to determine the channel configuration
 *@retval void
 *==============================================================================================================================================*/
void DMA_SetStreamInteruptConfig(DMA_ChannelConfig_t *DMA_CONFIG);

/*==============================================================================================================================================
 *@fn  DMA_StartTransfer
 *@brief  This function is used to start a transfer of a specific channel with polling 
 *@paramter[in] DMA_CONFIG: This parameter is used to determine the channel configuration
 *@paramter[in] Local_u32SourceAddress: This parameter is used to determine the source address
 *@paramter[in] Local_u32DestinationAddress: This parameter is used to determine the destination address
 *@paramter[in] Local_u16DataLength: This parameter is used to determine the data length
 *@retval void
 *==============================================================================================================================================*/
void DMA_StartTransfer(DMA_ChannelConfig_t *DMA_CONFIG, uint32_t Local_u32SourceAddress, uint32_t Local_u32DestinationAddress, uint16_t Local_u16DataLength);

/*==============================================================================================================================================
 *@fn  DMA_StartTransfer_IT
 *@brief  This function is used to start a transfer of a specific channel with interrupt
 *@paramter[in] DMA_CONFIG: This parameter is used to determine the channel configuration
 *@paramter[in] Local_u32SourceAddress: This parameter is used to determine the source address
 *@paramter[in] Local_u32DestinationAddress: This parameter is used to determine the destination address
 *@paramter[in] Local_u16DataLength: This parameter is used to determine the data length
 *@retval void
 *==============================================================================================================================================*/
void DMA_StartTransfer_IT(DMA_ChannelConfig_t *DMA_CONFIG, uint32_t Local_u32SourceAddress, uint32_t Local_u32DestinationAddress, uint16_t Local_u16DataLength);
/*==============================================================================================================================================
 *@fn  DMA_CheckingInterruptFlagSource
 *@brief  This function is used to check the interrupt flag source of a specific channel
 *@paramter[in] DMA_Number: This parameter is used to determine the DMA number
 *@paramter[in] StreamNumber: This parameter is used to determine the stream number
 *@paramter[in] Local_u8Flag: This parameter is used to determine the interrupt flag
 *@retval uint8_t: This return value is used to determine the interrupt flag source
 *==============================================================================================================================================*/
uint8_t DMA_CheckingInterruptFlagSource(DMA_Number_t DMA_Number, DMA_Stream_t StreamNumber, DMA_Flag_t Local_u8Flag);

/*==============================================================================================================================================
 *@fn  DMA_SetCallBack
 *@brief  This function is used to set the callback function of a specific channel
 *@paramter[in] DMA_CONFIG: This parameter is used to determine the channel configuration
 *@paramter[in] Local_DMA_CallBack: This parameter is used to determine the callback function
 *@paramter[in] Local_u8Flag: This parameter is used to determine the interrupt flag source
 *@retval void
 *==============================================================================================================================================*/
void DMA_SetCallBack(DMA_ChannelConfig_t *DMA_CONFIG, void (*Local_DMA_CallBack)(void), DMA_Flag_t Local_u8Flag);
#endif /* DMA_INCLUDE_DMA_INTERFACE_H_ */
