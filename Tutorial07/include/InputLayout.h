#pragma once
#include "Prerequisities.h"

//Call to the Class is begin used in cpp (Device)
class
	Device;

class InputLayout
{
public:
	InputLayout() = default;
	~InputLayout() { SAFE_RELEASE(m_inputLayout) };

	// Create the input layout, it need a vector & device
	void
		init(Device device,
			std::vector<D3D11_INPUT_ELEMENT_DESC> Layout,
			ID3DBlob* VertexShaderData);

	void
		update();

	void
		render();

	void
		destroy();

public:
	ID3D11InputLayout* m_inputLayout = nullptr;

};