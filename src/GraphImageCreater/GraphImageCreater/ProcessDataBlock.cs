using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GraphImageCreater
{
    class ProcessDataBlock
    {
        public List<string> fileNames;
        public List<ProcessDataLine> dataLines;
        public ProcessDataLine finalLine;

        public ProcessDataBlock()
        {
            fileNames = new List<string>();
            dataLines = new List<ProcessDataLine>();
            finalLine = new ProcessDataLine();
        }
    }
}
