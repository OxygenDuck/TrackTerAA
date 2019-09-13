#ifndef RAILVAR
#include "variables.h"
#endif

void handleMotor(int a_outputValue){
  int m_outputValueInA;
  int m_outputValueInB;

  m_outputValueInA = a_outputValue;
  m_outputValueInB = 254 - a_outputValue;

  analogWrite(aoSpeedOnTrackPjan, m_outputValueInA);
  analogWrite(baseTrackValue, m_outputValueInB);
}

void readHalSensor(){
  for(int i = 0; i < 9; i++){
    int halSensor = digitalRead(diTrainDetectedBlockAdee[i]);
    if(halSensor == LOW){
    // print out the state of the hal sensor:
    Serial.println("sensor " + (String)diTrainDetectedBlockAdee[i] + " has been triggered");
    //delay(1);
    }else{
      Serial.println("nothing");
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
    digitalWrite(doTurnOutEnableAdee, HIGH);

    
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
      digitalWrite(doTurnOutEnableAdee, HIGH);
    }else{
      Serial.println("stop wrong command");
    }
    delay(250);
    digitalWrite(doTurnOutEnableAdee, LOW);
  }
  
  else if (a_inputString.indexOf("sp") >= 0 && m_length == 5)
  {   
    m_index  = a_inputString.indexOf("p");

    m_command = a_inputString.substring(m_index + 1);

    Serial.println("switching speed to: " + m_command);
    Serial.println(m_command.toInt(), HEX);

    handleMotor(m_command.toInt());
    delay(250);
  }
  else
  {
    Serial.println("ERROR: command not recognized");
  }
}


//void switchSetTrack(){
//  
//}
