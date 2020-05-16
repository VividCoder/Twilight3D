#pragma once
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

using namespace Diligent;


namespace Vivid {

	namespace Maths {

		const double PI = 3.1415926535897932384626433832795028841971693993751058209;

		struct Ray {

			float3 origin;
			float3 vec;

		};

		class MathsUtil
		{
		public:

			static float DegToRad(float deg) {

				return (deg * PI) / 180.0f;

			};

			static float RadToDeg(float rad) {

				return (rad * 180) / PI;

			}

			static float DotProduct(float3 l, float3 r) {

				return (l.x * r.x) + (l.y * r.y) + (l.z * r.z);

			}

			static float Distance(float3 v0, float3 v1) {

				float xd = v1.x - v0.x;
				float yd = v1.y - v0.y;
				float zd = v1.z - v0.z;

				return sqrt(xd * xd + yd * yd + zd * zd);

			}

			static float3 CrossProduct(float3 l, float3 r)
			{

				float3 res;

				res.x = (l.y * r.z) - (l.z * r.y);
				res.y = (l.z * r.x) - (l.x * r.z);
				res.z = (l.x * r.y) - (l.y * r.x);

				return res;

			}

		};

	}

}
