#pragma once
#include "SceneRenderer.h"
#include "SceneBase.h"

namespace Vivid {

	namespace Renderer {

		class SceneRenderer
		{
		public:

			SceneRenderer(Vivid::Scene::SceneBase* scene);
			void Build();
			void Bind();
			void Render();

		private:

			Vivid::Scene::SceneBase* pScene;

		};

	}

}
