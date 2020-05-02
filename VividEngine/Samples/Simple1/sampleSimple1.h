#pragma once
#pragma warning(push)
#pragma warning(disable : 4201) 
#include <VividApp.h>

#include "Common/interface/BasicMath.hpp"
//#include "VMesh2D.h"




class sampleSimple1 :
	public VividApp
{
public:

	void InitApp();
	void UpdateApp();
	void RenderApp();
	void CloseApp();

private:

	//VMesh2D* testMesh2D;


};

