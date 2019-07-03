#include "unity.h"
#include "valves.h"
#include <stdio.h>
#include "mock_stm32f4xx_hal.h"
#include "mock_stm32f4xx_hal_gpio.h"

static uint16_t VALVE_STATE = 0;

void writePinCallback(GPIO_TypeDef* GPIOx, uint16_t GPIO_PIN, 
                    GPIO_PinState PinState, int num_calls) {

    if (PinState == GPIO_PIN_SET) {
        VALVE_STATE |= GPIO_PIN;
    } else {
        VALVE_STATE &= ~GPIO_PIN;
    }
}

void setUp(void) {
    VALVE_STATE = 0;
    HAL_GPIO_Init_Ignore();
    HAL_GPIO_WritePin_StubWithCallback(writePinCallback);
    valves_init();
}

void tearDown(void)
{
}

void test_valves_default_state(void) {
    TEST_ASSERT(VALVE_STATE == (0b00000000 << 8)); 
}

void test_valves_all_open(void) {
    valves_set(VALVE_N2_FILL, VALVE_STATE_OPEN);
    valves_set(VALVE_HE_FILL, VALVE_STATE_OPEN);
    valves_set(VALVE_LOX_MAIN, VALVE_STATE_OPEN);

    TEST_ASSERT(VALVE_STATE == (0b00000111 << 8));

    valves_set(VALVE_CH4_MAIN, VALVE_STATE_OPEN);
    valves_set(VALVE_LOX_FILL, VALVE_STATE_OPEN);
    valves_set(VALVE_CH4_FILL, VALVE_STATE_OPEN);
    valves_set(VALVE_LOX_BLEED, VALVE_STATE_OPEN);
    valves_set(VALVE_CH4_BLEED, VALVE_STATE_OPEN);

    TEST_ASSERT(VALVE_STATE == (0b00111111 << 8));
}

void test_valves_all_close(void) {
    valves_set(VALVE_LOX_BLEED, VALVE_STATE_CLOSED);
    valves_set(VALVE_CH4_BLEED, VALVE_STATE_CLOSED);
    TEST_ASSERT(VALVE_STATE == (0b11000000 << 8));
}