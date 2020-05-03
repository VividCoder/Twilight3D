#pragma once
#include "VSceneEntity.h"
#include "VividApp.h"

using namespace Vivid::Scene::Nodes;

namespace Vivid {

	namespace Import {

		class Importer
		{
		public:

			static VSceneEntity* LoadEntityAI(const char* path);


		private:
		};

	}

}

