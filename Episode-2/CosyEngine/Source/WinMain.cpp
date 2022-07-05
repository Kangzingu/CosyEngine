#include "pch.h"

/* ---------------------------------------- */
/* GlobalVariables                          */
/* ---------------------------------------- */
#pragma region GlobalVariables

WCHAR WindowClass[MAX_LEN_OF_NAME_STRING];
WCHAR WindowTitle[MAX_LEN_OF_NAME_STRING];
INT WindowWidth;
INT WindowHeight;
HICON hIcon;
#pragma endregion
/* ---------------------------------------- */

/* ---------------------------------------- */
/* Pre-Declarations                         */
/* ---------------------------------------- */
#pragma region Pre-Declarations

VOID InitializeVariables();
VOID CreateWindowClass();
VOID InitializeAndShowWindow();
VOID HandleMessage();
LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#pragma endregion
/* ---------------------------------------- */

/* ---------------------------------------- */
/* Operations                               */
/* ---------------------------------------- */
#pragma region Operations

// 2번째 파라미터는 지금(Win 10에서?) 쓰지 않는 애라고 함
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	InitializeVariables();
	CreateWindowClass();
	InitializeAndShowWindow();
	HandleMessage();
	return 0;
}
LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
#pragma endregion
/* ---------------------------------------- */

/* ---------------------------------------- */
/* Functions                                */
/* ---------------------------------------- */
#pragma region Functions

VOID InitializeVariables() {
	// 이 2개는 스트링 테이블로 값을 넣은것임 Resources\CosyEngine.rc에서 확인 가능
	LoadString(HInstance(), IDS_WINDOW_CLASS, WindowClass, MAX_LEN_OF_NAME_STRING);
	LoadString(HInstance(), IDS_WINDOW_TITLE, WindowTitle, MAX_LEN_OF_NAME_STRING);

	WindowWidth = 1200;
	WindowHeight = 800;

	hIcon = LoadIcon(HInstance(), MAKEINTRESOURCE(IDI_MAIN_ICON));
}
VOID CreateWindowClass() {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcex.hIcon = hIcon;
	wcex.hIconSm = hIcon;

	wcex.lpszClassName = WindowClass;

	wcex.lpszMenuName = nullptr;

	wcex.hInstance = HInstance();

	wcex.lpfnWndProc = WindowProcess;

	RegisterClassEx(&wcex);
}
VOID InitializeAndShowWindow() {
	HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);
	if (!hWnd) {
		MessageBox(0, L"Failed to Create Window", 0, 0);
		PostQuitMessage(0);
	}
	ShowWindow(hWnd, SW_SHOW);
}
VOID HandleMessage() {
	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
#pragma endregion
/* ---------------------------------------- */