using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GraphImageCreator
{
    class ProcessDataBlock
    {
        public List<string> fileNames;
        public List<ProcessDataLine> dataLines;
        public ProcessDataLine finalLine;
        public ProcessDataLineStd finalLineStd;
        public TimeSpan timePerGenMean;
        public double timePerGenStd;

        public ProcessDataBlock()
        {
            fileNames = new List<string>();
            dataLines = new List<ProcessDataLine>();
            finalLine = new ProcessDataLine();
            finalLineStd = new ProcessDataLineStd();
            timePerGenMean = new TimeSpan(0);
        }
    }
}
