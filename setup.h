
  #define clear(REG, BIT) ((REG) &= ~(1U << (BIT)))// set bit to 0
  #define set(REG, BIT) ((REG) |= (1U << (BIT))) //set bit to 1

  #define TIM3_BASE 0x4000040
  #define TIM3_CCR3 *((volatile unsigned int *)(TIM3_BASE + 0x3C)) //channel 3 count compare reg
  #define TIM3_CCR4 *((volatile unsigned int *)(TIM3_BASE + 0x40)) //channel 4 count compare reg
  #define TIM3_PSC *((volatile unsigned int *)(TIM3_BASE + 0x28)) //TIM3 counting speed
  #define TIM3_ARR *((volatile unsigned int *)(TIM3_BASE + 0x2C)) //TIM3 frequency
  #define TIM3_CCMR2 *((volatile unsigned int *)(TIM3_BASE + 0x1C)) //TIM3 channel mode reg
  #define TIM3_CCER *((volatile unsigned int *)(TIM3_BASE + 0x20)) //TIM3 channel enable reg
  #define TIM3_CR1 *((volatile unsigned int *)(TIM3_BASE + 0x00)) //timer enable 


  #define RCC_BASE 0x40023800
  #define RCC_APB1ENR *((volatile unsigned int *)(RCC_BASE + 0x40)) // connecting TIM to a clock

  
  #define MODER_OFFSET 0x00000000
  #define GPIOA_MODER *((volatile unsigned int *)(0x40020000 + MODER_OFFSET)) // GPIO mode setter


  #define ODR_OFFSET 0x00000014
  #define GPIO_ODR *((volatile unsigned int *)(0x40020000 + ODR_OFFSET)) // output on hte pin


  #define AFRL_OFFSET 0x00000020
  #define GPIO_AFRL *((volatile unsigned int *)(0x40020000 + AFRL_OFFSET)) // Alternate function mode
