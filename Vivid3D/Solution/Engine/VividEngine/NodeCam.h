#pragma once
#include "vSceneNode.h"

namespace Vivid {

	namespace Scene {

		namespace Nodes {
			class NodeCam : public Vivid::Scene::VSceneNode
			{
			public:

				float4x4 GetWorld();

			private:
			};

		}
	}
}
