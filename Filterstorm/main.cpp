#include <Windows.h>
#include <WinUser.h>
#include <gdiplus.h>
#include "resource.h"
#include <minwinbase.h>
#include <winuser.h>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <fstream>
#include "Picture.h"
#include "Filter.h"
using namespace cv;
using namespace std;
using namespace Gdiplus;


HINSTANCE hInst;
Picture *picture;

BOOL CALLBACK DialogProcedure(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ImageProcedure(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK VideoProcedure(HWND, UINT, WPARAM, LPARAM);

bool passOpenCVImageToControl(HWND, string);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdParam, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdParam);

	hInst = hInstance;
	picture = NULL;

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

	RECT lb_pic_image, lb_pic_histogram;
	Mat hist;

	switch (msg)
	{
	case WM_INITDIALOG:
		Picture::adaptControl(GetDlgItem(hwnd, PIC_IMAGE), "pic_image");
		Picture::adaptControl(GetDlgItem(hwnd, PIC_HISTOGRAM), "pic_histogram");

		SendMessageW(GetDlgItem(hwnd, CB_CHANNELS), CB_ADDSTRING, 0, (LPARAM)L"Canal RGB");
		SendMessageW(GetDlgItem(hwnd, CB_CHANNELS), CB_ADDSTRING, 0, (LPARAM)L"Canal R");
		SendMessageW(GetDlgItem(hwnd, CB_CHANNELS), CB_ADDSTRING, 0, (LPARAM)L"Canal G");
		SendMessageW(GetDlgItem(hwnd, CB_CHANNELS), CB_ADDSTRING, 0, (LPARAM)L"Canal B");

		waitKey(1);
		return TRUE;
	case WM_COMMAND:
		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			switch (LOWORD(wParam))
			{
			case CB_CHANNELS:
				HWND hcombo = (HWND)lParam;
				LRESULT index = SendMessageW(hcombo, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);

				switch (index)
				{
				case CHANNEL_RGB:
					hist = picture->getHistogram(160, 132, CHANNEL_RGB);
					imshow("pic_histogram", hist);
					break;
				case CHANNEL_R:
					hist = picture->getHistogram(160, 132, CHANNEL_R);
					imshow("pic_histogram", hist);
					break;
				case CHANNEL_G:
					hist = picture->getHistogram(160, 132, CHANNEL_G);
					imshow("pic_histogram", hist);
					break;
				case CHANNEL_B:
					hist = picture->getHistogram(160, 132, CHANNEL_B);
					imshow("pic_histogram", hist);
					break;
				}

				/*wchar_t buf[256];

				SendMessageW(hcombo, (UINT)CB_GETLBTEXT, (WPARAM)index, (LPARAM)buf);
				MessageBoxW(hwnd, buf, L"Good Example", 0);*/
				break;
			}
			break;
		}
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
				char fileName[260],
					fileBuffer = ' ';
				WideCharToMultiByte(CP_ACP, 0, path, -1, fileName, 260, &fileBuffer, NULL);
				picture = new Picture(string(fileName));

				wchar_t dimensions[100];
				wsprintf(dimensions, L"%dpx*%dpx", picture->image.cols, picture->image.rows);

				ifstream img(string(fileName).c_str(), ifstream::in | ifstream::binary);
				img.seekg(0, ios::end);
				int fileSize = img.tellg();
				img.close();
				wchar_t size[100];
				wsprintf(size, L"%dKB", fileSize / 1000);

				SetDlgItemText(hwnd, LBL_DIMENSIONS, dimensions);
				SetDlgItemText(hwnd, LBL_SIZE, size);
				SetDlgItemText(hwnd, LBL_PATH, path);

				imshow("pic_image", picture->image);
				SendMessage(GetDlgItem(hwnd, PIC_IMAGE), LB_GETITEMRECT, 0, (LPARAM)&lb_pic_histogram);
				hist = picture->getHistogram(160, 132, CHANNEL_RGB);
				imshow("pic_histogram", hist);

				EnableWindow(GetDlgItem(hwnd, CB_CHANNELS), true);
				SendMessage(GetDlgItem(hwnd, CB_CHANNELS), CB_SETCURSEL, 0, 0);
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

bool passOpenCVImageToControl(HWND parentWnd, string nombreShow)
{
	string WIN_NAME_CV = nombreShow;

	namedWindow(WIN_NAME_CV, CV_WINDOW_KEEPRATIO);

	HWND cvWnd = (HWND)cvGetWindowHandle(WIN_NAME_CV.c_str());
	if (!cvWnd) return false;

	HWND hOldParent = ::GetParent(cvWnd);
	::SetParent(cvWnd, parentWnd);
	::ShowWindow(hOldParent, SW_HIDE);

	//Ajustes varios
	RECT parentRect;
	::GetClientRect(parentWnd, &parentRect);
	cvResizeWindow(WIN_NAME_CV.c_str(), parentRect.right, parentRect.bottom);
	return true;
}