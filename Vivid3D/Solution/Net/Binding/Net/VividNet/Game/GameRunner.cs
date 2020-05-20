using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace VividNet.Game
{
    public class GameRunner
    {

        public Scene.SceneBase Scene;
        public GameLevel ActiveLevel;

        public void LoadScripts()
        {

            Scene.LoadScripts();

        }
        public void Begin()
        {

        }

        public void Run()
        {
            Run_T = new Thread(new ThreadStart(Run_Thread));
            Run_T.Start();
        }

        public Thread Run_T;

        public void Run_Thread()
        {
            while (true)
            {
                Scene.UpdateScripts();
                Thread.Sleep(1000 / 30);
            }
        }


    }
}
