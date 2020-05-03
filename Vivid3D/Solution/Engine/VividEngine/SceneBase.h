#pragma once
#include <vector>
#include "vSceneNode.h"

namespace Vivid {

	namespace Scene {

		class SceneBase
		{
		public:

			SceneBase();

			void AddNode(VSceneNode* node);
			VSceneNode* GetRoot();

		private:

			VSceneNode* root;

		};

	}

}

