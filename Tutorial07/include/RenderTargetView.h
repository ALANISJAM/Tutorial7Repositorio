#pragma once
#include "Prerequisities.h"

//se llaman las clases que vamos a usar
class
	Device;
class
	Texture;

class RenderTargetView
{
public:
	RenderTargetView() = default;
	~RenderTargetView() {};

	void
		init(Device device, Texture backBuffer, DXGI_FORMAT Format);

	void
		update();

	void
		render();

	void
		destroy();

public:
	//se igualan las variables que necesitamoss
	ID3D11RenderTargetView* m_renderTargetView = nullptr;

};