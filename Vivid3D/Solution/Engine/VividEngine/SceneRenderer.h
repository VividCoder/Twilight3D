#pragma once
#include "SceneRenderer.h"
#include "SceneBase.h"
#include "VSceneEntity.h"
#include "RenderState3DNormal.h"
#include "RenderState3DFullBright.h"



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
			Vivid::Renderer::States::RenderState3DNormal* rsLit;
			Vivid::Renderer::States::RenderState3DFullBright* rsFB;

		};

	}

}

