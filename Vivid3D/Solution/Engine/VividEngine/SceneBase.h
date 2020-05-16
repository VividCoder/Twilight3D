#pragma once
#include <vector>
#include "vSceneNode.h"
#include "VSceneEntity.h"
#include "NodeCam.h"
#include "NodeLight.h"

namespace Vivid {

	namespace Scene {

		class SceneHit {
		public:
			float3 pos;
			bool hit = false;
			float dis = 0;
		};

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

			SceneHit* CamPick(int x, int y);

			SceneHit* RayToTri(float3 origin, float3 vec);

			void SetRoot(Vivid::Scene::VSceneNode* node) {

				root = node;

			}

			int LightCount() {

				return lights.size();

			}

			Vivid::Scene::Nodes::NodeLight* GetLight(int num) {

				return lights.at(num);

			}

			vector<Vivid::Scene::Nodes::NodeLight*> GetLights() {
				return lights;
			}

		private:

			VSceneNode* root;
			Nodes::NodeCam* cam;
			vector<Vivid::Scene::Nodes::NodeLight*> lights;

		};

	}

}

