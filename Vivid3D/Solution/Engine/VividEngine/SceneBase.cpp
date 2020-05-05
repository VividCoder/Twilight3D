#include "pch.h"
#include "SceneBase.h"

using namespace Vivid::Scene;

SceneBase::SceneBase() {

	root = (VSceneNode *)new Vivid::Scene::Nodes::VSceneEntity();
	cam = new Nodes::NodeCam();
	lights.resize(0);

}

void SceneBase::AddNode(VSceneNode* node) {

	root->AddNode(node);

}

VSceneNode* SceneBase::GetRoot() {

	return root;

}
