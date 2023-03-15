//--------------------------------------------------------------------------------------
// File: Tutorial07.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "Prerequisities.h"
#include "Commons.h"
#include "CTime.h"

#include "Window.h"
#include "DeviceContext.h"
#include "Device.h"
#include "DepthStencilView.h"
#include "Texture.h"
#include "InputLayout.h"
#include "SwapChain.h"
#include "RenderTargetView.h"
#include "SamplerState.h"
#include "Viewport.h"


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------

D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11VertexShader* g_pVertexShader = nullptr;
ID3D11PixelShader* g_pPixelShader = nullptr;
ID3D11Buffer* g_pVertexBuffer = nullptr;
ID3D11Buffer* g_pIndexBuffer = nullptr;
ID3D11Buffer* g_Camera = nullptr;
ID3D11Buffer* g_pCBChangesEveryFrame = nullptr;
ID3D11SamplerState* g_pSamplerLinear = nullptr;

XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);

Window                              g_window;
DeviceContext                       g_devicecontext;
Camera                              cam;
Device                              g_device;
DepthStencilView                    g_depthStencilView;
Texture                             g_ModelTexture;
Texture                             g_depthStencil;
Texture                             g_backBuffer;
InputLayout                         g_inputLayout;
SwapChain                           g_swapChain;
RenderTargetView                    g_renderTargetView;
SamplerState                        g_samplerstate;
Viewport                            g_viewport;

Vector3 PosicionVec; //we create a global Variable called PosicionVec that is a Vector3
float Speed = 0.15f; //We put a global variable called Speed that will be the speed at which our cube will move
CTime  g_Time; 


//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow); 
HRESULT InitDevice(); 

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void Render();
void update(float deltaTSime);
void destroy();


//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int 
WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow){
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (FAILED(g_window.init( hInstance, nCmdShow,  WndProc, "cuadrito")))
        return 0;

    if (FAILED(InitDevice()))
    {
        
        destroy();
        return 0;
    }

    g_Time.init();
    // Main message loop
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            g_Time.update();
            update(g_Time.m_deltaTime);
            Render();

        }
    }


    destroy();

    return (int)msg.wParam;
}



//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT 
CompileShaderFromFile(char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut){
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
    #if defined( DEBUG ) || defined( _DEBUG )
    
    dwShaderFlags |= D3DCOMPILE_DEBUG;
    #endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, nullptr, ppBlobOut, &pErrorBlob, nullptr);
    if (FAILED(hr))
    {
        if (pErrorBlob != nullptr)
            OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
        if (pErrorBlob) pErrorBlob->Release();
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT 
InitDevice(){
    HRESULT hr = S_OK;

    //se crea el swapchchain
    g_swapChain.init(g_device, g_devicecontext, g_backBuffer, g_window);

    //se crea el rendertargetview
    g_renderTargetView.init(g_device, g_backBuffer, DXGI_FORMAT_R8G8B8A8_UNORM);

    g_backBuffer.destroy();
    if (FAILED(hr))
        return hr;

    g_depthStencil.init(g_device,
        g_window.m_width,
        g_window.m_height,
        DXGI_FORMAT_D24_UNORM_S8_UINT,
        D3D11_BIND_DEPTH_STENCIL);

    // se crea el depthstencilview
    g_depthStencilView.init(g_device, g_depthStencil.m_texture, DXGI_FORMAT_D24_UNORM_S8_UINT);

    //Iniciamos el viewport
    g_viewport.init(g_window);


    // Compilamos el vertex shader
    ID3DBlob* pVSBlob = nullptr;
    hr = CompileShaderFromFile("Tutorial07.fx", "VS", "vs_4_0", &pVSBlob);
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
        return hr;
    }
    // 
    // se crea el vertex shader
    hr = g_device.CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }

    //Define InputLayout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION",
            0,
            DXGI_FORMAT_R32G32B32_FLOAT,
            0,
            D3D11_APPEND_ALIGNED_ELEMENT,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT /*12*/, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    unsigned int numElements = ARRAYSIZE(layout);
    
    //Definimos el InputLayout
    std::vector <D3D11_INPUT_ELEMENT_DESC> Layout;

    D3D11_INPUT_ELEMENT_DESC position;
    position.SemanticName = "POSITION";
    position.SemanticIndex = 0;
    position.Format = DXGI_FORMAT_R32G32B32_FLOAT;
    position.InputSlot = 0;
    position.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    position.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    position.InstanceDataStepRate = 0;
    Layout.push_back(position);

    D3D11_INPUT_ELEMENT_DESC texcoord;
    texcoord.SemanticName = "TEXCOORD";
    texcoord.SemanticIndex = 0;
    texcoord.Format = DXGI_FORMAT_R32G32_FLOAT;
    texcoord.InputSlot = 0;
    texcoord.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    texcoord.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    texcoord.InstanceDataStepRate = 0;
    Layout.push_back(texcoord);

    
    // se crea el input layout
    g_inputLayout.init(g_device, Layout, pVSBlob);

    pVSBlob->Release();
    if (FAILED(hr))
        return hr;

    // Compile the pixel shader
    ID3DBlob* pPSBlob = nullptr;
    hr = CompileShaderFromFile("Tutorial07.fx", "PS", "ps_4_0", &pPSBlob);
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
        return hr;
    }

    // Create the pixel shader
    hr = g_device.CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &g_pPixelShader);
    pPSBlob->Release();
    if (FAILED(hr))
        return hr;
    // 
    // Create vertex buffer
    SimpleVertex vertices[] =
    {
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
    };

    D3D11_BUFFER_DESC bd;
    memset(&bd, 0, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(SimpleVertex) * 24;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA InitData;
    memset(&InitData, 0, sizeof(InitData));
    InitData.pSysMem = vertices;
    hr = g_device.CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
    if (FAILED(hr))
        return hr;
    // 
    // Set vertex buffer
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    g_devicecontext.IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

    // Create index buffer
    // Create vertex buffer
    WORD indices[] =
    {
        3,1,0,
        2,1,3,

        6,4,5,
        7,4,6,

        11,9,8,
        10,9,11,

        14,12,13,
        15,12,14,

        19,17,16,
        18,17,19,

        22,20,21,
        23,20,22
    };
    // 
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(WORD) * 36;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    InitData.pSysMem = indices;
    hr = g_device.CreateBuffer(&bd, &InitData, &g_pIndexBuffer);
    if (FAILED(hr))
        return hr;

    // Set index buffer
    g_devicecontext.IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    // 
    // Set primitive topology
    g_devicecontext.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(Camera);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    hr = g_device.CreateBuffer(&bd, nullptr, &g_Camera);
    if (FAILED(hr))
        return hr;

    bd.ByteWidth = sizeof(CBChangesEveryFrame);
    hr = g_device.CreateBuffer(&bd, nullptr, &g_pCBChangesEveryFrame);
    if (FAILED(hr))
        return hr;

    // Load the Texture
    g_ModelTexture.init(g_device, "seafloor.dds");

    if (FAILED(hr))
        return hr;
    // 
    // Create the sample state
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = g_device.CreateSamplerState(&sampDesc, &g_samplerstate.m_sampler);
    if (FAILED(hr))
        return hr;

    // Initialize the world matrices
    g_World = XMMatrixIdentity();

    // Initialize the view matrix
    XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
    XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    g_View = XMMatrixLookAtLH(Eye, At, Up);



    // Initialize the projection matrix
    g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, g_window.m_width / (FLOAT)g_window.m_height, 0.01f, 100.0f);

    cam.mView = XMMatrixTranspose(g_View);
    cam.mProjection = XMMatrixTranspose(g_Projection);

    return S_OK;

}

void 
update(float deltatime){
    // Update our time

    if (g_driverType == D3D_DRIVER_TYPE_REFERENCE)
    {
        g_Time.m_deltaTime += (float)XM_PI * 0.0125f;
    }
    else
    {
        static unsigned int dwTimeStart = 0;
        unsigned int dwTimeCur = GetTickCount();
        if (dwTimeStart == 0)
            dwTimeStart = dwTimeCur;
        g_Time.m_deltaTime = (dwTimeCur - dwTimeStart) / 1000.0f;
    }

    g_World = XMMatrixScaling(.5f, .5f, .5f) * XMMatrixRotationY(g_Time.m_deltaTime) * XMMatrixTranslation(PosicionVec.x, PosicionVec.y, PosicionVec.z);
    //
    // Update variables that change once per frame
    //
    CBChangesEveryFrame cb;
    cb.mWorld = XMMatrixTranspose(g_World);
    cb.vMeshColor = g_vMeshColor;



    //Update Mesh Buffers
    g_devicecontext.m_deviceContext->UpdateSubresource(g_pCBChangesEveryFrame, 0, nullptr, &cb, 0, 0);
    g_devicecontext.m_deviceContext->UpdateSubresource(g_Camera, 0, nullptr, &cam, 0, 0);

}

void
destroy(){
    //if (g_devicecontext.m_deviceContext) g_devicecontext.m_deviceContext->ClearState();
    g_devicecontext.destroy();
    g_samplerstate.destroy();
    g_ModelTexture.destroy();

    if (g_Camera) g_Camera->Release();
    if (g_pCBChangesEveryFrame) g_pCBChangesEveryFrame->Release();
    if (g_pVertexBuffer) g_pVertexBuffer->Release();
    if (g_pIndexBuffer) g_pIndexBuffer->Release();
    if (g_pVertexShader) g_pVertexShader->Release();
    if (g_pPixelShader) g_pPixelShader->Release();

    g_depthStencil.destroy();
    g_depthStencilView.destroy();
    g_renderTargetView.destroy();
    g_swapChain.destroy();
    g_device.destroy();
}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT 
CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        //For the movement section we make that every time a 
        //letter is entered on the keyboard, it changes its position in x, y or z
        //depending on the letter
        switch (wParam)
        {
        case 'A': 
            PosicionVec.x -= Speed * g_Time.m_deltaTime;//when you press the letter a, the cube will move to the left, 
            //causing the velocity to be subtracted from the vector in x multiplying with real time
            break;
        case 'D':
            PosicionVec.x += Speed * g_Time.m_deltaTime; //when you press the letter d, the cube will move to the right, 
            //causing the velocity to be added to the vector in x multiplying with real time
            break;
        case 'W': 
            PosicionVec.y += Speed * g_Time.m_deltaTime; //when you press the letter w, the cube will move up, 
                //causing the velocity to be added to the vector in y multiplying with the real time
            break;
        case 'S': 
            PosicionVec.y -= Speed * g_Time.m_deltaTime; //when you press the letter s, the cube will move down,
            //causing the vector to slow down in y multiplying with real time
            break;
        case 'Z': 
            PosicionVec.z += Speed * g_Time.m_deltaTime; //when you press the letter z, the cube will move to the bottom, 
            //causing the speed to be added to the vector in z multiplying with the real time
            break;
        case 'X': 
            PosicionVec.z -= Speed * g_Time.m_deltaTime; //when you press the letter z, the cube will move forward, 
            //causing the velocity to be subtracted from the vector in z multiplying with real time
            break;
   
   
        }

        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}



//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void 
Render(){
    // Clear the back buffer
       //
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
    g_devicecontext.ClearRenderTargetView(g_renderTargetView.m_renderTargetView, ClearColor);
    //
    // Clear the depth buffer to 1.0 (max depth)
    //
    g_devicecontext.ClearDepthStencilView(g_depthStencilView.m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    g_devicecontext.OMSetRenderTargets(1, &g_renderTargetView.m_renderTargetView, g_depthStencilView.m_pDepthStencilView);
    g_devicecontext.RSSetViewports(1, &g_viewport.m_viewport);


    //Set inputlayout
    g_devicecontext.IASetInputLayout(g_inputLayout.m_inputLayout);

    //
    // Render the cube
    //
    g_devicecontext.VSSetShader(g_pVertexShader, nullptr, 0);
    g_devicecontext.VSSetConstantBuffers(0, 1, &g_Camera);

    g_devicecontext.VSSetConstantBuffers(1, 1, &g_pCBChangesEveryFrame);
    g_devicecontext.PSSetShader(g_pPixelShader, nullptr, 0);

    g_devicecontext.PSSetConstantBuffers(1, 1, &g_pCBChangesEveryFrame);
    g_devicecontext.PSSetShaderResources(0, 1, &g_ModelTexture.m_textureFromImg);

    g_devicecontext.PsSetSamplers(0, 1, &g_samplerstate.m_sampler);
    g_devicecontext.DrawIndexed(36, 0, 0);

    //
    // Present our back buffer to our front buffer
    //
    g_swapChain.present();
}