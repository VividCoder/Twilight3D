#include "pch.h"
#include "NodeCam.h"

using namespace Vivid;
using namespace Vivid::Scene;
using namespace Vivid::Scene::Nodes;


float4x4 NodeCam::GetWorld() {

	 //float4x4::Translation(Position) * Rotation * float4x4::Scale(Scale);

	auto world = VSceneNode::GetWorld();

	return world;

}