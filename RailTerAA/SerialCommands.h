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
        trainDetectedBlock0 = digitalRead(diTrainDetectedBlock0);
        break;
      case 1:
        trainDetectedBlock1 = digitalRead(diTrainDetectedBlock1);
        break;
    }

    Serial.println("Train in block " + m_command + " : " + (String)trainDetectedBlock0);
  }
  else if (a_inputString.indexOf("sb") >= 0 && m_length == 3)
  {
    m_index = a_inputString.indexOf("b");

    //detect which input pin should be read
    //check pin number
    m_command = a_inputString.substring(m_index + 1);

    switch (m_command.toInt())
    {
      case 0:
        switchTrainBlock0Adee = digitalRead(doActivateBlock0Adee);
        break;
      case 1:
        switchTrainBlock1Adee = digitalRead(doActivateBlock1Adee);
        break;
    }
  }
  else
  {
    Serial.println("ERROR: command not recognized");
  }

}
