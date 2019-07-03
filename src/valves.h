#ifndef VALVES_H
#define VALVES_H

#include "stm32f4xx_hal.h"

#define VALVE_GPIO_PORT  GPIOD

#define VALVE_N2_FILL    GPIO_PIN_8
#define VALVE_HE_FILL    GPIO_PIN_9
#define VALVE_LOX_MAIN   GPIO_PIN_10 
#define VALVE_CH4_MAIN   GPIO_PIN_11
#define VALVE_LOX_FILL   GPIO_PIN_12
#define VALVE_CH4_FILL   GPIO_PIN_13
#define VALVE_LOX_BLEED  GPIO_PIN_14
#define VALVE_CH4_BLEED  GPIO_PIN_15

#define VALVE_STATE_CLOSED 0
#define VALVE_STATE_OPEN   1

void valves_init();
void valves_set(uint16_t valve, int value);

#endif