#include "Filter.h"

Vec3b Filter::apply_median(Mat img, uint x, uint y)
{
	float	b, g, r;
	float	sum_b = 0, sum_g = 0, sum_r = 0;
	Vec3b	pixel;
	Vec3b	result;
	int		pX, pY;
	int		mask[3][3] = {
		1, 1, 1,
		1, 1, 1,
		1, 1, 1
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

Vec3b Filter::apply_weighted_median(Mat img, uint x, uint y, uint weight)
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

Vec3b Filter::apply_minus_median(Mat img, uint x, uint y)
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

Vec3b Filter::apply_laplacian(Mat img, uint x, uint y)
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

Vec3b Filter::apply_minus_laplacian(Mat img, uint x, uint y)
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

Vec3b Filter::apply_directional_north(Mat img, uint x, uint y)
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

Vec3b Filter::apply_directional_east(Mat img, uint x, uint y)
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

Vec3b Filter::apply_grayscale_average(Mat img, uint x, uint y)
{
	float	b, g, r;
	float	gray;
	Vec3b	pixel;
	Vec3b	result;

	pixel = img.at<Vec3b>(Point(x, y));
	b = pixel[0];
	g = pixel[1];
	r = pixel[2];

	gray = (b + g + r) / 3;


	result = img.at<Vec3b>(Point(x, y));
	result[0] = gray;
	result[1] = gray;
	result[2] = gray;

	return result;
}

Vec3b Filter::apply_grayscale_luminosity(Mat img, uint x, uint y)
{
	float	b, g, r;
	float	gray;
	Vec3b	pixel;
	Vec3b	result;

	pixel = img.at<Vec3b>(Point(x, y));
	b = pixel[0];
	g = pixel[1];
	r = pixel[2];

	gray = (r*0.3)+(g*0.59)+(b*0.11);


	result = img.at<Vec3b>(Point(x, y));
	result[0] = gray;
	result[1] = gray;
	result[2] = gray;

	return result;
}

Vec3b Filter::apply_sepia(Mat img, uint x, uint y)
{
	float	b, g, r;
	float	fb, fg, fr;
	float	gray;
	Vec3b	pixel;
	Vec3b	result;

	pixel = img.at<Vec3b>(Point(x, y));
	b = pixel[0];
	g = pixel[1];
	r = pixel[2];

	fr = ((r*0.393) + (g*0.769) + (b*0.189)) / 2;
	fg = ((r*0.349) + (g*0.686) + (b*0.168)) / 2;
	fb = ((r*0.272) + (g*0.534) + (b*0.131)) / 2;

	result = img.at<Vec3b>(Point(x, y));
	result[0] = fb;
	result[1] = fg;
	result[2] = fr;

	return result;
}

Vec3b Filter::apply_sobel(Mat img, uint x, uint y)
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

Vec3b Filter::apply_gaussian(Mat img, uint x, uint y, float sigma)
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
			pX = x + j -1;
			pY = y + i -1;

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

Mat Filter::apply(string path, uint filter)
{
	Mat img = imread(path);

	for (uint y = 1; y < (img.rows - 1); y++)
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			Vec3b color = img.at<Vec3b>(Point(x, y));
			Vec3b result = img.at<Vec3b>(Point(x, y));
			switch (filter)
			{
			case F_MEDIAN:
				color = apply_median(img, x, y);
				break;
			case F_WEIGHTED_MEDIAN:
				color = apply_weighted_median(img, x, y, 10);
				break;
			case F_MINUS_MEDIAN:
				color = apply_minus_median(img, x, y);
				break;
			case F_GAUSSIAN:
				result[0] = 255;
				result[1] = 255;
				result[2] = 255;
				color = result;
				break;
			case F_LAPLACIAN:
				color = apply_laplacian(img, x, y);
				break;
			case F_MINUS_LAPLACIAN:
				color = apply_minus_laplacian(img, x, y);
				break;
			case F_DIRECTIONAL_NORTH:
				color = apply_directional_north(img, x, y);
				break;
			}
			img.at<Vec3b>(Point(x, y)) = color;
		}

	return img;
}

Mat Filter::apply(Mat img, uint filter)
{
	for (uint y = 1; y < (img.rows - 1); y++)
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			Vec3b color = img.at<Vec3b>(Point(x, y));
			Vec3b result = img.at<Vec3b>(Point(x, y));
			switch (filter)
			{
			case F_MEDIAN:
				color = apply_median(img, x, y);
				break;
			case F_WEIGHTED_MEDIAN:
				color = apply_weighted_median(img, x, y, 9);
				break;
			case F_MINUS_MEDIAN:
				color = apply_minus_median(img, x, y);
				break;
			case F_LAPLACIAN:
				color = apply_laplacian(img, x, y);
				break;
			case F_MINUS_LAPLACIAN:
				color = apply_minus_laplacian(img, x, y);
				break;
			case F_DIRECTIONAL_NORTH:
				color = apply_directional_north(img, x, y);
				break;
			case F_DIRECTIONAL_EAST:
				color = apply_directional_east(img, x, y);
				break;
			case F_GRAYSCALE_AVERAGE:
				color = apply_grayscale_average(img, x, y);
				break;
			case F_GRAYSCALE_LUMINOSITY:
				color = apply_grayscale_luminosity(img, x, y);
				break;
			case F_SEPIA:
				color = apply_sepia(img, x, y);
				break;
			case F_SOBEL:
				color = apply_sobel(img, x, y);
				break;
			case F_GAUSSIAN:
				color = apply_gaussian(img, x, y, 1);
				break;
			}
			img.at<Vec3b>(Point(x, y)) = color;
		}

	return img;
}

Mat Filter::getHistogram(Mat img, uint histSizeX, uint histSizeY)
{
	vector<Mat>		bgr;
	int				histSize = 256;
	float			range[] = { 0, 256 };
	const float*	histRange = { range };
	Mat				hist_b, hist_g, hist_r;

	split(img, bgr);
	calcHist(&bgr[0], 1, 0, Mat(), hist_b, 1, &histSize, &histRange, true, false);
	calcHist(&bgr[1], 1, 0, Mat(), hist_g, 1, &histSize, &histRange, true, false);
	calcHist(&bgr[2], 1, 0, Mat(), hist_r, 1, &histSize, &histRange, true, false);

	int histWidth = cvRound((double)histSizeX / histSize);
	Mat histImage(histSizeY, histSizeX, CV_8UC3, Scalar(0, 0, 0));

	normalize(hist_b, hist_b, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(hist_g, hist_g, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(hist_r, hist_r, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(histWidth*(i - 1), histSizeY - cvRound(hist_b.at<float>(i - 1))), Point(histWidth*(i), histSizeY - cvRound(hist_b.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(histWidth*(i - 1), histSizeY - cvRound(hist_g.at<float>(i - 1))), Point(histWidth*(i), histSizeY - cvRound(hist_g.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(histWidth*(i - 1), histSizeY - cvRound(hist_r.at<float>(i - 1))), Point(histWidth*(i), histSizeY - cvRound(hist_r.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	}

	return histImage;
}
