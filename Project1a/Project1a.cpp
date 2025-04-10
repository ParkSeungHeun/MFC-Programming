#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND	hwnd; // 윈도우 핸들
	MSG		msg; // 메시지 구조체
	WNDCLASSEX	WndClass; // 윈도우 클래스 구조체

	// 1. 윈도우 클래스 구조체에 값을 채워 윈도우 클래스를 등록합니다.

	// WndClass를 0으로 초기화 해주어야 합니다
	WndClass = { 0 };

	WndClass.cbSize = sizeof(WNDCLASSEX); // 구조체 크기
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; // 클래스 스타일
	WndClass.lpfnWndProc = WndProc; // 윈도우 프로시저
	WndClass.cbClsExtra = 0; // 윈도우클래스 데이터 영역
	WndClass.cbWndExtra = 0; // 윈도우의 데이터 영역
	WndClass.hInstance = hInstance; // 인스턴스 핸들
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 아이콘 핸들
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서 핸들
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 배경 브러시 핸들
	WndClass.lpszClassName = "EasyText"; // 윈도우 클래스 이름, 유니코드 문자라 앞에 L 붙음
	WndClass.hIconSm = 0; // 기본적인 작은 아이콘

	// 해당 윈도우 클래스를 등록
	RegisterClassEx(&WndClass);

	// 2. 프레임 윈도우 생성
	hwnd = CreateWindow( // 윈도우 생성 API
		"EasyText", // 등록된 윈도우 클래스 이름
		"Practice1a", // 타이틀 바에 출력될 문자열
		WS_OVERLAPPEDWINDOW, // 윈도우 스타일
		CW_USEDEFAULT, // 좌상 x
		CW_USEDEFAULT, // 좌상 y
		CW_USEDEFAULT, // 윈도우 너비
		CW_USEDEFAULT, // 윈도우 높이
		NULL, // 부모 윈도우 핸들
		NULL, // 메뉴, 또는 자식 윈도우의 핸들
		hInstance, // 애플리케이션 인스턴스 핸들
		NULL // 윈도우 생성 데이터의 주소
	);

	// 프레임 윈도우 등록
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// 3. 메시지큐로부터 메시지를 받아와 메시지를 해당 윈도우 프로시저로 보냄
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); // 메시지 번역

		DispatchMessage(&msg); // 메시지를 해당 윈도우프로시저로 보낸다.
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc; // 디바이스 컨텍스트
	RECT rect; // RECT 구조체
	PAINTSTRUCT ps; // 페인트 구조체
	LPCSTR szMsg1 = "I love Window Programming";
	LPCSTR szMsg2 = "키보드가 눌러졌습니다.";
	LPCSTR szMsg3 = "키보드가 떼어졌습니다.";
	LPSTR szMsg4 = new char[10];

	// 좌표를 표시하는 구조체 POINT
	POINT mousePoint;

	// 1. 커널에서 들어온 메시지를 Switch문을 이용해 처리
	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		// 위치를 정해서 출력하는 TextOut
		TextOut(hdc, 10, 10, szMsg1, strlen(szMsg1));
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		// 영역을 정하고 그에 맞춰 출력하는 DrawOut
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
		MessageBox(hwnd, "마우스 더블클릭 ~", "마우스 메시지", MB_OK | MB_ICONASTERISK);
		
		break;

	case WM_LBUTTONDOWN:
		hdc = GetDC(hwnd);
		// x좌표는 LOWORD 매크로, y좌표는 HIWORD 매크로로 흭득 가능
		mousePoint.x = LOWORD(lParam);
		mousePoint.y = HIWORD(lParam);

		// szMsg4에 메시지 기록
		wsprintf(szMsg4, " X:%ld, Y:%ld", mousePoint.x, mousePoint.y);

		// 메시지 출력
		TextOut(hdc, mousePoint.x, mousePoint.y, szMsg4, strlen(szMsg4));

		ReleaseDC(hwnd, hdc);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);

	}
	return 0;
}
