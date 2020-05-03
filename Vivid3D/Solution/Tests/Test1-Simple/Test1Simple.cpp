#include "pch.h"
#include "Test1Simple.h"



void Test1Simple::InitApp() {
	SetPath("C:/Projects/Vivid3D/Solution/x64/Debug/");

//	testMesh2D = new VMesh2D();
	Drawer = new Vivid::Draw::Draw2D();
	
	tex1 = new Vivid::Texture::Texture2D("tex1.jpg");
	tex2 = new Vivid::Texture::Texture2D("tex2.jpg");
	
	srand(time(NULL));

	scene = new Vivid::Scene::SceneBase();
	
	auto e = Vivid::Import::Importer::LoadEntityAI("model/spider.obj");

	scene->AddNode(e);
}

void Test1Simple::UpdateApp() {

};

void Test1Simple::RenderApp() {

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