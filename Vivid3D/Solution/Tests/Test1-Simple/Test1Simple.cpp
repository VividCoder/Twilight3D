#include "pch.h"
#include "Test1Simple.h"



void Test1Simple::InitApp() {
	SetPath("C:/Projects/Vivid3D/Solution/x64/Debug/");

//	testMesh2D = new VMesh2D();
	Drawer = new Vivid::Draw::Draw2D();
	tex1 = new Vivid::Texture::Texture2D("tex1.jpg");


	

}

void Test1Simple::UpdateApp() {

};

void Test1Simple::RenderApp() {

	Drawer->SetTexture(tex1);
	Drawer->SetColor(1, 0, 0, 1);
	Drawer->Rect(20, 20, 200, 200);
	//Drawer->SetColor(0, 1, 1, 1);
	//Drawer->Rect(20, 300, 200, 200);

};

void Test1Simple::CloseApp() {


};