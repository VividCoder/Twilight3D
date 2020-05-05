#include "pch.h"
#include "Material.h"

using namespace Vivid::Material;

Material::Material() {

	auto white = new Texture2D("white.png");

	tDiffuse = white;
	tNormal = white;

}