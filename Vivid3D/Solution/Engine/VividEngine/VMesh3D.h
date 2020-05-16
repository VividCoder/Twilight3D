#pragma once
#include "pch.h"
#include "MeshTypes2.h"
#include <vector>
#include "VertexBuffer3D.h"
#include "Material.h"
#include "BoundingBox.h"

using namespace std;

using namespace Vivid::DataTypes;
using namespace Vivid::Buffer::Vertex;

namespace Vivid {

	namespace Mesh {

		class Mesh3D
		{
		public:
			
			Mesh3D(int vertices, int indices);
			void SetVertex(int index,Vertex3D* v);
			void SetTri(int index,Tri* t);
			void Final();
			VertexBuffer3D* GetVB()
			{
				return vb;
			}

			int IndicesNum() {

				return indices.size();

			}

			void SetMaterial(Material::Material* mat)
			{

				material = mat;

			}
			Material::Material * GetMaterial()
			{
				return material;
			}

			bool RayToTri(float4x4 mat, float3 origin, float3 vec, float3& out);

			BoundingBox* GetBounds(float4x4 m);

		private:

			//vector
			vector<Vertex3D* > vertices;
			vector<Tri* > indices;
			VertexBuffer3D* vb;
			Material::Material* material = NULL;
			BoundingBox* bb;

		};

		
	}

}