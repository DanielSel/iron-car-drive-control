void EmergencyBrake() {
  if (!EBS) {
    EBS = 0;
    // Emergency going forward
    if (DesiredSpeed > 0) 
    {
      Timer1.setPwmDuty(pwmPin2, 51); // 100% brake = reverse
      //delay(10);
      //Timer1.setPwmDuty(pwmPin2, 77); //  brake = stop
      
      DesiredSpeed = 0;
     
      Serial.println("Brake: Forward");
      return;
    }

    //////////////////////////
    // brake from neutral
    if (DesiredSpeed == 0) {
      Timer1.setPwmDuty(pwmPin2, 77);
     DesiredSpeed = 0;
      Serial.println("Brake: neutral");
      return;
    }

    // Emergency going backward
    if (DesiredSpeed < 0) 
    {
      Timer1.setPwmDuty(pwmPin2, 100); // engage neutral
      delay(10);
      Timer1.setPwmDuty(pwmPin2, 76); // engage neutral
      DesiredSpeed = 0;
      Serial.println("Brake: Backward");
      return;
    }
  }
}


// for UltraSonic 
int readPing() {
delay(70);
int cm = sonar.ping_cm(); 
if(cm==0 || cm == 5){cm = 250; }
return cm; }


// Move Back for Ultra Sonic. 
// After brake, the car will move backward so it can drive again
// without mB() the Emergency Brake will remain on
//void mB() {
//Timer1.setPwmDuty(pwmPin2, 65);
//}




