#pragma once

#include "pch.h"

#include <VividApp.h>

#include "VMesh2D.h"
#include "Draw2D.h"
#include "Texture2D.h"
#include "SceneBase.h"
#include "Importer.h"
#include "SceneRenderer.h"
#include "NodeLight.h"
using namespace Vivid::App;

class Test1Simple :
	public VividApp
{
public:

	void InitApp();
	void UpdateApp();
	void RenderApp();
	void CloseApp();
	void MouseMoved(int x, int y);
	void SetKeyDown(int key);
	void SetKeyUp(int key);

private:

	Vivid::Mesh::VMesh2D* testMesh2D;
	Vivid::Texture::Texture2D *tex1;
	Vivid::Texture::Texture2D* tex2;
	Vivid::Draw::Draw2D* Drawer;
	int x, y;
	Vivid::Scene::SceneBase* scene;
	Vivid::Renderer::SceneRenderer* sceneRen;
	float ang = 0.0f;
	Vivid::Scene::Nodes::NodeLight* l1,* l2;


};

