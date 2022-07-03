#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "diag/Trace.h"

#include "SCB.h"

#define SCB_VTOR 	   				*((volatile u32*)0xE000ED08)
#define SCB_AIRCR 	   				*((volatile u32*)0xE000ED0C)

#define SCB_AIRCR_SYSRESETREQ		(u32)0x4u

#define VECTKEY						(u32)0x5FA0004u
#define VECTKEY_CLEAR				(u32)0xFFFF0000u

void SCB_ChangeINTVECTadd(u32 Add)
{
	SCB_VTOR = Add;
}
void SCB_RestSys(void)
{
	SCB_AIRCR = VECTKEY;
	//SCB_AIRCR |= SCB_AIRCR;
}
