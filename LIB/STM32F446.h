/*******************************************************************************
 * Filename              :   STM32F446.h
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
#ifndef STM32F446_H_
#define STM32F446_H_

/*Various meomry Base Addresses*/

#define Flash_BASEADD 0x80000000UL
#define SRAM_BASEADD 0x20000000UL
#define ROM_BASEADD 0x1FFF0000UL

/*AHP1 PREPHIRAL BASE ADD */
#define GPIOA_BASEADD 0x40020000UL
#define GPIOB_BASEADD 0x40020400UL
#define GPIOC_BASEADD 0x40020800UL
#define GPIOD_BASEADD 0x40020C00UL
#define GPIOE_BASEADD 0x40021000UL
#define GPIOF_BASEADD 0x40021400UL
#define GPIOG_BASEADD 0x40021C00UL
#define GPIOH_BASEADD 0x40020000UL

/*AHP2 PREPHIRAL BASE ADD */

/*AHP3 PREPHIRAL BASE ADD */

/*APB1 PREPHIRAL BASE ADD */

/*APB2 PREPHIRAL BASE ADD */

/*GPIO REGISTER DEFINITION STRUCTURE */
typedef struct
{
  volatile uint32_t MODER;   /*GPIO PORT MODE REGISTER */
  volatile uint32_t OTYPER;  /*GPIO PORT OUTPUT TYPE REGISTER*/
  volatile uint32_t OSPEEDR; /*GPIO PORT OUTPUT SPEED REGISTER*/
  volatile uint32_t PUPDR;   /*GPIO PORT PULL UP / DOWN REGISTER */
  volatile uint32_t IDR;     /*GPIO PORT INPUT DAATA REGISTER */
  volatile uint32_t ODR;     /*GPIO PORT OUTPUT DATA REGISTER */
  volatile uint32_t BSRR;    /*GPIO PORT BIT SET / RESET REGISTER  */
  volatile uint32_t LCKR;    /*GPIO PORT LOCK REGISTER  */
  volatile uint32_t AFRL[2]; /*GPIO PORT ALTERNATE FUNCTION REGISTER  */
} GPIO_RegDef_t;

/* GPIO PREPHIRAL DEFINITION  */
#define GPIOA ((GPIO_RegDef_t *)GPIOA_BASEADD)
#define GPIOB ((GPIO_RegDef_t *)GPIOB_BASEADD)
#define GPIOC ((GPIO_RegDef_t *)GPIOC_BASEADD)
#define GPIOD ((GPIO_RegDef_t *)GPIOD_BASEADD)
#define GPIOE ((GPIO_RegDef_t *)GPIOE_BASEADD)
#define GPIOF ((GPIO_RegDef_t *)GPIOF_BASEADD)
#define GPIOG ((GPIO_RegDef_t *)GPIOG_BASEADD)
#define GPIOH ((GPIO_RegDef_t *)GPIOH_BASEADD)

typedef struct
{
  volatile uint32_t CR;         /*!< RCC clock control register,                                   */
  volatile uint32_t PLLCFGR;    /*!< RCC PLL configuration register,                               */
  volatile uint32_t CFGR;       /*!< RCC clock configuration register,                             */
  volatile uint32_t CIR;        /*!< RCC clock interrupt register,                                 */
  volatile uint32_t AHB1RSTR;   /*!< RCC AHB1 peripheral reset register,                           */
  volatile uint32_t AHB2RSTR;   /*!< RCC AHB2 peripheral reset register,                           */
  volatile uint32_t AHB3RSTR;   /*!< RCC AHB3 peripheral reset register,                           */
  uint32_t RESERVED0;           /*!< Reserved, 0x1C                                                */
  volatile uint32_t APB1RSTR;   /*!< RCC APB1 peripheral reset register,                           */
  volatile uint32_t APB2RSTR;   /*!< RCC APB2 peripheral reset register,                           */
  uint32_t RESERVED1[2];        /*!< Reserved, 0x28-0x2C                                           */
  volatile uint32_t AHB1ENR;    /*!< RCC AHB1 peripheral clock register,                           */
  volatile uint32_t AHB2ENR;    /*!< RCC AHB2 peripheral clock register,                           */
  volatile uint32_t AHB3ENR;    /*!< RCC AHB3 peripheral clock register,                           */
  uint32_t RESERVED2;           /*!< Reserved, 0x3C                                                */
  volatile uint32_t APB1ENR;    /*!< RCC APB1 peripheral clock enable register,                    */
  volatile uint32_t APB2ENR;    /*!< RCC APB2 peripheral clock enable register,                    */
  uint32_t RESERVED3[2];        /*!< Reserved, 0x48-0x4C                                           */
  volatile uint32_t AHB1LPENR;  /*!< RCC AHB1 peripheral clock enable in low power mode register,  */
  volatile uint32_t AHB2LPENR;  /*!< RCC AHB2 peripheral clock enable in low power mode register,  */
  volatile uint32_t AHB3LPENR;  /*!< RCC AHB3 peripheral clock enable in low power mode register,  */
  uint32_t RESERVED4;           /*!< Reserved, 0x5C                                                */
  volatile uint32_t APB1LPENR;  /*!< RCC APB1 peripheral clock enable in low power mode register,  */
  volatile uint32_t APB2LPENR;  /*!< RCC APB2 peripheral clock enable in low power mode register,  */
  uint32_t RESERVED5[2];        /*!< Reserved, 0x68-0x6C                                           */
  volatile uint32_t BDCR;       /*!< RCC Backup domain control register,                           */
  volatile uint32_t CSR;        /*!< RCC clock control & status register,                          */
  uint32_t RESERVED6[2];        /*!< Reserved, 0x78-0x7C                                           */
  volatile uint32_t SSCGR;      /*!< RCC spread spectrum clock generation register,                */
  volatile uint32_t PLLI2SCFGR; /*!< RCC PLLI2S configuration register,                            */
  volatile uint32_t PLLSAICFGR; /*!< RCC PLLSAI configuration register,                            */
  volatile uint32_t DCKCFGR;    /*!< RCC Dedicated Clocks configuration register,                  */
  volatile uint32_t CKGATENR;   /*!< RCC Clocks Gated ENable Register,                             */
  volatile uint32_t DCKCFGR2;   /*!< RCC Dedicated Clocks configuration register 2,                */
} RCC_RegDef_t;

/*******************   BASE Address Definition    *********************/
/* Defining Base Address Of RCC */
#define RCC_BASE_ADDRESS 0x40023800UL

#define RCC ((RCC_RegDef_t *)RCC_BASE_ADDRESS)

typedef enum
{
  HSION = 0,
  HSIRDY = 1,
  HSEON = 16,
  HSERDY = 17,
  HSEBYP = 18,
  CSSON = 19,
  PLLON = 24,
  PLLRDY = 25,
  PLLI2SON = 26,
  PLLI2SRDY = 27,
  PLLSAION = 28,
  PLLSAIRDY = 29
} RCC_CR_BITS_t;
typedef enum
{
  PLLM = 0,
  PLLN = 6,
  PLLP = 16,
  PLLSRC = 22,
  PLLQ = 24,
  PLLR = 28
} RCC_PLLCFGR_BITS_t;
typedef enum
{
  SW = 0,
  SWS = 2,
  HPRE = 4,
  PPRE1 = 10,
  PPRE2 = 13,
  RTCPRE = 16,
  MCO1 = 21,
  MCO1PRE = 24,
  MCO2PRE = 27,
  MCO2 = 30
} RCC_CFGR_BITS_t;

/*******************  SysTick Register Definition        ********************/
typedef struct
{
  volatile uint32_t SYST_CSR;
  volatile uint32_t SYST_RVR;
  volatile uint32_t SYST_CVR;
  volatile uint32_t SYST_CALIB;
} SysTick_REG_t;
#define SYST_CSR_ENABLE 0
#define SYST_CSR_TICKINT 1
#define SYST_CSR_CLKSOURCE 2
#define SYST_CSR_COUNTFLAG 16

#define SYST_RVR_RELOAD 0

#define SYST_CVR_CURRENT 0

/*******************  SysTick BASE Address Definition    *********************/
/* Defining Base Address Of RCC */
#define SysTick_BASE_ADDRESS 0xE000E010

#define SysTick ((SysTick_REG_t *)SysTick_BASE_ADDRESS)

/*******************  NVIC BASE Address Definition    *********************/

#define NVIC_BASE_ADDRESS 0xE000E100UL

#define NVIC ((NVIC_Reg_t *)NVIC_BASE_ADDRESS)
typedef struct
{
  volatile uint32_t ISER[8];
  volatile uint32_t RESERVED0[24];
  volatile uint32_t ICER[8];
  volatile uint32_t RSERVED1[24];
  volatile uint32_t ISPR[8];
  volatile uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8];
  volatile uint32_t RESERVED3[24];
  volatile uint32_t IABR[8];
  volatile uint32_t RESERVED4[56];
  volatile uint8_t IPR[240];
  volatile uint32_t RESERVED5[644];
  volatile uint32_t STIR;
} NVIC_Reg_t;

/*******************  SCB BASE Address Definition    *********************/
#define SCB_BASE_ADDRESS 0xE000E008UL

#define SCB ((SCB_Reg_t *)SCB_BASE_ADDRESS)
typedef struct
{
  volatile uint32_t ACTLR;
  volatile uint32_t CPUID;
  volatile uint32_t ICSR;
  volatile uint32_t VTOR;
  volatile uint32_t AIRCR;
  volatile uint32_t SCR;
  volatile uint32_t CCR;
  volatile uint32_t SHPR[3];
  volatile uint32_t SHCSR;
  volatile uint32_t CFSR;
  volatile uint32_t MMSR;
  volatile uint32_t BFSR;
  volatile uint32_t UFSR;
  volatile uint32_t HFSR;
  volatile uint32_t MMAR;
  volatile uint32_t BFAR;
  volatile uint32_t AFSR;
} SCB_Reg_t;
/*******************  SYSCFG BASE Address Definition    *********************/
#define SYSCFG_BASE_ADDRESS 0x40013800UL
#define SYSCFG ((SYSCFG_Reg_t *)SYSCFG_BASE_ADDRESS)
typedef struct
{
  volatile uint32_t MEMRMP;
  volatile uint32_t PMC;
  volatile uint32_t EXTICR[4];
  volatile uint32_t RESERVED0[2];
  volatile uint32_t CMPCR;
  volatile uint32_t RESERVED1[2];
  volatile uint32_t CFGR;
} SYSCFG_Reg_t;

/*******************  EXTI BASE Address Definition    *********************/
#define EXTI_BASE_ADDRESS 0x40013C00UL
#define EXTI ((EXTI_Reg_t *)EXTI_BASE_ADDRESS)
typedef struct
{
  volatile uint32_t IMR;
  volatile uint32_t EMR;
  volatile uint32_t RTSR;
  volatile uint32_t FTSR;
  volatile uint32_t SWIER;
  volatile uint32_t PR;
} EXTI_Reg_t;

/*******************  DMA BASE Address Definition    *********************/

#define DMA1_BASE_ADDRESS 0x40026000UL
#define DMA2_BASE_ADDRESS 0x40026400UL

#define DMA1 ((DMA_Reg_t *)DMA1_BASE_ADDRESS)
#define DMA2 ((DMA_Reg_t *)DMA2_BASE_ADDRESS)
typedef struct
{
  volatile uint32_t SCR;
  volatile uint32_t SNDTR;
  volatile uint32_t SPAR;
  volatile uint32_t SM0AR;
  volatile uint32_t SM1AR;
  volatile uint32_t SFCR;
} DMA_Stream_Reg_t;
typedef struct
{
  volatile uint32_t ISR[2];
  volatile uint32_t IFCR[2];
  DMA_Stream_Reg_t * STREAM[8];
} DMA_Reg_t;

typedef enum
{
  FEIFO0 = 0,  // FIFO error interrupt flag for stream 0
  DMEIF0 = 2,  // Direct mode error interrupt flag for stream 0
  TEIF0 = 3,   // Transfer error interrupt flag for stream 0
  HTIF0 = 4,   // Half transfer interrupt flag for stream 0
  TCIF0 = 5,   // Transfer complete interrupt flag for stream 0
  FEIFO1 = 6,  // FIFO error interrupt flag for stream 1
  DMEIF1 = 8,  // Direct mode error interrupt flag for stream 1
  TEIF1 = 9,   // Transfer error interrupt flag for stream 1
  HTIF1 = 10,  // Half transfer interrupt flag for stream 1
  TCIF1 = 11,  // Transfer complete interrupt flag for stream 1
  FEIFO2 = 16, // FIFO error interrupt flag for stream 2
  DMEIF2 = 18, // Direct mode error interrupt flag for stream 2
  TEIF2 = 19,  // Transfer error interrupt flag for stream 2
  HTIF2 = 20,  // Half transfer interrupt flag for stream 2
  TCIF2 = 21,  // Transfer complete interrupt flag for stream 2
  FEIFO3 = 22, // FIFO error interrupt flag for stream 3
  DMEIF3 = 24, // Direct mode error interrupt flag for stream 3
  TEIF3 = 25,  // Transfer error interrupt flag for stream 3
  HTIF3 = 26,  // Half transfer interrupt flag for stream 3
  TCIF3 = 27,  // Transfer complete interrupt flag for stream 3
} DMA_LISR_BITS_t;

typedef enum
{
  FEIF4 = 0,   // FIFO error interrupt flag for stream 4
  DMEIF4 = 2,  // Direct mode error interrupt flag for stream 4
  TEIF4 = 3,   // Transfer error interrupt flag for stream 4
  HTIF4 = 4,   // Half transfer interrupt flag for stream 4
  TCIF4 = 5,   // Transfer complete interrupt flag for stream 4
  FEIF5 = 6,   // FIFO error interrupt flag for stream 5
  DMEIF5 = 8,  // Direct mode error interrupt flag for stream 5
  TEIF5 = 9,   // Transfer error interrupt flag for stream 5
  HTIF5 = 10,  // Half transfer interrupt flag for stream 5
  TCIF5 = 11,  // Transfer complete interrupt flag for stream 5
  FEIF6 = 16,  // FIFO error interrupt flag for stream 6
  DMEIF6 = 18, // Direct mode error interrupt flag for stream 6
  TEIF6 = 19,  // Transfer error interrupt flag for stream 6
  HTIF6 = 20,  // Half transfer interrupt flag for stream 6
  TCIF6 = 21,  // Transfer complete interrupt flag for stream 6
  FEIF7 = 22,  // FIFO error interrupt flag for stream 7
  DMEIF7 = 24, // Direct mode error interrupt flag for stream 7
  TEIF7 = 25,  // Transfer error interrupt flag for stream 7
  HTIF7 = 26,  // Half transfer interrupt flag for stream 7
  TCIF7 = 27,  // Transfer complete interrupt flag for stream 7
} DMA_HISR_BITS_t;

typedef enum
{
  EN = 0,      // DMA stream enable
  DMEIE = 1,   // Direct mode error interrupt enable
  TEIE = 2,    // Transfer error interrupt enable
  HTIE = 3,    // Half transfer interrupt enable
  TCIE = 4,    // Transfer complete interrupt enable
  PFCTRL = 5,  // Peripheral flow controller
  DIR = 6,     // Data transfer direction
  CIRC = 8,    // Circular mode
  PINC = 9,    // Peripheral increment mode
  MINC = 10,   // Memory increment mode
  PSIZE = 11,  // Peripheral data size
  MSIZE = 13,  // Memory data size
  PINCOS = 15, // Peripheral increment offset size
  PL = 16,     // Priority level
  DBM = 18,    // Double buffer mode  HINT: This bit can be written only if EN = 0
  CT = 19,     // Current target (only in double buffer mode) HINT: This bit can be written only if EN = 0
  PBURST = 21, // Peripheral burst transfer configuration
  MBURST = 23, // Memory burst transfer configuration
  CHSEL = 25,  // Channel selection
} DMA_SCR_BITS_t;
typedef enum
{
  NDT = 0 // Number of data items to transfer
} DMA_SNDTR_BITS_t;

typedef enum
{
  PAR = 0 // Peripheral address
} DMA_SPAR_BITS_t;
typedef enum
{
  M0A = 0 // Memory 0 address
} DMA_SM0AR_BITS_t;

typedef enum
{
  M1A = 0 // Memory 0 address
} DMA_SM1AR_BITS_t;

typedef enum
{
  FTH = 0,   // FIFO threshold selection
  DMDIS = 2, // Direct mode disable
  FS = 3,    // FIFO status
  FEIE = 7,  // FIFO error interrupt enable
} DMA_SFCR_BITS_t;

#endif /* STM32F446_H_ */
