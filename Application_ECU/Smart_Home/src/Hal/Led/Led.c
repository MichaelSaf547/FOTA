



#include "../../Lib/Std_types.h"
#include "../../Lib/Bit_utils.h"
#include "../../Mcal/Gpio/Gpio.h"
#include "Led.h"
#include "Led_cfg.h"

extern Led_cfg_t Leds[NUM_OF_LEDS];

extern Led_tenuErrorStatus Led_enuInit()
{

	Led_tenuErrorStatus Loc_enuRetrunStatus = Led_enuOk;

	gpioErrorStatus_t Loc_enuGpio = gpio_enuOk;

	gpioPinCfg_t Loc_strLed;

	u16 Loc_u16ForCounter = NUM_OF_LEDS;
	
	for(Loc_u16ForCounter = NUM_OF_LEDS; Loc_u16ForCounter > 0; Loc_u16ForCounter--)
	{
		if(Leds[Loc_u16ForCounter - 1].Led_OType == OTYPE_PP)
		{
			Loc_strLed.mode = GPIO_PIN_OUT_PP;
		}
		else 
		{
			Loc_strLed.mode = GPIO_PIN_OUT_OD;
		}
		
		Loc_strLed.speed = GPIO_PIN_SPEED2;
		Loc_strLed.pin = Leds[Loc_u16ForCounter - 1].Led_u8PinNum;
		Loc_strLed.port = Leds[Loc_u16ForCounter - 1].Led_u8Port;
		
		Loc_enuGpio = gpio_initPin(& Loc_strLed);

		if(Loc_enuGpio != gpio_enuOk)
		{
			Loc_enuRetrunStatus = Led_enuNotOk;
		}
	}

	return Loc_enuRetrunStatus;
}


extern Led_tenuErrorStatus Led_enuSetState(u16 Copy_u16LedNum, u8 Copy_LedState)
{
	Led_tenuErrorStatus Loc_enuRetrunStatus = Led_enuOk;
	gpioErrorStatus_t Loc_enuGpio = gpio_setPinValue(Leds[Copy_u16LedNum].Led_u8Port,\
						Leds[Copy_u16LedNum].Led_u8PinNum,\
						Leds[Copy_u16LedNum].Led_u8ActiveState ^ Copy_LedState);

	if(Loc_enuGpio == gpio_enuOk)
	{
		//Do Nothing
	}
	else
	{
		Loc_enuRetrunStatus = Led_enuNotOk;
	}

	return Loc_enuRetrunStatus;
}
