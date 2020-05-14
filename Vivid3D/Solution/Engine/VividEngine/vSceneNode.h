#pragma once
#include "pch.h"
#include "Common/interface/BasicMath.hpp"
#include "MathsUtil.h"
//#include <vector>

using namespace std;
using namespace Diligent;
using namespace Vivid::Maths;

namespace Vivid {

	namespace Scene {

		class VSceneNode
		{
		public:

			VSceneNode();
			virtual void Update() {};
			virtual void Render() {};

			virtual float4x4 GetWorld();

			void AddNode(VSceneNode* node);

			int NodeCount() {

				return nodes.size();

			}

			float3 GetPosition() {

				return Position;

			}

			VSceneNode* GetNode(int num) {

				return nodes.at(num);

			}

			void SetName(const char* n)
			{
				name = n;
			}

			const char * GetName()
			{
				return name;
			}

			void SetRoot(VSceneNode* node) {
				root = node;
			}

			VSceneNode* GetRoot() {

				return root;
				
			}

			void SetPosition(float x, float y, float z) {

				Position = float3(x, y, z);

			}

			void SetRotation(float pitch, float yaw, float roll) {

			
				float4x4 p = float4x4::RotationX(MathsUtil::DegToRad(pitch));
				float4x4 y = float4x4::RotationY(MathsUtil::DegToRad(yaw));
				float4x4 r = float4x4::RotationZ(MathsUtil::DegToRad(roll));

				Rotation = p * y * r;

			}

			void Move(float x, float y, float z) {

				auto mv = float3(x, y, z);

				mv = mv * Rotation;

				Position = Position + mv;

			}

			void Turn(float pitch, float yaw, float roll) {


				float4x4 p = float4x4::RotationX(MathsUtil::DegToRad(pitch));
				float4x4 y = float4x4::RotationY(MathsUtil::DegToRad(yaw));
				float4x4 r = float4x4::RotationZ(MathsUtil::DegToRad(roll));

				Rotation = Rotation * (p * y * r);


			}

			void SetScale(float x, float y, float z) {

				Scale = float3(x, y, z);

			}

			float4x4 GetRotation() {

				float4x4 top = float4x4::Identity();

				if (root != NULL) {
					top = root->GetRotation();
				}

				return top * Rotation;


			}

		private:

			float4x4 Rotation;
			float3 Scale;
			float3 Position;

			const char* name;

			vector<VSceneNode*> nodes;

			VSceneNode* root = NULL;
		
			

		};

	}

}