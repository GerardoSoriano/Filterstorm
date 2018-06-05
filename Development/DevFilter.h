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
* Mediana							-WAIT
* Laplaciano						-OK
* Menos laplaciano					-OK
* Direccional norte					-OK
* Direccional este					-OK
* Gris promedio						-OK
* Gris por luminosidad				-OK
* Gris por luminancia				-WAIT
* Sepia								-OK
* Sobel								-OK
* Gaussiano							-CHECK
* Histograma normazilado			-WAIT
* Histograma ecualizado simple		-WAIT
* Histograma ecualizado uniforme	-WAIT
*/

class DevFilter
{
private:
	static void apply_median(float(&bgr)[3], uint x, uint y, uint rows, uint cols, int(&color)[3]);
	static int* apply_weighted_median(float bgr[], uint x, uint y, uint weight);
	static int* apply_minus_median(float bgr[], uint x, uint y);
	static int* apply_average(float bgr[], uint x, uint y);
	static int* apply_laplacian(float bgr[], uint x, uint y);
	static int* apply_minus_laplacian(float bgr[], uint x, uint y);
	static int* apply_directional_north(float bgr[], uint x, uint y);
	static int* apply_directional_east(float bgr[], uint x, uint y);
	static int* apply_grayscale_average(float bgr[], uint x, uint y);
	static int* apply_grayscale_luminosity(Mat img, uint x, uint y);
	static int* apply_grayscale_luminance(Mat img, uint x, uint y);
	static void apply_sepia(float(&bgr)[3], uint x, uint y, int(&color)[3]);
	static int* apply_sobel(Mat img, uint x, uint y);
	static int* apply_gaussian(Mat img, uint x, uint y, float sigma);
	static int* apply_normalize_histogram(Mat img, uint x, uint y);
	static int* apply_histogram_simple(Mat img, uint x, uint y);
	static int* apply_histogram_uniform(Mat img, uint x, uint y);
public:
	static Mat apply(string path, uint filter);
	static void apply(Mat &img, uint filter);

	static Mat median(string path);
	static Mat gaussian(string path, float sigma);
};