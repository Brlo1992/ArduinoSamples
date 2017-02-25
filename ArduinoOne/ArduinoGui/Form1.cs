using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ArduinoDriver.SerialProtocol;
using ArduinoUploader.Hardware;

namespace ArduinoGui {
    public partial class Form1 : Form
    {
        private readonly SerialPort _port = new SerialPort();
        public Form1() {
            InitializeComponent();
            _port.BaudRate = 9600;
            _port.PortName = "COM5";
            _port.Open();
        }

        private void button1_Click(object sender, EventArgs e) {
            while (true)
            {
                var data = _port.ReadLine();
                textBox1.Text = data;
            }
        }
    }
}
