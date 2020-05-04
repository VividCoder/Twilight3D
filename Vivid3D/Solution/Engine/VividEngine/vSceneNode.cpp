#include "pch.h"
#include "vSceneNode.h"

using namespace Vivid::Scene;

VSceneNode::VSceneNode() {

	nodes.resize(0);
	name = "\n";
	Position = float3(0, 0, 0);
	Rotation = float4x4::Identity();
	Scale = float3(1, 1, 1);

};

float4x4 VSceneNode::GetWorld()
{

	float4x4 top = float4x4::Identity();

	if (root != NULL) {

		top = root->GetWorld();

	}

	return top * (float4x4::Translation(Position) * Rotation * float4x4::Scale(Scale));


}

void VSceneNode::AddNode(VSceneNode* node) {

	nodes.push_back(node);
	node->SetRoot(this);

}