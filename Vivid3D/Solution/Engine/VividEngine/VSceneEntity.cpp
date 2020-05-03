#include "pch.h"
#include "VSceneEntity.h"

using namespace Vivid::Scene::Nodes;

//using namespace Vivid::Scene::Nodes

VSceneEntity::VSceneEntity() {

	meshes.resize(0);

}

void VSceneEntity::AddMesh(Vivid::Mesh::Mesh3D* mesh) {

	meshes.push_back(mesh);

}