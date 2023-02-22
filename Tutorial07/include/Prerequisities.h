#pragma once

#include <windows.h> 
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>
#include "resource.h"
#include <vector>
#include "Time.h"
#include <iostream>
#include <sstream>
#define WINDOWS
#include "Commons.h"


//MACRO for  safe realease of resources
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

// * To check monster
#define OutputLOG(_ClassName, _FunctionName, _OutputMessage)           \
OutputDebugStringA(_ClassName);                                                          \
OutputDebugStringA(" : In Function : ");                                          \
OutputDebugStringA(_FunctionName);                                                    \
OutputDebugStringA(" : ");                                                                \
OutputDebugStringA(_OutputMessage);                                                    \
OutputDebugStringA("\n");