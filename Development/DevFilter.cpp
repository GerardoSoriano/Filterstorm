#include "DevFilter.h"
#include <cmath>

void DevFilter::apply_median(float(&bgr)[3], uint x, uint y, uint rows, uint cols, int(&color)[3])
{
	float	b, g, r;
	float	sum_b = 0, sum_g = 0, sum_r = 0;
	int		pX, pY,
			rx = x - 1,
			ry = y - 1;
	int		mask[3][3] = {
		1, 1, 1,
		1, 1, 1,
		1, 1, 1
	};

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			pX = rx + j;
			pY = ry + i;

			if (pX > cols - 1 || pY > rows - 1) {
				sum_b = sum_b + 0;
				sum_g = sum_g + 0;
				sum_r = sum_r + 0;
			}
			else
			{
				b = bgr[0];
				g = bgr[1];
				r = bgr[2];

				sum_b = sum_b + mask[j][i] * b;
				sum_g = sum_g + mask[j][i] * g;
				sum_r = sum_r + mask[j][i] * r;
			}
		}
	}

	sum_b = sum_b / 9;
	sum_g = sum_g / 9;
	sum_r = sum_r / 9;

	if (sum_b < 0)
		sum_b = 0;
	if (sum_g < 0)
		sum_g = 0;
	if (sum_r < 0)
		sum_r = 0;

	if (sum_b > 255)
		sum_b = 255;
	if (sum_g > 255)
		sum_g = 255;
	if (sum_r > 255)
		sum_r = 255;

	color[0] = sum_b;
	color[1] = sum_g;
	color[2] = sum_r;
}
/*
int* DevFilter::apply_weighted_median(Mat img, uint x, uint y, uint weight)
{
	float	b, g, r;
	float	sum_b = 0, sum_g = 0, sum_r = 0;
	Vec3b	pixel;
	Vec3b	result;
	int		pX, pY;
	int		mask[3][3] = {
		1,		1, 1,
		1, weight, 1,
		1,		1, 1
	};

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			pX = x + j;
			pY = y + i;

			if (pX > img.cols - 1 || pY > img.rows - 1) {
				sum_b = sum_b + 0;
				sum_g = sum_g + 0;
				sum_r = sum_r + 0;
			}
			else
			{
				pixel = img.at<Vec3b>(Point(pX, pY));
				b = pixel[0];
				g = pixel[1];
				r = pixel[2];

				sum_b = sum_b + mask[j][i] * b;
				sum_g = sum_g + mask[j][i] * g;
				sum_r = sum_r + mask[j][i] * r;
			}
		}

	result = img.at<Vec3b>(Point(x, y));
	sum_b = sum_b / (8 + weight);
	sum_g = sum_g / (8 + weight);
	sum_r = sum_r / (8 + weight);

	if (sum_b < 0)
		sum_b = 0;
	if (sum_g < 0)
		sum_g = 0;
	if (sum_r < 0)
		sum_r = 0;

	if (sum_b > 255)
		sum_b = 255;
	if (sum_g > 255)
		sum_g = 255;
	if (sum_r > 255)
		sum_r = 255;

	result[0] = sum_b;
	result[1] = sum_g;
	result[2] = sum_r;

	return result;
}

int* DevFilter::apply_minus_median(Mat img, uint x, uint y)
{
	float	b, g, r;
	float	sum_b = 0, sum_g = 0, sum_r = 0;
	Vec3b	pixel;
	Vec3b	result;
	int		pX, pY;
	int		mask[3][3] = {
		-1, -1, -1,
		-1,  8, -1,
		-1, -1, -1
	};

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			pX = x + j;
			pY = y + i;

			if (pX > img.cols - 1 || pY > img.rows - 1) {
				sum_b = sum_b + 0;
				sum_g = sum_g + 0;
				sum_r = sum_r + 0;
			}
			else
			{
				pixel = img.at<Vec3b>(Point(pX, pY));
				b = pixel[0];
				g = pixel[1];
				r = pixel[2];

				sum_b = sum_b + mask[j][i] * b;
				sum_g = sum_g + mask[j][i] * g;
				sum_r = sum_r + mask[j][i] * r;
			}
		}

	result = img.at<Vec3b>(Point(x, y));
	sum_b = sum_b / 9;
	sum_g = sum_g / 9;
	sum_r = sum_r / 9;

	if (sum_b < 0)
		sum_b = 0;
	if (sum_g < 0)
		sum_g = 0;
	if (sum_r < 0)
		sum_r = 0;

	if (sum_b > 255)
		sum_b = 255;
	if (sum_g > 255)
		sum_g = 255;
	if (sum_r > 255)
		sum_r = 255;

	result[0] = sum_b;
	result[1] = sum_g;
	result[2] = sum_r;

	return result;
}

int* DevFilter::apply_laplacian(Mat img, uint x, uint y)
{
	float	b, g, r;
	float	gray, sum = 0;
	Vec3b	pixel;
	Vec3b	result;
	int		pX, pY;
	int		mask[3][3] = {
		0,  1, 0,
		1, -4, 1,
		0,  1, 0
	};

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			pX = x + j;
			pY = y + i;

			if (pX > img.cols - 1 || pY > img.rows - 1)
				sum = sum + 0;
			else
			{
				pixel = img.at<Vec3b>(Point(pX, pY));
				b = pixel[0];
				g = pixel[1];
				r = pixel[2];

				gray = (b + g + r) / 3;

				sum = sum + mask[j][i] * gray;
			}
		}

	if (sum > 255)
		sum = 255;
	if (sum < 0)
		sum = 0;

	result = img.at<Vec3b>(Point(x, y));
	result[0] = sum;
	result[1] = sum;
	result[2] = sum;

	return result;
}

int* DevFilter::apply_minus_laplacian(Mat img, uint x, uint y)
{
	float	b, g, r;
	float	gray, sum = 0;
	Vec3b	pixel;
	Vec3b	result;
	int		pX, pY;
	int		mask[3][3] = {
		0, -1,  0,
		-1,  5, -1,
		0, -1,  0
	};

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			pX = x + j;
			pY = y + i;

			if (pX > img.cols - 1 || pY > img.rows - 1)
				sum = sum + 0;
			else
			{
				pixel = img.at<Vec3b>(Point(pX, pY));
				b = pixel[0];
				g = pixel[1];
				r = pixel[2];

				gray = (b + g + r) / 3;

				sum = sum + mask[j][i] * gray;
			}
		}

	if (sum > 255)
		sum = 255;
	if (sum < 0)
		sum = 0;

	result = img.at<Vec3b>(Point(x, y));
	result[0] = sum;
	result[1] = sum;
	result[2] = sum;

	return result;
}

int* DevFilter::apply_directional_north(Mat img, uint x, uint y)
{
	float	b, g, r;
	float	gray, sum = 0;
	Vec3b	pixel;
	Vec3b	result;
	int		pX, pY;
	int		mask[3][3] = {
		1,  1,  1,
		1, -2,  1,
		-1, -1, -1
	};

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			pX = x + j;
			pY = y + i;

			if (pX > img.cols - 1 || pY > img.rows - 1)
				sum = sum + 0;
			else
			{
				pixel = img.at<Vec3b>(Point(pX, pY));
				b = pixel[0];
				g = pixel[1];
				r = pixel[2];

				gray = (b + g + r) / 3;

				sum = sum + mask[j][i] * gray;
			}
		}

	if (sum > 255)
		sum = 255;
	if (sum < 0)
		sum = 0;

	result = img.at<Vec3b>(Point(x, y));
	result[0] = sum;
	result[1] = sum;
	result[2] = sum;

	return result;
}

int* DevFilter::apply_directional_east(Mat img, uint x, uint y)
{
	float	b, g, r;
	float	gray, sum = 0;
	Vec3b	pixel;
	Vec3b	result;
	int		pX, pY;
	int		mask[3][3] = {
		-1,  1,  1,
		-1, -2,  1,
		-1,  1,  1
	};

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			pX = x + j;
			pY = y + i;

			if (pX > img.cols - 1 || pY > img.rows - 1)
				sum = sum + 0;
			else
			{
				pixel = img.at<Vec3b>(Point(pX, pY));
				b = pixel[0];
				g = pixel[1];
				r = pixel[2];

				gray = (b + g + r) / 3;

				sum = sum + mask[j][i] * gray;
			}
		}

	if (sum > 255)
		sum = 255;
	if (sum < 0)
		sum = 0;

	result = img.at<Vec3b>(Point(x, y));
	result[0] = sum;
	result[1] = sum;
	result[2] = sum;

	return result;
}
*/
int* DevFilter::apply_grayscale_average(float bgr[], uint x, uint y)
{
	float	b, g, r;
	float	gray;
	int		result[3];

	b = bgr[0];
	g = bgr[1];
	r = bgr[2];

	gray = (b + g + r) / 3;

	result[0] = gray;
	result[1] = gray;
	result[2] = gray;

	return result;
}
/*
int* DevFilter::apply_grayscale_luminosity(Mat img, uint x, uint y)
{
	float	b, g, r;
	float	gray;
	Vec3b	pixel;
	Vec3b	result;

	pixel = img.at<Vec3b>(Point(x, y));
	b = pixel[0];
	g = pixel[1];
	r = pixel[2];

	gray = (r*0.3) + (g*0.59) + (b*0.11);


	result = img.at<Vec3b>(Point(x, y));
	result[0] = gray;
	result[1] = gray;
	result[2] = gray;

	return result;
}
*/
void DevFilter::apply_sepia(float(&bgr)[3], uint x, uint y, int(&color)[3])
{
	float	b, g, r;
	float	fb, fg, fr;

	b = bgr[0];
	g = bgr[1];
	r = bgr[2];

	fr = ((r*0.393) + (g*0.769) + (b*0.189)) / 2;
	fg = ((r*0.349) + (g*0.686) + (b*0.168)) / 2;
	fb = ((r*0.272) + (g*0.534) + (b*0.131)) / 2;

	color[0] = fb;
	color[1] = fg;
	color[2] = fr;
}
/*
int* DevFilter::apply_sobel(Mat img, uint x, uint y)
{
	float	b, g, r;
	float	gray, sum_x = 0, sum_y = 0, sum;
	Vec3b	pixel;
	Vec3b	result;
	int		pX, pY;
	int		maskX[3][3] = {
		-1, 0, 1,
		-2, 0, 2,
		-1, 0, 1
	};
	int		maskY[3][3] = {
		-1, -2, -1,
		0,  0,  0,
		1,  2,  1
	};

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			pX = x + j;
			pY = y + i;

			if (pX > img.cols - 1 || pY > img.rows - 1) {
				sum_x = sum_x + 0;
				sum_y = sum_y + 0;
			}
			else
			{
				pixel = img.at<Vec3b>(Point(pX, pY));
				b = pixel[0];
				g = pixel[1];
				r = pixel[2];

				gray = (b + g + r) / 3;

				sum_x = sum_x + maskX[j][i] * gray;
				sum_y = sum_y + maskY[j][i] * gray;
			}
		}
	sum = sqrt(pow(sum_x, 2) + pow(sum_y, 2));

	if (sum > 255)
		sum = 255;
	if (sum < 0)
		sum = 0;

	result = img.at<Vec3b>(Point(x, y));
	result[0] = sum;
	result[1] = sum;
	result[2] = sum;

	return result;
}

int* DevFilter::apply_gaussian(Mat img, uint x, uint y, float sigma)
{
	//Primero que nada, obtenemos la mascara preeliminar
	float	pre[3][3], product;
	int		mask[3][3], sum_mask = 0;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			int px = j - 1,
				py = i - 1;

			product = 0;
			product = (px * px) + (py * py);
			product = product / (sigma * sigma);
			product = exp(-product);
			product = product / (2 * 3.1416 * (sigma * sigma));
			pre[i][j] = product;
		}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			mask[i][j] = (int)(pre[i][j] / pre[0][0]);
			sum_mask += mask[i][j];
		}

	float	b, g, r;
	float	sum_b = 0, sum_g = 0, sum_r = 0;
	Vec3b	pixel;
	Vec3b	result;
	int		pX, pY;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			pX = x + j - 1;
			pY = y + i - 1;

			if (pX > img.cols - 1 || pY > img.rows - 1) {
				sum_b = sum_b + 0;
				sum_g = sum_g + 0;
				sum_r = sum_r + 0;
			}
			else
			{
				pixel = img.at<Vec3b>(Point(pX, pY));
				b = pixel[0];
				g = pixel[1];
				r = pixel[2];

				sum_b = sum_b + mask[j][i] * b;
				sum_g = sum_g + mask[j][i] * g;
				sum_r = sum_r + mask[j][i] * r;
			}
		}

	result = img.at<Vec3b>(Point(x, y));
	sum_b = sum_b / sum_mask;
	sum_g = sum_g / sum_mask;
	sum_r = sum_r / sum_mask;

	if (sum_b < 0)
		sum_b = 0;
	if (sum_g < 0)
		sum_g = 0;
	if (sum_r < 0)
		sum_r = 0;

	if (sum_b > 255)
		sum_b = 255;
	if (sum_g > 255)
		sum_g = 255;
	if (sum_r > 255)
		sum_r = 255;

	result[0] = sum_b;
	result[1] = sum_g;
	result[2] = sum_r;

	return result;
}
*/
Mat DevFilter::apply(string path, uint filter)
{
	Mat		img = imread(path),
			aux = img.clone();
	uint	rows = img.rows, 
			cols = img.cols;

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = img.ptr<uchar>(y);
		uchar *output = aux.ptr<uchar>(y);

		for (uint x = 1; x < (img.cols - 1); x++)
		{
			float	bgr[3];
			bgr[0] = input[x * 3];
			bgr[1] = input[x * 3 + 1];
			bgr[2] = input[x * 3 + 2];
			int		color[3];
			switch (filter)
			{
			case F_MEDIAN:
				apply_median(bgr, x, y, rows, cols, color);
				break;
			/*case F_WEIGHTED_MEDIAN:
				color = apply_weighted_median(img, x, y, 10);
				break;
			case F_MINUS_MEDIAN:
				color = apply_minus_median(img, x, y);
				break;
			case F_GRAYSCALE_AVERAGE:
				color = apply_grayscale_average(bgr, x, y);
				break;*/
			case F_SEPIA:
				apply_sepia(bgr, x, y, color);
				break;
			/*case F_LAPLACIAN:
				color = apply_laplacian(img, x, y);
				break;
			case F_MINUS_LAPLACIAN:
				color = apply_minus_laplacian(img, x, y);
				break;
			case F_DIRECTIONAL_NORTH:
				color = apply_directional_north(img, x, y);
				break;*/
			}
			output[x * 3] = static_cast<int>(color[0]);
			output[x * 3 + 1] = static_cast<int>(color[1]);
			output[x * 3 + 2] = static_cast<int>(color[2]);
		}
	}
	return aux;
}

void DevFilter::apply(Mat & img, uint filter)
{
	uchar *p;
	for (uint y = 1; y < img.rows; y++)
	{
		p = img.ptr<uchar>(y);

		for (uint x = 1; x < (img.cols * img.channels()); x += 3)
		{
			
		}
	}
}

Mat DevFilter::median(string path)
{
	Mat		img = imread(path),
			aux = img.clone();
	uint	rows = img.rows,
			cols = img.cols;

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = img.ptr<uchar>(y);
		uchar *output = aux.ptr<uchar>(y);

		for (uint x = 1; x < (img.cols - 1); x++)
		{
			float	bgr[3];
			int		color[3];

			//TO DO

			float	b, g, r;
			float	sum_b = 0, sum_g = 0, sum_r = 0;
			int		pX, pY,
					rx = x - 1,
					ry = y - 1;
			int		mask[3][3] = {
				1, 1, 1,
				1, 1, 1,
				1, 1, 1
			};

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					pX = rx + j;
					pY = ry + i;

					if (pX > cols - 1 || pY > rows - 1) {
						sum_b = sum_b + 0;
						sum_g = sum_g + 0;
						sum_r = sum_r + 0;
					}
					else
					{
						bgr[0] = input[((x - 1) + j) * 3];
						bgr[1] = input[((x - 1) + j) * 3 + 1];
						bgr[2] = input[((x - 1) + j) * 3 + 2];

						b = bgr[0];
						g = bgr[1];
						r = bgr[2];

						sum_b = sum_b + mask[j][i] * b;
						sum_g = sum_g + mask[j][i] * g;
						sum_r = sum_r + mask[j][i] * r;
					}
				}
			}

			sum_b = sum_b / 9;
			sum_g = sum_g / 9;
			sum_r = sum_r / 9;

			if (sum_b < 0)
				sum_b = 0;
			if (sum_g < 0)
				sum_g = 0;
			if (sum_r < 0)
				sum_r = 0;

			if (sum_b > 255)
				sum_b = 255;
			if (sum_g > 255)
				sum_g = 255;
			if (sum_r > 255)
				sum_r = 255;

			color[0] = sum_b;
			color[1] = sum_g;
			color[2] = sum_r;

			//END TO DO
			
			output[x * 3] = static_cast<int>(color[0]);
			output[x * 3 + 1] = static_cast<int>(color[1]);
			output[x * 3 + 2] = static_cast<int>(color[2]);
		}
	}
	return aux;
}

Mat DevFilter::gaussian(string path, float sigma)
{
	//Primero que nada, obtenemos la mascara preeliminar
	float	pre[3][3], product;
	int		mask[3][3], sum_mask = 0;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			int px = j - 1,
				py = i - 1;

			product = 0;
			product = (px * px) + (py * py);
			product = product / 2 * pow(sigma, 2);
			product = exp(-product);
			product = product / ((2 * 3.1416) * (pow(sigma, 2)));
			pre[i][j] = product;
		}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			mask[i][j] = (int)(pre[i][j] / pre[0][0]);
			sum_mask += mask[i][j];
		}

	Mat		img = imread(path),
			aux = img.clone();
	uint	rows = img.rows,
			cols = img.cols;

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = NULL;
		uchar *output = aux.ptr<uchar>(y);
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			float	bgr[3];
			int		color[3];

			//TO DO

			float	b, g, r;
			float	sum_b = 0, sum_g = 0, sum_r = 0;
			int		pX, pY,
				rx = x - 1,
				ry = y - 1;
	
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					input = img.ptr<uchar>((y - 1) + i);

					pX = rx + j;
					pY = ry + i;

					if (pX > cols - 1 || pY > rows - 1) {
						sum_b = sum_b + 0;
						sum_g = sum_g + 0;
						sum_r = sum_r + 0;
					}
					else
					{
						bgr[0] = input[((x - 1) + j) * 3];
						bgr[1] = input[((x - 1) + j) * 3 + 1];
						bgr[2] = input[((x - 1) + j) * 3 + 2];

						b = bgr[0];
						g = bgr[1];
						r = bgr[2];

						sum_b = sum_b + (mask[j][i] * b);
						sum_g = sum_g + (mask[j][i] * g);
						sum_r = sum_r + (mask[j][i] * r);
					}
				}
			}

			//CHECAR ESTA PARTE
			sum_b = sum_b / sum_mask;
			sum_g = sum_g / sum_mask;
			sum_r = sum_r / sum_mask;

			if (sum_b < 0)
				sum_b = 0;
			if (sum_g < 0)
				sum_g = 0;
			if (sum_r < 0)
				sum_r = 0;

			if (sum_b > 255)
				sum_b = 255;
			if (sum_g > 255)
				sum_g = 255;
			if (sum_r > 255)
				sum_r = 255;

			color[0] = sum_b;
			color[1] = sum_g;
			color[2] = sum_r;

			//END TO DO

			output[x * 3] = static_cast<int>(color[0]);
			output[x * 3 + 1] = static_cast<int>(color[1]);
			output[x * 3 + 2] = static_cast<int>(color[2]);
		}
	}
	return aux;
}

vector <unsigned int> getMask(int width, int height, int row, int col, Mat &frame) {
	vector <unsigned int> mask;
	int pivX = -((width - 1) / 2);
	int pivY = -((height - 1) / 2);
	int rows = frame.rows;
	int cols = frame.cols * frame.channels();
	uchar *o;
	for (int i = pivY; i <= ((height - 1) / 2); i++) {
		for (int j = pivX; j <= ((width - 1) / 2); j++) {
			if ((row + i) < 0 || ((col + (j * 3))) < 0 || (row + i) >= rows || (col + (j * 3)) >= cols) {
				mask.push_back(255);
				mask.push_back(255);
				mask.push_back(255);
			}
			else {
				o = frame.ptr<uchar>(row + i);
				mask.push_back(o[((col + (j * 3)) + 0)]);
				mask.push_back(o[((col + (j * 3)) + 1)]);
				mask.push_back(o[((col + (j * 3)) + 2)]);
			}
		}
	}
	return mask;
}

Mat medianFilter(Mat frame, int maskWidth, int maskHeight) {
	Mat frame2 = frame.clone();
	int channels = frame.channels();
	int nRows = frame.rows;
	int nCols = frame.cols * channels;
	uchar *p, *q;
	for (int i = 0; i < nRows; i++) {
		p = frame.ptr<uchar>(i);
		q = frame2.ptr<uchar>(i);
		for (int j = 0; j < nCols; j += 3) {
			vector <unsigned int> mask = getMask(maskWidth, maskHeight, i, j, frame);
			vector <unsigned int> sortBlue;
			vector <unsigned int> sortGreen;
			vector <unsigned int> sortRed;
			for (int k = 0; k < mask.size(); k += 3) {
				sortBlue.push_back(mask[k]);
				sortGreen.push_back(mask[k + 1]);
				sortRed.push_back(mask[k + 2]);
			}
			sort(sortBlue.begin(), sortBlue.end());
			sort(sortGreen.begin(), sortGreen.end());
			sort(sortRed.begin(), sortRed.end());
			int blue = sortBlue[(sortBlue.size() / 2)];
			int green = sortGreen[(sortGreen.size() / 2)];
			int red = sortRed[(sortRed.size() / 2)];
			q[j] = blue;
			q[j + 1] = green;
			q[j + 2] = red;
		}
	}
	return frame2;
}
