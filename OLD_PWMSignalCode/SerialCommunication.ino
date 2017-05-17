#define SERIAL_INPUT_DELAY 1

void serialM() { // Serial Monitor
  //read via serial
  Serial.print(DesiredSpeed); // speed
  Serial.print(';');
  Serial.print(angle); // angle
  Serial.print(';');
  Serial.print(uS / US_ROUNDTRIP_CM); // UltraSonic
  Serial.print(';');
  Serial.print(EBS); //Brake
  Serial.println(';');
}

// Receiving
bool receiveMessage() 
{
  if (Serial.available()>0) 
  {
    message_1 = Serial.readStringUntil(';'); // speed
    message_2 = Serial.readStringUntil(';'); //angle
    //Serial.println(message_1);
    //Serial.println(message_2);

    if (message_1[0] == 'b' )  //emergency brake
      // Example: b;10;
    {
      //Serial.println("Get shwifty");
      EmergencyBrake();

    }

    if (message_1 != NULL && message_2 != NULL)   //no message recieved
    {
      clear_serial_input_buffer(); 
      return true;
    }
  }
  //}
  return false; // no new message
}

void clear_serial_input_buffer(){
  while(Serial.available()>0){
     char t = Serial.read(); 
  }
  //hardcore solution; not tested
  //Serial.end();
  //Serial.begin(19200); 
  
}
