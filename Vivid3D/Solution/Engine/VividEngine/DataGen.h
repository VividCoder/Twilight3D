#pragma once
#include "MeshTypes2.h"
#include <vector>

using namespace std;

using namespace Vivid::DataTypes;

namespace Vivid {

	namespace DataGen {
		class DataGen
		{
		public:

			static vector<Vertex2D*> MakeQuad(float x, float y, float w, float h, float z = 0);

		};

	}
}


