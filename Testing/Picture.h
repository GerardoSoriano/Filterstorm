#pragma once
#include <opencv2/core/mat.hpp>
using namespace cv;

class Picture
{
public:
	Mat image;
	Picture(Mat _image);
	Picture(String path);
	Mat getHistogram(uint histSizeX, uint histSizeY);
	void resize(uint width);
};

