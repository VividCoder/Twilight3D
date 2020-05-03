#include "pch.h"
#include "Test1Simple.h"



void Test1Simple::InitApp() {

//	testMesh2D = new VMesh2D();
	Drawer = new Vivid::Draw::Draw2D();


}

void Test1Simple::UpdateApp() {

};

void Test1Simple::RenderApp() {

	Drawer->Rect(20, 20, 200, 200);

};

void Test1Simple::CloseApp() {


};