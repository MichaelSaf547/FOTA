#ifndef DMA_H_
#define DMA_H_



typedef struct
{
	u32 DMA_SCR;
	u32 DMA_SNDTR;
	u32 DMA_SPAR;
	u32 DMA_SM0AR;
	u32 DMA_SM1AR;
	u32 DMA_SFCR;
}DMAReg_t;


typedef struct
{
  u32 DMA_LISR;   /*!< DMA interrupt status register */
  u32 DMA_HISR;
  u32 DMA_LIFCR;  /*!< DMA interrupt flag clear register */
  u32 DMA_HIFCR;

} DMA_Base_Registers_t;

typedef enum
{
	DMAOk,
	DMANot_Ok,
	DMANull_ptr,
	DMAbusy,
}DMA_StatusTypeDef;

typedef struct
{
	u32 BaseAddress; /*---DMA BaseAddress Selection---*/

	u32 StreamNum;	/*0 - 7*/

	u32 Channel; /*---DMA Channel Selection---*/

	u32 DataTransferDirection;  /*---DMA DataTransferDirection Selection---*/

	u32 PriorityLevel;  /*---DMA PriorityLevel Selection---*/

	u32 MemoryDataSize; /*---DMA MemoryDataSize Selection---*/

	u32 PeripheralDataSize;  /*---DMA PeripheralDataSize Selection---*/

	u32 MemoryIncrementMode; /*---DMA MemoryIncrementMode Selection---*/

	u32 PeripheralIncrementMode; /*---DMA PeripheralIncrementMode Selection---*/

	u32 Mode;	/*---DMA Mode Selection---*/

	u32 TransferCompleteInterruptEnable;  /*---DMA TransferCompleteInterruptEnable Selection---*/

	u32 CurrentTarget;

}DMAcfg_t;


typedef enum
{
	DMA1_Stream0Cbf = 0,
	DMA1_Stream1Cbf = 1,
	DMA1_Stream2Cbf = 2,
	DMA1_Stream3Cbf = 3,
	DMA1_Stream4Cbf = 4,
	DMA1_Stream5Cbf = 5,
	DMA1_Stream6Cbf = 6,
	DMA1_Stream7Cbf = 7,
	DMA2_Stream0Cbf = 8,
	DMA2_Stream1Cbf = 9,
	DMA2_Stream2Cbf = 10,
	DMA2_Stream3Cbf = 11,
	DMA2_Stream4Cbf = 12,
	DMA2_Stream5Cbf = 13,
	DMA2_Stream6Cbf = 14,
	DMA2_Stream7Cbf = 15,
}StramCbfNum_t;

/*---Bits definition for DMA_SxCR register---*/
#define DMA_SxCR_EN											0x1u
#define DMA_SxCR_DMEIE                                      0x2u
#define DMA_SxCR_TEIE                                       0x4u
#define DMA_SxCR_HTIE                                       0x8u
#define DMA_SxCR_TCIE                                       0x10u
#define DMA_SxCR_PFCTRL                                     0x20u
#define DMA_SxCR_DIR0                                       0x40u
#define DMA_SxCR_DIR1                                       0x80u
#define DMA_SxCR_CIRC                                       0x100u
#define DMA_SxCR_PINC                                       0x200u
#define DMA_SxCR_MINC                                       0x400u
#define DMA_SxCR_PSIZE0                                     0x800u
#define DMA_SxCR_PSIZE1                                     0x1000u
#define DMA_SxCR_MSIZE0                                     0x2000u
#define DMA_SxCR_MSIZE1                                     0x4000u
#define DMA_SxCR_PINCOS                                     0x8000u
#define DMA_SxCR_PL0                                        0x10000u
#define DMA_SxCR_PL1                                        0x20000u
#define DMA_SxCR_DBM                                        0x40000u
#define DMA_SxCR_CT                                         0x80000u
#define DMA_SxCR_PBURST0                                    0x200000u
#define DMA_SxCR_PBURST1                                    0x400000u
#define DMA_SxCR_MBURST0                                    0x800000u
#define DMA_SxCR_MBURST1                                    0x1000000u
#define DMA_SxCR_CHSEL0                                     0x2000000u
#define DMA_SxCR_CHSEL1                                     0x4000000u
#define DMA_SxCR_CHSEL2                                     0x8000000u

#define DMA_SxCR											(u32)0xFEFFFFFu



/*---Macro for hardware access---*/
#define __STREAM_REG(BaseAdress,StreamNum)				((volatile DMAReg_t *) (BaseAdress+(0x10+StreamNum*0x18)))

/*---DMA BaseAddress Selection---*/
#define DMA1_BASE												0x40026000u
#define DMA2_BASE												0x40026400u


/*---DMA Channel Selection---*/
#define DMA_CH_0												0x0000000U
#define DMA_CH_1                                                0x2000000U
#define DMA_CH_2                                                0x4000000U
#define DMA_CH_3                                                0x6000000U
#define DMA_CH_4                                                0x8000000U
#define DMA_CH_5                                                0xA000000U
#define DMA_CH_6                                                0xC000000U
#define DMA_CH_7                                                0xE000000U


/*---DMA PriorityLevel Selection---*/
#define DMA_PRIORTY_LEVEL_LOW									(u32)0x0u
#define DMA_PRIORTY_LEVEL_MEDIUM								(u32)DMA_SxCR_PL0
#define DMA_PRIORTY_LEVEL_HIGH									(u32)DMA_SxCR_PL1
#define DMA_PRIORTY_LEVEL_VERY_HIGH						    	(u32)(DMA_SxCR_PL0|DMA_SxCR_PL1)


/*---DMA MemoryDataSize Selection---*/
#define DMA_MEMORY_DATA_SIZE_BYTE								(u32)0x0u
#define DMA_MEMORY_DATA_SIZE_HALF_WORD							(u32)DMA_SxCR_MSIZE0
#define DMA_MEMORY_DATA_SIZE_WORD								(u32)DMA_SxCR_MSIZE1



/*---DMA PeripheralDataSize Selection---*/
#define DMA_PERIPHERAL_DATA_SIZE_BYTE							(u32)0x0u
#define DMA_PERIPHERAL_DATA_SIZE_HALF_WORD						(u32)DMA_SxCR_PSIZE0
#define DMA_PERIPHERAL_DATA_SIZE_WORD							(u32)DMA_SxCR_PSIZE1


/*---DMA MemoryIncrementMode Selection---*/
#define DMA_MEMORY_INCREMENT_MODE_FIXED							(u32)0x0u
#define DMA_MEMORY_INCREMENT_MODE_INCREMENTED					(u32)DMA_SxCR_MINC


/*---DMA PeripheralIncrementMode Selection---*/
#define DMA_PERIPHERAL_INCREMENT_MODE_FIXED						(u32)0x0u
#define DMA_PERIPHERAL_INCREMENT_MODE_INCREMENTED				(u32)DMA_SxCR_PINC

/*---DMA Mode Selection---*/
#define DMA_NORMAL_MODE											(u32)0x0u
#define DMA_CIRCULAR_MODE										(u32)DMA_SxCR_CIRC
#define DMA_PERIPHERAL_FLOW_CONTROLLER_MODE						(u32)DMA_SxCR_PFCTRL


/*---DMA DataTransferDirection Selection---*/
#define DMA_DIRECTION_PERIPHERAL_TO_MEMORY						(u32)0x0u
#define DMA_DIRECTION_MEMORY_TO_PERIPHERAL						(u32)DMA_SxCR_DIR0
#define DMA_DIRECTION_MEMORY_TO_MEMORY		 				    (u32)DMA_SxCR_DIR1

/*---DMA TransferCompleteInterruptEnable Selection---*/
#define DMA_TCIN_DISABLED										(u32)0x0u
#define DMA_TCIN_ENABLED										(u32)DMA_SxCR_TCIE


extern DMA_StatusTypeDef DMA_Init(DMAcfg_t* psDMAcfg);
extern DMA_StatusTypeDef DMA_Start(DMAcfg_t* psDMAcfg,u32 pu32Src,u32 pu32Dest,u32 DataSize);

void DMA_StremRegisterCbf( void (*pfDmaStrCbf) (void) ,StramCbfNum_t num);
void DMA1_Stream0_IRQHandler(void);
void DMA1_Stream1_IRQHandler(void);
void DMA1_Stream2_IRQHandler(void);
void DMA1_Stream3_IRQHandler(void);
void DMA1_Stream4_IRQHandler(void);
void DMA1_Stream5_IRQHandler(void);
void DMA1_Stream6_IRQHandler(void);
void DMA1_Stream7_IRQHandler(void);

void DMA2_Stream0_IRQHandler(void);
void DMA2_Stream1_IRQHandler(void);
void DMA2_Stream2_IRQHandler(void);
void DMA2_Stream3_IRQHandler(void);
void DMA2_Stream4_IRQHandler(void);
void DMA2_Stream5_IRQHandler(void);
void DMA2_Stream6_IRQHandler(void);
void DMA2_Stream7_IRQHandler(void);


#endif
