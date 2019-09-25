using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace RailTerAaControllerPjan
{
    public partial class form1 : Form
    {
        SerialPort serialPortPjan = new SerialPort();
        Button[] blocksPjan;
        Button[] turnoutsPjan;
        Panel[] halSensorsPjan;
        bool[] blockState = new bool[9];
        bool[] turnoutState = new bool[7];

        public form1()
        {
            InitializeComponent();
            serialPortPjan.PortName = "COM4"; //TODO: DETECT ACTUAL SERIAL PORT;
            serialPortPjan.BaudRate = 115200;
            serialPortPjan.Open();

            blocksPjan = new Button[9] { btnBlock1Pjan, btnBlock2Pjan, btnBlock3Pjan, btnBlock4Pjan, btnBlock5Pjan, btnBlock6Pjan, btnBlock7Pjan, btnBlock8Pjan, btnBlock9Pjan };
            turnoutsPjan = new Button[7] { btnTurnout1Pjan, btnTurnout2Pjan, btnTurnout3Pjan, btnTurnout4Pjan, btnTurnout5Pjan, btnTurnout6Pjan, btnTurnout7Pjan };
            halSensorsPjan = new Panel[9] { pnlSensor1Pjan, pnlSensor2Pjan, pnlSensor3Pjan, pnlSensor4Pjan, pnlSensor5Pjan, pnlSensor6Pjan, pnlSensor7Pjan, pnlSensor8Pjan, pnlSensor9Pjan };
            SetBlockColors();

            tmrSerialReadPjan.Enabled = true;
        }

        private void WriteSerial(string input)
        {
            //Write input to arduino serial event
            serialPortPjan.Write(input);
        }

        private void SwitchBlock(object sender, EventArgs e)
        {
            Button origin = null;
            foreach (Button button in blocksPjan)
            {
                if (sender == button)
                {
                    origin = button;
                    break;
                }
            }

            int block = Convert.ToInt16(origin.Tag);
            //Set Value and Make string for Serial Write
            string inputStringPjan = "sb" + block;
            if (!blockState[block])
            {
                inputStringPjan += "x";
                blockState[block] = true;
            }
            else
            {
                inputStringPjan += "y";
                blockState[block] = false;
            }

            //Write to Arduino
            Thread.Sleep(250);
            WriteSerial(inputStringPjan);

            //update button layout
            SetBlockColors();
        }

        private void SwitchTurnout(object sender, EventArgs e)
        {
            Button origin = null;
            foreach (Button button in turnoutsPjan)
            {
                if (sender == button)
                {
                    origin = button;
                    break;
                }
            }

            int turnout = Convert.ToInt16(origin.Tag);
            //Set Value and Make string for Serial Write
            string inputStringPjan = "sw" + turnout;
            if (!turnoutState[turnout])
            {
                inputStringPjan += "x";
                turnoutState[turnout] = true;
            }
            else
            {
                inputStringPjan += "y";
                turnoutState[turnout] = false;
            }

            //Write to Arduino
            Thread.Sleep(250);
            WriteSerial(inputStringPjan);

            //update button layout
            SetBlockColors();
        }

        private void SetBlockColors()
        {
            for (int i = 0; i < blocksPjan.Length; i++)
            {
                if (blockState[i])
                {
                    blocksPjan[i].BackColor = Color.Yellow;
                }
                else
                {
                    blocksPjan[i].BackColor = Color.LightGray;
                }

                if (i <= 6)
                {
                    if (turnoutState[i])
                    {
                        turnoutsPjan[i].BackColor = Color.Yellow;
                    }
                    else
                    {
                        turnoutsPjan[i].BackColor = Color.LightGray;
                    }
                }
            }
        }

        private void tbrSpeedPjan_ValueChanged(object sender, EventArgs e)
        {
            serialPortPjan.Write("sp" + tbrSpeedPjan.Value.ToString());
        }

        //private void tmrSerialReadPjan_Tick(object sender, EventArgs e)
        //{
        //    rtbSerialMonitorPjan.Text += serialPortPjan.ReadExisting();

        //    if (serialPortPjan.ReadLine() == "Led turned on")
        //    {
        //        halSensorsPjan[0].BackColor = Color.Red;
        //    }
        //    else if (serialPortPjan.ReadLine() == "Led turned off")
        //    {
        //        halSensorsPjan[0].BackColor = Color.DarkGray;
        //    }
        //    //for (int i = 0; i < 9; i++)
        //    //{
        //    //    serialPortPjan.Write("db" + i);
        //    //    Thread.Sleep(10);
        //    //    if (serialPortPjan.ReadExisting() == "Train in block " + i + " detected : " + 1)
        //    //    {
        //    //        halSensorsPjan[i].BackColor = Color.Red;
        //    //    }
        //    //    else
        //    //    {
        //    //        halSensorsPjan[i].BackColor = Color.DarkGray;
        //    //    }
        //    //}
        //}
    }
}
