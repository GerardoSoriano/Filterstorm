#include <opencv2/opencv.hpp>
#include <iostream>
#include "Filter.h"
#include "Picture.h"

using namespace std;
using namespace cv;

Mat filter(Mat);

int main()
{
	Picture *picture	= new Picture(imread(R"(C:\Users\gerar\OneDrive\Imágenes\Laura.jpg)"));
	Mat hist;
	if (picture->image.empty())
	{
		cout << "No se pudo abrir la imagen chavo" << endl;
		return -1;
	}
	picture->resize(250);
	picture->image = Filter::apply(picture->image, F_SEPIA);
	hist = picture->getHistogram(512, 400);

	namedWindow("Test01");
	imshow("Test01", picture->image);

	namedWindow("Test02");
	imshow("Test02", hist);

	/*Mat image = imread(R"(C:\Users\gerar\OneDrive\Imágenes\Laura.jpg)");

	if (image.empty())
	{
		cout << "No se pudo abrir la imagen chavo" << endl;
		return -1;
	}
	Mat image2 = Filter::apply(image.clone(), F_SEPIA);
	Mat image3 = Filter::apply(image.clone(), F_SOBEL);
	Mat hist = Filter::getHistogram(image.clone(), 512, 400);

	cout << "Tu imagen es de: " << image.cols << " x " << image.rows << endl;

	namedWindow("Test01");
	imshow("Test01", image);

	namedWindow("Test02");
	imshow("Test02", image2);

	namedWindow("Test03");
	imshow("Test03", image3);

	namedWindow("Histograma");
	imshow("Histograma", hist);*/

	waitKey(0);
	return 1;
}
