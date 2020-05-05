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

				RefCntAutoPtr<IBuffer> GetConsts2() {

					return vsConsts2;

				}



				RefCntAutoPtr<IPipelineState> GetState2() {
					
					return pState2;

				}

				RefCntAutoPtr<IShaderResourceBinding> GetBinding2() {

					return pRB2;

				}

			private:

				RefCntAutoPtr<IBuffer> vsConsts;
				RefCntAutoPtr<IPipelineState> pState;
				RefCntAutoPtr<IShaderResourceBinding> pRB;
				RefCntAutoPtr<IBuffer> vsConsts2;
				RefCntAutoPtr<IPipelineState> pState2;
				RefCntAutoPtr<IShaderResourceBinding> pRB2;

			};

		}

	}

}

