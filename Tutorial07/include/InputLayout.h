#pragma once
#include "Prerequisities.h"
//se llaman las clases que vamos a usar
class
Device;

class InputLayout
{
public:
InputLayout() = default;
~InputLayout() { SAFE_RELEASE(m_inputLayout) };

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
//se igualan las variables que necesitamos
ID3D11InputLayout* m_inputLayout = nullptr;

};