/*

http://www.codingfriends.com/index.php/2010/02/17/mysql-connection-example/

To compile up this program you will need to link to the mysql libraries and headers that are used within the program, 
* e.g. mysql.h at the top of the program. To gain access to these, there is a nice mysql_config (you may need to install it via 
* your package manager system if you do not have it already).

Here are my outputs of what is required on the command line for the g++ compiler



g++ -I/usr/include/mysql winedb.cpp -o winedb -L/usr/lib/mysql -lmysqlclient


./windb "select * from wineInfo where price > 100"

*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include "lab.h"
#include "wine.h"
#include <mysql.h>
#include "dbconnect.h"

using namespace std;
 
double calculateAveragePrice(List<Wine> &wines);               //calculate the average for a numbr of wines
void displayWinesList(List<Wine> &wines);                      //display wines in a vectors
void processCommandSQL(string sql_command, List<Wine> &wines); //extract infox from sql database with "command"
void inputInteger(int &x, int low, int high);                  //validate input integer
void inputDouble(double &x, double low, double high);          //validate input is double
void printMeFirst(string personName, string courseName, string version);
int showMenu();
void wineScore(); //wine sorted by the score
void winePrice(); //wine sorted by the price
void wineYear(); //wine sorted by the year 

int main(int argc, char* argv[])
{
	int selection;
	while(true)
	{
		system("tput reset");
		selection = showMenu();

		if(selection == 1) wineScore();
		else 
		if(selection == 2) winePrice();
		else 
		if(selection == 3) wineYear();
		else 
		if(selection == 4) break;

		cout << "Please press Enter to continue. . ."; cin.get();
	}

	cout << "Please press Enter to exit the program..."; cin.get();

	return 0;
}

int showMenu()
{
	int selection;
	printMeFirst("Mohammed Abbas", "CS116 - 2017 Spring", "1.1");
	cout<< "1 --> Display wines by score" << endl;
	cout<< "2 --> Display wines by price" << endl;
	cout<< "3 --> Display wines by year" << endl;
	cout<< "4 --> Exit the program" << endl;

	do
	{
		cout << "Your selection >>"; cin >> selection;

		if(!cin || selection < 1 || selection > 4)
		{
			selection = -1;
			if(!cin)
			{
				cin.clear();
				cin.ignore(9999);
			}
			cout << "Invalid selection." << endl << endl;
		}
		else cout << endl;
	}
	while(selection == -1);

	cin.ignore();
	return selection;	
}

void inputInteger(int &x, int low, int high)
{
	do
	{
		cin >> x;
		if(!cin || x < low || x > high)
		{
			x = low - 1;
			if(!cin)
			{
				cin.clear();
				cin.ignore(9999, '\n');
			}
		}
	} while(x < low);
	cin.ignore();
}

double calculateAveragePrice(List<Wine> &wines)
{
	double total = 0;
	ListNode<Wine> *currentPtr = wines.getFirstPtr();
	while(currentPtr)
	{
		total += currentPtr->getData().get_price();
		currentPtr = currentPtr->getNextPtr();
	}

	double average = total / (double)wines.size();
	return average;
}

void inputDouble(double &x, int low, int high)
{
	do
	{
		cin >> x;
		if(!cin || x < low || x > high)
		{
			x = low - 1;
			if(!cin)
			{
				cin.clear();
				cin.ignore(9999, '\n');
			}
		}
	} while(x < low);
	cin.ignore();	
}

void wineScore()
{
	double x, y;
	double xx, yy;

	cout << "Enter min score >>";
	inputDouble(xx, 0, 100000);

	cout << "Enter max score >>";
	inputDouble(yy, 0, 100000);

	int i;
	double average, total;
	List<Wine> wines;

	string sql_cmd;
	stringstream ss;

	// When xx > yy, we should swap two values or else it will not work
	if(xx > yy)
	{
		x = yy;
		y = xx;
	}
	else
	{
		x = xx;
		y = yy;
	}

	ss << "Select * from wineInfo where score >= " << x << " and score <= " << y << " order by score ASC, price ASC;";
	sql_cmd = ss.str();

	processCommandSQL(sql_cmd, wines);

	cout << "(Wines with all selections)" << endl << endl;
	displayWinesList(wines);

	cout << endl;

	if(wines.size() > 0)
	{
		double averagePrice = calculateAveragePrice(wines);

		cout << "Total wines selected (" << wines.size() << ")"<< endl;
		cout << "Average price for selected wines : " << averagePrice << endl;

		cout << endl;
	}

	cout << "Please press Enter to continue. . .";

	cin.get();
	cout << endl;

	if(wines.size() > 0)
	{
		Wine wine;
		cout << "(Wines with the last element removed)" << endl << endl;
		wines.removeFromBack(wine);
		displayWinesList(wines);
		cout << endl;

		if(wines.size() > 0)
		{
			double averagePrice = calculateAveragePrice(wines);

			cout << "Total wines selected (" << wines.size() << ")"<< endl;
			cout << "Average price for selected wines : " << averagePrice << endl;
			cout << endl;
		}
	}

}

void winePrice()
{
	double x, y;
	double xx, yy;
	List<Wine> wines;

	string sql_cmd;
	stringstream ss;

	cout << "Enter min price >>";
	inputDouble(xx, 0, 100000);

	cout << "Enter max price >>";
	inputDouble(yy, 0, 100000);

	// When xx > yy, we should swap two values or else it will not work
	if(xx > yy)
	{
		x = yy;
		y = xx;
	}
	else
	{
		x = xx;
		y = yy;
	}

	ss << "Select * from wineInfo where price >= " << x << " and price <= " << y << " order by price ASC;";
	sql_cmd = ss.str();

	processCommandSQL(sql_cmd, wines);
	displayWinesList(wines);

	cout << endl;

	if(wines.size() > 0)
	{
		double averagePrice = calculateAveragePrice(wines);

		cout << "Total wines selected (" << wines.size() << ")" << endl;
		cout << "Average price for selected wines : " << averagePrice << endl;

		cout << endl;
	}

}

void wineYear() 
{
	int x, y;
	int xx, yy;
	List<Wine> wines;

	string sql_cmd;
	stringstream ss;

	cout << "Enter min year >>";
	inputInteger(xx, 1700, 2500);

	cout << "Enter max year >>";
	inputInteger(yy, 1700, 2500);

	// When xx > yy, we should swap two values or else it will not work
	if(xx > yy)
	{
		x = yy;
		y = xx;
	}
	else
	{
		x = xx;
		y = yy;
	}

	ss << "Select * from wineInfo where vintage >= " << x << " and vintage <= " << y << " order by score DESC, price ASC;";
	sql_cmd = ss.str();

	processCommandSQL(sql_cmd, wines);
	displayWinesList(wines);

	cout << endl;

	if(wines.size() > 0)
	{
		double averagePrice = calculateAveragePrice(wines);

		cout << "Total wines selected (" << wines.size() << ")" << endl;
		cout << "The average price for the selected wines : " << averagePrice << endl;

		cout << endl;
	}
}

void displayWinesList(List<Wine> &wines)
{
	int i;
	string wine_name;

	if(wines.empty()) 
	{
		cout << "  (There are no wines to be displayed. Please try again.)" << endl;
		return;
	}

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	cout << "|" << setw(23);
	cout << "Wine-Name" << setw(30) << "Vintage" << setw(8) << "Score" << setw(8) << "Price" << setw(6) << "Type" << " |" << endl;

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	 
	ListNode<Wine> *currentPtr = wines.getFirstPtr();
	int index = 0;
	char index_str[10];
	while(currentPtr)
	{
		Wine wine = currentPtr->getData();
		sprintf(index_str, "%.2d.", index + 1);

		wine_name = wine.get_name();
		while(wine_name.size() < 42) wine_name += ' ';

		cout << left << setw(4) << index_str << right << " " << wine_name << ' ' << setw(5) // Wine Name
			<< wine.get_vintage() << setw(8) // Wine Vintage
			<< wine.get_score() << setw(8) // Wine score
			<< wine.get_price() << setw(8) // Wine Price
			<< wine.get_type()                // Wine type
		<< endl;
		index++;
		currentPtr = currentPtr->getNextPtr();
      }
}


void processCommandSQL(string sql_command, List<Wine> &wines)
{
	string wine_name;
	int wine_vintage;
	int wine_score;
	double wine_price;
	string wine_type;

	wines.clear();
	
	MYSQL *conn; // The connection
	MYSQL_RES *res; // The results
	MYSQL_ROW row; // The results row (line by line)

	struct connection_details mysqlD;
	mysqlD.server = (char *)"localhost"; // Where the mysql database is
	mysqlD.user = (char *)"root"; // The root user of mysql	
	mysqlD.password = (char *)"password"; // The password of the root user in mysql
	mysqlD.database = (char *)"mysql"; // The databse to pick
 
	// Connect to the mysql database
	conn = mysql_connection_setup(mysqlD);

	res = mysql_perform_query(conn, (char *)("use wine"));

	// Assign the results return to the MYSQL_RES pointer
	res = mysql_perform_query(conn, (char *)&sql_command[0]);

	int key = 0;
	// Extract Wine sql items one by one
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		wine_name = (row[0]);

		// Erase spaces from the end
		while(wine_name[wine_name.size() - 1] == ' ') wine_name.erase(wine_name.begin() + (wine_name.size() - 1));

		wine_vintage = atoi(row[1]);
		wine_score = atoi(row[2]);
		wine_price = atof(row[3]);

		wine_type = (row[4]);
		// Erase spaces from the end
		while(wine_type[wine_type.size() - 1] == ' ') wine_type.erase(wine_type.begin() + (wine_type.size() - 1));

		wines.insertAtBack(Wine(wine_name, wine_vintage, wine_score, wine_price, wine_type), key); key++;
      }

	// Clean up the database result set
	mysql_free_result(res);
	// Clean up the database link
	mysql_close(conn);
}

void printMeFirst(string personName, string courseName, string version)
{
   cout << "Program written by : " << personName << endl;
   cout << "Course info : " << courseName << endl;
   cout << "version number: " << version << endl;

   time_t localtime;
   time (&localtime);

   cout << "Date : " << ctime(&localtime) << endl;
}

