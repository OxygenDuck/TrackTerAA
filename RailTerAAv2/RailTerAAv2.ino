//main system to control the RailTerAa track layout
//created: Dick van Kalsbeek, 05jun2019
//version:
//05jun2019 initial:
//- create basic command structure for serial commmands, implementing block detection
//- send command 'db#',returns status as a boolean
//- send command 'dbAll', gets all statusses for all block

//#include "variables.h"
//#include "SerialCommands.h"
//#include "variables.h"
//#include "SerialCommands.h"

//io
int aoSpeedOnTrackAdee = 2;

int doActivateBlock0Adee = 0; //sb0x on ; sb0o off
int doActivateBlock1Adee = 1;
int doActivateBlock2Adee = 2;
int doActivateBlock3Adee = 3;
int doActivateBlock4Adee = 4;
int doActivateBlock5Adee = 6;
int doActivateBlock6Adee = 7;
int doActivateBlock7Adee = 8;
int doActivateBlock8Adee = 9;

int diTrainDetectedBlock0Adee = 22;//db0 returns true or false
int diTrainDetectedBlock1Adee = 23;
int diTrainDetectedBlock2Adee = 24;
int diTrainDetectedBlock3Adee = 25;
int diTrainDetectedBlock4Adee = 26;
int diTrainDetectedBlock5Adee = 27;
int diTrainDetectedBlock6Adee = 28;
int diTrainDetectedBlock7Adee = 29;
int diTrainDetectedBlock8Adee = 30;

int doTakeTurnTurnout0Adee = 7;//31;//sw0x straight sw0o turn
int doTakeTurnTurnout1Adee = 33;
int doTakeTurnTurnout2Adee = 35;
int doTakeTurnTurnout3Adee = 37;
int doTakeTurnTurnout4Adee = 39;
int doTakeTurnTurnout5Adee = 41;
int doTakeTurnTurnout6Adee = 43;
int doTakeTurnTurnout7Adee = 45;

int doStraightAheadTurnout0Adee = 32;
int doStraightAheadTurnout1Adee = 34;
int doStraightAheadTurnout2Adee = 36;
int doStraightAheadTurnout3Adee = 38;
int doStraightAheadTurnout4Adee = 40;
int doStraightAheadTurnout5Adee = 42;
int doStraightAheadTurnout6Adee = 44;
int doStraightAheadTurnout7Adee = 46;

int doTurnOutEnableAdee = 47;


//globals
bool trainDetectedBlock0 = false;
bool trainDetectedBlock1 = false;

bool switchTrainBlock0Adee = false;
bool switchTrainBlock1Adee = false;
bool trainDetected = false;

void setup()
{
  Serial.begin(115200);
  
  pinMode(doTakeTurnTurnout0Adee, OUTPUT);
  //pinMode(doTurnOutEnableAdee, OUTPUT);
}

void loop()
{
  //testIo();
}

void testIo()
{
  digitalWrite(doActivateBlock0Adee, HIGH);
  delay(1000);
  digitalWrite(doActivateBlock0Adee, LOW);
  delay(1000);
}

void serialEvent()//ISR
{
  String m_inputString;
  char m_inChar;

  while (Serial.available())
  {
    m_inChar = (char)Serial.read();

    m_inputString = m_inputString + m_inChar;
  }

  //Serial.println("command is: " + m_inputString);

  HandleSerialEvent(m_inputString);
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
    m_index = a_inputString.indexOf("b");

    //detect which input pin should be read
    //check pin number
    m_command = a_inputString.substring(m_index + 1);

    Serial.println("checking block nr: " + m_command);

    //read actual hardware
    switch (m_command.toInt())
    {
      case 0:
        trainDetected = digitalRead(diTrainDetectedBlock0Adee);
        break;
      case 1:
        trainDetected = digitalRead(diTrainDetectedBlock1Adee);
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

  if (a_inputString.indexOf("sw") >= 0 && m_length == 4)
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
