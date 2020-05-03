#pragma once
#include "pch.h"
//#include <vector>

using namespace std;

namespace Vivid {

	namespace Scene {

		class VSceneNode
		{
		public:

			VSceneNode();
			virtual void Update() {};
			virtual void Render() {};

		private:

			vector<VSceneNode*> nodes;

		};

	}

}