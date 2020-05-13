#pragma once
#include "Graphics/GraphicsTools/interface/MapHelper.hpp"
#include "Graphics/GraphicsTools/interface/GraphicsUtilities.h"
#include "Common/interface/BasicMath.hpp"

#include "VividApp.h"
namespace Vivid {

	namespace Texture {

		class Texture2D
		{
		public:

			Texture2D(void* data, int w, int h,int bpp);

			Texture2D(const char* path,bool imp);
			RefCntAutoPtr<ITextureView> GetView() {

				return texView;

			}

			RefCntAutoPtr<ITexture> GetTex() {

				return tex;

			}

			const char* GetPath() {
				
				return texpath;

			}

		private:
			
			RefCntAutoPtr<ITexture> tex;
			RefCntAutoPtr<ITextureView> texView;
			const char* texpath = NULL;

		};

	}

}
