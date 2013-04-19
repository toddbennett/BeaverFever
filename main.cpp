/**
 * BEAVER FEVER / LEAVE IT TO BEAVER / I CAN'T BEAVER IT'S NOT BUTTER /
 * JUSTIN BEAVER
 * A summer project by Todd and Tyson
 *
 * Original work, do not steal
 */

#include <Windows.h>

const char className[] = "beaverfeverwinclass";

WNDCLASSEX winclass;

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
 * This is our entry point because LOL windoze. I hope you're happy!
 */
int CALLBACK WinMain(
	HINSTANCE	hInstance,		// handle to instance of application
	HINSTANCE	hPrevInstance,	// DEPRECATED
	LPSTR		lpCmdLine,		// cmd args
	int			nCmdShow		// Google winmain to learn all about this on
								// MSDN. we should deal with it eventually.
								// It's a bunch of display hints.
)
{
	ATOM winclassatom;
	HWND window;
	MSG message;

	// Set up our window class WHY IS THIS SO MUCH WORK
	// I DON'T EVEN KNOW WHAT A WINDOW CLASS IS
	init_winclass(hInstance);
	winclassatom = RegisterClassEx(&winclass);
	if (!winclassatom) {
		MessageBox(NULL, "Could not register winclass!",
			"winclass registration error", MB_ICONSTOP);
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
		MessageBox(NULL, "Could not create window!",
			"Window creation error", MB_ICONSTOP);
		return 1;
	}
	
	ShowWindow(window, nCmdShow);
    UpdateWindow(window);

    while (1) {
		BOOL test;	// Why the fuck did Micro$haft make this a BOOL when
					// it can be a bunch of different values what the hell
		test = GetMessage(&message, window, 0, 0);
		if (test == 0) {
			break;
		}
		if (test == -1) {
			MessageBox(NULL, "ERROR ERROR ERROR ERROR ERROR",
				"I MUST BE COMPLETE", MB_ICONSTOP);
			return 1;
		}
		else {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	
	return message.wParam;
}