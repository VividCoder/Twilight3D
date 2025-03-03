#pragma once
#include "Texture2D.h"
#include "VertexBuffer2D.h"
#include "DataGen.h"
#include "VividApp.h"
#include "RenderState2D.h"

namespace Vivid {

	namespace Draw {

		enum BlendMode {
			Solid,Additive,Alpha,Mask
		};

		class Draw2D
		{
		public:

			Draw2D();

			void Rect(int x, int y, int w, int h);
			
			void SetColor(float r, float g, float b, float a = 1.0f);

			void SetBlend(BlendMode mode);

			void SetTexture(Vivid::Texture::Texture2D* tex);

			void Bind();

			void Release();

	

		private:

			Vivid::Texture::Texture2D* bTex;
			float cRed, cGreen, cBlue, cAlpha;
			BlendMode bMode;
			Vivid::RenderState::RenderState2D * ren;


		};

	}

}