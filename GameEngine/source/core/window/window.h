#pragma once
#include "./core/event/event.h"
//
#include <string>
#include <windows.h>


class Window
{
public:
	Window(const std::string& _title, const uint32_t _width, const uint32_t _height);
	~Window();

	// Updates windows event queue and processes events
	void PollEvents();

	// Shows window or hides main application window
	void Show();
	void Hide();

	// Functions to help with window closure
	void Close();
	// TODO:: Replace with event system callback
	inline bool ShouldClose() const { return m_Closed; }

	// Getters for the native window handle
	inline HWND GetWindowHandle() const { return m_WindowHandle; }
	inline void* GetWindowHandlePtr() const { return m_WindowHandle; } 

	// Getter for the window title
	inline const std::string GetTitle() const { return m_Title; }

	// Getters for window dimension
	inline uint32_t GetWidth() const { return m_Width; }
	inline uint32_t GetHeight() const { return m_Height; }

	// Event callback
	EventCallbackFn EventCallback = nullptr;
	virtual void SetEventCallback(const EventCallbackFn& _callback) { EventCallback = _callback; }

private:
	HWND m_WindowHandle;  // Main window handle used to reference the window in various API's

	// General window information
	std::string m_Title;
	uint32_t m_Width;
	uint32_t m_Height;

	bool m_Closed   = false;
	bool m_Focussed = false; // Whether or not the window is currently in focus
};