#pragma once

#include <opencv2/opencv.hpp>
#include <cmath>
using namespace cv;
using namespace std;

#define F_MEDIAN 1
#define F_WEIGHTED_MEDIAN 2
#define F_MINUS_MEDIAN 3
#define F_GAUSSIAN 4
#define F_LAPLACIAN 5
#define F_MINUS_LAPLACIAN 6
#define F_DIRECTIONAL_NORTH 7
#define F_DIRECTIONAL_SOUTH 8
#define F_GRAY_SCALE 9
/**
 * FILTROS A REALIZAR
 * 
 * Media						-OK
 * Media ponderada				-OK
 * Substracción de la media		-OK
 * Gaussiano					-WAIT
 * Laplaciano					-OK
 * Menos laplaciano				-OK
 * Direccional norte			-CHECK
 * Direccional sur				-CHECK
 * Direccional este				-WAIT
 * Direccional oeste			-WAIT
 * Escala de grises				-OK
 */

class Filter
{
private:
	static Vec3b apply_median(Mat img, uint x, uint y);
	static Vec3b apply_weighted_median(Mat img, uint x, uint y, uint weight);
	static Vec3b apply_minus_median(Mat img, uint x, uint y);
	static Vec3b apply_gaussian(Mat img, uint x, uint y);
	static Vec3b apply_laplacian(Mat img, uint x, uint y);
	static Vec3b apply_minus_laplacian(Mat img, uint x, uint y);
	static Vec3b apply_directional_north(Mat img, uint x, uint y);
	static Vec3b apply_directional_south(Mat img, uint x, uint y);
	static Vec3b apply_directional_east(Mat img, uint x, uint y);
	static Vec3b apply_directional_west(Mat img, uint x, uint y);
	static Vec3b apply_gray_scale(Mat img, uint x, uint y);
public:
	static Mat apply(string path, uint filter);
	static Mat apply(Mat img, uint filter);
};

