#include "variables.h"

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
    m_index = a_inputString.indexOf("b");

    //detect which input pin should be read
    //check pin number
    m_command = a_inputString.substring(m_index + 1);

    Serial.println("checking block nr: " + m_command);

    //read actual hardware
    switch (m_command.toInt())
    {
      case 0:
        trainDetected = digitalRead(diTrainDetectedBlock0);
        break;
      case 1:
        trainDetected = digitalRead(diTrainDetectedBlock1);
        break;
    }

    //Serial.println("Train in block " + m_command + " detected : " + (String)trainDetected);
  }
  else if (a_inputString.indexOf("sb") >= 0 && m_length == 4)
  {
    m_index = a_inputString.indexOf("b");

    //detect which input pin should be read
    //check pin number
    m_command = a_inputString.substring(m_index + 1);
    m_value = a_inputString.substring(m_index + 2);

    switch (m_command.toInt())
    {
      case 0:
        if (m_value == "x")
        {
          digitalWrite(doActivateBlock0Adee, HIGH);
        }
        else
        {
          digitalWrite(doActivateBlock0Adee, LOW);
        }
        break;
      case 1:
        if (m_value == "x")
        {
          digitalWrite(doActivateBlock1Adee, HIGH);
        }
        else
        {
          digitalWrite(doActivateBlock1Adee, LOW);
        }
        break;
    }
  }

  if (a_inputString.indexOf("sw") >= 0 && m_length == 3)
  {
    m_index  = a_inputString.indexOf("w");

    m_command = a_inputString.substring(m_index + 1);
    m_value = a_inputString.substring(m_index + 2);

    Serial.println("switching switch nr: " + m_command);

    digitalWrite(doTurnOutEnableAdee, HIGH);
    delay(500);

    //read actual hardware
    switch (m_command.toInt())
    {
      case 0:
        if (m_value == "x")
        {
          digitalWrite(doTakeTurnTurnout0Adee, HIGH);
        }
        else
        {
          digitalWrite(doTakeTurnTurnout0Adee, LOW);
        }
        break;
      case 1:
        break;
    }

    digitalWrite(doTurnOutEnableAdee, LOW);
  }
  else
  {
    Serial.println("ERROR: command not recognized");
  }

}
