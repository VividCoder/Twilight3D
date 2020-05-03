#pragma once
#include "pch.h"
#include "Common/interface/BasicMath.hpp"
//#include <vector>

using namespace std;
using namespace Diligent;

namespace Vivid {

	namespace Scene {

		class VSceneNode
		{
		public:

			VSceneNode();
			virtual void Update() {};
			virtual void Render() {};

			virtual float4x4 GetWorld();

			void AddNode(VSceneNode* node);

		private:

			float4x4 Rotation;
			float3 Scale;
			float3 Position;

			vector<VSceneNode*> nodes;
		
			

		};

	}

}