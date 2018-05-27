#include <opencv2/opencv.hpp>
#include <iostream>
#include "Filter.h"
using namespace std;
using namespace cv;

Mat filter(Mat);

int main()
{
	Mat image = imread(R"(C:\Users\gerar\OneDrive\Imágenes\Laplaciano.png)");
	if (image.empty())
	{
		cout << "No se pudo abrir la imagen chavo" << endl;
		return -1;
	}
	Mat image2 = Filter::apply(image.clone(), F_LAPLACIAN);
	/*Mat image3 = Filter::apply(R"(C:\Users\gerar\OneDrive\Imágenes\Laplaciano.png)", F_MINUS_LAPLACIAN);*/

	cout << "Tu imagen es de: " << image.cols << " x " << image.rows << endl;

	namedWindow("Test01");
	imshow("Test01", image);

	namedWindow("Test02");
	imshow("Test02", image2);

	/*namedWindow("Test03");
	imshow("Test03", image3);*/
	waitKey(0);
	return 1;
}

//Filtro
Mat filter(Mat image)
{
	Mat result = image.clone();

	//definimos la matriz del filtro
	const int	filterHeight = 3,
				filterWidth = 3;

	int filter[filterHeight][filterWidth] = {
		{ 1, 1, 1 },
		{ 1, 2, 1 },
		{ 1, 1, 1 }
	};

	Vec3b pixel;
	for (int x = 0; x < image.cols; x++)
		for (int y = 0; y < image.rows; y++)
		{

		}


	return result;
}

/// c / Users / gerar / OneDrive / Imágenes
