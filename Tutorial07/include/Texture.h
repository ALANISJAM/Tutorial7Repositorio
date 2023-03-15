#pragma once
#include "Prerequisities.h"
#include "Commons.h"

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
	
	ID3D11Texture2D* m_texture = nullptr;


	ID3D11ShaderResourceView* m_textureFromImg = nullptr;

};
