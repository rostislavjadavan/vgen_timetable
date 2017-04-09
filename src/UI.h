
#include "Windows.h"
#include "UIHelper.h"

class UI {

public:
	
	static UI* getInstance() {		
		if (instance == NULL) {
			instance = new UI();
		}
		return instance;
	}

	~UI() {
		delete instance;
	}

	HWND hwnd;
	HWND hwndEdit, hwndButton1, hwndButton2;

	void open();
	void create(HWND hwnd);
	void processCommand(WPARAM wParam, LPARAM lParam);

private:
	static UI* instance;
	UI() {}
};

UI* UI::instance = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	UI *ui = UI::getInstance();

	switch (msg) {
		case WM_CREATE:
			ui->create(hwnd);		
			break;

		case WM_COMMAND:
			ui->processCommand(wParam, lParam);		
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void UI::processCommand(WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == BN_CLICKED && (HWND)lParam == this->hwndButton1) {
		MessageBox(this->hwnd, L"Button1 clicked", L"Message", 0);
	}

	if (HIWORD(wParam) == BN_CLICKED && (HWND)lParam == this->hwndButton2) {
		MessageBox(this->hwnd, L"Button2 clicked", L"Message", 0);
	}
}

void UI::create(HWND hwnd) {

	createText(hwnd, L"DJ", 10, 20, 50);
	createText(hwnd, L"Size", 220, 20, 50);
	createText(hwnd, L"From", 270, 20, 50);
	createText(hwnd, L"Time to", 390, 20, 50);
	for (int i = 0; i < 6; i++) {		
		createEdit(hwnd, 10, 50 + i * 25, 200);
		createEdit(hwnd, 220,50 + i * 25, 40);
		createTimePicker(hwnd, 270, 50 + i * 25, 100);
		createTimePicker(hwnd, 390, 50 + i * 25, 100);
	}
}

void UI::open() {	
	WNDCLASSW wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = L"Window";
	wc.hInstance = GetModuleHandle(0);
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassW(&wc);
	this->hwnd = CreateWindowW(wc.lpszClassName, L"Window",
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE,
		100, 100, 520, 400, NULL, NULL, GetModuleHandle(0), NULL);

	ShowWindow(this->hwnd, SW_SHOW);
	UpdateWindow(this-> hwnd);
}