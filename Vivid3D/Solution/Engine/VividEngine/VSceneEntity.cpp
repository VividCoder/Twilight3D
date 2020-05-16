#include "pch.h"
#include "VSceneEntity.h"

using namespace Vivid::Scene::Nodes;

//using namespace Vivid::Scene::Nodes

VSceneEntity::VSceneEntity() {

	meshes.resize(0);
	rendermode = RenderMode::Lit;

}

bool VSceneEntity::RayToTri(float3 origin, float3 vec, float3& out) {

	float sd = 1000.0f;
	bool first = true;
	float3 shit;

	//printf("Checking meshes.\n");

	for (int i = 0; i < meshes.size(); i++) {

		auto mesh = meshes[i];

		float3 out2;

	//	printf("Checking mesh:%d \n", i);

		if (mesh->RayToTri(this->GetWorld(), origin, vec, out2)) {

			float dis = Maths::MathsUtil::Distance(origin, out2);
			if (dis < sd || first) {

				sd = dis;
				first = false;
				shit = out2;
			}

		}

	}

	if (!first) {

		out = shit;
		return true;

	}

	return false;
}


void VSceneEntity::AddMesh(Vivid::Mesh::Mesh3D* mesh) {

	meshes.push_back(mesh);

}