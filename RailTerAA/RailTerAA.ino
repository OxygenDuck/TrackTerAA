//main system to control the RailTerAa track layout
//created: Dick van Kalsbeek, 05jun2019
//version:
//05jun2019 initial: 
//- create basic command structure for serial commmands, implementing block detection
//- send command 'db#',returns status as a boolean
//- send command 'dbAll', gets all statusses for all block

#ifndef RAILVAR
#include "variables.h"
#endif
#include "SerialCommands.h"

void setup()
{
  Serial.begin(115200);

  for(int i = 0; i < 9; i++)
  {
    pinMode(doActivateBlockAdee[i], OUTPUT);
    pinMode(diTrainDetectedBlockAdee[i], INPUT);
    if (i < 8)
    {
      pinMode(doTakeTurnTurnoutAdee[i], OUTPUT);
    }
  }

  pinMode(doTurnOutEnableAdee, OUTPUT);
}

void loop()
{
  //testIo();
}

void testIo()
{
  digitalWrite(doActivateBlockAdee[0], HIGH);
  delay(1000);
  digitalWrite(doActivateBlockAdee[0], LOW);
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
