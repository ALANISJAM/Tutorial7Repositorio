#include "Prerequisities.h"
#pragma once

class Device
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

	//se crea el depthstencilview
	HRESULT
		CreateDepthStencilView(ID3D11Resource* pResource,
			const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
			ID3D11DepthStencilView** ppDepthStencilView);

	//se crea el rendertargetview
	HRESULT
		CreateRenderTargetView(ID3D11Resource* pResource,
			const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
			ID3D11RenderTargetView** ppRTView);

	//se crean las texturas 2D
	HRESULT
		CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
			const D3D11_SUBRESOURCE_DATA* pInitialData,
			ID3D11Texture2D** ppTexture2D);

	//se crea el vertexshader
	HRESULT
		CreateVertexShader(const void* pShaderBytecode,
			unsigned int BytecodeLength,
			ID3D11ClassLinkage* pClassLinkage,
			ID3D11VertexShader** ppVertexShader);

	//se crea el inputlayout
	HRESULT
		CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
			unsigned int NumElements,
			const void* pShaderBytecodeWithInputSignature,
			unsigned int BytecodeLength,
			ID3D11InputLayout** ppInputLayout);

	//se crea el pixelshader
	HRESULT
		CreatePixelShader(const void* pShaderBytecode,
			unsigned int BytecodeLength,
			ID3D11ClassLinkage* pClassLinkage,
			ID3D11PixelShader** ppPixelShader);

	//se crean los buffers
	HRESULT
		CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
			const D3D11_SUBRESOURCE_DATA* pInitialData,
			ID3D11Buffer** ppBuffer);

	//se crea el samplerstate
	HRESULT
		CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
			ID3D11SamplerState** ppSamplerState);

public:
	ID3D11Device* m_device = nullptr;
};

