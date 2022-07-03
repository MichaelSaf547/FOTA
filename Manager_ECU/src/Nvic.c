/*
 * Nvic.c
 *
 *  Created on: July 1, 2022
 *      Author: FOTA || ITI_42
 */
#include"Bits_utils.h"
#include"Nvic.h"
#include"Nvic_cfg.h"



pu32 NVIC_ISER = (pu32)0xE000E100;
pu32 NVIC_ICER = (pu32)0xE000E180;
pu32 NVIC_ISPR = (pu32)0xE000E200;
pu32 NVIC_ICPR = (pu32)0xE000E280;
pu32 NVIC_IABR = (pu32)0xE000E300;
pu32 NVIC_IPR = (pu32)0xE000E400;
#define NVIC_STIR	*((pu32) 0xE000EF00U)
#define SCB_AIRCR	*((pu32) 0xE000ED0CU)
#define VECTKEY		0x05FA0000
#define PRIGROUP	0x00000700


/*
 * Purpose : Enable Peripheral Interrupt , this function takes 1 argument and return void
 *
 * Arguments : Peripheral name (IRQx) x : 0-->239
 *
 * Return : void
 */
void Nvic_EnableIRQ(u16 Irq_type)
{
	u8 bit_num = Irq_type%32;
	u8 reg = Irq_type/32;
	SET_BIT(NVIC_ISER[reg],bit_num);
}

/*
 * Purpose : Disable Peripheral Interrupt , this function takes 1 argument and return void
 *
 * Arguments : Peripheral name (IRQx) x : 0-->239
 *
 * Return : void
 */
void Nvic_DisableIRQ(u16 Irq_type)
{
	u8 bit_num = Irq_type%32;
	u8 reg = Irq_type/32;
	SET_BIT(NVIC_ICER[reg],bit_num);
}

/*
 * Purpose : Set pending of peripheral interrupt by software , this function takes 1 argument and
 * 			 return void
 *
 * Arguments : Peripheral name (IRQx) x : 0-->239
 *
 * Return : void
 */
void Nvic_SetPendingIRQ(u16 Irq_type)
{
	u8 bit_num = Irq_type%32;
	u8 reg = Irq_type/32;
	SET_BIT(NVIC_ISPR[reg],bit_num);
}

/*
 * Purpose : Set software interrupt , this function takes number of peripheral and return void
 *
 * Argument : u16 IRQ(x) x : 0-->239
 *
 * Return : void
 */
void Nvic_SetSWInterrupt(u16 Irq_type)
{
	NVIC_STIR = Irq_type;
}

/*
 * Purpose : Clear pending of peripheral interrupt , this function takes 1 argument and
 * 			 return void
 *
 * Arguments : Peripheral name (IRQx) x : 0-->239
 *
 * Return : void
 */
void Nvic_ClearPendingIRQ(u16 Irq_type)
{
	u8 bit_num = Irq_type%32;
	u8 reg = Irq_type/32;
	SET_BIT(NVIC_ICPR[reg],bit_num);
}

/*
 * Purpose : Get active status of peripheral interrupt , this function takes 1 argument and return Active status
 *
 * Arguments : Peripheral name (IRQx) x : 0-->239
 *
 * Return : Active status : Active , NotActive
 */
u8 Nvic_GetActiveStatusTRQ(u16 Irq_type)
{
	u8 bit_num = Irq_type%32;
	u8 reg = Irq_type/32;
	u8 state=GET_BIT(NVIC_IABR[reg],bit_num);
	return state;
}

/*
 * Purpose : set priority of peripheral , this function takes 2 arguments and return void
 *
 * Arguments : Peripheral name (IRQx) x : 0-->239
 * 			   Priority
 *
 * Return : void
 */
void Nvic_SetPriorityIRQ(u16 Irq_type,u32 priority)
{
	u16 reg = Irq_type/4;
	u16 bit_num = Irq_type%4;
	NVIC_IPR[reg] = priority << (bit_num*8);
}

/*
 * Purpose : Set subgroup priority of peripheral , this function takes 2 arguments and return void
 *
 * Arguments : Peripheral name (IRQx) x : 0-->239
 * 			   Subgroup priority
 *
 * Return : void
 */
void Nvic_SetSubgroupPriority(u8 subgroup)
{
//	u32 temp = SCB_AIRCR;
//	temp &= ~(VECTKEY);
//	temp |= VECTKEY;
//	SCB_AIRCR = temp;
//	temp &= ~(PRIGROUP);
//	SCB_AIRCR = temp;
//	SCB_AIRCR |= subgroup<<8;
	SCB_AIRCR |= (VECTKEY | (subgroup<<8));

}

/*
 * Purpose : Encode Priority , this function takes the priority and subgroup priority and number of bits
 * 			 used in subgroup and it return the value of register
 *
 * Arguments : u8 subgroup , u8 priority, u8 number of subgroup bits
 *
 * Return u8 : value of priority register
 */
u8 Nvic_EncodePriority(u8 subgroup , u8 priority , u8 num_of_bits)
{
	u8 value=0;
	value = (priority << num_of_bits) | subgroup;
	value &= (0xFFFF)<<PRIORITY_BITS_IMPLEMENTED;
	return value;
}

/*
 * Purpose : Enable all Interrupts
 *
 * Arguments : void
 *
 * Return : void
 */
void Nvic_EnableInterupts()
{
	asm("CPSIE i");
}

/*
 * Purpose : Disable all Interrupts
 *
 * Arguments : void
 *
 * Return : void
 */
void Nvic_DisableInterupts()
{
	asm("CPSID i");
}

/*
 * Purpose : Enable all Interrupts with fault
 *
 * Arguments : void
 *
 * Return : void
 */
void Nvic_EnableInterupts_Faults()
{
	asm("CPSIE f");
}

/*
 * Purpose : Disable all Interrupts with fault
 *
 * Arguments : void
 *
 * Return : void
 */
void Nvic_DisableInterupts_Faults()
{
	asm("CPSID f");
}

/*
 * Purpose : Disable Interrupts with higher priority
 *
 * Arguments : u8 Priority
 *
 * Return : void
 */
void Nvic_DisableLowerPriority(u8 Priority)
{
	//no thing
	u8 temp= Priority;
	temp++;

}



