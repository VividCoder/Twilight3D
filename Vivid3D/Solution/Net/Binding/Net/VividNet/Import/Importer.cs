using System;
using System.Collections.Generic;
using System.IO;
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

            VividApp.SetPath(Environment.CurrentDirectory + "\\");

            var i = new FileInfo(path).Directory.FullName + "\\";

            VividApp.SetImpPath(i);


            return new NodeEntity(BindImport.vImportEntityAI(path));


        }

    }
}
