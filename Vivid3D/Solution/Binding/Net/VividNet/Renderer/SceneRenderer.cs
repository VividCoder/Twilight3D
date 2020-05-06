using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VividNet.Bind;
using VividNet.Scene;

namespace VividNet.Renderer
{
    public class SceneRenderer : VividObj
    {

        public SceneBase Scene
        {
            get;
            set;

        }
        public SceneRenderer(SceneBase scene)
        {

            ID = BindRenderer.vNewRenderer(scene.ID);
            Scene = scene;
        }

        public void Render()
        {

            BindRenderer.vRendererRender(ID);

        }

    }
}
