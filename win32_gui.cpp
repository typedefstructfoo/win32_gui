#include <windows.h>

bool app_running = false;

LRESULT CALLBACK
MyWndProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	LRESULT Result = 0;
	switch(Message)
	{
		case WM_CREATE:
		{
			HWND CloseButton = CreateWindow("button",NULL,
											WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
											600-18,0,18,16,Window,(HMENU)1,
											GetModuleHandle(NULL),NULL);
		} break;
		
		case WM_NCHITTEST:
		{
			if(DefWindowProc(Window, Message, WParam, LParam) == HTCLIENT)
			{
				Result = HTCAPTION;
			}
		} break;

		case WM_COMMAND:
		{
			switch(WParam)
			{
				case 1:
					DestroyWindow(Window);
				break;
			}
		} break;
		
		case WM_CLOSE:
		{
			app_running = false;
			DestroyWindow(Window);
		} break;

		case WM_DESTROY:
		{
			app_running = false;
			PostQuitMessage(0);
		} break;

		default:
		{
			Result = DefWindowProc(Window, Message, WParam, LParam);
		} break;		
	}
	return Result;
}

int CALLBACK
WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CommandLine, int CommandShow)
{
	WNDCLASSEX WindowClass = {};
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style  = CS_HREDRAW;
	WindowClass.lpfnWndProc = MyWndProc;
	WindowClass.hInstance = Instance;
	WindowClass.lpszClassName = "CustomGui";
	
	MSG Message;
	
	if(RegisterClassEx(&WindowClass))
	{
		HWND Window = CreateWindowEx(WS_EX_LAYERED,WindowClass.lpszClassName,
									 "CustomGui Title",
									 WS_POPUP|WS_VISIBLE,
									 100, 100, 600, 400,
									 0, 0, Instance, 0);

		SetLayeredWindowAttributes(Window, RGB(255, 255, 255), 255, LWA_ALPHA);
		
		if(Window)
		{
			app_running = true;
			while(app_running)
			{
				while(PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
			}
		}
	}

	return Message.wParam;
}
