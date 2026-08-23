#include "setup.h"
void L298N_init(int IN1, int IN2, int ENA);
void L298N_drive(int IN1, int IN2, int ENA, int speed_in_pwm);