#pragma once

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

			void Bind();

			void Release();

	

		private:

			float cRed, cGreen, cBlue, cAlpha;
			BlendMode bMode;


		};

	}

}