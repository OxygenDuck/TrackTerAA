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
  Serial.println("rail ter aa started");

  for(int i = 0; i <3; i++){
    pinMode(trigPin[i], OUTPUT);
    pinMode(echoPin[i], INPUT);
  }
  for(int i = 0; i < 9; i++)
  {
    pinMode(doActivateBlockAdee[i], OUTPUT);
    digitalWrite(doActivateBlockAdee[i], HIGH);
    pinMode(diTrainDetectedBlockAdee[i], INPUT);
    if (i < 8)
    {
      pinMode(doTakeTurnTurnoutAdee[i], OUTPUT);
      digitalWrite(doTakeTurnTurnoutAdee[i], LOW);
      delay(250);
      digitalWrite(doTakeTurnTurnoutAdee[i], HIGH);    
      delay(250);
      digitalWrite(doActivateBlockAdee[i], LOW);
      delay(250);
      digitalWrite(doActivateBlockAdee[i], HIGH);
    }
  }
  pinMode(aoSpeedOnTrackPjan, OUTPUT);
  pinMode(baseTrackValue, OUTPUT);
  pinMode(doTurnOutEnableAdee, OUTPUT);
  digitalWrite(doTurnOutEnableAdee, HIGH);
}

void loop()
{
  //testIo();
  //readHalSensor();
  //  Serial.println("  ");
  //  delay(500);
  //readUltraSonicSensor();
  //activateBlockOnTrainDetect();
  //delay(500);
}

void testIo()
{
  //digitalWrite(doActivateBlockAdee[0], HIGH);
//  delay(1000);
//  digitalWrite(doActivateBlockAdee[0], LOW);
//  delay(1000);
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
