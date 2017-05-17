int p = 0; // correct reverse movement
void motor(int DesiredSpeed) 
{
  speedValue = map(DesiredSpeed, speedMax, SpeedMin, MaxPwm, MinPwm ); // mapping 
  
  if (DesiredSpeed == 0) // when DiseredSpeed is 0 (neutral)
  {
   Timer1.setPwmDuty(pwmPin2, speedValue ); // Pwm Signal (77)
     p = 0;
  }

  if (DesiredSpeed > 0) //going forward
  {
    Serial.println(speedValue); // Serial Monitor
    Timer1.setPwmDuty(pwmPin2, speedValue );
    //delay(500);
    p = 1;
  }

  if (DesiredSpeed < 0) { // reverse
  Serial.println(p);
    // case 1: already in reverse
    if (p == -1) {
      Timer1.setPwmDuty(pwmPin2, speedValue ); // p is negative!
      Serial.println("Rückwärts P==-1");
      p = -1;
    }

    // case 2: going from forwards to backwards
    if (p == 1) {
      Serial.println("p==1");
      // Start go backwards command sequence
      Timer1.setPwmDuty(pwmPin2, 51); // reverse -> Brake State
      delay(150);
      Timer1.setPwmDuty(pwmPin2, 77); // Neutral -> N2 State
      delay(150);
      Timer1.setPwmDuty(pwmPin2, speedValue ); // Backwards with correct power -> Backward State
      p = -1;
      
    }

    // case 3: N1/N2 - not sure which neutral, safe strategy (Forward->Brake->N2->Backwards)
    if (p ==  0) {
      p = -1;
      Timer1.setPwmDuty(pwmPin2, 78); // forward state
      delay(100);
      Timer1.setPwmDuty(pwmPin2, 51); // reverse -> Brake State
      delay(100);
      Timer1.setPwmDuty(pwmPin2, 77); // Neutral -> N2 State
      delay(100);
      Timer1.setPwmDuty(pwmPin2, speedValue );
      
    }

  }
}

// Steering Angle
void steering(float angle) {
  if (angle > 15) {
    angle = 15;
  }
  if (angle < -15) {
    angle = -15;
  }

  float DutySteering = 77 + angle * 30 / 17; // Setting angle
  Timer1.setPwmDuty(pwmPin1, DutySteering);
}

