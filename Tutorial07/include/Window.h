#pragma once
#include "Prerequisities.h"
#include "Commons.h"


class
	Window {
public:
	Window();
	~Window();

	HRESULT
		init(HINSTANCE hinstance, int nCmdShow, WNDPROC wndProc);
	void update()
	{

	}

	void render()
	{

	}
	void destroy()
	{

	}
public:
	HWND m_hwnd = nullptr;
	HINSTANCE m_hInst = nullptr;
	RECT m_rect;
	unsigned int m_width;
	unsigned int m_height;
	std::string m_windowName = "HeartBlast Engine";
};