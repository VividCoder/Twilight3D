#include "pch.h"
#include "vSceneNode.h"

using namespace Vivid::Scene;

VSceneNode::VSceneNode() {

	nodes.resize(0);

};

float4x4 VSceneNode::GetWorld()
{

	return float4x4::Translation(Position) * Rotation * float4x4::Scale(Scale);


}

void VSceneNode::AddNode(VSceneNode* node) {

	nodes.push_back(node);

}