#include "Filter.h"

struct Coord
{
	int x;
	int y;
};

Vec3b Filter::apply_median(Mat img, uint x, uint y)
{
	//Declaramos todas las variables que utilizaremos
	float	b, g, r;
	float	sum_b = 0, sum_g = 0, sum_r = 0;
	Vec3b	pixel;
	Vec3b	result;
	Coord	matrix[9] = {
		{ x - 1,	y - 1 },
		{ x,		y - 1 },
		{ x + 1,	y - 1 },
		{ x - 1,	y },
		{ x,		y },
		{ x + 1,	y },
		{ x - 1,	y + 1 },
		{ x,		y + 1 },
		{ x + 1,	y + 1 },
	};

	//Este for nos sirve para recorrer el dominio de posciones
	//a los cuales se va a afectar.
	for (int i = 0; i < 9; i++)
	{
		//Para cada posición, limpiamos el rastro de los demas colores
		b = 0; g = 0; r = 0;

		//Obtenemos el pixel y sus propiedades r g b
		pixel = img.at<Vec3b>(Point(matrix[i].x, matrix[i].y));
		b = pixel[0];
		g = pixel[1];
		r = pixel[2];

		//Vamos haciendo la sumatoria a medida que va recorriendo las poisciones
		sum_b += b;
		sum_g += g;
		sum_r += r;
	}

	//Aquí dividimos por cada posicion que existe en el arreglo
	result = img.at<Vec3b>(Point(x, y));
	sum_b /= 9;
	sum_g /= 9;
	sum_r /= 9;

	//Establecemos rango de 0 a 255 
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

	//El pixel a devolver es la sumatoria
	result[0] = sum_b;
	result[1] = sum_g;
	result[2] = sum_r;

	//retornamos
	return result;
}

Vec3b Filter::apply_weighted_median(Mat img, uint x, uint y, uint weight)
{
	float	b, g, r;
	float	sum_b = 0, sum_g = 0, sum_r = 0;
	Vec3b	pixel;
	Vec3b	result;
	Coord	matrix[9] = {
		{ x - 1,	y - 1 },
		{ x,		y - 1 },
		{ x + 1,	y - 1 },
		{ x - 1,	y },
		{ x,		y },
		{ x + 1,	y },
		{ x - 1,	y + 1 },
		{ x,		y + 1 },
		{ x + 1,	y + 1 },
	};

	for (int i = 0; i < 9; i++)
	{
		b = 0; g = 0; r = 0;

		pixel = img.at<Vec3b>(Point(matrix[i].x, matrix[i].y));
		b = pixel[0];
		g = pixel[1];
		r = pixel[2];

		if (matrix[i].x == int(x) && matrix[i].y == int(y))
		{
			sum_b += b * weight;
			sum_g += g * weight;
			sum_r += r * weight;
		}else
		{
			sum_b += b;
			sum_g += g;
			sum_r += r;
		}
	}

	result = img.at<Vec3b>(Point(x, y));
	sum_b /= 8 + weight;
	sum_g /= 8 + weight;
	sum_r /= 8 + weight;

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
	Coord	matrix[9] = {
		{ x - 1,	y - 1 },
		{ x,		y - 1 },
		{ x + 1,	y - 1 },
		{ x - 1,	y },
		{ x,		y },
		{ x + 1,	y },
		{ x - 1,	y + 1 },
		{ x,		y + 1 },
		{ x + 1,	y + 1 },
	};

	for (int i = 0; i < 9; i++)
	{
		b = 0; g = 0; r = 0;

		pixel = img.at<Vec3b>(Point(matrix[i].x, matrix[i].y));
		b = pixel[0];
		g = pixel[1];
		r = pixel[2];

		if (matrix[i].x == int(x) && matrix[i].y == int(y))
		{
			sum_b += b * 8;
			sum_g += g * 8;
			sum_r += r * 8;
		}
		else
		{
			sum_b += b * -1;
			sum_g += g * -1;
			sum_r += r * -1;
		}
	}

	result = img.at<Vec3b>(Point(x, y));
	sum_b /= 9;
	sum_g /= 9;
	sum_r /= 9;

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

/*Vec3b Filter::apply_gaussian(Mat img, uint x, uint y)
{
}*/

Vec3b Filter::apply_laplacian(Mat img, uint x, uint y)
{
	float	average;
	float	sum_averge = 0;
	float	b, g, r;
	float	sum_b = 0, sum_g = 0, sum_r = 0;
	Vec3b	pixel;
	Vec3b	result;
	Coord	matrix[9] = {
		{ x - 1,	y - 1 },
		{ x,		y - 1 },
		{ x + 1,	y - 1 },
		{ x - 1,	y },
		{ x,		y },
		{ x + 1,	y },
		{ x - 1,	y + 1 },
		{ x,		y + 1 },
		{ x + 1,	y + 1 },
	};

	for (int i = 0; i < 9; i++)
	{
		b = 0; g = 0; r = 0;

		pixel = img.at<Vec3b>(Point(matrix[i].x, matrix[i].y));
		b = pixel[0];
		g = pixel[1];
		r = pixel[2];

		average = (b + g + r) / 3;

		if (i == 4)
		{
			sum_averge += average * -4;
		}
		else if(i == 1 || i == 3 || i == 5 || i == 7)
		{
			sum_averge += average;
		}
	}

	result = img.at<Vec3b>(Point(x, y));
	/*sum_b /= 4;
	sum_g /= 4;
	sum_r /= 4;*/

	/*if (sum_b < 0)
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
		sum_r = 255;*/

	if (sum_averge < 0)
		sum_averge = 0;
	if (sum_averge > 255)
		sum_averge = 255;

	result[0] = sum_averge;
	result[1] = sum_averge;
	result[2] = sum_averge;

	return result;
}

Vec3b Filter::apply_minus_laplacian(Mat img, uint x, uint y)
{
	int		average;
	float	b, g, r;
	float	sum_b = 0, sum_g = 0, sum_r = 0;
	Vec3b	pixel;
	Vec3b	result;
	Coord	matrix[9] = {
		{ x - 1,	y - 1 },
		{ x,		y - 1 },
		{ x + 1,	y - 1 },
		{ x - 1,	y },
		{ x,		y },
		{ x + 1,	y },
		{ x - 1,	y + 1 },
		{ x,		y + 1 },
		{ x + 1,	y + 1 },
	};

	for (int i = 0; i < 9; i++)
	{
		b = 0; g = 0; r = 0;

		pixel = img.at<Vec3b>(Point(matrix[i].x, matrix[i].y));
		b = pixel[0];
		g = pixel[1];
		r = pixel[2];

		average = (int)(b + g + r) / 3;

		if (matrix[i].x == int(x) && matrix[i].y == int(y))
		{
			sum_b += average * 5;
			sum_g += average * 5;
			sum_r += average * 5;
		}
		else if ((matrix[i].x == matrix[0].x && matrix[i].y == matrix[0].y) ||
				 (matrix[i].x == matrix[2].x && matrix[i].y == matrix[2].y) ||
				 (matrix[i].x == matrix[6].x && matrix[i].y == matrix[6].y) ||
				 (matrix[i].x == matrix[8].x && matrix[i].y == matrix[8].y))
		{
			sum_b += average * 0;
			sum_g += average * 0;
			sum_r += average * 0;
		}
		else
		{
			sum_b += average * -1;
			sum_g += average * -1;
			sum_r += average * -1;
		}
	}

	result = img.at<Vec3b>(Point(x, y));
	sum_b /= 1;
	sum_g /= 1;
	sum_r /= 1;

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

Vec3b Filter::apply_directional_north(Mat img, uint x, uint y)
{
	int		average;
	float	b, g, r;
	float	sum_b = 0, sum_g = 0, sum_r = 0;
	Vec3b	pixel;
	Vec3b	result;
	Coord	matrix[9] = {
		{ x - 1,	y - 1 },
		{ x,		y - 1 },
		{ x + 1,	y - 1 },
		{ x - 1,	y },
		{ x,		y },
		{ x + 1,	y },
		{ x - 1,	y + 1 },
		{ x,		y + 1 },
		{ x + 1,	y + 1 },
	};

	for (int i = 0; i < 9; i++)
	{
		b = 0; g = 0; r = 0;

		pixel = img.at<Vec3b>(Point(matrix[i].x, matrix[i].y));
		b = pixel[0];
		g = pixel[1];
		r = pixel[2];

		average = (b + g + r) / 3;

		if (matrix[i].x == int(x) && matrix[i].y == int(y))
		{
			sum_b += average * -2;
			sum_g += average * -2;
			sum_r += average * -2;
		}
		else if (matrix[i].y == matrix[6].y ||
				 matrix[i].y == matrix[7].y ||
				 matrix[i].y == matrix[8].y)
		{
			sum_b += average * -1;
			sum_g += average * -1;
			sum_r += average * -1;
		}
		else
		{
			sum_b += average;
			sum_g += average;
			sum_r += average;
		}
	}

	result = img.at<Vec3b>(Point(x, y));
	sum_b /= 1;
	sum_g /= 1;
	sum_r /= 1;

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

Vec3b Filter::apply_directional_south(Mat img, uint x, uint y)
{
	float	b, g, r;
	float	sum_b = 0, sum_g = 0, sum_r = 0;
	Vec3b	pixel;
	Vec3b	result;
	Coord	matrix[9] = {
		{ x - 1,	y - 1 },
		{ x,		y - 1 },
		{ x + 1,	y - 1 },
		{ x - 1,	y },
		{ x,		y },
		{ x + 1,	y },
		{ x - 1,	y + 1 },
		{ x,		y + 1 },
		{ x + 1,	y + 1 },
	};

	for (int i = 0; i < 9; i++)
	{
		b = 0; g = 0; r = 0;

		pixel = img.at<Vec3b>(Point(matrix[i].x, matrix[i].y));
		b = pixel[0];
		g = pixel[1];
		r = pixel[2];

		if (matrix[i].x == int(x) && matrix[i].y == int(y))
		{
			sum_b += b * -2;
			sum_g += g * -2;
			sum_r += r * -2;
		}
		else if (matrix[i].y == matrix[0].y ||
				 matrix[i].y == matrix[1].y ||
				 matrix[i].y == matrix[2].y)
		{
			sum_b += b * -1;
			sum_g += g * -1;
			sum_r += r * -1;
		}
		else
		{
			sum_b += b;
			sum_g += g;
			sum_r += r;
		}
	}

	result = img.at<Vec3b>(Point(x, y));
	sum_b /= 1;
	sum_g /= 1;
	sum_r /= 1;

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

Vec3b Filter::apply_gray_scale(Mat img, uint x, uint y)
{
	int		average;
	float	b, g, r;
	Vec3b	pixel;
	Vec3b	result;

	b = 0; g = 0; r = 0;

	pixel = img.at<Vec3b>(Point(x, y));
	b = pixel[0];
	g = pixel[1];
	r = pixel[2];

	average = (int)(b + g + r) / 3;

	result = img.at<Vec3b>(Point(x, y));

	result[0] = average;
	result[1] = average;
	result[2] = average;

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
			case F_DIRECTIONAL_SOUTH:
				color = apply_directional_south(img, x, y);
				break;
			case F_GRAY_SCALE:
				color = apply_gray_scale(img, x, y);
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
				//cout << color << endl;
				break;
			case F_MINUS_LAPLACIAN:
				color = apply_minus_laplacian(img, x, y);
				break;
			case F_DIRECTIONAL_NORTH:
				color = apply_directional_north(img, x, y);
				break;
			case F_DIRECTIONAL_SOUTH:
				color = apply_directional_south(img, x, y);
				break;
			case F_GRAY_SCALE:
				color = apply_gray_scale(img, x, y);
				break;
			}
			img.at<Vec3b>(Point(x, y)) = color;
		}

	return img;
}
