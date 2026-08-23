#include "L298N.h"
#include "BTS7960.h"
#include "MDD10A.h"
#define IN1 0
#define IN2 1
#define ENA 2 
#define RPWM 3
#define LPWM 4
#define PWM 5 
#define DIR 6

void setup()
{
  //Dont run multiple drivers at once
  
  L298N_init( IN1,  IN2,  ENA);
  // BTS7960_init( RPWM,  LPWM);
  // MDD10A_init( DIR,  PWM)
}
void loop()
{
  // Forward at half speed
  L298N_drive(IN1, IN2, ENA, 500);
  // delay(2000);

  // Forward at full speed
  L298N_drive(IN1, IN2, ENA, 999);
  // delay(2000);

  // Stop
  L298N_drive(IN1, IN2, ENA, 0);
  // delay(1000);

  // Backward at half speed
  L298N_drive(IN1, IN2, ENA, -500);
  // delay(2000);

  // Stop again before repeating
  L298N_drive(IN1, IN2, ENA, 0);
  // delay(1000);


  // BTS7960_drive(RPWM, LPWM, 500);
  // delay(2000);
  // BTS7960_drive(RPWM, LPWM, 0);
  // delay(1000);
  // BTS7960_drive(RPWM, LPWM, -500);
  // delay(2000);
  // BTS7960_drive(RPWM, LPWM, 0);
  // delay(1000);




}