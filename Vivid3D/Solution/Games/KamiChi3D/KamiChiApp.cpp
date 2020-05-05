#include "KamiChiApp.h"

int mx, my;
int mdx, mdy;
bool firstm = true;

int cp = 0, cy = 0;

void KamiChiApp::MouseMoved(int x, int y) {

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
	//cam->SetRotation(-cp, cy, 0);
	scene->GetRoot()->SetRotation(cp, cy, 25);

}


void KamiChiApp::InitApp() {
	SetPath("C:/Projects/Vivid3D/Solution/x64/Debug/");

	scene = new Vivid::Scene::SceneBase();

	auto e = Vivid::Import::Importer::LoadEntityAI("data/model/game/ship/fx/scene.gltf");

	scene->AddNode(e);

	sceneRen = new Vivid::Renderer::SceneRenderer(scene);

	l1 = new Vivid::Scene::Nodes::NodeLight();
	l2 = new Vivid::Scene::Nodes::NodeLight();

	l2->SetPosition(20, 35, -60);
	l2->SetDiffuse(1,1,1);
	l1->SetPosition(0, 0, 15);
	l1->SetDiffuse(1, 1, 1);

	scene->AddLight(l2);
	scene->AddLight(l1);

}

void KamiChiApp::UpdateApp() {


}

void KamiChiApp::RenderApp() {

	auto cam = scene->GetCam();

	cam->SetPosition(0, 0.2f, 50.8f);

	ang = ang + 1.4f;
	float x, z;

	x = cosf(Vivid::Maths::MathsUtil::DegToRad(ang)) * 60;
	z = sinf(Vivid::Maths::MathsUtil::DegToRad(ang)) * 60;

	//	scene->GetRoot()->SetRotation(25, 65, 25);
	//scene->GetRoot()->GetNode(0)->SetRotation(0, ang, 0);
	//scene->GetRoot()->SetRotation(60, 0, 0);
	l1->SetPosition(x, 25, z);





	sceneRen->Render();


}