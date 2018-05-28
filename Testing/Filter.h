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
 * Media							-OK
 * Media ponderada					-OK
 * Substracción de la media			-OK
 * Mediana							-WAIT
 * Laplaciano						-OK
 * Menos laplaciano					-OK
 * Direccional norte				-OK
 * Direccional este					-OK
 * Gris promedio					-OK
 * Gris por luminosidad				-OK
 * Gris por luminancia				-WAIT
 * Sepia							-OK
 * Sobel							-OK
 * Gaussiano						-WAIT
 * Histograma normazilado			-WAIT
 * Histograma ecualizado simple		-WAIT
 * Histograma ecualizado uniforme	-WAIT
 */

class Filter
{
private:
	static Vec3b apply_median(Mat img, uint x, uint y);
	static Vec3b apply_weighted_median(Mat img, uint x, uint y, uint weight);
	static Vec3b apply_minus_median(Mat img, uint x, uint y);
	static Vec3b apply_average(Mat img, uint x, uint y);
	static Vec3b apply_laplacian(Mat img, uint x, uint y);
	static Vec3b apply_minus_laplacian(Mat img, uint x, uint y);
	static Vec3b apply_directional_north(Mat img, uint x, uint y);
	static Vec3b apply_directional_east(Mat img, uint x, uint y);
	static Vec3b apply_grayscale_average(Mat img, uint x, uint y);
	static Vec3b apply_grayscale_luminosity(Mat img, uint x, uint y);
	static Vec3b apply_grayscale_luminance(Mat img, uint x, uint y);
	static Vec3b apply_sepia(Mat img, uint x, uint y);
	static Vec3b apply_sobel(Mat img, uint x, uint y);
	static Vec3b apply_gaussian(Mat img, uint x, uint y);
	static Vec3b apply_normalize_histogram(Mat img, uint x, uint y);
	static Vec3b apply_histogram_simple(Mat img, uint x, uint y);
	static Vec3b apply_histogram_uniform(Mat img, uint x, uint y);
public:
	static Mat apply(string path, uint filter);
	static Mat apply(Mat img, uint filter);
};

