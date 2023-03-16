#include "DeviceContext.h"

void
DeviceContext::init() {

}

void
DeviceContext::update() {

}

void
DeviceContext::render() {

}

void
DeviceContext::destroy() {
	m_deviceContext->ClearState();
}

void
DeviceContext::DrawIndexed(unsigned int IndexCount,
						               unsigned int StartIndexLocation,
						               unsigned int BaseVertexLocation) {
	m_deviceContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

void
DeviceContext::PsSetSamplers(unsigned int StartSlot,
	                           unsigned int NumSamplers,
	                           ID3D11SamplerState* const* ppSamplers) {
	m_deviceContext->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void 
DeviceContext::PSSetShaderResources(UINT StartSlot,
	                                  UINT NumViews,
	                                  ID3D11ShaderResourceView* const* ppShaderResourceViews = 0) {
	m_deviceContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void
DeviceContext::PSSetConstantBuffers(UINT StartSlot,
	                                  UINT NumBuffers,
	                                  ID3D11Buffer* const* ppConstantBuffers) {
	m_deviceContext->PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void 
DeviceContext::PSSetShader(ID3D11PixelShader* pPixelShader,
	                         ID3D11ClassInstance* const* ppClassInstances,
	                         UINT NumClassInstances

) {
	m_deviceContext->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
}

void
DeviceContext::VSSetConstantBuffers(UINT StartSlot,
	                                  UINT NumBuffers,
	                                  ID3D11Buffer* const* ppConstantBuffers
) {
	m_deviceContext->VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void
DeviceContext::VSSetShader(ID3D11VertexShader* pVertexShader,
	                         ID3D11ClassInstance* const* ppClassInstances,
	                         UINT NumClassInstances
) {
	m_deviceContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
}

void
DeviceContext::ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
	                                   UINT ClearFlags,
	                                   FLOAT Depth,
	                                   UINT8 Stencil

) {
	m_deviceContext->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
}

void 
DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
	                                   const FLOAT ColorRGBA[4]
) {
	m_deviceContext->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}

void
DeviceContext::OMSetRenderTargets(UINT NumViews,
	                                ID3D11RenderTargetView* const* ppRenderTargetViews,
	                                ID3D11DepthStencilView* pDepthStencilView
) {
	m_deviceContext->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
}

void
DeviceContext::RSSetViewports(UINT NumViewports,
	                            const D3D11_VIEWPORT* pViewports
) {
	m_deviceContext->RSSetViewports(NumViewports, pViewports);
}
void
DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout
) {
	m_deviceContext->IASetInputLayout(pInputLayout);
}

void
DeviceContext::IASetVertexBuffers(UINT StartSlot,
	                                UINT NumBuffers,
	                                ID3D11Buffer* const* ppVertexBuffers,
	                                const UINT* pStrides,
	                                const UINT* pOffsets
) {
	m_deviceContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void
DeviceContext::IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
	                              DXGI_FORMAT Format,
	                              UINT Offset
) {
	m_deviceContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}

void
DeviceContext::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology
) {
	m_deviceContext->IASetPrimitiveTopology(Topology);
}