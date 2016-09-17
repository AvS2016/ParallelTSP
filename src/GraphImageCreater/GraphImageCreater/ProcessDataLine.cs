﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace GraphImageCreater
{
    /// <summary>
    /// Singel ProcessData - 1 Line = 1 TSP Solution
    /// </summary>
    class ProcessDataLine
    {

        public List<double> distancePerGen { get; set; }
        public double finalDist { get; set; }
        public int genCount { get; set; }
        public int nodeCount { get; set; }
        public List<double> timePerGen { get; set; }
        public DateTime totalTime { get; set; }
       
    }
}
