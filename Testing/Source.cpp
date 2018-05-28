#include <opencv2/opencv.hpp>
#include <iostream>
#include "Filter.h"
using namespace std;
using namespace cv;

Mat filter(Mat);

int main()
{
	Mat image = imread(R"(C:\Users\gerar\OneDrive\Imágenes\Dexter1.jpg)");
	if (image.empty())
	{
		cout << "No se pudo abrir la imagen chavo" << endl;
		return -1;
	}
	Mat image2 = Filter::apply(image.clone(), F_SEPIA);
	Mat image3 = Filter::apply(image.clone(), F_GRAYSCALE_LUMINOSITY);

	cout << "Tu imagen es de: " << image.cols << " x " << image.rows << endl;

	namedWindow("Test01");
	imshow("Test01", image);

	namedWindow("Test02");
	imshow("Test02", image2);

	namedWindow("Test03");
	imshow("Test03", image3);

	waitKey(0);
	return 1;
}
