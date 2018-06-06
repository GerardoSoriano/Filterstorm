#pragma once

#include <opencv2/opencv.hpp>
#include <cmath>
using namespace cv;
using namespace std;

#define F_MEDIAN 1
#define F_WEIGHTED_MEDIAN 2
#define F_MINUS_MEDIAN 3
#define F_AVERAGE 4
#define F_LAPLACIAN 5
#define F_MINUS_LAPLACIAN 6
#define F_DIRECTIONAL_NORTH 7
#define F_DIRECTIONAL_EAST 8
#define F_GRAYSCALE_AVERAGE 9
#define F_GRAYSCALE_LUMINOSITY 10
#define F_GRAYSCALE_LUMINANCE 11
#define F_SEPIA 12
#define F_SOBEL 13
#define F_GAUSSIAN 14
#define F_NORMALIZE_HISTOGRAM 15
#define F_HISTOGRAM_SIMPLE 16
#define F_HISTOGRAM_UNIFORM 17

/**
* FILTROS A REALIZAR
*
* Media								-OK
* Media ponderada					-OK
* Substracción de la media			-OK
* Mediana							-OK
* Laplaciano						-OK
* Menos laplaciano					-OK
* Direccional norte					-OK
* Direccional este					-OK
* Gris promedio						-OK
* Gris por luminosidad				-OK
* Gris por luminancia				-OK
* Sepia								-OK
* Sobel								-OK
* Gaussiano							-CHECK
* Histograma normazilado			-WAIT
* Histograma ecualizado simple		-WAIT
* Histograma ecualizado uniforme	-WAIT
*/

class DevFilter
{
public:
	static Mat median(string path);
	static Mat weighted_median(string path, float weight);
	static Mat minus_median(string path);
	static Mat average(string path);
	static Mat laplacian(string path);
	static Mat minus_laplacian(string path);
	static Mat directional_north(string path);
	static Mat directional_east(string path);
	static Mat grayscale_average(string path);
	static Mat grayscale_luminosity(string path);
	static Mat grayscale_luminance(string path);
	static Mat sepia(string path);
	static Mat sobel(string path);
	static Mat gaussian(string path, float sigma);

	static Mat median(Mat img);
	static Mat weighted_median(Mat img, float weight);
	static Mat minus_median(Mat img);
	static Mat average(Mat img);
	static Mat laplacian(Mat img);
	static Mat minus_laplacian(Mat img);
	static Mat directional_north(Mat img);
	static Mat directional_east(Mat img);
	static Mat grayscale_average(Mat img);
	static Mat grayscale_luminosity(Mat img);
	static Mat grayscale_luminance(Mat img);
	static Mat sepia(Mat img);
	static Mat sobel(Mat img);
	static Mat gaussian(Mat img, float sigma);

	static void median(Mat &img);
	static void weighted_median(Mat &img, float weight);
	static void minus_median(Mat &img);
	static void average(Mat &img);
	static void laplacian(Mat &img);
	static void minus_laplacian(Mat &img);
	static void directional_north(Mat &img);
	static void directional_east(Mat &img);
	static void grayscale_average(Mat &img);
	static void grayscale_luminosity(Mat &img);
	static void grayscale_luminance(Mat &img);
	static void sepia(Mat &img);
	static void sobel(Mat &img);
	static void gaussian(Mat &img, float sigma);
};