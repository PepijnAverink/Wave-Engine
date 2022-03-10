#include "./core/window/window.h"
#include "./core/event/window/window_resize_event.h"

// Static forward declare
static Window* s_Window = nullptr;
static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// Forward declare function
// These function are used to determine windows border size to get the actual screen dimensions you want
int GetSingleBorder();
int GetDefaultBorderHeight();
int GetDefaultBorderWidth();

Window::Window(const std::string& _title, const uint32_t _width, const uint32_t _height)
	: m_Title(_title)
	, m_Width(_width)
	, m_Height(_height)
{
	// Set static
	s_Window = this;

	// WindowClass
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// Window Properties
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(wc.hInstance, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = "WindowClass";
	wc.hIconSm = LoadIcon(wc.hInstance, IDI_APPLICATION);

	// register the window class
	RegisterClassEx(&wc);

	DWORD flags = WS_OVERLAPPED;
	flags |= WS_CAPTION | WS_SYSMENU;
	flags |= WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;


	// create the window and use the result as the handle
	m_WindowHandle = CreateWindowEx(NULL, "WindowClass", _title.c_str(), flags, CW_USEDEFAULT, CW_USEDEFAULT,
		m_Width + GetDefaultBorderWidth(), m_Height + GetDefaultBorderHeight(), NULL, NULL, GetModuleHandle(NULL), NULL);
}

Window::~Window()
{

}

void Window::PollEvents()
{
	// Focussed
	m_Focussed = (m_WindowHandle == GetForegroundWindow());

	// Handle messages
	MSG msg;
	while (PeekMessage(&msg, m_WindowHandle, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Window::Show()
{
	ShowWindow(m_WindowHandle, SW_SHOW);
}

void Window::Hide()
{
	ShowWindow(m_WindowHandle, SW_HIDE);
}

void Window::Close()
{
	m_Closed = true;
}

int GetSingleBorder()
{
	const int sizingBorder = GetSystemMetrics(SM_CYFRAME);
	const int borderPadding = GetSystemMetrics(SM_CXPADDEDBORDER);
	return     sizingBorder + borderPadding;
}

int GetDefaultBorderHeight()
{
	return GetSingleBorder() * 2 + GetSystemMetrics(SM_CYCAPTION);
}

int GetDefaultBorderWidth()
{
	return GetSingleBorder() * 2;
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Sort through the messages
	switch (message)
	{
		case WM_DESTROY:
		{
			// TODO:: Let engine know window is closed
			s_Window->Close();

			PostQuitMessage(0);
			break;
		}
		case WM_SIZE:
		{
			UINT width = LOWORD(lParam);
			UINT height = HIWORD(lParam);

			// Do not dispatch event on creation
			if (s_Window->GetWidth() == width && s_Window->GetHeight() == height)
				break;

			// Dispatch event
			if (s_Window->EventCallback != nullptr)
			{
				WindowResizeEvent event = WindowResizeEvent(width, height);
				s_Window->EventCallback(event);
			}
			break;
		}
	}
	// Handle any messages the switch statement didn't
	return DefWindowProc(hwnd, message, wParam, lParam);
}