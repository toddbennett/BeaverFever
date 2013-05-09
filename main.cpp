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

const char className[] = "beaverfeverwinclass";

WNDCLASSEX winclass;

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
	HRESULT result = 0;
	D3DPRESENT_PARAMETERS params = {};

	*d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (*d3d == NULL) {
		return 0;
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

char *getLastErrorString()
{
	DWORD errorCode = GetLastError();
	LPTSTR errorString;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		errorCode,
		0,
		(LPTSTR) &errorString, // not a bug
		0,
		NULL
	);

	return errorString;
}

LRESULT CALLBACK WndProc(
	HWND hwnd,		// handle to window
	UINT uMsg,		// message information
	WPARAM wParam,	// parameters to message
	LPARAM lParam	// more parameters to message
)
{
    switch(uMsg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

/**
 * Fills in our WNDCLASSEX.
 */
void init_winclass(HINSTANCE hInstance)
{
	winclass.cbSize = sizeof(WNDCLASSEX);	// This is stupid.
	winclass.style = 0; // There's lots of things to do with this, but we don't
						// need any of them just yet...
	winclass.lpfnWndProc = WndProc;	// Procedure to handle window
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = className;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
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
 * This is our entry point because LOL windoze. I hope you're happy!
 */
int WINAPI WinMain(
	HINSTANCE	hInstance,		// handle to instance of application
	HINSTANCE	hPrevInstance,	// DEPRECATED
	LPSTR		lpCmdLine,		// cmd args
	int			nShowCmd		// Google winmain to learn all about this on
								// MSDN. we should deal with it eventually.
								// It's a bunch of display hints.
)
{
	ATOM winclassatom;
	HWND window;
	MSG message;

	IDirect3D9 *d3d;
	IDirect3DDevice9 *d3dDevice;

	// Set up our window class WHY IS THIS SO MUCH WORK
	// I DON'T EVEN KNOW WHAT A WINDOW CLASS IS
	init_winclass(hInstance);
	winclassatom = RegisterClassEx(&winclass);
	if (!winclassatom) {
		printf(getLastErrorString());
		return 1;
	}
	
	window = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		className,
		"BeaverFever!",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		600,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!window) {
		MessageBox(NULL, "CreateWindowEx failed!", NULL, NULL);
		return 1;
	}
	
	ShowWindow(window, nShowCmd);
    UpdateWindow(window);

	if (d3d_init(&d3d, window, &d3dDevice)) {
		MessageBox(NULL, "d3d_init failed!", NULL, NULL);
		return 1;
	}

    while (1) {
		BOOL test;	// Why the fuck did Micro$haft make this a BOOL when
					// it can be a bunch of different values what the hell
		d3d_draw_test(d3dDevice);
		test = GetMessage(&message, window, 0, 0);
		if (test == 0) {
			break;
		}
		if (test == -1) {
			char *s = getLastErrorString();
			return 1;
		}
		else {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	
	return message.wParam;
}