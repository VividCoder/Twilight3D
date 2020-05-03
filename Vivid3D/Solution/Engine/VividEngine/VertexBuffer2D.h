#pragma once

#include "Graphics/GraphicsTools/interface/MapHelper.hpp"
#include "Graphics/GraphicsTools/interface/GraphicsUtilities.h"
#include <vector>
#include "MeshTypes2.h"

using namespace std;
using namespace Diligent;

namespace Vivid {

	namespace Buffer {

		namespace Vertex {

			class VertexBuffer2D
			{
			public:

				VertexBuffer2D(vector<Vivid::DataTypes::Vertex2D *> verts,vector<Uint32> indices);

			private:
			
				RefCntAutoPtr<IBuffer> VBuf;
				RefCntAutoPtr<IBuffer> IBuf;
				//RefCntAutoPtr<Diligent::IBuffer> VBuffer;
			
			};


		}
	}

}
