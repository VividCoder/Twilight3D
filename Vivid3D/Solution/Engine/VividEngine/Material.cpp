#include "pch.h"
#include "Material.h"

using namespace Vivid::Material;

Material::Material() {

	auto white = new Texture2D("white.png",false);

	tDiffuse = white;
	tNormal = new Texture2D("normalBlank.png",false);

}