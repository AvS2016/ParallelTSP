using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;
using System.Drawing.Imaging;
using System.IO;
using Newtonsoft.Json;

namespace GraphImageCreater
{
    
    /// <summary>
    /// Form drawing the needed graph, onclick img saved
    /// </summary>
    public partial class GraphImage : Form
    {
        public GraphImage()
        {
            InitializeComponent();
        }

        private void chart1_Click(object sender, EventArgs e)
        {

            //screen on click
            using (Bitmap bitmap = new Bitmap(this.Size.Width, this.Size.Height))
            {
                using (Graphics g = Graphics.FromImage(bitmap))
                {
                    g.CopyFromScreen(new Point(this.DesktopLocation.X, this.DesktopLocation.Y), new Point(0, 0), this.Size);
                }

                bitmap.Save(@"C:\test.png", ImageFormat.Png);
            }
        }


        // benötigt zum laufen, downnload!
        // System.Windows.Forms.DataVisualization.Charting;
        // https://www.microsoft.com/en-us/download/details.aspx?id=14422



        private void GraphImage_Load(object sender, EventArgs e)
        {
            // Getting Data...
            string dir = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            string file = dir + @"\sample_data\01_Proc_Machines_0.json";
            ProcessDataLine test = new ProcessDataLine();

            using (StreamReader r = new StreamReader(@"C:\Users\User\Documents\visual studio 2015\Projects\GraphImageCreater\GraphImageCreater\sample_data\test.json"))
            {
                string json = r.ReadToEnd();
                //List<ProcessDataLine> items = JsonConvert.DeserializeObject<List<ProcessDataLine>>(json);
                
                test = JsonConvert.DeserializeObject<ProcessDataLine>(json);
            

                // test


            // Alle Json in list<obj>
            // werte mitteln
            // paramater on they fly beim konvertieren berechnen


            chart1.Series.Add(test.FinalDist);
            // Bug some here Dezerializer into null
            // prolly help http://stackoverflow.com/questions/15915503/net-newtonsoft-json-deserialize-map-to-a-different-property-name

            // Drawing...
            chart1.Series.Add("Balken");
            chart1.Series.Add("Area");

            //Ausssehen festlegen
            chart1.Series["Balken"].ChartType = SeriesChartType.Column;
            chart1.Series["Linien"].ChartType = SeriesChartType.Line;
            chart1.Series["Area"].ChartType = SeriesChartType.Area;

            //Zufällige Werte generieren
            Random random = new Random();

            for (int pointIndex = 0; pointIndex < 10; pointIndex++)
            {

                chart1.Series["Area"].Points.AddY(random.Next(20, 50));
            }

            for (int pointIndex = 0; pointIndex < 10; pointIndex++)
            {

                chart1.Series["Balken"].Points.AddY(random.Next(50, 100));
            }

            for (int pointIndex = 0; pointIndex < 10; pointIndex++)
            {

                chart1.Series["Linien"].Points.AddY(random.Next(70, 100));
            }



        }
    }
}
