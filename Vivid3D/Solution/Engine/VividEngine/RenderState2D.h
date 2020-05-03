#pragma once
#include "Graphics/GraphicsTools/interface/MapHelper.hpp"
#include "Graphics/GraphicsTools/interface/GraphicsUtilities.h"
#include "Common/interface/BasicMath.hpp"
#include "VividApp.h"

namespace Vivid {

	namespace RenderState {

		class RenderState2D
		{
		public:
			RenderState2D();
		private:
			RefCntAutoPtr<IBuffer> vsConsts;
			RefCntAutoPtr<IPipelineState> pState;
			RefCntAutoPtr<IShaderResourceBinding> pRB;
		};
		

	}

}

