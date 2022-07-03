#ifndef FLASH_H_
#define FLASH_H_



typedef struct
{
	volatile u32 FLASH_ACR;
	volatile u32 FLASH_KEYR;
	volatile u32 FLASH_OPTKEYR;
	volatile u32 FLASH_SR;
	volatile u32 FLASH_CR;
	volatile u32 FLASH_OPTCR;
}FlashReg_t;

#define  FLASH_BASE  		((volatile FlashReg_t*) (0x40023C00))


/*---Bits definition for FLASH_SR register---*/
#define FLASH_SR_EOP					(u32)0x1u
#define FLASH_SR_OPERR                  (u32)0x2u
#define FLASH_SR_WRPERR                 (u32)0x10u
#define FLASH_SR_PGAERR                 (u32)0x20u
#define FLASH_SR_PGPERR                 (u32)0x40u
#define FLASH_SR_PGSERR                 (u32)0x80u
#define FLASH_SR_RDERR                  (u32)0x100u
#define FLASH_SR_BSY                    (u32)0x10000u

/*---Bits definition for FLASH_CR register---*/
#define FLASH_CR_PG					    (u32)0x1u
#define FLASH_CR_SER                    (u32)0x2u
#define FLASH_CR_MER					(u32)0x4u
#define FLASH_CR_SNB0                   (u32)0x8u
#define FLASH_CR_SNB1                   (u32)0x10u
#define FLASH_CR_SNB2                   (u32)0x20u
#define FLASH_CR_SNB3                   (u32)0x40u
#define FLASH_CR_SNB                    (u32)0x78u
#define FLASH_CR_PSIZE0                 (u32)0x100u
#define FLASH_CR_PSIZE1                 (u32)0x200u
#define FLASH_CR_PSIZE                  (u32)0x300u
#define FLASH_CR_STRT                   (u32)0x10000u
#define FLASH_CR_EOPIE                  (u32)0x1000000u
#define FLASH_CR_ERRIE                  (u32)0x2000000u
#define FLASH_CR_LOCK                   (u32)0x80000000u


/*---DMA PriorityLevel Selection---*/
#define FLASH_PROGRAM_SIZE_x8						(u32)0x0u
#define FLASH_PROGRAM_SIZE_x16					    FLASH_CR_PSIZE0
#define FLASH_PROGRAM_SIZE_x32	  					FLASH_CR_PSIZE1
#define FLASH_PROGRAM_SIZE_x64				    	(FLASH_CR_PSIZE0|FLASH_CR_PSIZE1)


typedef enum
{
	Flash_OK,
	Flash_NOK
}FlashReturn_t;

extern void Flash_Init(void);
extern void Flash_DeInit(void);


extern FlashReturn_t Flash_SectorErase(u32 Copy_u8SectorNum);
extern FlashReturn_t Flash_Program(u32 ProgramType,u32 Address,u64 Data);


#endif
