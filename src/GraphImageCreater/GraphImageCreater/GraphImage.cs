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

        private void CrunchData(ProcessDataBlock dataBlock)
        {
            int maxGen = 0;
            foreach (ProcessDataLine data in dataBlock.dataLines)
            {
                if (data.genCount > maxGen)
                    maxGen = data.genCount;
            }

            dataBlock.finalLine.finalDist = 0;
            dataBlock.finalLine.timePerGen.Clear();
            dataBlock.finalLine.distancePerGen.Clear();
            dataBlock.finalLine.timePerGen.Capacity = maxGen;
            dataBlock.finalLine.distancePerGen.Capacity = maxGen;
            int[] genCount = new int[maxGen];

            for (int i = 0; i < maxGen; ++i)
            {
                dataBlock.finalLine.timePerGen.Add(new TimeSpan(0));
                dataBlock.finalLine.distancePerGen.Add(0);
                genCount[i] = 0;
            }

            foreach (ProcessDataLine data in dataBlock.dataLines)
            {
                dataBlock.finalLine.finalDist += data.finalDist;
                dataBlock.finalLine.genCount += data.genCount;
                dataBlock.finalLine.nodeCount = data.nodeCount;
                dataBlock.finalLine.totalTime += data.totalTime;

                for (int i = 0; i < data.genCount; ++i)
                {
                    dataBlock.finalLine.timePerGen[i] += data.timePerGen[i];
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
                dataBlock.finalLine.distancePerGen[i] /= genCount[i];
            }
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
            dia.Filter = "Picture|*.json";
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
            dia.Filter = "Picture|*.png";
            dia.CheckFileExists = false;
            if (dia.ShowDialog() != DialogResult.OK)
                return;
            Console.WriteLine(dia.FileName);

            bitmap.Save(dia.FileName, ImageFormat.Png);
        }


    }
}
