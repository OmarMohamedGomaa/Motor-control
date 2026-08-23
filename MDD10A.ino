#include "MDD10A.h"
#ifndef MDD10A_H
#define MDD10A_H

void MDD10A_init(int DIR, int PWM)
{
    // Enable TIM3 clock
    set(RCC_APB1ENR, 1);

    // DIR  General Purpose Output
    clear(GPIOA_MODER, DIR * 2);
    set(GPIOA_MODER, DIR * 2);

    // PWM  Alternate Function
    clear(GPIOA_MODER, PWM * 2);
    set(GPIOA_MODER, PWM * 2 + 1);

    // set AF2 to TIM3
    clear(GPIO_AFRL, PWM * 4);
    clear(GPIO_AFRL, PWM * 4 + 1);
    clear(GPIO_AFRL, PWM * 4 + 2);
    clear(GPIO_AFRL, PWM * 4 + 3);
    set(GPIO_AFRL, PWM * 4 + 1);   // AF2 = 0010

    // Timer counter frequency = 1 MHz
    TIM3_PSC = 83;

    // 1000 counts = 1 ms period = 1 kHz PWM
    TIM3_ARR = 999;

    // PWM Mode 1 for Channel 3, OC3M = 110
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


void MDD10A_drive(int DIR, int PWM, int speed_in_pwm)
{
    // Stop
    if (speed_in_pwm == 0)
    {
        clear(GPIO_ODR, DIR);

        // PWM = 0
        TIM3_CCR3 = 0;
    }

    // Forward
    else if (speed_in_pwm > 0)
    {
        set(GPIO_ODR, DIR);

        TIM3_CCR3 = speed_in_pwm;
    }

    // Backward
    else
    {
        clear(GPIO_ODR, DIR);

        TIM3_CCR3 = -speed_in_pwm;
    }
}

#endif

