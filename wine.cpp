#include "wine.h"

// Wine constructor
Wine::Wine(string new_name, string new_type, int new_vintage, int new_rating, double new_price)
{
	wine_price = new_price;
	wine_name = new_name;
	wine_score = new_rating;
	wine_vintage = new_vintage;
	wine_type = new_type;
}

int Wine::get_vintage()
{
	return wine_vintage;
}

int Wine::get_score()
{
	return wine_score;
}

string Wine::get_name()
{
	return wine_name;
}

string Wine::get_type()
{
	return wine_type;
}

double Wine::get_price()
{
	return wine_price;
}

