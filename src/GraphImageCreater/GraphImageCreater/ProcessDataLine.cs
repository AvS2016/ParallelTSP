using System;
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


        /*
        [JsonProperty("distancePerGen")]
        public List<double> distancePerGen { get; set; }
        */

        [JsonProperty("finalDist")]
        public string FinalDist { get; set; }


        /*
        [JsonProperty("genCount")]
        public int genCount { get; set; }

        [JsonProperty("nodeCount")]
        public int nodeCount { get; set; }

        [JsonProperty("timePerGen")]
        public List<double> timePerGen { get; set; }

        [JsonProperty("totalTime")]
        public DateTime totalTime { get; set; }
        */

        


        
    }
}
