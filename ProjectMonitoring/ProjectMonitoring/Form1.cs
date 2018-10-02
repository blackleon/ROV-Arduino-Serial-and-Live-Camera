using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using AForge.Video;
using AForge.Video.DirectShow;
using System.IO.Ports;
using System.IO;

namespace ProjectMonitoring
{
    public partial class Form1 : Form
    {
        public FilterInfoCollection webcam;
        public VideoCaptureDevice cam;
        public SerialPort serialPort1;
        public List<String> ports;
        public List<String> telemetry;
        public Random r;

        public int zoomMode = -1;

        public Form1()
        {
            InitializeComponent();
            updateCAM();
            updatePORTS();

            this.KeyPreview = true;
            this.KeyPress += new KeyPressEventHandler(Form1_KeyPress);
        }

        private void updatePORTS()
        {
            telemetry = new List<String>();
            ports = new List<string>();
            ports.Clear();
            ports.AddRange(SerialPort.GetPortNames());
            comboBox2.Items.Clear();
            foreach (String s in ports)
            {
                if (!comboBox2.Items.Contains(s))
                {
                    comboBox2.Items.Add(s);
                }
            }
            //comboBox1.SelectedIndex = 0;
            r = new Random();
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            try
            {
                if (serialPort1.IsOpen)
                {
                    string line = serialPort1.ReadLine();
                    this.BeginInvoke(new LineReceivedEvent(LineReceived), line);
                }
            }
            catch{}
        }

        private delegate void LineReceivedEvent(string line);
        private void LineReceived(string line)
        {
            try
            {
                if (serialPort1.IsOpen)
                {
                    String[] degerler = line.Split();
                    textBox1.Text = degerler[0];
                    textBox2.Text = degerler[1];
                    textBox4.Text = degerler[2];
                    textBox3.Text = degerler[3];
                    textBox6.Text = degerler[4];
                    textBox5.Text = degerler[5];
                    label8.Text = degerler[6];
                    label9.Text = degerler[7];
                }
            }
            catch {}
        }
        
        public void readSerial()
        {
            try
            {
                serialPort1 = new SerialPort();
                serialPort1.BaudRate = 19200;
                if (comboBox2.SelectedItem != null)
                {
                    serialPort1.PortName = comboBox2.SelectedItem.ToString();
                    if(!serialPort1.IsOpen)
                    {
                        try
                        {
                            serialPort1.Open();
                        }
                        catch { }
                    }
                    serialPort1.DataReceived += serialPort1_DataReceived;
                }
            }
            catch (ArgumentException e) {}
        }

        public void writeSerial(String s)
        {
            try
            {
                serialPort1.Write(s);
            }
            catch {}
        }

        private void button2_Click(object sender, EventArgs e)
        {
            updatePORTS();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            readSerial();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            updateCAM();
        }

        private void updateCAM()
        {
            webcam = new FilterInfoCollection(FilterCategory.VideoInputDevice);
            comboBox1.Items.Clear();
            foreach (FilterInfo VideoCaptureDevice in webcam)
            {
                comboBox1.Items.Add(VideoCaptureDevice.Name);
            }
            comboBox1.SelectedIndex = -1;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(cam!=null)
            {
                cam.Stop();
            }
            if (comboBox1.SelectedIndex!=-1)
            {
                cam = new VideoCaptureDevice(webcam[comboBox1.SelectedIndex].MonikerString);
                cam.NewFrame += new NewFrameEventHandler(cam_NewFrame);
                cam.Start();
            }
        }
        
        public Bitmap CropBitmap(Bitmap bitmap, int cropX, int cropY, int cropWidth, int cropHeight)
        {
            Rectangle rect = new Rectangle(cropX*cropWidth, cropY*cropHeight, cropWidth, cropHeight);
            Bitmap cropped = bitmap.Clone(rect, bitmap.PixelFormat);
            return cropped;
        }

        void cam_NewFrame(object sender, NewFrameEventArgs eventArgs)
        {
            try
            {
                Bitmap bit = (Bitmap)eventArgs.Frame.Clone();
                int width = bit.Width;
                int height = bit.Height;
                int rate = height / width;

                //bit.RotateFlip(RotateFlipType.RotateNoneFlipX);

                if(zoomMode != -1)
                {
                    bit = CropBitmap(bit, zoomMode % 3, zoomMode / 3, width / 3, height / 3);
                }

                bit = new Bitmap(bit, new Size(pictureBox1.Width, pictureBox1.Height));
                pictureBox1.Image = bit;
            }catch(ArgumentException a)
            {
                if (cam != null && cam.IsRunning)
                {
                    cam.Stop();
                }
            }            
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if(cam!=null && cam.IsRunning)
            {
                cam.Stop();
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            updateCAM();
        }

        /* private void button7_Click(object sender, EventArgs e)
        {
            writeSerial();
        }*/

        private void button6_Click_1(object sender, EventArgs e)
        {
            if(serialPort1!= null)
            {
                serialPort1.Close();
            }
        }
        

        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {
            if(serialPort1!=null && serialPort1.IsOpen)
            {
                try
                {
                    writeSerial(e.KeyChar.ToString().ToUpper());
                }
                catch { }
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            zoomMode = 3;
        }

        private void button8_Click(object sender, EventArgs e)
        {
            zoomMode = 1;
        }

        private void button9_Click(object sender, EventArgs e)
        {
            zoomMode = 2;
        }

        private void button12_Click(object sender, EventArgs e)
        {
            zoomMode = 0;
        }

        private void button11_Click(object sender, EventArgs e)
        {
            zoomMode = 4;
        }

        private void button10_Click(object sender, EventArgs e)
        {
            zoomMode = 5;
        }

        private void button15_Click(object sender, EventArgs e)
        {
            zoomMode = 6;
        }

        private void button14_Click(object sender, EventArgs e)
        {
            zoomMode = 7;
        }

        private void button13_Click(object sender, EventArgs e)
        {
            zoomMode = 8;
        }

        private void button16_Click(object sender, EventArgs e)
        {
            zoomMode = -1;
        }
    }
}
