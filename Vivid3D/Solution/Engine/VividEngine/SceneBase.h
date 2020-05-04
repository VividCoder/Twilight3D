#pragma once
#include <vector>
#include "vSceneNode.h"
#include "VSceneEntity.h"
#include "NodeCam.h"

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

		private:

			VSceneNode* root;
			Nodes::NodeCam* cam;

		};

	}

}

