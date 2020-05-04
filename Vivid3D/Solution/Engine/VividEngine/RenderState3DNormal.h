#pragma once
#include "Graphics/GraphicsTools/interface/MapHelper.hpp"
#include "Graphics/GraphicsTools/interface/GraphicsUtilities.h"
#include "Common/interface/BasicMath.hpp"
#include "VividApp.h"

namespace Vivid {

	namespace Renderer {

		namespace States {

			class RenderState3DNormal
			{
			public:

				RenderState3DNormal();

				RefCntAutoPtr<IBuffer> GetConsts() {

					return vsConsts;

				}

				RefCntAutoPtr<IPipelineState> GetState() {

					return pState;

				}

				RefCntAutoPtr<IShaderResourceBinding> GetBinding() {

					return pRB;

				}

			private:

				RefCntAutoPtr<IBuffer> vsConsts;
				RefCntAutoPtr<IPipelineState> pState;
				RefCntAutoPtr<IShaderResourceBinding> pRB;

			};

		}

	}

}

