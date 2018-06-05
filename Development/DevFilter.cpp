#include "DevFilter.h"
#include <cmath>

int min_element(int a[], int i)
{
	if (i == 0) return 0;
	int j = min_element(a, i - 1);
	if (a[i - 1] < a[j]) return i - 1;
	return j;
}

void swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

void sort(int* a, int sz)
{
	if (sz == 1) return;
	int j = min_element(a, sz);
	if (j != 0) swap(*a, a[j]);
	sort(++a, sz - 1);
}

Mat DevFilter::median(string path)
{
	Mat img = imread(path);
	Mat aux = img.clone();
	const uint rows = img.rows;
	const uint cols = img.cols;
	int mask[3][3] = {
		1, 1, 1,
		1, 1, 1,
		1, 1, 1
	};

	for (uint y = 1; y < (rows - 1); y++)
	{
		uchar *input = nullptr;
		uchar *output = aux.ptr<uchar>(y);
		for (uint x = 1; x < (cols - 1); x++)
		{
			int sum_b = 0;
			int sum_g = 0;
			int sum_r = 0;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					input = img.ptr<uchar>((y - 1) + i);

					const int px = (x - 1) + j;
					const int py = (y - 1) + i;

					if (px > cols - 1 || py > rows - 1) {
						sum_b = sum_b + 0;
						sum_g = sum_g + 0;
						sum_r = sum_r + 0;
					}
					else
					{
						const float b = input[((x - 1) + j) * 3];;
						const float g = input[((x - 1) + j) * 3 + 1];
						const float r = input[((x - 1) + j) * 3 + 2];

						sum_b = sum_b + (mask[j][i] * b);
						sum_g = sum_g + (mask[j][i] * g);
						sum_r = sum_r + (mask[j][i] * r);
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

			output[x * 3] = sum_b;
			output[x * 3 + 1] = sum_g;
			output[x * 3 + 2] = sum_r;
		}
	}
	return aux;
}

Mat DevFilter::weighted_median(string path, float weight)
{
	Mat img = imread(path);
	Mat aux = img.clone();
	const uint rows = img.rows;
	const uint cols = img.cols;
	int mask[3][3] = {
		1,		1, 1,
		1, weight, 1,
		1,		1, 1
	};

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = nullptr;
		uchar *output = aux.ptr<uchar>(y);
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			int sum_b = 0;
			int sum_g = 0;
			int sum_r = 0;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					input = img.ptr<uchar>((y - 1) + i);

					const int px = (x - 1) + j;
					const int py = (y - 1) + i;

					if (px > cols - 1 || py > rows - 1) {
						sum_b = sum_b + 0;
						sum_g = sum_g + 0;
						sum_r = sum_r + 0;
					}
					else
					{
						const float b = input[((x - 1) + j) * 3];;
						const float g = input[((x - 1) + j) * 3 + 1];
						const float r = input[((x - 1) + j) * 3 + 2];

						sum_b = sum_b + (mask[j][i] * b);
						sum_g = sum_g + (mask[j][i] * g);
						sum_r = sum_r + (mask[j][i] * r);
					}
				}
			}

			sum_b = sum_b / 8 + weight;
			sum_g = sum_g / 8 + weight;
			sum_r = sum_r / 8 + weight;

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

			output[x * 3] = sum_b;
			output[x * 3 + 1] = sum_g;
			output[x * 3 + 2] = sum_r;
		}
	}
	return aux;
}

Mat DevFilter::minus_median(string path)
{
	Mat img = imread(path);
	Mat aux = img.clone();
	const uint rows = img.rows;
	const uint cols = img.cols;
	int mask[3][3] = {
		-1, -1, -1,
		-1,  8, -1,
		-1, -1, -1
	};

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = nullptr;
		uchar *output = aux.ptr<uchar>(y);
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			int sum_b = 0;
			int sum_g = 0;
			int sum_r = 0;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					input = img.ptr<uchar>((y - 1) + i);

					const int px = (x - 1) + j;
					const int py = (y - 1) + i;

					if (px > cols - 1 || py > rows - 1) {
						sum_b = sum_b + 0;
						sum_g = sum_g + 0;
						sum_r = sum_r + 0;
					}
					else
					{
						const float b = input[((x - 1) + j) * 3];;
						const float g = input[((x - 1) + j) * 3 + 1];
						const float r = input[((x - 1) + j) * 3 + 2];

						sum_b = sum_b + (mask[j][i] * b);
						sum_g = sum_g + (mask[j][i] * g);
						sum_r = sum_r + (mask[j][i] * r);
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

			output[x * 3] = sum_b;
			output[x * 3 + 1] = sum_g;
			output[x * 3 + 2] = sum_r;
		}
	}
	return aux;
}

Mat DevFilter::average(string path)
{
	Mat img = imread(path);
	Mat aux = img.clone();
	const uint rows = img.rows;
	const uint cols = img.cols;
	int arr_b[3][3], arr_g[3][3], arr_r[3][3];

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = nullptr;
		uchar *output = aux.ptr<uchar>(y);
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					input = img.ptr<uchar>((y - 1) + i);

					arr_b[j][i] = input[((x - 1) + j) * 3];
					arr_g[j][i] = input[((x - 1) + j) * 3 + 1];
					arr_r[j][i] = input[((x - 1) + j) * 3 + 2];
				}
			}

			sort(arr_b[0], 3 * 3);
			sort(arr_g[0], 3 * 3);
			sort(arr_r[0], 3 * 3);

			output[x * 3] = arr_b[1][1];
			output[x * 3 + 1] = arr_g[1][1];
			output[x * 3 + 2] = arr_r[1][1];
		}
	}
	return aux;
}

Mat DevFilter::laplacian(string path)
{
	Mat img = imread(path);
	Mat aux = img.clone();
	const uint rows = img.rows;
	const uint cols = img.cols;
	int	mask[3][3] = {
		0,  1, 0,
		1, -4, 1,
		0,  1, 0
	};

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = nullptr;
		uchar *output = aux.ptr<uchar>(y);
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			int sum = 0;
			float grey;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					input = img.ptr<uchar>((y - 1) + i);

					const float b = input[((x - 1) + j) * 3];;
					const float g = input[((x - 1) + j) * 3 + 1];
					const float r = input[((x - 1) + j) * 3 + 2];

					grey = (b + g + r) / 3;

					sum = sum + mask[j][i] * grey;

				}
			}

			if (sum < 0)
				sum = 0;
			if (sum > 255)
				sum = 255;

			output[x * 3] = sum;
			output[x * 3 + 1] = sum;
			output[x * 3 + 2] = sum;
		}
	}
	return aux;
}

Mat DevFilter::minus_laplacian(string path)
{
	Mat img = imread(path);
	Mat aux = img.clone();
	const uint rows = img.rows;
	const uint cols = img.cols;
	int	mask[3][3] = {
		 0, -1,  0,
		-1,  5, -1,
		 0, -1,  0
	};

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = nullptr;
		uchar *output = aux.ptr<uchar>(y);
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			int sum = 0;
			float grey;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					input = img.ptr<uchar>((y - 1) + i);

					const float b = input[((x - 1) + j) * 3];;
					const float g = input[((x - 1) + j) * 3 + 1];
					const float r = input[((x - 1) + j) * 3 + 2];

					grey = (b + g + r) / 3;

					sum = sum + mask[j][i] * grey;

				}
			}

			if (sum < 0)
				sum = 0;
			if (sum > 255)
				sum = 255;

			output[x * 3] = sum;
			output[x * 3 + 1] = sum;
			output[x * 3 + 2] = sum;
		}
	}
	return aux;
}

Mat DevFilter::directional_north(string path)
{
	Mat img = imread(path);
	Mat aux = img.clone();
	const uint rows = img.rows;
	const uint cols = img.cols;
	int	mask[3][3] = {
		 1,  1,  1,
		 1, -2,  1,
		-1, -1, -1
	};

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = nullptr;
		uchar *output = aux.ptr<uchar>(y);
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			int sum = 0;
			float grey;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					input = img.ptr<uchar>((y - 1) + i);

					const float b = input[((x - 1) + j) * 3];;
					const float g = input[((x - 1) + j) * 3 + 1];
					const float r = input[((x - 1) + j) * 3 + 2];

					grey = (b + g + r) / 3;

					sum = sum + mask[j][i] * grey;

				}
			}

			if (sum < 0)
				sum = 0;
			if (sum > 255)
				sum = 255;

			output[x * 3] = sum;
			output[x * 3 + 1] = sum;
			output[x * 3 + 2] = sum;
		}
	}
	return aux;
}

Mat DevFilter::directional_east(string path)
{
	Mat img = imread(path);
	Mat aux = img.clone();
	const uint rows = img.rows;
	const uint cols = img.cols;
	int	mask[3][3] = {
		-1,  1,  1,
		-1, -2,  1,
		-1,  1,  1
	};

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = nullptr;
		uchar *output = aux.ptr<uchar>(y);
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			int sum = 0;
			float grey;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					input = img.ptr<uchar>((y - 1) + i);

					const float b = input[((x - 1) + j) * 3];;
					const float g = input[((x - 1) + j) * 3 + 1];
					const float r = input[((x - 1) + j) * 3 + 2];

					grey = (b + g + r) / 3;

					sum = sum + mask[j][i] * grey;

				}
			}

			if (sum < 0)
				sum = 0;
			if (sum > 255)
				sum = 255;

			output[x * 3] = sum;
			output[x * 3 + 1] = sum;
			output[x * 3 + 2] = sum;
		}
	}
	return aux;
}

Mat DevFilter::grayscale_average(string path)
{
	Mat img = imread(path);
	Mat aux = img.clone();

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = img.ptr<uchar>(y);
		uchar *output = aux.ptr<uchar>(y);
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			float	b, g, r;
			float	gray;

			b = input[x * 3];
			g = input[x * 3 + 1];
			r = input[x * 3 + 2];

			gray = (b + g + r) / 3;

			output[x * 3] = static_cast<int>(gray);
			output[x * 3 + 1] = static_cast<int>(gray);
			output[x * 3 + 2] = static_cast<int>(gray);
		}
	}
	return aux;
}

Mat DevFilter::grayscale_luminosity(string path)
{
	Mat img = imread(path);
	Mat aux = img.clone();

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = img.ptr<uchar>(y);
		uchar *output = aux.ptr<uchar>(y);
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			float	b, g, r;
			float	gray;

			b = input[x * 3];
			g = input[x * 3 + 1];
			r = input[x * 3 + 2];

			gray = (r*0.3) + (g*0.59) + (b*0.11);

			output[x * 3] = static_cast<int>(gray);
			output[x * 3 + 1] = static_cast<int>(gray);
			output[x * 3 + 2] = static_cast<int>(gray);
		}
	}
	return aux;
}

Mat DevFilter::grayscale_luminance(string path)
{
	Mat img = imread(path);
	Mat aux = img.clone();
	int gray[3][3];

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = nullptr;
		uchar *output = aux.ptr<uchar>(y);
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					input = img.ptr<uchar>((y - 1) + i);
					float b = input[((x - 1) + j) * 3];
					float g = input[((x - 1) + j) * 3 + 1];
					float r = input[((x - 1) + j) * 3 + 2];

					gray[j][i] = (b + g + r) / 3;
				}
			}

			sort(gray[0], 3 * 3);

			output[x * 3] = (gray[0][0] + gray[2][2]) / 2;
			output[x * 3 + 1] = (gray[0][0] + gray[2][2]) / 2;
			output[x * 3 + 2] = (gray[0][0] + gray[2][2]) / 2;
		}
	}
	return aux;
}

Mat DevFilter::sepia(string path)
{
	Mat img = imread(path);
	Mat aux = img.clone();

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = img.ptr<uchar>(y);
		uchar *output = aux.ptr<uchar>(y);
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			float	b, g, r;
			float	fb, fg, fr;

			b = input[x * 3];
			g = input[x * 3 + 1];
			r = input[x * 3 + 2];

			fr = ((r*0.393) + (g*0.769) + (b*0.189)) / 2;
			fg = ((r*0.349) + (g*0.686) + (b*0.168)) / 2;
			fb = ((r*0.272) + (g*0.534) + (b*0.131)) / 2;

			output[x * 3] = static_cast<int>(fb);
			output[x * 3 + 1] = static_cast<int>(fg);
			output[x * 3 + 2] = static_cast<int>(fr);
		}
	}
	return aux;
}

Mat DevFilter::sobel(string path)
{
	Mat img = imread(path);
	Mat aux = img.clone();
	const uint rows = img.rows;
	const uint cols = img.cols;
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

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = nullptr;
		uchar *output = aux.ptr<uchar>(y);
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			int sum = 0, sum_x = 0, sum_y = 0;
			float gray;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					input = img.ptr<uchar>((y - 1) + i);

					const float b = input[((x - 1) + j) * 3];;
					const float g = input[((x - 1) + j) * 3 + 1];
					const float r = input[((x - 1) + j) * 3 + 2];

					gray = (b + g + r) / 3;

					sum_x = sum_x + maskX[j][i] * gray;
					sum_y = sum_y + maskY[j][i] * gray;
				}
			}
			sum = sqrt(pow(sum_x, 2) + pow(sum_y, 2));

			if (sum < 0)
				sum = 0;
			if (sum > 255)
				sum = 255;

			output[x * 3] = sum;
			output[x * 3 + 1] = sum;
			output[x * 3 + 2] = sum;
		}
	}
	return aux;
}

Mat DevFilter::gaussian(string path, float sigma)
{
	float	pre[3][3];
	int		mask[3][3], sum_mask = 0;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			const int px = j - 1;
			const int py = i - 1;

			float product = 0;
			product = (px * px) + (py * py);
			product = product / 2 * pow(sigma, 2);
			product = exp(-product);
			product = product / ((2 * 3.1416) * (pow(sigma, 2)));
			pre[i][j] = product;
		}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			mask[i][j] = static_cast<int>(pre[i][j] / pre[0][0]);
			sum_mask += mask[i][j];
		}

	Mat img = imread(path);
	Mat aux = img.clone();
	const uint rows = img.rows;
	const uint cols = img.cols;

	for (uint y = 1; y < (img.rows - 1); y++)
	{
		uchar *input = nullptr;
		uchar *output = aux.ptr<uchar>(y);
		for (uint x = 1; x < (img.cols - 1); x++)
		{
			int sum_b = 0;
			int sum_g = 0;
			int sum_r = 0;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					input = img.ptr<uchar>((y - 1) + i);

					const int px = (x - 1) + j;
					const int py = (y - 1) + i;

					if (px > cols - 1 || py > rows - 1) {
						sum_b = sum_b + 0;
						sum_g = sum_g + 0;
						sum_r = sum_r + 0;
					}
					else
					{
						const float b = input[((x - 1) + j) * 3];;
						const float g = input[((x - 1) + j) * 3 + 1];
						const float r = input[((x - 1) + j) * 3 + 2];

						sum_b = sum_b + (mask[j][i] * b);
						sum_g = sum_g + (mask[j][i] * g);
						sum_r = sum_r + (mask[j][i] * r);
					}
				}
			}

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

			output[x * 3] = sum_b;
			output[x * 3 + 1] = sum_g;
			output[x * 3 + 2] = sum_r;
		}
	}
	return aux;
}
