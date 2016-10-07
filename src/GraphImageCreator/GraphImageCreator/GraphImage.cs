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

namespace GraphImageCreator
{
    
    /// <summary>
    /// Form drawing the needed graph, onclick img saved
    /// </summary>
    public partial class GraphImage : Form
    {

        private List<ProcessDataBlock> dataBlocks;
        private string[] scenarioNames = { "1 Process", "8 Processes", "40 Processes", "80 Processes" };
        private string[] outFileNames = { "dist_per_gen.png" , "final_dist.png", "gen_count.png", "time_per_gen.png" };
        private Chart[] charts;
        private const string MEAN_NAME = "Mean";
        private const string STD_NAME = "Standard Deviation";

        public GraphImage()
        {
            InitializeComponent();
            dataBlocks = new List<ProcessDataBlock>();
            for (int i = 0; i < scenarioNames.Length; ++i)
                dataBlocks.Add(new ProcessDataBlock());
            charts = new Chart[] { chart1, chart2, chart3, chart4 };

            this.WindowState = FormWindowState.Maximized;
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
                    ++genCount[i];
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
            int[] genCount = new int[maxGen];

            int div = dataBlock.dataLines.Count - 1;
            if (div <= 0)
                return;

            for (int i = 0; i < maxGen; ++i)
            {
                dataBlock.finalLineStd.timePerGen.Add(0);
                dataBlock.finalLineStd.distancePerGen.Add(0);
                genCount[i] = 0;
            }

            foreach (ProcessDataLine data in dataBlock.dataLines)
            {
                dataBlock.finalLineStd.finalDist += Varianz(data.finalDist, dataBlock.finalLine.finalDist);
                dataBlock.finalLineStd.totalTime += Varianz(data.totalTime, dataBlock.finalLine.totalTime);
                dataBlock.finalLineStd.genCount += Varianz(data.genCount, dataBlock.finalLine.genCount);

                TimeSpan prev = new TimeSpan(0);
                for (int i = 0; i < data.genCount; ++i)
                {
                    dataBlock.finalLineStd.timePerGen[i] += Varianz(data.timePerGen[i] - prev, dataBlock.finalLine.timePerGen[i]);
                    prev = data.timePerGen[i];
                    dataBlock.finalLineStd.distancePerGen[i] += Varianz(data.distancePerGen[i], dataBlock.finalLine.distancePerGen[i]);
                    ++genCount[i];
                }
            }

            dataBlock.finalLineStd.finalDist = Math.Sqrt(dataBlock.finalLineStd.finalDist / div);
            dataBlock.finalLineStd.totalTime = Math.Sqrt(dataBlock.finalLineStd.totalTime / div);
            dataBlock.finalLineStd.genCount = Math.Sqrt(dataBlock.finalLineStd.genCount / div);
            
            for (int i = 0; i < maxGen; ++i)
            {
                dataBlock.timePerGenStd += Varianz(dataBlock.finalLine.timePerGen[i].TotalSeconds, dataBlock.timePerGenMean.TotalSeconds);

                div = genCount[i] - 1;
                if(div <= 0)
                {
                    dataBlock.finalLineStd.distancePerGen[i] = 0;
                    dataBlock.finalLineStd.timePerGen[i] = 0;
                    continue;
                }

                dataBlock.finalLineStd.distancePerGen[i] = Math.Sqrt(dataBlock.finalLineStd.distancePerGen[i] / div);
                dataBlock.finalLineStd.timePerGen[i] = Math.Sqrt(dataBlock.finalLineStd.timePerGen[i] / div);
            }

            div = maxGen - 1;
            if (div <= 0)
                dataBlock.timePerGenStd = 0;
            else
                dataBlock.timePerGenStd = Math.Sqrt(dataBlock.timePerGenStd / div);
        }

        private void CrunchData(ProcessDataBlock dataBlock)
        {
            if (dataBlock.fileNames.Count == 0)
                return;
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
            string graphName = scenarioNames[id];
            double minErr, maxErr;

            chart1.Series.Add(graphName);
            chart1.Series[graphName].BorderWidth = 3;
            chart1.Series[graphName].ChartType = SeriesChartType.Line;            

            foreach (double val in dataBlock.finalLine.distancePerGen)
                chart1.Series[graphName].Points.AddY(val);

            minErr = dataBlock.finalLine.finalDist - dataBlock.finalLineStd.finalDist;
            maxErr = dataBlock.finalLine.finalDist + dataBlock.finalLineStd.finalDist;
            chart2.Series[MEAN_NAME].Points.AddXY(id, dataBlock.finalLine.finalDist);
            chart2.Series[STD_NAME].Points.AddXY(id, dataBlock.finalLine.finalDist, minErr, maxErr);

            minErr = dataBlock.finalLine.genCount - dataBlock.finalLineStd.genCount;
            maxErr = dataBlock.finalLine.genCount + dataBlock.finalLineStd.genCount;
            chart3.Series[MEAN_NAME].Points.AddXY(id, dataBlock.finalLine.genCount);
            chart3.Series[STD_NAME].Points.AddXY(id, dataBlock.finalLine.genCount, minErr, maxErr);

            minErr = dataBlock.timePerGenMean.TotalSeconds - dataBlock.timePerGenStd;
            maxErr = dataBlock.timePerGenMean.TotalSeconds + dataBlock.timePerGenStd;
            chart4.Series[MEAN_NAME].Points.AddXY(id, dataBlock.timePerGenMean.TotalSeconds);
            chart4.Series[STD_NAME].Points.AddXY(id, dataBlock.timePerGenMean.TotalSeconds, minErr, maxErr);
        }

        private void InitBarChart(Chart chart)
        {
            chart.Series.Add(MEAN_NAME);
            chart.Series.Add(STD_NAME);
            chart.Series[MEAN_NAME].ChartType = SeriesChartType.Column;
            chart.Series[STD_NAME].ChartType = SeriesChartType.ErrorBar;
            //chart2.Series[MEAN_NAME].Color = Color.Blue;
            chart.Series[STD_NAME].Color = Color.DarkOrange;
            chart.ChartAreas["ChartArea"].AxisX.Interval = 0;
            chart.ChartAreas["ChartArea"].AxisX.Maximum = 4;

            for(int i = 0; i < scenarioNames.Length; ++i)
                chart.ChartAreas["ChartArea"].AxisX.CustomLabels.Add(i + -0.5, i + 0.5, scenarioNames[i]);
        }

        private void CrunchButton_Click(object sender, EventArgs e)
        {
            int id = 0;
            chart1.Series.Clear();
            chart2.Series.Clear();
            chart3.Series.Clear();
            chart4.Series.Clear();

            InitBarChart(chart2);
            InitBarChart(chart3);
            InitBarChart(chart4);

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
            FolderBrowserDialog dia = new FolderBrowserDialog();
            if (dia.ShowDialog() != DialogResult.OK)
                return;

            string[] files01 = Directory.GetFiles(dia.SelectedPath, "01_*.json", System.IO.SearchOption.AllDirectories);
            string[] files08 = Directory.GetFiles(dia.SelectedPath, "08_*.json", System.IO.SearchOption.AllDirectories);
            string[] files40 = Directory.GetFiles(dia.SelectedPath, "40_*.json", System.IO.SearchOption.AllDirectories);
            string[] files80 = Directory.GetFiles(dia.SelectedPath, "80_*.json", System.IO.SearchOption.AllDirectories);

            dataBlocks[0].fileNames = files01.OfType<string>().ToList();
            dataBlocks[1].fileNames = files08.OfType<string>().ToList();
            dataBlocks[2].fileNames = files40.OfType<string>().ToList();
            dataBlocks[3].fileNames = files80.OfType<string>().ToList();
        }

        private void saveAsImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dia = new FolderBrowserDialog();
            if (dia.ShowDialog() != DialogResult.OK)
                return;
            
            for(int i = 0; i < charts.Length; ++i)
            {
                string fileName = dia.SelectedPath + "\\" + outFileNames[i];
                charts[i].SaveImage(fileName, ChartImageFormat.Png);
            }
        }
    }
}
