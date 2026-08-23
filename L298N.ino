#include "L298N.h"

#ifndef L298N_h
#define L298N_h
void L298N_init(int IN1, int IN2, int ENA)
{

    // Enable TIM3 clock
    set(RCC_APB1ENR, 1);


    // IN1 -> General Purpose Output
    clear(GPIOA_MODER, IN1 * 2);
    set(GPIOA_MODER, IN1 * 2);


    // IN2 -> General Purpose Output
    clear(GPIOA_MODER, IN2 * 2);
    set(GPIOA_MODER, IN2 * 2);


    // ENA -> Alternate Function
    clear(GPIOA_MODER, ENA * 2);
    set(GPIOA_MODER, ENA * 2 + 1);


    // ENA AF2 (TIM3)
    // Clear the 4 AFR bits first
    clear(GPIO_AFRL, ENA * 4);
    clear(GPIO_AFRL, ENA * 4 + 1);
    clear(GPIO_AFRL, ENA * 4 + 2);
    clear(GPIO_AFRL, ENA * 4 + 3);

    // AF2 = 0010
    set(GPIO_AFRL, ENA * 4 + 1);

    // Timer counter frequency = 1 MHz
    // Assuming TIM3 clock = 84 MHz
    TIM3_PSC = 83;


    // 1000 counts = 1 ms period = 1 kHz PWM
    TIM3_ARR = 999;


    // PWM Mode 1 for Channel 3
    // OC3M = 110
    clear(TIM3_CCMR2, 4);
    set(TIM3_CCMR2, 5);
    set(TIM3_CCMR2, 6);


    // Enable preload for Channel 3
    set(TIM3_CCMR2, 3);


    // Enable TIM3 Channel 3 output
    set(TIM3_CCER, 8);


    // Start TIM3
    set(TIM3_CR1, 0);
}


void L298N_drive(int IN1, int IN2, int ENA, int speed_in_pwm)
{

    // Stop
    if (speed_in_pwm == 0)
    {
        clear(GPIO_ODR, IN1);
        clear(GPIO_ODR, IN2);
    }

    // Forward
    else if (speed_in_pwm > 0)
    {
        set(GPIO_ODR, IN1);
        clear(GPIO_ODR, IN2);

        TIM3_CCR3 = speed_in_pwm;
    }

    // Backward
    else
    {
        clear(GPIO_ODR, IN1);
        set(GPIO_ODR, IN2);
        TIM3_CCR3 = -speed_in_pwm;
    }
}

#endif