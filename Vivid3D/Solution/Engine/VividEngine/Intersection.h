#pragma on
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

#include "MathsUtil.h"

using namespace Diligent;

namespace Vivid {

	namespace Intersections {

		class Intersection
		{
		public:

			static bool RayToTri(float3 origin, float3 vec, float3 v0, float3 v1, float3 v2, float3& outPoint);


		};


	}

}