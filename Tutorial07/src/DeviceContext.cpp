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