#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND	hwnd; // ������ �ڵ�
	MSG		msg; // �޽��� ����ü
	WNDCLASSEX	WndClass; // ������ Ŭ���� ����ü

	// 1. ������ Ŭ���� ����ü�� ���� ä�� ������ Ŭ������ ����մϴ�.

	WndClass.cbSize = sizeof(WNDCLASSEX); // ����ü ũ��
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; // Ŭ���� ��Ÿ��
	WndClass.lpfnWndProc = WndProc; // ������ ���ν���
	WndClass.cbClsExtra = 0; // ������Ŭ���� ������ ����
	WndClass.cbWndExtra = 0; // �������� ������ ����
	WndClass.hInstance = hInstance; // �ν��Ͻ� �ڵ�
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ������ �ڵ�
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ�� �ڵ�
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ��� �귯�� �ڵ�
	WndClass.lpszClassName = "EasyText"; // ������ Ŭ���� �̸�, �����ڵ� ���ڶ� �տ� L ����
	WndClass.hIconSm = 0; // �⺻���� ���� ������

	// �ش� ������ Ŭ������ ���
	RegisterClassEx(&WndClass);

	// 2. ������ ������ ����
	hwnd = CreateWindow( // ������ ���� API
		"EasyText", // ��ϵ� ������ Ŭ���� �̸�
		"Practice1a", // Ÿ��Ʋ �ٿ� ��µ� ���ڿ�
		WS_OVERLAPPEDWINDOW, // ������ ��Ÿ��
		CW_USEDEFAULT, // �»� x
		CW_USEDEFAULT, // �»� y
		CW_USEDEFAULT, // ������ �ʺ�
		CW_USEDEFAULT, // ������ ����
		NULL, // �θ� ������ �ڵ�
		NULL, // �޴�, �Ǵ� �ڽ� �������� �ڵ�
		hInstance, // ���ø����̼� �ν��Ͻ� �ڵ�
		NULL // ������ ���� �������� �ּ�
	);

	// ������ ������ ���
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// 3. �޽���ť�κ��� �޽����� �޾ƿ� �޽����� �ش� ������ ���ν����� ����
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); // �޽��� ����

		DispatchMessage(&msg); // �޽����� �ش� ���������ν����� ������.
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc; // ����̽� ���ؽ�Ʈ
	RECT rect; // RECT ����ü
	PAINTSTRUCT ps; // ����Ʈ ����ü
	LPCSTR szMsg1 = "I love Window Programming";
	LPCSTR szMsg2 = "Ű���尡 ���������ϴ�.";
	LPCSTR szMsg3 = "Ű���尡 ���������ϴ�.";

	// 1. Ŀ�ο��� ���� �޽����� Switch���� �̿��� ó��
	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 10, 10, szMsg1, strlen(szMsg1));
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, szMsg2, strlen(szMsg2), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		ReleaseDC(hwnd, hdc);
		break;

	case WM_KEYUP:
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, szMsg3, strlen(szMsg3), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		ReleaseDC(hwnd, hdc);
		break;

	case WM_MBUTTONDBLCLK:
		MessageBox(hwnd, "���콺 ����Ŭ�� ~", "���콺 �޽���", MB_OK | MB_ICONASTERISK);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
		
	}
	return 0;
}
