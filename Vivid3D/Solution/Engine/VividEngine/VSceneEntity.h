#pragma once
#include "vSceneNode.h"
#include "VMesh3D.h"

namespace Vivid {

	namespace Scene {

		namespace Nodes {


			enum RenderMode {

				Lit,FullBright

			};

			class VSceneEntity :
				public VSceneNode
			{
			public:

				VSceneEntity();
				
				void AddMesh(Vivid::Mesh::Mesh3D* mesh);
			
				int MeshCount()
				{

					return meshes.size();

				}

				bool RayToTri(float3 origin, float3 vec, float3& out);

				Vivid::Mesh::Mesh3D* GetMesh(int num) {

					return meshes.at(num);

				}

				void SetRenderMode(RenderMode mode) {

					rendermode = mode;

				}

				RenderMode GetRenderMode() {

					return rendermode;

				}

				bool CanPick() {
					return canPick;
				}

				void SetCanPick(bool pick) {

					canPick = pick;

				}

			private:

				vector<Vivid::Mesh::Mesh3D*> meshes;
				RenderMode rendermode;
				bool canPick = true;

			};

		}
	}

}


