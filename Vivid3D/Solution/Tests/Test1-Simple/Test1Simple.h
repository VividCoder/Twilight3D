#pragma once

#include "pch.h"

#include <VividApp.h>

#include "VMesh2D.h"
#include "Draw2D.h"
#include "Texture2D.h"
#include "SceneBase.h"
#include "Importer.h"

using namespace Vivid::App;

class Test1Simple :
	public VividApp
{
public:

	void InitApp();
	void UpdateApp();
	void RenderApp();
	void CloseApp();

private:

	Vivid::Mesh::VMesh2D* testMesh2D;
	Vivid::Texture::Texture2D *tex1;
	Vivid::Texture::Texture2D* tex2;
	Vivid::Draw::Draw2D* Drawer;
	int x, y;
	Vivid::Scene::SceneBase* scene;


};

