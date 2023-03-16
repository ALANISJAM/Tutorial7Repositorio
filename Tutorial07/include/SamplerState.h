#pragma once
#include "Prerequisities.h"

//se llaman las clases que vamos a usar
class 
Device;

class
SamplerState
{
public:
SamplerState() = default;
~SamplerState(){};

void
init(Device device);

void
update();

void
render();

void
destroy();

public:
//se igualan las variables que necesitamos
ID3D11SamplerState* m_sampler = nullptr;
};

