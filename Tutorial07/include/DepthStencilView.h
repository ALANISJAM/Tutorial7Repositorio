#include "Prerequisities.h"
#pragma once

//se llaman las clases que vamos a usar
class
	Device;

class
	DepthStencilView
{
public:
	DepthStencilView() = default;
	~DepthStencilView() { SAFE_RELEASE(m_pDepthStencilView) };

	// creamos el depthstencilview
	void
		init(Device device, ID3D11Resource* depthStencil, DXGI_FORMAT Format);

	void
		update();

	void
		render();

	void
		destroy();

public:
	//se igualan las variables que necesitamos
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;

};