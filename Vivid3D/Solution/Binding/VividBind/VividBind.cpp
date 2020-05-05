// VividBind.cpp : Defines the exported functions for the DLL.
//
#include "pch.h"

#include <VividApp.h>

#include "VMesh2D.h"
#include "Draw2D.h"
#include "Texture2D.h"
#include "SceneBase.h"
#include "Importer.h"
#include "SceneRenderer.h"
#include "NodeLight.h"
using namespace Vivid::App;

#include "framework.h"
#include "VividBind.h"

#include <iostream>

#include "EngineMain.h"


// This is an example of an exported variable
VIVIDBIND_API int nVividBind=0;

// This is an example of an exported function.
VIVIDBIND_API int fnVividBind(void)
{
    return 0;
}

extern "C" {

    VIVIDBIND_API int testBind(int f)
    {

        return f * 2;
    }

}

// This is the constructor of a class that has been exported.
CVividBind::CVividBind()
{
    return;
}
