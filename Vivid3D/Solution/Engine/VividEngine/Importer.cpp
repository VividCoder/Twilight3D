#include "pch.h"
#include "Importer.h"
#include "assimp\cimport.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "VMesh3D.h"

using namespace Vivid::Import;

vector<Vivid::Mesh::Mesh3D*> meshes;

void add_node(const C_STRUCT aiNode* nd, VSceneEntity* ent)
{

	Vivid::Scene::Nodes::VSceneEntity *ne = new Vivid::Scene::Nodes::VSceneEntity();

	ent->AddNode(ne);


	for (int i = 0; i < nd->mNumMeshes; i++) {

		int mi = nd->mMeshes[i];

		ne->AddMesh(meshes.at(mi));

	}

	for (int i = 0; i < nd->mNumChildren; i++) {

		add_node(nd->mChildren[i], ne);

	}

}

VSceneEntity* Importer::LoadEntityAI(const char* path) {

	auto rpath = Vivid::App::VividApp::GetResPath(path);

	unsigned int flags = aiProcessPreset_TargetRealtime_MaxQuality;

	auto root = aiImportFile(rpath, flags);

	//vector<Vivid::Mesh::Mesh3D*> meshes;

	meshes.resize(0);

	

	for (int i = 0; i < root->mNumMeshes; i++) {

		const C_STRUCT aiMesh* mesh = root->mMeshes[i];


		auto eMesh = new Vivid::Mesh::Mesh3D(mesh->mNumVertices, mesh->mNumFaces);

		meshes.push_back(eMesh);

		for (int v = 0; v < mesh->mNumVertices; v++) {

			auto nv = new Vivid::DataTypes::Vertex3D();

			auto pv = mesh->mVertices[v];
			auto nmv = mesh->mNormals[v];
			aiVector3D tv, bv;
			if (mesh->HasTangentsAndBitangents()) {
				tv = mesh->mTangents[v];
				bv = mesh->mBitangents[v];
			}
			auto uv = mesh->mTextureCoords[0];

			auto uvv = uv[v];

		

			nv->Pos = Diligent::float3(pv.x, pv.y, pv.z);
			nv->Normal = Diligent::float3(nmv.x, nmv.y, nmv.z);
			nv->BiNormal = Diligent::float3(bv.x, bv.y, bv.z);
			nv->Tangent = Diligent::float3(tv.x, tv.y, tv.z);
			nv->UV = Diligent::float3(uvv.x, uvv.y, uvv.z);
	
			eMesh->SetVertex(v, nv);

		}

		for (int t = 0; t < mesh->mNumFaces; t++) {

			const C_STRUCT aiFace* face = &mesh->mFaces[t];

			auto nt = new Vivid::DataTypes::Tri();

			nt->V0 = face->mIndices[0];
			nt->V1 = face->mIndices[1];
			nt->V2 = face->mIndices[2];

			eMesh->SetTri(t, nt);
		

		}
		

	}

	auto res = new Vivid::Scene::Nodes::VSceneEntity();


	add_node(root->mRootNode, res);

	return res;

};