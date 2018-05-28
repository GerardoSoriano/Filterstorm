#include <Windows.h>
#include <WinUser.h>
#include <gdiplus.h>
#include "resource.h"
#include <minwinbase.h>
#include <winuser.h>
using namespace Gdiplus;

HINSTANCE hInst;

BOOL CALLBACK DialogProcedure(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ImageProcedure(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK VideoProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdParam, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdParam);

	hInst = hInstance;

	HWND hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, (DLGPROC)DialogProcedure);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) == TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

BOOL CALLBACK DialogProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case BTN_IMAGE:
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_IMAGE), hwnd, (DLGPROC)ImageProcedure);
			break;
		}
		break;
	case WM_CLOSE:
		if (MessageBox(NULL, L"¿Seguro que deseas cerrar la ventana?", L"Alerta", MB_YESNO | MB_ICONWARNING) == IDYES)
			DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return FALSE;
}

BOOL CALLBACK ImageProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	OPENFILENAME ofn;
	WCHAR path[260];

	HBITMAP image;
	HWND pic_image;

	switch (msg)
	{
	case WM_INITDIALOG:
		pic_image = GetDlgItem(hwnd, PIC_IMAGE);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_IMAGEN_CARGAR:
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = path;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(path);
			ofn.lpstrFilter = L"Image files (*.jpg;*.png;*.bmp)\0*.jpg;*.png;*.bmp\0"
								"All files\0*.*\0";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			if (GetOpenFileName(&ofn) == TRUE)
			{
				SetDlgItemText(hwnd, LBL_PATH, path);
				image = LoadBitmap(hInst, path);
				SendDlgItemMessage(hwnd, PIC_IMAGE, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)image);
			}
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, NULL);
		break;
	}
	return FALSE;
}