#pragma once
#include "Prerequisities.h"
#include "Commons.h"

//se llaman las clases que vamos a usar
class
Device;

class
Texture
{
public:
Texture() = default;
~Texture() {};

void
init(Device device, std::string textureName);

void
init(Device device,
unsigned int width,
unsigned int height,
DXGI_FORMAT Format,
unsigned int BindFlags);

void
update();

void
render();

void
destroy();


public:
//se igualan las variables que necesitamos
ID3D11Texture2D* m_texture = nullptr;
ID3D11ShaderResourceView* m_textureFromImg = nullptr;

};
