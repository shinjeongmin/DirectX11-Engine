#include "Window.h"

#include "InputProcessor.h"

HINSTANCE Window::hInstance;
HWND Window::hwnd;
int Window::width;
int Window::height;
std::wstring Window::title;

// ������ �޽��� ó���� �� ����� ���ν��� �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// â�� ������ ���α׷� ����.
	switch (msg)
	{
	case WM_DESTROY:
		// ���� �޽��� �߻� ��Ŵ.
		PostQuitMessage(0);
		return 0;
	// �Է� ó��.
	case WM_ACTIVATEAPP:
		{
			Keyboard::ProcessMessage(msg, wParam, lParam);
			Mouse::ProcessMessage(msg, wParam, lParam);
		}
		return 0;

	// Ű���� �Է� ó��.
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		{
			Keyboard::ProcessMessage(msg, wParam, lParam);
		}
		return 0;

	// ���콺 �Է� ó��.
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_MOUSEHOVER:
		{
			Mouse::ProcessMessage(msg, wParam, lParam);
		}
		return 0;
	}

	// �⺻ ������ ���ν��� �Լ� ȣ��. (�⺻ �޽����� �����쿡 �ñ�.)
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool Window::InitializeWindow()
{
	return InitializeWindow(hInstance, width, height, title);
}

// ������ ���� �� �ʱ�ȭ.
bool Window::InitializeWindow(HINSTANCE hInstance, int width, int height, std::wstring title)
{
	// ���� �� ����.
	Window::hInstance = hInstance;
	Window::width = width;
	Window::height = height;
	Window::title = title;

	// ������ Ŭ���� ����.
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc)); // ��� 0���� �ʱ�ȭ.

	// �� ����.
	wc.lpszClassName = TEXT("GfxEngine");		// Ŭ���� �̸�.
	wc.hInstance = hInstance;					// �ν��Ͻ�.
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);	// ������.
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	// Ŀ��.
	wc.lpfnWndProc = WindowProc;					// �޽��� ó�� �Լ�.

	// Ŭ���� ���.
	if (RegisterClass(&wc) == false)
	{
		// ���� ����.
		MessageBox(nullptr, L"Ŭ���� ��� ����", L"����", 0);

		// ���� ����.
		exit(-1);
	}

	// �ʺ� ����.
	RECT rect = { 0, 0, width, height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	// ������ ����.
	hwnd = CreateWindow(
		wc.lpszClassName,
		title.c_str(),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	// ���� �˻�.
	if (hwnd == nullptr)
	{
		MessageBox(nullptr, L"������ ���� ����", L"����", 0);
		return false;
	}

	// ������ ���̱�.
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// �Է� �ʱ�ȭ.
	InputProcessor::InitializeInput(hwnd);

	return true;
}

HINSTANCE Window::Instance()
{
	return hInstance;
}

void Window::SetInstance(HINSTANCE hInstance)
{
	Window::hInstance = hInstance;
}

HWND Window::WindowHandle()
{
	return hwnd;
}

int Window::Width()
{
	return width;
}

void Window::SetWidth(int width)
{
	Window::width = width;
}

int Window::Height()
{
	return height;
}

void Window::SetHeight(int height)
{
	Window::height = height;
}

std::wstring Window::Title()
{
	return title;
}

void Window::SetTitle(std::wstring title)
{
	Window::title = title;
}
