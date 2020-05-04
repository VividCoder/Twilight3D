#pragma once
#include "Graphics/GraphicsTools/interface/MapHelper.hpp"
#include "Graphics/GraphicsTools/interface/GraphicsUtilities.h"
#include "Common/interface/BasicMath.hpp"
#include "TextureLoader/interface/TextureLoader.h"
#include "TextureLoader/interface/TextureUtilities.h"
#include "VividApp.h"
namespace Vivid {

	namespace Texture {

		class Texture2D
		{
		public:

			Texture2D(const char* path);
			RefCntAutoPtr<ITextureView> GetView() {

				return texView;

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
