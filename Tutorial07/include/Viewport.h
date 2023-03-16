#pragma once
#include "Prerequisities.h"

//se llaman las clases que vamos a usar
class 
Window;
class 
Viewport
{
public:
Viewport() = default;
~Viewport(){};
void
init(Window window);

void
update();

void
render();

void
destroy();

public:
//se igualan las variables que necesitamos
D3D11_VIEWPORT m_viewport;
};

