#pragma once
#include "vSceneNode.h"
#include "VMesh3D.h"

namespace Vivid {

	namespace Scene {

		namespace Nodes {

			class VSceneEntity :
				public VSceneNode
			{
			public:

				VSceneEntity();
				void AddMesh(Vivid::Mesh::Mesh3D* mesh);

			private:

				vector<Vivid::Mesh::Mesh3D*> meshes;

			};

		}
	}

}


