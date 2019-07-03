# Valve to pin mapping:

    PD8 ->   N2_FILL
    PD9 ->   HE_FILL
    PD10 ->  LOX_MAIN
    PD11 ->  CH4_MAIN
    PD12 ->  LOX_FILL
    PD13 ->  CH4_FILL
    PD14 ->  LOX_BLEED
    PD15 ->  CH4_BLEED
    
# Usage
Call `valves_init()` to initialize everything to a default state. Then, call `valves_set(uinit16_t valve, int state)` to set a valve open or closed. The library automatically takes care of inverting the bleed valve output.

# Example
    int main(void)  {
      SystemClock_Config();
      HAL_Init();


      __HAL_RCC_GPIOD_CLK_ENABLE();
      __HAL_RCC_GPIOA_CLK_ENABLE();
      __HAL_RCC_GPIOC_CLK_DISABLE();

      valves_init();

      while (1)  {
          valves_set(VALVE_CH4_MAIN, VALVE_STATE_CLOSED);
          HAL_Delay(5);
          valves_set(VALVE_CH4_MAIN, VALVE_STATE_OPEN);
          HAL_Delay(5);
      }
    }
