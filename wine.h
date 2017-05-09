#ifndef WINE_H__
#define WINE_H__
#include <iostream>
#include <string>

using namespace std;

class Wine
{
private: 
	string wine_name;
	double wine_price;
	int wine_score;
	int wine_vintage;
	string wine_type;

public: 
	Wine() 
	{
		wine_price = 0;
		wine_score = 0;
		wine_vintage = 0;
	}
	Wine(string new_name, int new_vintage, int new_rating, double new_price, string new_type);
	void printInfo(ostream &os) const
	{ 
		os << "Name: "<< wine_name << ' ';
		os << "Vintage: "<< wine_vintage << ' ';
		os << "Score: "<< wine_score << ' ';
		os << "Price: "<< wine_price << ' ';
		os << "Type: "<< wine_type;
	};
	int get_vintage();
	double get_price();
	string get_name();
	int get_score();
	string get_type();
};

static ostream& operator << (ostream &os, const Wine& wine)
{
	wine.printInfo(os);
	return os;
}

#endif // WINE_H__

