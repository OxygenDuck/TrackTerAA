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

unsigned long previousMillis = 0;
const long interval = 25; 

void setup()
{
  Serial.begin(115200);
  Serial.println("rail ter aa started");
  pinMode(aoSpeedOnTrackPjan, OUTPUT);
  pinMode(baseTrackValueAdee, OUTPUT);
  pinMode(doTurnOutEnableAdee, OUTPUT);

  for(int i = 0; i <3; i++){
    pinMode(trigPinAdee[i], OUTPUT);
    pinMode(echoPinAdee[i], INPUT);
  }
  for(int i = 0; i < 9; i++)
  {
    pinMode(doActivateBlockAdee[i], OUTPUT);
    digitalWrite(doActivateBlockAdee[i], HIGH);
    pinMode(doTakeTurnTurnoutAdee[i], OUTPUT);
    pinMode(diTrainDetectedBlockAdee[i], INPUT);
    digitalWrite(doTurnOutEnableAdee, LOW);
    if (i < 8)
    {
      digitalWrite(doTakeTurnTurnoutAdee[i], LOW);
      delay(250);
      digitalWrite(doTakeTurnTurnoutAdee[i], HIGH);   
      delay(250);
      digitalWrite(doActivateBlockAdee[i], LOW);
      delay(250);
      digitalWrite(doActivateBlockAdee[i], HIGH);
    }
    digitalWrite(doTurnOutEnableAdee, HIGH); 
  }
}

void loop()
{
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    // save the last time the delay fired
    previousMillis = currentMillis;
    readHalSensor(); 
    //Serial.println((String)currentMillis);
    readUltraSonicSensor();
  }
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
