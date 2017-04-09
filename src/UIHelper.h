#pragma once
#include "Windows.h"

HWND createText(HWND hwnd, LPCWSTR text, int x, int y, int width) {
	return CreateWindowW(L"Static", text,
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		x, y, width, 20, hwnd, NULL,
		NULL, NULL);
}

HWND createEdit(HWND hwnd, int x, int y, int width) {
	return CreateWindowW(L"Edit", NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		x, y, width, 20, hwnd, NULL,
		NULL, NULL);
}

HWND createButton(HWND hwnd, LPCWSTR text, int x, int y, int width) {
	return CreateWindowW(L"Button", text,
		WS_VISIBLE | WS_CHILD, x, y, width, 25,
		hwnd, NULL, NULL, NULL);
}

HWND createTimePicker(HWND hwnd, int x, int y, int width) {
	HWND hwndCombo = CreateWindowW(L"Combobox", NULL,
		WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | WS_VSCROLL | WS_TABSTOP,
		x, y, width, 330, hwnd, NULL, NULL, NULL);


	for (int h = 0; h < 24; h++) {
		for (int m = 0; m < 60; m += 5) {
			wchar_t result[20];
			if (m < 10) {
				swprintf(result, 19, L"%i:0%i", h, m);
			}
			else {
				swprintf(result, 19, L"%i:%i", h, m);
			}
			SendMessageW(hwndCombo, CB_ADDSTRING, 0, (LPARAM)result);
		}
	}

	return hwndCombo;
}