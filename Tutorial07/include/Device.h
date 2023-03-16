#include "Prerequisities.h"
#pragma once

class 
Device
{
public:
Device() = default;
~Device() { SAFE_RELEASE(m_device) };

void
init();

void
update();

void
render();

void
destroy();

	
HRESULT
//Pointer to the resource that will serve as the depth-stencil surface.
CreateDepthStencilView(ID3D11Resource* pResource,
                       const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
                       ID3D11DepthStencilView** ppDepthStencilView);

	
HRESULT
//Creates a render-target view for accessing resource data
CreateRenderTargetView(ID3D11Resource* pResource,
                       const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
                       ID3D11RenderTargetView** ppRTView);

	
HRESULT
//creates a 2D texture resource, which can contain a number of 2D subresources
CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
                const D3D11_SUBRESOURCE_DATA* pInitialData,
                ID3D11Texture2D** ppTexture2D);

	
HRESULT
//Create a vertex-shader object from a compiled shader.
CreateVertexShader(const void* pShaderBytecode,
                   unsigned int BytecodeLength,
                   ID3D11ClassLinkage* pClassLinkage,
                   ID3D11VertexShader** ppVertexShader);

	
HRESULT
//Create an input-layout object to describe the input-buffer data for the input-assembler stage.
CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
                  unsigned int NumElements,
                  const void* pShaderBytecodeWithInputSignature,
                  unsigned int BytecodeLength,
                  ID3D11InputLayout** ppInputLayout);

	
HRESULT
//This method returns one of the following Direct3D 11 Return Codes. 
CreatePixelShader(const void* pShaderBytecode,
                  unsigned int BytecodeLength,
                  ID3D11ClassLinkage* pClassLinkage,
                  ID3D11PixelShader** ppPixelShader);

	
HRESULT
//Creates a buffer (vertex buffer, index buffer, or shader-constant buffer).
CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
             const D3D11_SUBRESOURCE_DATA* pInitialData,
             ID3D11Buffer** ppBuffer);

	
HRESULT
//Create a sampler-state object that encapsulates sampling information for a texture
CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
                   ID3D11SamplerState** ppSamplerState);

public:
//se igualan las variables que necesitamos
ID3D11Device* m_device = nullptr;
};

