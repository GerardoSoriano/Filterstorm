#include <iostream>
#include "DevPicture.h"
#include "DevFilter.h"
using namespace std;

struct Node
{
	Node *back;
	int filter;
	DevPicture *dp;
	Node *next;
}*current, *old;

void apply_filter_routine();
void modify_filter_routine();
void see_history_routine();
void exit_routine();

void add_node(Node *&ptr, Node *&aux);

void main()
{
	namedWindow("main");

	current = new Node();
	current->back = nullptr;
	current->filter = 0;
	current->dp = new DevPicture(R"(C:\Users\gerar\OneDrive\Imágenes\Dexter1.jpg)");
	current->next = nullptr;
	old = current;

	imshow("main", current->dp->image);
	waitKey(1);

	bool exit = true;
	do
	{
		int option = 0;
		cout << "Que deseas realizar?" << endl;
		cout << "1.\t Aplicar filtro." << endl;
		cout << "2.\t Modificar ultimo filtro." << endl;
		cout << "3.\t Ver historial de filtros." << endl;
		cout << "4.\t Salir." << endl;
		cin >> option;

		system("CLS");

		switch (option)
		{
		case 1:
			apply_filter_routine();
			break;
		case 2:
			modify_filter_routine();
			break;
		case 3:
			see_history_routine();
			break;
		case 4:
			exit_routine();
			break;
		}
	} while (exit);

	system("PAUSE");
}

void apply_filter_routine()
{
	int filter;
	cout << "Que filtro deseas aplicar?" << endl;
	cout << "1.\t Filtro de la media" << endl;
	cout << "2.\t Filtro de la media ponderada" << endl;
	cout << "3.\t Filtro de sustraccion de la media" << endl;
	cout << "4.\t Filtro del promedio" << endl;
	cout << "5.\t Filtro laplaciano" << endl;
	cout << "6.\t Filtro menos laplaciano" << endl;
	cout << "7.\t Filtro direccional norte" << endl;
	cout << "8.\t Filtro direccional este" << endl;
	cout << "9.\t Filtro escala de gris por promedio" << endl;
	cout << "10.\t Filtro escala de gris por luminosidad" << endl;
	cout << "11.\t Filtro escala de gris por luminancia" << endl;
	cout << "12.\t Filtro sepia" << endl;
	cout << "13.\t Filtro sobel" << endl;
	cout << "14.\t Filtro gaussiano" << endl;
	cout << "15.\t Filtro de histograma normalizado" << endl;
	cout << "16.\t Filtro de histograma simple" << endl;
	cout << "17.\t Filtro de histograma uniforme" << endl;
	cin >> filter;

	current = new Node;
	current->filter = filter;

	switch (filter)
	{
	case F_MEDIAN:
		current->dp = new DevPicture(old->dp->image.clone());
		current->dp->image = DevFilter::median(current->dp->image);
		break;
	case F_WEIGHTED_MEDIAN:
		current->dp->image = DevFilter::weighted_median(old->dp->image.clone(), 2);
		break;
	case F_MINUS_MEDIAN:
		current->dp->image = DevFilter::minus_median(old->dp->image.clone());
		break;
	case F_AVERAGE:
		current->dp->image = DevFilter::average(old->dp->image.clone());
		break;
	case F_LAPLACIAN:
		current->dp->image = DevFilter::laplacian(old->dp->image.clone());
		break;
	case F_MINUS_LAPLACIAN:
		current->dp->image = DevFilter::minus_laplacian(old->dp->image.clone());
		break;
	case F_DIRECTIONAL_NORTH:
		current->dp->image = DevFilter::directional_north(old->dp->image.clone());
		break;
	case F_DIRECTIONAL_EAST:
		current->dp->image = DevFilter::directional_east(old->dp->image.clone());
		break;
	case F_GRAYSCALE_AVERAGE:
		current->dp->image = DevFilter::grayscale_average(old->dp->image.clone());
		break;
	case F_GRAYSCALE_LUMINOSITY:
		current->dp->image = DevFilter::grayscale_luminosity(old->dp->image.clone());
		break;
	case F_GRAYSCALE_LUMINANCE:
		current->dp->image = DevFilter::grayscale_luminance(old->dp->image.clone());
		break;
	case F_SEPIA:
		current->dp->image = DevFilter::sepia(old->dp->image.clone());
		break;
	case F_SOBEL:
		current->dp->image = DevFilter::sobel(old->dp->image.clone());
		break;
	case F_GAUSSIAN:
		current->dp->image = DevFilter::gaussian(old->dp->image.clone(), 1);
		break;
	case 15:
		break;
	case 16:
		break;
	case 17:
		break;
	}

	add_node(current, old);
}

void modify_filter_routine()
{
}

void see_history_routine()
{
}

void exit_routine()
{
}

void add_node(Node *& ptr, Node *& aux)
{
	ptr->back = aux;
	ptr->next = nullptr;

	aux->next = ptr;
	aux = ptr;

	imshow("main", ptr->dp->image);
	waitKey(1);
}
