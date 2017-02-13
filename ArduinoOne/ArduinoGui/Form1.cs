using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ArduinoDriver.SerialProtocol;
using ArduinoUploader.Hardware;

namespace ArduinoGui {
    public partial class Form1 : Form
    {
        private ArduinoDriver.ArduinoDriver driver;
        public Form1() {
            InitializeComponent();
            driver = new ArduinoDriver.ArduinoDriver(ArduinoModel.UnoR3);
        }

        private void button1_Click(object sender, EventArgs e) {
            var request = new DigitalReadRequest();
            driver.Send()
        }
    }
}
