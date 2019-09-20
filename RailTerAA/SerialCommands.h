#ifndef RAILVAR
#include "variables.h"
#endif

int trainSpeed = 0;
int HalSensorTriggered;

void handleMotor(int a_outputValue){
  int m_outputValueInA;
  int m_outputValueInB;

  m_outputValueInA = a_outputValue;
  m_outputValueInB = 254 - a_outputValue;

  analogWrite(aoSpeedOnTrackPjan, m_outputValueInA);
  analogWrite(baseTrackValue, m_outputValueInB);

  trainSpeed = a_outputValue;
}

void readUltraSonicSensor(){
  long duration;
  int distance;
  for(int i = 0; i < 3; i++){
     // Clears the trigPin
    digitalWrite(trigPin[i], LOW);
    delayMicroseconds(2);
  
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin[i], LOW);
  
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin[i], HIGH);
  
    // Calculating the distance
    distance = (duration/2) / 29.1;
  
    // Prints the distance on the Serial Monitor
    Serial.println((String)trigPin[i] + " has a Distance of: "  + (String)distance);
  }
}

void readHalSensor(){
  for(int i = 0; i < 9; i++){
    int halSensor = digitalRead(diTrainDetectedBlockAdee[i]);
    HalSensorTriggered = halSensor;
    if(halSensor == LOW){
    // print out the state of the hal sensor:
    //Serial.println("sensor " + (String)diTrainDetectedBlockAdee[i] + " has been triggered");
    //delay(1);
    }else{
      //Serial.println("nothing");
    }
  }
}

void activateBlockOnTrainDetect(){
  if(trainSpeed < 127){
    for (int i = 0; i < 9; i++){
      if(HalSensorTriggered == diTrainDetectedBlockAdee[i]){
        if(i < 8){
          digitalWrite(doActivateBlockAdee[i+1], LOW);
          digitalWrite(doActivateBlockAdee[i-1], HIGH);
        }
        if(i == 8){
            digitalWrite(doActivateBlockAdee[0], HIGH);
        }
        if(i == 0){
          digitalWrite(doActivateBlockAdee[8], LOW);
        }
      }else{
        digitalWrite(doActivateBlockAdee[i], HIGH);
      }
    }
  }
  if(trainSpeed > 127){
    for (int i = 0; i < 9; i++){
      if(HalSensorTriggered == diTrainDetectedBlockAdee[i]){
        if(i < 8){
          digitalWrite(doActivateBlockAdee[i-1], LOW);
          digitalWrite(doActivateBlockAdee[i+1], HIGH);
        }
        if(i == 8){
            digitalWrite(doActivateBlockAdee[0], LOW);
        }
        if(i == 0){
          digitalWrite(doActivateBlockAdee[8], HIGH);
        }
      }else{
        digitalWrite(doActivateBlockAdee[i], HIGH);
      }
    }
  }
}

void HandleSerialEvent(String a_inputString) //Main Function
{
  String m_command;
  String m_value;
  int m_index;
  int m_length;

  m_length = a_inputString.length();

  Serial.println("Command is: " + a_inputString + " > length is : " + (String)m_length);

  //detect which command
  if (a_inputString.indexOf("db") >= 0 && m_length == 3)
  {
    bool trainInBlock = false;
    m_index = a_inputString.indexOf("b");

    //detect which input pin should be read
    //check pin number
    m_command = a_inputString.substring(m_index + 1, m_index + 2);

    Serial.println("checking block nr: " + m_command);

    trainInBlock = digitalRead(diTrainDetectedBlockAdee[m_command.toInt()]);

    Serial.println("Train in block " + m_command + " detected : " + (String)trainInBlock);
  }
  else if (a_inputString.indexOf("sb") >= 0 && m_length == 4)
  {
    m_index = a_inputString.indexOf("b");

    //detect which input pin should be read
    //check pin number
    m_command = a_inputString.substring(m_index + 1, m_index + 2);
    m_value = a_inputString.substring(m_index + 2);

    if (m_value == "x")
    {
      digitalWrite(doActivateBlockAdee[m_command.toInt()], LOW);
    }
    else if(m_value == "y")
    {
      digitalWrite(doActivateBlockAdee[m_command.toInt()], HIGH);
    }else{
      Serial.println("stop wrong command");
    }
  }

  else if (a_inputString.indexOf("sw") >= 0 && m_length == 4)
  {
    digitalWrite(doTurnOutEnableAdee, LOW);
    
    m_index  = a_inputString.indexOf("w");

    m_command = a_inputString.substring(m_index + 1, m_index + 2);
    m_value = a_inputString.substring(m_index + 2);

    Serial.println("switching switch nr: " + m_command);
    Serial.println(m_command.toInt(), HEX);

    delay(250);

    if (m_value == "x")
    {
      digitalWrite(doTakeTurnTurnoutAdee[m_command.toInt()], HIGH);
      digitalWrite(doTurnOutEnableAdee, LOW);
    }
    else if(m_value == "y")
    {
      digitalWrite(doTakeTurnTurnoutAdee[m_command.toInt()], LOW);
      digitalWrite(doTurnOutEnableAdee, LOW);
    }else{
      Serial.println("stop wrong command");
    }
    delay(250);
    digitalWrite(doTurnOutEnableAdee, HIGH);
  }
  
  else if (a_inputString.indexOf("sp") >= 0 && m_length == 5 || a_inputString.indexOf("sp") >= 0 && m_length == 4)
  {   
    m_index  = a_inputString.indexOf("p");

    m_command = a_inputString.substring(m_index + 1);

    Serial.println("switching speed to: " + m_command);
    Serial.println(m_command.toInt(), HEX);

    handleMotor(m_command.toInt());
    delay(250);
    Serial.println(m_command);
  }
  else
  {
    Serial.println("ERROR: command not recognized");
  }
}


//void switchSetTrack(){
//  
//}
