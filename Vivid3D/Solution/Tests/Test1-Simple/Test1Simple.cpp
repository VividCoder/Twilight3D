#include "pch.h"
#include "Test1Simple.h"
#include <filesystem>

int mx, my;
int mdx, mdy;
bool firstm = true;

int cp=0, cy=0;

void Test1Simple::MouseMoved(int x, int y) {

	//e//xit(1);
	int lx, ly;
	lx = mx;
	ly = my;
	mx = x;
	my = y;
	if (firstm) {
		mdx = 0;
		mdy = 0;
		firstm = false;
		return;
	}
	mdx = mx - lx;
	mdy = my - ly;

	cp = cp + mdy;
	cy = cy + mdx;

	auto cam = scene->GetCam();
	cam->SetRotation(-cp,cy, 0);


}

void Test1Simple::SetKeyDown(int key) {

	if(key ==)

	exit(1);

};

void Test1Simple::SetKeyUp(int key) {

};

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

	l1 = new Vivid::Scene::Nodes::NodeLight();

	l1->SetPosition(0, 0, -15);
	scene->AddLight(l1);

//	VividApp::SetMouseMoveFunc(F_MouseMove);

}

void Test1Simple::UpdateApp() {

};

void Test1Simple::RenderApp() {

	auto cam = scene->GetCam();

	cam->SetPosition(0, 0.2f, 0.8f);

	ang = ang + 1.4f;
	float x, z;

	x = cosf(Vivid::Maths::MathsUtil::DegToRad(ang)) * 7;
	z = sinf(Vivid::Maths::MathsUtil::DegToRad(ang)) * 7;

	
	//scene->GetRoot()->GetNode(0)->SetRotation(0, ang, 0);
	//scene->GetRoot()->SetRotation(60, 0, 0);
	l1->SetPosition(x, 0, z);




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