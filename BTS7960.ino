#include "BTS7960.h"
#ifndef BTS7960_H
#define BTS7960_H

void BTS7960_init(int RPWM, int LPWM)
{
    // Enable TIM3 clock
    set(RCC_APB1ENR, 1);

    // set GPIO pins to AFRL
    clear(GPIOA_MODER, RPWM * 2);
    set(GPIOA_MODER, RPWM * 2 + 1);


    clear(GPIOA_MODER, LPWM * 2);
    set(GPIOA_MODER, LPWM * 2 + 1);

    // set AF2 (TIM3) for both pins
    clear(GPIO_AFRL, LPWM * 4);
    clear(GPIO_AFRL, LPWM * 4 + 1);
    clear(GPIO_AFRL, LPWM * 4 + 2);
    clear(GPIO_AFRL, LPWM * 4 + 3);

    clear(GPIO_AFRL, RPWM * 4);
    clear(GPIO_AFRL, RPWM * 4 + 1);
    clear(GPIO_AFRL, RPWM * 4 + 2);
    clear(GPIO_AFRL, RPWM * 4 + 3);

    set(GPIO_AFRL, RPWM * 4 + 1);  // AF2 = 0010
    set(GPIO_AFRL, LPWM * 4 + 1);

    // Timer base: 1 MHz counter, 1 kHz PWM
    TIM3_PSC = 83;
    TIM3_ARR = 999;

    // set channel 3 to PWM mode 
    clear(TIM3_CCMR2, 4);
    set(TIM3_CCMR2, 5);
    set(TIM3_CCMR2, 6);

    // Enable preload for Channel 3
    set(TIM3_CCMR2, 3);   

    // set channel 4 to PWM mode 
    clear(TIM3_CCMR2, 12);
    set(TIM3_CCMR2, 13);
    set(TIM3_CCMR2, 14);

    // Enable preload for Channel 4
    set(TIM3_CCMR2, 11);  

    // Enable both channel outputs
    set(TIM3_CCER, 8);    // CC3E
    set(TIM3_CCER, 12);   // CC4E

    // Start TIM3
    set(TIM3_CR1, 0);
}


void BTS7960_drive(int RPWM, int LPWM, int speed_in_pwm)
{
    // Stop
    if (speed_in_pwm == 0)
    {
        TIM3_CCR3 = 0;
        TIM3_CCR4 = 0;
    }

    // Forward
    else if (speed_in_pwm > 0)
    {
        TIM3_CCR3 = speed_in_pwm;
        TIM3_CCR4 = 0;
    }

    // Backward
    else
    {
        TIM3_CCR3 = 0;
        TIM3_CCR4 = -speed_in_pwm;
    }
}

#endif