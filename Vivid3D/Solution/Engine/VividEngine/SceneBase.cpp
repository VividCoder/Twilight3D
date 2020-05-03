#include "pch.h"
#include "SceneBase.h"

using namespace Vivid::Scene;

SceneBase::SceneBase() {

	root = new VSceneNode();

}

void SceneBase::AddNode(VSceneNode* node) {

	root->AddNode(node);

}

VSceneNode* SceneBase::GetRoot() {

	return root;

}
