#pragma once

#include "pch.h"

#include <VividApp.h>

#include "VMesh2D.h"
#include "Draw2D.h"

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

	Vivid::Draw::Draw2D* Drawer;



};

