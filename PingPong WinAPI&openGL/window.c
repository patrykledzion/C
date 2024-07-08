#include "window.h"

#include <Windows.h>
#include <stdlib.h>
#include <gl/GL.h>

static ATOM windowClass = (ATOM)null;

LRESULT Wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	window* w = (window*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
	switch (message)
	{
	case WM_KEYDOWN:
		w->keysPressed[wParam] = 1;
		break;
	case WM_KEYUP:
		w->keysPressed[wParam] = 0;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

WNDCLASS createWindowClass()
{
	if (windowClass != null)return;

	WNDCLASS wc = {
		.style = 0,
		.lpfnWndProc = &Wndproc,
		.cbClsExtra = 0,
		.cbWndExtra = 0,
		.hInstance = null,
		.hIcon = null,
		.hCursor = null,
		.hbrBackground = COLOR_WINDOWTEXT,
		.lpszMenuName = null,
		.lpszClassName = CLASS_NAME
	};

	windowClass = RegisterClass(&wc);
}

window* createWindow(int width, int height, char* title)
{
	createWindowClass();

	window* w = malloc(sizeof(window));

	if (w == null)
	{
		return null;
	}


	//Creating window
	HWND wnd = CreateWindowExA(
		0,
		windowClass,
		title,
		WS_TILEDWINDOW,
		200, 200,			//X,Y
		width, height,
		null,
		null,
		null,
		null
	);

	if (wnd == NULL)
	{
		free(w);
		return null;
	}
	w->instance = wnd;
	SetWindowLongPtrW(wnd, GWLP_USERDATA, (LONG_PTR)w);
	ShowWindow(wnd, SW_SHOW);

	//Getting drawing context 
	HDC context = GetDC(wnd);

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,	//struct version
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		32, //Color bits,
		8,	//R
		0,	//R-S
		8,	//G
		0,	//G-S
		8,	//B
		0,	//B-S
		8,  //A
		0,	//A-S
		32, //Accum
		8,8,8,8, //Depth
		24,
		8,	//Stencil
		0,	//AUX
		PFD_MAIN_PLANE,
		0,	//visible mask
		0	//Dmg mask
	};

	int res = ChoosePixelFormat(context, &pfd);
	BOOL ret = SetPixelFormat(context, res, &pfd);

	HGLRC glInstance = wglCreateContext(context);
	wglMakeCurrent(context, glInstance);


	RECT rcCli;
	GetClientRect(WindowFromDC(context), &rcCli);

	w->width = (int)rcCli.right;
	w->height = (int)rcCli.bottom;
	w->offsetX = 0;
	w->offsetY = 10;

	for (int i = 0; i < 0xFF; i++)
	{
		w->keysPressed[i] = 0;
	}


	return w;

}

void updateWindow()
{
	MSG msg;

	if (PeekMessage(&msg, 0, 0, 0, 1))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

int isWindowOpened(window* window)
{
	return IsWindow(window->instance);
}

void startDraw(window* window)
{
	long width = (long)window->width;
	long height = (long)window->height;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(0.0l, width, height, 0.0l, -1.0l, 1.0l);
	glViewport(0, 0, width, height);
}

void endDraw(window* window)
{
	HDC dc = GetDC(window->instance);
	SwapBuffers(dc);
	ReleaseDC(window->instance, dc);
}

void renderFrame(window* window)
{
}

