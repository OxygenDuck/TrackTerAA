//main system to control the RailTerAa track layout
//created: Dick van Kalsbeek, 05jun2019
//version:
//05jun2019 initial: 
//- create basic command structure for serial commmands, implementing block detection
//- send command 'db#',returns status as a boolean
//- send command 'dbAll', gets all statusses for all block

#include "variables.h"
#include "SerialCommands.h"

void setup()
{


}

void loop()
{


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
