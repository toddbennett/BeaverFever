/**
 * BEAVER FEVER / LEAVE IT TO BEAVER / I CAN'T BEAVER IT'S NOT BUTTER /
 * JUSTIN BEAVER
 * A summer project by Todd and Tyson
 *
 * Original work, do not steal
 */

#include <stdio.h>
#include <Windows.h>
#include <D3D9.h>

#include "Baxter.h"
#include "Geometry.h"
// You're right, we need these here...
// Why are these not defined in Windows.h?
#define VK_A 0x0041
#define VK_D 0x0044
#define VK_S 0x0053
#define VK_W 0x0057
#define gravity f0.01 //Define gravity as a universal constant so it's easy to tweak later

//color codes for ease of use

#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
//This apparently defines what information we want to pass through to the hardware, so as not to waste time
//D3DFVF_XYZRHW passes xyz geometry coordinates plus information for converting to screen coordinates. D3DFVF_DIFFUSE passes a color for diffuse lighting
//Eventually we will define different formats with D3DFVF_TEX0 which is for textured models





Baxter *bax; //Create pointer to instance of Baxter named bax

/**
 * d3d_init
 *
 * Initializes Direct3D 9, specifically an IDirect3D9 and an IDirect3DDevice9
 */
int d3d_init(
	IDirect3D9 **d3d,				// OUT
	HWND window,					// IN
	IDirect3DDevice9 **d3dDevice	// OUT
	)
{
	HRESULT result;
	D3DPRESENT_PARAMETERS params;

	// Supposedly this is the best practice for initializing things. ={}
	// doesn't work with bitfields or some such thing. I read too much
	// StackExchange.
	ZeroMemory(&params, sizeof(params));

	*d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (*d3d == NULL) {
		return 1;
	}

	params.Windowed = TRUE;
	params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	params.hDeviceWindow = window;
	result = (*d3d)->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_MIXED_VERTEXPROCESSING,
		&params,
		d3dDevice
		);
	if (result != D3D_OK) {
		return 1;
	}

	return 0;
}
/**
 * getLastErrorString
 *
 * Returns a string from Windows indicating what the deal is.
 */
char *getLastErrorString()
{
	DWORD errorCode = GetLastError();
	LPTSTR errorString;

	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		errorCode,
		NULL,
		(LPTSTR) &errorString, // not a bug
		NULL,
		NULL
	);

	return errorString;
}

LRESULT CALLBACK wndProc(
	HWND hWnd,		// handle to window
	UINT uMsg,		// message information
	WPARAM wParam,	// parameters to message
	LPARAM lParam	// more parameters to message
)
{

	switch (uMsg) {
	case WM_QUIT:
		return DestroyWindow(hWnd);
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
	{
		case VK_A:
			bax->turn(-0.1);
		case VK_D:
			bax->turn(0.1);
		case VK_W:
			bax->move(0.5);
		case VK_S:
			bax->move(-0.3);
	}
		return 0;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

/**
 * Draws some stuff every time? Maybe a cube?
 *
 * Returns 1 at the first sign of a problem, 0 otherwise.
 */
int d3d_draw_test(IDirect3DDevice9 *d3dDevice, IDirect3DVertexBuffer9 *d3dVertexBuffer)
{
	if (d3dDevice->BeginScene()) {
		return 1;
	}
	d3dDevice->SetFVF(CUSTOMFVF);
	d3dDevice->SetStreamSource(0,d3dVertexBuffer,0,sizeof(CUSTOMVERTEX));
	d3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST ,0,1);
	if (d3dDevice->EndScene()) {
		return 1;
	}

	if (d3dDevice->Present(NULL, NULL, NULL, NULL)) {
		return 1;
	}

	return 0;
}

/**
 * WinMain
 *
 * Entry point, set things up and enter the message loop.
 */
int WINAPI WinMain(
	HINSTANCE	hInstance,		// Instance of application
	HINSTANCE	hPrevInstance,	// DEPRECATED
	LPSTR		lpCmdLine,		// Command line arguments
	int			nCmdShow		// Display hints
	)
{
	WNDCLASS wndClass;
	HWND window;
	MSG message;
	BOOL test;
	HRESULT result;
	IDirect3D9 *d3d;
	IDirect3DDevice9 *d3dDevice;
	IDirect3DVertexBuffer9 *d3dVertexBuffer;
	IDirect3DVertexShader9 *pShader;

	bax = new Baxter();
	ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.lpfnWndProc = wndProc;
	wndClass.hInstance = hInstance;
	wndClass.lpszClassName = "Beaver Fever";
	if(!RegisterClass(&wndClass)) {
		MessageBox(NULL, getLastErrorString(), "RegisterClass Error", NULL);
		return 1;
	}
	
	window = CreateWindow(
		"Beaver Fever",
		"Beaver Fever",
		WS_OVERLAPPEDWINDOW,
		0, 0,		// X, Y,
		800, 600,	// W, H,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!window) {
		MessageBox(NULL, getLastErrorString(), "CreateWindow Error", NULL);
		return 1;
	}
	
	ShowWindow(window, nCmdShow);
    UpdateWindow(window);

	if (d3d_init(&d3d, window, &d3dDevice)) {
		MessageBox(NULL, "d3d_init failed!", NULL, NULL);
		return 1;
	}

	result = d3dDevice->CreateVertexBuffer(
		1024,
		0,
		0,
		D3DPOOL_DEFAULT,
		&d3dVertexBuffer,
		NULL
	);
	if (result) {
		MessageBox(NULL, getLastErrorString(), "CreateVertexBuffer Error", NULL);
		return 1;
	}
	//Put our cube on the vertex buffer
	VOID* pVoid; //This is a pointer to an undefined space I guess? The tutorial told me I needed one
	d3dVertexBuffer->Lock(0,0,(void**)&pVoid, 0);
	memcpy(pVoid,Cube,sizeof(Cube));
	d3dVertexBuffer->Unlock();
    while ((test = GetMessage(&message, NULL, 0, 0)) != 0) {
		if (d3d_draw_test(d3dDevice,d3dVertexBuffer)) {
			MessageBox(NULL, "d3d_draw_test failed!", NULL, NULL);
			return 1;
		}
		if (test == -1) {
			MessageBox(NULL, getLastErrorString(), "GetMessage Error", NULL);
			return 1;
		}
		else {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	
	return message.wParam;
}