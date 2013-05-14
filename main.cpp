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
#include <math.h>

#define VK_A 0x0041
#define VK_D 0x0044
#define VK_S 0x0053
#define VK_W 0x0057


// Baxter structure. this should be put in a header or something depending on how you want to do it
struct Baxter{
float x,y,z;  //coordinates in 3d space
float facing; //angle of facing in radians. could also do degrees if you prefer. 0 is right along the y-axis
void init() //funtion that initializes all of Baxter's variables to 0 just in case
{
	x=0;
	y=0;
	z=0;
	facing=0;
}
void move(float distance)//function that moves Baxter with facing. distance should be passed in as a speed variable. Negative value denotes moving backwards
{
	x = x + distance*sin(facing);
	y = y + distance*cos(facing);
}
//obviously more variables later
};

Baxter *Bax; //Create pointer to instance of Baxter named Bax
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
			Bax->facing -= 0.1;
		case VK_D:
			Bax->facing += 0.1;
		case VK_W:
			Bax->move(0.5);
		case VK_S:
			Bax->move(-0.3);
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
int d3d_draw_test(IDirect3DDevice9 *d3dDevice)
{
	if (d3dDevice->BeginScene()) {
		return 1;
	}

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

	Bax->init();
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


    while ((test = GetMessage(&message, NULL, 0, 0)) != 0) {
		if (d3d_draw_test(d3dDevice)) {
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