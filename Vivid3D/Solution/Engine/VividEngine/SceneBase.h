#pragma once
#include <vector>
#include "vSceneNode.h"
#include "VSceneEntity.h"
#include "NodeCam.h"
#include "NodeLight.h"

namespace Vivid {

	namespace Scene {

		class SceneBase
		{
		public:

			SceneBase();

			void AddNode(VSceneNode* node);
			VSceneNode* GetRoot();
			Nodes::NodeCam* GetCam() {

				return cam;

			}

			void AddLight(Vivid::Scene::Nodes::NodeLight* light) {

				lights.push_back(light);

			}

			int LightCount() {

				return lights.size();

			}

			Vivid::Scene::Nodes::NodeLight* GetLight(int num) {

				return lights.at(num);

			}

		private:

			VSceneNode* root;
			Nodes::NodeCam* cam;
			vector<Vivid::Scene::Nodes::NodeLight*> lights;

		};

	}

}

