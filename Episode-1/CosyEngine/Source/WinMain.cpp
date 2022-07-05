#include <windows.h>

#define MAX_LEN_OF_NAME_STRING 256
#define HInstance() GetModuleHandle(NULL)

WCHAR WindowClass[MAX_LEN_OF_NAME_STRING];
WCHAR WindowTitle[MAX_LEN_OF_NAME_STRING];

INT WindowWidth;
INT WindowHeight;

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	// 2��° �Ķ���ʹ� ����(Win 10����?) ���� �ʴ� �ֶ�� ��

	/* ���� ���� �ʱ�ȭ*/
	wcscpy_s(WindowClass, TEXT("WindowClass"));
	wcscpy_s(WindowTitle, TEXT("WindowTitle"));

	WindowWidth = 1200;
	WindowHeight = 800;

	/* ������ Ŭ���� ���� */
	WNDCLASSEX wcex;
	
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);

	wcex.lpszClassName = WindowClass;
	
	wcex.lpszMenuName = nullptr;

	wcex.hInstance = HInstance();

	wcex.lpfnWndProc = DefWindowProc;

	RegisterClassEx(&wcex);

	/* ������ �����ϰ� ����*/
	HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);
	if (!hWnd) {
		MessageBox(0, L"Failed to Create Window", 0, 0);
		return 0;
	}

	ShowWindow(hWnd, SW_SHOW);

	/* �޽��� �̺�Ʈ �ޱ� */
	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}