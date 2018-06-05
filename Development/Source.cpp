#include <opencv2/opencv.hpp>
#include <iostream>
#include "DevFilter.h"
using namespace std;
using namespace cv;

int main()
{
	Mat image = imread(R"(C:\Users\gerar\OneDrive\Imágenes\Dexter1.jpg)");
	if (image.empty())
	{
		cout << "No se pudo abrir la imagen chavo" << endl;
		return -1;
	}
	Mat image2 = DevFilter::gaussian(R"(C:\Users\gerar\OneDrive\Imágenes\Dexter1.jpg)", 2);

	cout << "Tu imagen es de: " << image.cols << " x " << image.rows << endl;

	namedWindow("Test01");
	imshow("Test01", image);

	namedWindow("Test02");
	imshow("Test02", image2);

	waitKey(0);
	return 1;
}