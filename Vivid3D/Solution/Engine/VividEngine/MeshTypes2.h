#pragma once

//#include "Graphics/GraphicsTools/interface/MapHelper.hpp"
//#include "Graphics/GraphicsTools/interface/GraphicsUtilities.h"
#include <vector>
#include "pch.h"

#include "Graphics//GraphicsEngine/interface/EngineFactory.h"
#include "Graphics/GraphicsEngineD3D11/interface/EngineFactoryD3D11.h"
#include "Graphics/GraphicsEngineD3D12/interface/EngineFactoryD3D12.h"
#include "Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h"
#include "Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h"

#include "Graphics/GraphicsEngine/interface/RenderDevice.h"
#include "Graphics/GraphicsEngine/interface/DeviceContext.h"
#include "Graphics/GraphicsEngine/interface/SwapChain.h"

#include "Common/interface/RefCntAutoPtr.hpp"
#include "Common/interface/BasicMath.hpp"



struct Vertex2D {

	Diligent::float3 Pos;
	Diligent::float2 Uv;
	Diligent::float4 Col;

};


/*
struct Index {

	int VertexID;

};
*/