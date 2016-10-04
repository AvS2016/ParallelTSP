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
using Newtonsoft.Json.Linq;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Globalization;

namespace GraphImageCreater
{
    
    /// <summary>
    /// Form drawing the needed graph, onclick img saved
    /// </summary>
    public partial class GraphImage : Form
    {

        private List<string> fileNames;
        private List<ProcessDataLine> dataLines;

        public GraphImage()
        {
            InitializeComponent();
        }

        // benötigt zum laufen, downnload!
        // System.Windows.Forms.DataVisualization.Charting;
        // https://www.microsoft.com/en-us/download/details.aspx?id=14422



        private ProcessDataLine ParseDataFile(string file)
        {
            ProcessDataLine statObj = new ProcessDataLine();

            using (StreamReader r = new StreamReader(file))
            {
                string jsonStr = r.ReadToEnd();
                dynamic dynStats = JsonConvert.DeserializeObject(jsonStr);

                statObj.finalDist = dynStats.finalDist;
                statObj.genCount = dynStats.genCount;
                statObj.nodeCount = dynStats.nodeCount;
                statObj.totalTime = TimeSpan.Parse(dynStats.totalTime);
                statObj.distancePerGen = dynStats.distancePerGen;

                statObj.timePerGen.Capacity = dynStats.timePerGen.Count;
                foreach (string i in dynStats.timePerGen)
                    statObj.timePerGen.Add(TimeSpan.Parse(dynStats.timePerGen));
            }

            return statObj;
        }

        private void CrunchButton_Click(object sender, EventArgs e)
        {
            dataLines.Clear();
            dataLines.Capacity = fileNames.Count;

            foreach (string f in fileNames)
                dataLines.Add(ParseDataFile(f));

        }

        private void selectFilesToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void saveAsImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = new Bitmap(this.Size.Width, this.Size.Height);
            Graphics g = Graphics.FromImage(bitmap);
            g.CopyFromScreen(new Point(this.DesktopLocation.X, this.DesktopLocation.Y), new Point(0, 0), this.Size);

            OpenFileDialog dia = new OpenFileDialog();
            dia.Filter = "Picture|*.png";
            dia.CheckFileExists = false;
            if (dia.ShowDialog() != DialogResult.OK)
                return;
            Console.WriteLine(dia.FileName);

            bitmap.Save(dia.FileName, ImageFormat.Png);
        }

        private void GraphImage_Load(object sender, EventArgs e)
        {
            // Getting Data...

            /* dynamic file access
            string dir = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            string file = dir + @"\sample_data\01_Proc_Machines_0.json";
            */



                // using dynamic no proper mapping is working ... setting up manual mode :/
                /*dynamic data = JObject.Parse(json);

                //distancePerGen
                string tmp = data["distancePerGen"].ToString();

                    tmp = tmp.Replace('[', ' ');
                    tmp = tmp.Replace(']', ' ');
                    tmp = tmp.Replace("\r\n", String.Empty);

                    foreach (string s in tmp.Split(','))
                    {
                        file.distancePerGen.Add(double.Parse(s, CultureInfo.InvariantCulture));
                    }

                file.finalDist = Convert.ToDouble(data["finalDist"]); ;
                file.genCount = Convert.ToInt32(data["genCount"]);
                file.nodeCount = Convert.ToInt32(data["nodeCount"]);

                // timePerGen
                tmp = data["timePerGen"].ToString();

                    tmp = tmp.Replace('[', ' ');
                    tmp = tmp.Replace(']', ' ');
                    tmp = tmp.Replace('\"', ' ');
                    tmp = tmp.Replace("\r\n", String.Empty);              

                    foreach (string s in tmp.Split(','))
                    { 
                        file.timePerGen.Add(TimeSpan.Parse(s));
                    }

                tmp = data["totalTime"];

                file.totalTime = TimeSpan.Parse(tmp);


                // Alle Json in list<obj>
                // Todo: werte mitteln
                // paramater on they fly beim konvertieren berechnen

                */
            }
            /*
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


        
        }*/
    }
}
