#include "Prerequisities.h"
#pragma once

class DeviceContext
{
public:
	DeviceContext() = default;
	~DeviceContext() { SAFE_RELEASE(m_deviceContext) };

	void
		init();

	void
		update();

	void
		render();

	void
		destroy();

	void
		PsSetSamplers(unsigned int StartSlot,
			unsigned int NumSamplers,
			ID3D11SamplerState* const* ppSamplers
		);
	void
		DrawIndexed(unsigned int IndexCount,
			unsigned int StartIndexLocation,
			unsigned int BaseVertexLocation
		);
	void
		PSSetShaderResources(UINT StartSlot,
			UINT NumViews,
			ID3D11ShaderResourceView* const* ppShaderResourceViews
		);

	void
		PSSetConstantBuffers(UINT StartSlot,
			UINT NumBuffers,
			ID3D11Buffer* const* ppConstantBuffers
		);

	void
		PSSetShader(ID3D11PixelShader* pPixelShader,
			ID3D11ClassInstance* const* ppClassInstances,
			UINT NumClassInstances
		);


	void
		VSSetConstantBuffers(UINT StartSlot,
			UINT NumBuffers,
			ID3D11Buffer* const* ppConstantBuffers
		);

	void
		VSSetShader(ID3D11VertexShader* pVertexShader,
			ID3D11ClassInstance* const* ppClassInstances,
			UINT NumClassInstances
		);

	void
		ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
			UINT ClearFlags,
			FLOAT Depth,
			UINT8 Stencil

		);

	void
		ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
			const FLOAT ColorRGBA[4]
		);

	void
		OMSetRenderTargets(UINT NumViews,
			ID3D11RenderTargetView* const* ppRenderTargetViews,
			ID3D11DepthStencilView* pDepthStencilView
		);


	void
		RSSetViewports(UINT NumViewports,
			const D3D11_VIEWPORT* pViewports
		);

	void
		IASetInputLayout(ID3D11InputLayout* pInputLayout
		);

	void
		IASetVertexBuffers(UINT StartSlot,
			UINT NumBuffers,
			ID3D11Buffer* const* ppVertexBuffers,
			const UINT* pStrides,
			const UINT* pOffsets
		);

	void
		IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
			DXGI_FORMAT Format,
			UINT Offset
		);

	void
		IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology
		);




public:
	ID3D11DeviceContext* m_deviceContext = nullptr;
};
