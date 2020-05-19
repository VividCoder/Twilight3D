#include "pch.h"
#include "SceneBase.h"

using namespace Vivid::Scene;

SceneBase::SceneBase() {

	root = (VSceneNode *)new Vivid::Scene::Nodes::VSceneEntity();
	cam = new Nodes::NodeCam();
	lights.resize(0);

}

void SceneBase::AddNode(VSceneNode* node) {

	root->AddNode(node);

}

VSceneNode* SceneBase::GetRoot() {

	return root;

}

SceneHit* CheckRayTri(VSceneNode *node, float3 origin, float3 vec) {

	SceneHit* hit = new SceneHit;
	hit->hit = false;

	auto isn = dynamic_cast<Vivid::Scene::Nodes::VSceneEntity*>(node);

	if (isn == NULL) {
		
	}
	else {


		if (isn->CanPick()) {

			float3 out;
			//		printf("Checking entity\n");
			if (isn->RayToTri(origin, vec, out)) {

				//printf("Hit!\n");
				hit->pos = out;
				hit->dis = MathsUtil::Distance(origin, out);
				hit->hit = true;
				hit->Entity = isn;

			}
			else {
				//	printf("No hit!\n");
			}

		}
		else {

			return hit;

		}
		//return 2;
	}

	float sd = hit->dis;

	bool first = true;
	if (hit->hit) {
		first = false;
	}


	for (int i = 0; i < node->NodeCount(); i++) {

		auto r = node->GetNode(i);

		//printf("Checking sub node.\n");
		auto nh = CheckRayTri(r, origin, vec);

		if (nh->hit)
		{
		//	printf("Hit!\n");
			if (nh->dis < sd || first)
			{


				sd = nh->dis;
				first = false;
				hit->pos = nh->pos;
				hit->dis = sd;
				hit->hit = true;
				hit->Entity = nh->Entity;

			}

		}
		else {
	//		printf("No hit!2\n");
		}

	}


	return hit;
}

SceneHit* SceneBase::RayToTri(float3 origin, float3 vec) {
	
	//prin/tf("Checking:\n");
	auto hit = CheckRayTri(root, origin, vec);
	//printf("Checked\n");

	return hit;
};

float3 Unproject(float4x4 proj, float4x4 view, int w, int h, float mx, float my,float mz) {

	float4 vec;

	vec.x = 2.0f * mx / (float)w - 1;
	vec.y = -(2.0f * my / (float)h - 1);
	vec.z = mz;
	vec.w = 1.0f;

	float4x4 viewInv = view.Inverse();
	float4x4 projInv = proj.Inverse();

	vec = projInv * vec;
	vec = viewInv * vec;

	if (vec.w > FLT_EPSILON || vec.w < -FLT_EPSILON) {

		vec.x / vec.w;
		vec.y / vec.w;
		vec.z / vec.w;

	}

	return float3(vec.x, vec.y, vec.z);

}

Ray MouseRay(float4x4 proj, float4x4 view, int w, int h, int mx, int my) {

	//float3 v1 = Unproject();
	float3 v1 = Unproject(proj, view, w, h, mx, my, -1.5f);
	float3 v2 = Unproject(proj, view, w, h, mx, my, 1.0f);
	Ray r;
	r.origin = v1;
	r.vec = v2;
	return r;
}


SceneHit* SceneBase::CamPick(int x, int y) {

	float4x4 proj = Vivid::App::VividApp::GetProjMat();
	float4x4 view = cam->GetWorld();
	float vw = Vivid::App::VividApp::GetW();
	float vh = Vivid::App::VividApp::GetH();


	float mx = -1 + ((float)x / vw)*2.0f;
	float my = -1 + ((float)y / vh)*2.0f;

	float3 origin = float3(mx, my, 0);
	float3 vec = float3(mx, my, 1);

	float4x4 inv = view * proj;
	inv = inv.Inverse();

	float3 rayorigin = origin * inv;
	float3 rayvec = vec * inv;

	float3 dir = normalize(rayvec - rayorigin);


	//Ray r = MouseRay(proj, view, Vivid::App::VividApp::GetW(), Vivid::App::VividApp::GetH(), x, y);
	//printf("W:%d H:%d \n", Vivid::App::VividApp::GetW(), Vivid::App::VividApp::GetH());
	//while (true) {};

//	printf("CX:%4.2f CY:%4.2f CZ:%4.2f \n", cam->GetPosition().x, cam->GetPosition().y, cam->GetPosition().z);
//	printf("RX:%4.2f RY:%4.2f RZ:%4.2f DX:%4.2f DY:%4.2f DZ:%4.2f \n", r.origin.x, r.origin.y, r.origin.z, r.vec.x, r.vec.y, r.vec.z);
	SceneHit* hit = RayToTri(rayorigin, dir);

	return hit;

}