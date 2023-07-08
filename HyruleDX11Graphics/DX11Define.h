#pragma once

#ifdef _WIN64 

#ifdef _DEBUG 
#pragma comment(lib, "../DXTK/Effects11d.lib")
#pragma comment(lib, "../DXTK/DirectXTKd_x64.lib")
#else
#pragma comment(lib, "../DXTK/Effects11.lib")
#pragma comment(lib, "../DXTK/DirectXTK_x64.lib")
#endif

#else

#ifdef _DEBUG 
#pragma comment(lib, "../DXTK/Effects11d_x86.lib")
#pragma comment(lib, "../DXTK/DirectXTKd_x86.lib")
#else
#pragma comment(lib, "../DXTK/Effects11_x86.lib")
#pragma comment(lib, "../DXTK/DirectXTK_x86.lib")
#endif

#endif

#include "D3d11.h"
#include "D3d11_1.h"
#include "D3d11_2.h"
#include "D3d11_3.h"
#include "D3d11_4.h"
#pragma comment(lib, "d3d11.lib")

#include <dxgi.h>
#include <dxgi1_2.h>
#include <dxgi1_3.h>
#pragma comment(lib, "dxgi.lib")

/// Comptr
#include <wrl.h>

/// ����
#include "DXColor.h"

/// ���̴� ������ ���
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

/// FX
#include "../DXTK/inc/d3dx11effect.h"

/// �ؽ��� �δ�
#include "../DXTK/inc/DDSTextureLoader.h"