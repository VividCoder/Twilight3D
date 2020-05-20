using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VividNet.Game
{
    public class GameLevel
    {

        public string LevelPath = "";
        public Scene.SceneBase Scene;


        public void LoadLevel(string path)
        {

            FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read);
            BinaryReader r = new BinaryReader(fs);

            Scene.LoadScene(r);

            r.Close();
            fs.Close();


        }
        public void SaveLevel(string path)
        {
            FileStream fs = new FileStream(path, FileMode.Create, FileAccess.Write);
            BinaryWriter w = new BinaryWriter(fs);

            Scene.SaveScene(w);

            w.Flush();
            fs.Flush();
            w.Close();
            fs.Close();

        }

    }
}
