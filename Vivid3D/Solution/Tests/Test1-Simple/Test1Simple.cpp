#include "pch.h"
#include "Test1Simple.h"
#include <filesystem>


void Test1Simple::InitApp() {
	SetPath("C:/Projects/Vivid3D/Solution/x64/Debug/");

	

//	testMesh2D = new VMesh2D();
	Drawer = new Vivid::Draw::Draw2D();
	
	//tex1 = new Vivid::Texture::Texture2D("tex1.jpg");
//	tex2 = new Vivid::Texture::Texture2D("tex2.jpg");
	
	srand(time(NULL));

	scene = new Vivid::Scene::SceneBase();
	
	auto e = Vivid::Import::Importer::LoadEntityAI("scene.gltf");

	scene->AddNode(e);

	sceneRen = new Vivid::Renderer::SceneRenderer(scene);


}

void Test1Simple::UpdateApp() {

};

void Test1Simple::RenderApp() {

	auto cam = scene->GetCam();

	cam->SetPosition(0, 0, -7);

	ang = ang + 1;
	scene->GetRoot()->SetRotation(0, ang, 0);

	sceneRen->Render();

	return;
	Drawer->SetTexture(tex2);

	Drawer->Bind();

	Drawer->SetTexture(tex1);
	Drawer->SetColor(0, 1, 1, 1);

	

	for (int i = 0; i < 20; i++) {

		int x = rand() % 512;
		int y = rand() % 512;
		Drawer->Rect(x, y, 200, 200);
	}
		printf("Rendered");


};

void Test1Simple::CloseApp() {


};