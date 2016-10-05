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

        private List<ProcessDataBlock> dataBlocks;
        private string[] graphNames = { "1 Process", "8 Processes" };

        public GraphImage()
        {
            InitializeComponent();
            dataBlocks = new List<ProcessDataBlock>();
        }

        // benötigt zum laufen, downnload!
        // System.Windows.Forms.DataVisualization.Charting;
        // https://www.microsoft.com/en-us/download/details.aspx?id=14422

        private ProcessDataLine ParseDataFile(string file)
        {
            ProcessDataLine statObj = new ProcessDataLine();

            using (StreamReader r = new StreamReader(file))
            {
                var jtr = new JsonTextReader(r);
                var jsonSerializer = new JsonSerializer();
                dynamic dynStats = jsonSerializer.Deserialize(jtr);

                //string jsonStr = r.ReadToEnd();
                //dynamic dynStats = JsonConvert.DeserializeObject(jsonStr);

                statObj.finalDist = dynStats.finalDist;
                statObj.genCount = dynStats.genCount;
                statObj.nodeCount = dynStats.nodeCount;
                statObj.totalTime = TimeSpan.Parse(dynStats.totalTime.ToString());
                statObj.distancePerGen = dynStats.distancePerGen.ToObject<List<double>>();

                statObj.timePerGen.Capacity = dynStats.timePerGen.Count;
                foreach (string timeStr in dynStats.timePerGen)
                    statObj.timePerGen.Add(TimeSpan.Parse(timeStr.ToString()));
            }

            return statObj;
        }

        private void CalcMeanData(ProcessDataBlock dataBlock, int maxGen)
        {
            // initialize finalLine
            dataBlock.finalLine.finalDist = 0;
            dataBlock.finalLine.totalTime = new TimeSpan(0);
            dataBlock.finalLine.genCount = 0;
            dataBlock.finalLine.nodeCount = 0;
            dataBlock.finalLine.timePerGen.Clear();
            dataBlock.finalLine.distancePerGen.Clear();
            dataBlock.finalLine.timePerGen.Capacity = maxGen;
            dataBlock.finalLine.distancePerGen.Capacity = maxGen;
            dataBlock.timePerGenMean = new TimeSpan(0);
            int[] genCount = new int[maxGen];

            for (int i = 0; i < maxGen; ++i)
            {
                dataBlock.finalLine.timePerGen.Add(new TimeSpan(0));
                dataBlock.finalLine.distancePerGen.Add(0);
                genCount[i] = 0;
            }

            foreach (ProcessDataLine data in dataBlock.dataLines)
            {
                // sum up data
                dataBlock.finalLine.finalDist += data.finalDist;
                dataBlock.finalLine.genCount += data.genCount;
                dataBlock.finalLine.nodeCount = data.nodeCount;
                dataBlock.finalLine.totalTime += data.totalTime;

                TimeSpan prev = new TimeSpan(0);
                for (int i = 0; i < data.genCount; ++i)
                {
                    dataBlock.finalLine.timePerGen[i] += (data.timePerGen[i] - prev);
                    prev = data.timePerGen[i];
                    dataBlock.finalLine.distancePerGen[i] += data.distancePerGen[i];
                    genCount[i]++;
                }
            }

            dataBlock.finalLine.finalDist /= dataBlock.dataLines.Count;
            dataBlock.finalLine.genCount /= dataBlock.dataLines.Count;
            dataBlock.finalLine.totalTime = new TimeSpan(dataBlock.finalLine.totalTime.Ticks / dataBlock.dataLines.Count);

            for (int i = 0; i < maxGen; ++i)
            {
                dataBlock.finalLine.timePerGen[i] = new TimeSpan(dataBlock.finalLine.timePerGen[i].Ticks / genCount[i]);
                dataBlock.timePerGenMean += dataBlock.finalLine.timePerGen[i];
                dataBlock.finalLine.distancePerGen[i] /= genCount[i];
            }

            dataBlock.timePerGenMean = new TimeSpan(dataBlock.timePerGenMean.Ticks / maxGen);
        }

        private double Varianz(double val, double mean)
        {
            return Math.Pow(val - mean, 2);
        }

        private double Varianz(TimeSpan val, TimeSpan mean)
        {
            return Math.Pow(val.Ticks - mean.Ticks, 2);
        }

        private void CalcStdDeviation(ProcessDataBlock dataBlock, int maxGen)
        {
            // initialize finalLineStd
            dataBlock.finalLineStd.finalDist = 0;
            dataBlock.finalLineStd.totalTime = 0;
            dataBlock.finalLineStd.genCount = 0;
            dataBlock.finalLineStd.timePerGen.Clear();
            dataBlock.finalLineStd.distancePerGen.Clear();
            dataBlock.finalLineStd.timePerGen.Capacity = maxGen;
            dataBlock.finalLineStd.distancePerGen.Capacity = maxGen;
            dataBlock.timePerGenStd = 0;

            for (int i = 0; i < maxGen; ++i)
            {
                dataBlock.finalLineStd.timePerGen.Add(0);
                dataBlock.finalLineStd.distancePerGen.Add(0);
            }

            foreach (ProcessDataLine data in dataBlock.dataLines)
            {
                dataBlock.finalLineStd.finalDist += Varianz(data.finalDist, dataBlock.finalLine.finalDist);
                dataBlock.finalLineStd.totalTime += Varianz(data.totalTime, dataBlock.finalLine.totalTime);
                dataBlock.finalLineStd.genCount += Varianz(data.genCount, dataBlock.finalLine.genCount);

                for(int i = 0; i < data.genCount; ++i)
                {
                    dataBlock.finalLineStd.distancePerGen[i] += Varianz(data.distancePerGen[i], dataBlock.finalLine.distancePerGen[i]);
                    dataBlock.finalLineStd.timePerGen[i] += Varianz(data.timePerGen[i], dataBlock.finalLine.timePerGen[i]);
                }
            }

            dataBlock.finalLineStd.finalDist = Math.Sqrt(dataBlock.finalLineStd.finalDist);
            dataBlock.finalLineStd.totalTime = Math.Sqrt(dataBlock.finalLineStd.totalTime);
            dataBlock.finalLineStd.genCount = Math.Sqrt(dataBlock.finalLineStd.genCount);

            for (int i = 0; i < maxGen; ++i)
            {
                dataBlock.finalLineStd.distancePerGen[i] = Math.Sqrt(dataBlock.finalLineStd.distancePerGen[i]);
                dataBlock.finalLineStd.timePerGen[i] = Math.Sqrt(dataBlock.finalLineStd.timePerGen[i]);

                dataBlock.timePerGenStd += Varianz(dataBlock.finalLine.timePerGen[i], dataBlock.timePerGenMean);
            }

            dataBlock.timePerGenStd = Math.Sqrt(dataBlock.timePerGenStd);
        }

        private void CrunchData(ProcessDataBlock dataBlock)
        {
            // find maximum count of generations
            int maxGen = 0;
            foreach (ProcessDataLine data in dataBlock.dataLines)
            {
                if (data.genCount > maxGen)
                    maxGen = (int)data.genCount;
            }

            CalcMeanData(dataBlock, maxGen);
            CalcStdDeviation(dataBlock, maxGen);
        }

        private void LoadData(ProcessDataBlock dataBlock)
        {
            dataBlock.dataLines.Clear();
            dataBlock.dataLines.Capacity = dataBlock.fileNames.Count;

            foreach (string f in dataBlock.fileNames)
                dataBlock.dataLines.Add(ParseDataFile(f));
        }

        private void DrawData(ProcessDataBlock dataBlock, int id)
        {
            string graphName = graphNames[id];
            
            chart1.Series.Add(graphName);
            chart1.Series[graphName].ChartType = SeriesChartType.Line;            

            foreach (double val in dataBlock.finalLine.distancePerGen)
                chart1.Series[graphName].Points.AddY(val);

            chart2.Series.Add(graphName);
            chart2.Series[graphName].ChartType = SeriesChartType.Bar;
            chart2.Series[graphName].Points.AddY(dataBlock.finalLine.finalDist);

            chart3.Series.Add(graphName);
            chart3.Series[graphName].ChartType = SeriesChartType.Bar;
            chart3.Series[graphName].Points.AddY(dataBlock.finalLine.genCount);

            chart4.Series.Add(graphName);
            chart4.Series[graphName].ChartType = SeriesChartType.Bar;
            chart4.Series[graphName].Points.AddY(dataBlock.timePerGenMean.Ticks);
        }

        private void CrunchButton_Click(object sender, EventArgs e)
        {
            int id = 0;
            chart1.Series.Clear();
            foreach (ProcessDataBlock dataBlock in dataBlocks)
            {
                LoadData(dataBlock);
                CrunchData(dataBlock);
                DrawData(dataBlock, id);
                id++;
            }
        }

        private void selectFilesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog dia = new OpenFileDialog();
            dia.Filter = "JSON|*.json";
            dia.CheckFileExists = false;
            dia.Multiselect = true;
            if (dia.ShowDialog() != DialogResult.OK)
                return;

            dataBlocks.Add(new GraphImageCreater.ProcessDataBlock());
            dataBlocks.Last().fileNames = dia.FileNames.OfType<string>().ToList();
        }

        private void saveAsImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = new Bitmap(this.Size.Width, this.Size.Height);
            Graphics g = Graphics.FromImage(bitmap);
            g.CopyFromScreen(new Point(this.DesktopLocation.X, this.DesktopLocation.Y), new Point(0, 0), this.Size);

            OpenFileDialog dia = new OpenFileDialog();
            dia.Filter = "Portable Network Graphics|*.png";
            dia.CheckFileExists = false;
            if (dia.ShowDialog() != DialogResult.OK)
                return;
            Console.WriteLine(dia.FileName);

            bitmap.Save(dia.FileName, ImageFormat.Png);
        }
    }
}
