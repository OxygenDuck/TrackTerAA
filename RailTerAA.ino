//main system to control the RailTerAa track layout
//created: Dick van Kalsbeek, 05jun2019
//version:
//05jun2019 initial: 
//- create basic command structure for serial commmands, implementing block detection
//- send command 'db#',returns status as a boolean
//- send command 'dbAll', gets all statusses for all block

//io
int diTrainDetectedBlock0 = 22;
int diTrainDetectedBlock1 = 23;

//globals
bool trainDetectedBlock0 = false;
bool trainDetectedBlock1 = false;

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

void HandleSerialEvent(String a_inputString)
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

	}
	else
	{
		Serial.println("ERROR: command not recognized");
	}

}
