#pragma once
#include "vSceneNode.h"

namespace Vivid {


	namespace Scene {

		namespace Nodes {

			class NodeLight : public VSceneNode
			{
			public:

				NodeLight() {

					diffuse = float4(1, 1, 1, 1);
					spec = float4(0.2f, 0.2f, 0.2f, 1.0);
					range = 800;

				}

				float4 GetDiffuse() {
					return diffuse;
				}

				float4 GetSpecular() {
					return spec;
				}

				void SetDiffuse(float r, float g, float b) {

					diffuse = float4(r, g, b, 1.0);

				}

				void SetSpecular(float r, float g, float b) {

					spec = float4(r, g, b,1);

				}

			private:
			
				float4 diffuse;
				float4 spec;
				float range;

			};


		}
	}
}
