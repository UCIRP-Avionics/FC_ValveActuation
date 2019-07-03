#include "valves.h"

void valves_init() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    HAL_GPIO_WritePin(
        VALVE_GPIO_PORT,
        VALVE_N2_FILL | VALVE_HE_FILL |
        VALVE_LOX_MAIN | VALVE_CH4_MAIN |
        VALVE_LOX_FILL | VALVE_CH4_FILL |
        VALVE_LOX_BLEED | VALVE_CH4_BLEED,
        GPIO_PIN_RESET
    );

    GPIO_InitStruct.Pin = (VALVE_N2_FILL | VALVE_HE_FILL 
                            | VALVE_LOX_MAIN | VALVE_CH4_MAIN 
                            | VALVE_LOX_FILL | VALVE_CH4_FILL 
                            | VALVE_LOX_BLEED | VALVE_CH4_BLEED);
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void valves_set(uint16_t valve, int value) {
    int gpio_set = value;
    if (valve == VALVE_LOX_BLEED || valve == VALVE_CH4_BLEED) {
        gpio_set = !value;
    }

    HAL_GPIO_WritePin(VALVE_GPIO_PORT, valve, 
            gpio_set ? GPIO_PIN_SET : GPIO_PIN_RESET);
}