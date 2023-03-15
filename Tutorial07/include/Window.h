#pragma once
#include "Prerequisities.h"
#include "Commons.h"


class
	Window {
public:
	Window();
	~Window();

	HRESULT
		init(HINSTANCE hinstance, int nCmdShow, WNDPROC wndProc, LPCSTR windowName);
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
	HWND m_hWnd = nullptr;
	HINSTANCE m_hInst = nullptr;
	RECT m_rect;
	unsigned int m_width;
	unsigned int m_height;
	LPCSTR m_windowName = "HeartBlast Engine";
	
};