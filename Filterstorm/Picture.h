#pragma once

#include <windows.h>
#include <opencv2/core/mat.hpp>
using namespace cv;
using namespace std;

class Picture
{
public:
	Mat image;
	int rows, cols;
	Picture(Mat _image);
	Picture(string path);
	Mat getHistogram(uint histSizeX, uint histSizeY);
	void resize(uint width);
	static bool adaptControl(HWND hwnd, string name);
};