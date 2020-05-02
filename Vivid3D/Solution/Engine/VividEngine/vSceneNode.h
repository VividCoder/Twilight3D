#pragma once
#include "pch.h"
//#include <vector>

using namespace std;

class VSceneNode
{
public:

	VSceneNode();
	virtual void Update() {};
	virtual void Render() {};

private:

	vector<VSceneNode*> nodes;

};

