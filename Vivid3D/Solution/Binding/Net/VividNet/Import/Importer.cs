using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Bind;
using VividNet.Scene.Nodes;

namespace VividNet.Import
{
    public class Importer
    {

        public static NodeEntity ImportEntityAI(string path)
        {

            return new NodeEntity(BindImport.vImportEntityAI(path));


        }

    }
}
