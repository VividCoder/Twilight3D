#pragma once
#include "Texture2D.h"

using namespace Vivid::Texture;

namespace Vivid {

	namespace Material {

		class Material
		{
		public:

			Material();

			void SetNormal(Texture2D* norm) {

				tNormal = norm;

			}


			Texture2D* GetNormal()
			{

				return tNormal;

			}

			bool hasNormal() {

				if (tNormal == NULL) return false;
				return true;

			}

			void SetDiffuse(Texture2D* dif) {

				tDiffuse = dif;

			}

			Texture2D* GetDiffuse() {

				return tDiffuse;

			}

			bool hasDiffuse() {

				if (tDiffuse == NULL) {

					return false;

				}
				return true;

			}

		private:

			Texture2D* tDiffuse = NULL;
			Texture2D* tSpec;
			Texture2D* tRough;
			Texture2D* tNormal;
			Texture2D* tReflect;


		};

	}

}
