#pragma once

#include <windows.h>
#include <opencv2/core/mat.hpp>
using namespace cv;
using namespace std;

#define CHANNEL_RGB 0
#define CHANNEL_R 1
#define CHANNEL_G 2
#define CHANNEL_B 3

class DevPicture
{
public:
	Mat image;
	int rows, cols;
	DevPicture(Mat _image);
	DevPicture(string path);
	Mat getHistogram(uint histSizeX, uint histSizeY, uint channel);
	void resize(uint width);
	static bool adaptControl(HWND hwnd, string name);
};