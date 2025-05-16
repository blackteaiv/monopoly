#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include "Region.h"
#include "Player.h"

using namespace std;

void setTextColor(int textColor);
void setTextAndBackgroundColor(int textColor, int backgroundColor);
void resetColor();

void beginAnime();

void drawEdge();
void blank();

void regionName(int num);
void playerInRegion(int num);
void regionLevel(int num);
void drawMap();

void walk(int who, int count);

string dice[6][5] = { {"+-------+","|       |","|   ¡´   |","|       |","+-------+"},
					  {"+-------+","| ¡´     |","|       |","|     ¡´ |","+-------+"},
					  {"+-------+","| ¡´     |","|   ¡´   |","|     ¡´ |","+-------+"},
					  {"+-------+","| ¡´   ¡´ |","|       |","| ¡´   ¡´ |","+-------+"},
					  {"+-------+","| ¡´   ¡´ |","|   ¡´   |","| ¡´   ¡´ |","+-------+"},
					  {"+-------+","| ¡´   ¡´ |","| ¡´   ¡´ |","| ¡´   ¡´ |","+-------+"} };

int twoDiceTotal;
void rollDice();

Region area[28];
Player player[2];

clock_t startTime, endTime;

int main()
{
	srand(time(NULL));
	ifstream in;
	in.open("map.txt");

	for (int i = 0;i < 28;i++)
		in >> area[i].name;

	in.close();


	area[0].playerHere[0] = 1;area[0].playerHere[1] = 1;

	bool playerTurn = 0;
	string uselessStr;
	//beginAnime();

	while (1)
	{
		system("CLS");
		drawMap();
		cout << "Player " << (playerTurn == 0 ? "A" : "B") << " turn" << endl;
		cout << "(choose to roll the dice or check the items)" << endl << "Enter any word to continue : ";
		cin >> uselessStr;
		rollDice();
		cout << twoDiceTotal << endl;
		cout << "(check the dice)" << endl << "Enter any word to move : ";
		cin >> uselessStr;
		walk(playerTurn, twoDiceTotal);
		cout << "Player " << (playerTurn == 0 ? "A" : "B") << " turn" << endl;
		cout << "(Trigger events or check the items)" << endl;
		cout << "(After the events triggered, change side)" << endl;
		cout << "Enter any word to continue : ";
		cin >> uselessStr;
		playerTurn = !playerTurn;
	}
}

void setTextColor(int textColor)
{
	//white:0 red:31 green:32 yellow:33 blue:34 purple:35 light blue:36
	cout << "\033[" << textColor << "m";
}

void setTextAndBackgroundColor(int textColor, int backgroundColor)
{
	cout << "\033[" << textColor << ";" << backgroundColor << "m";
}

// Function to reset the console color
void resetColor()
{
	cout << "\033[0m";
}

void beginAnime()
{
	//white:0 red:31 green:32 yellow:33 blue:34 purple:35 light blue:36
	int color[11] = { 31,33,32,36,34,35,31,33,36,34,0 };
	int times = 45;

	for (int i = 0;i <= 10;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			cout << endl;
		}

		for (int j = 0;j < times;j++)
			cout << " ";

		setTextColor(color[i]);
		cout << "  /\\_/\\         ";
		resetColor();
		cout << i * 10 << "%" << endl;

		for (int j = 0;j < times;j++)
			cout << " ";

		setTextColor(color[i]);
		cout << "=( ¡P£s¡P )=";
		resetColor();
		cout << "       [";
		setTextColor(32);

		for (int j = 0;j < i;j++)
		{
			cout << "#";
		}

		setTextColor(31);
		for (int j = 10 - i;j > 0;j--)
		{
			cout << "_";
		}

		resetColor();
		cout << "]" << endl;

		for (int j = 0;j < times;j++)
			cout << " ";

		setTextColor(color[i]);
		cout << " / > < \\" << endl;
		resetColor();
		startTime = clock();

		do
		{
			endTime = clock();
		} while (endTime - startTime < 500);

		system("CLS");
	}
}

void drawEdge()
{
	for (int i = 0; i < 160; i++)
	{
		if (i % 20 == 0)
		{
			cout << "+";
		}
		else
		{
			cout << "-";
		}
	}

	cout << "+" << endl;
}

void blank()
{
	cout << "                   |";
}

void regionName(int num)
{
	int length = 3 + area[num].name.length();
	cout << " ";

	if (num >= 10)
	{
		length++;
	}

	if (area[num].owner == 0)
		setTextColor(31);
	else if (area[num].owner == 1)
		setTextColor(32);
	else if (area[num].name == "Start")
		setTextColor(42);
	else if (area[num].name == "Chance")
		setTextAndBackgroundColor(30, 43);
	else if (area[num].name == "Fate")
		setTextColor(45);
	else if (area[num].name == "Item Shop")
		setTextAndBackgroundColor(30, 46);
	else if (area[num].name == "Hospital")
		setTextColor(41);
	else
		resetColor();

	cout << num << " " << area[num].name;

	resetColor();

	for (int i = length;i < 19;i++)
	{
		cout << " ";
	}

	cout << "|";
}

void playerInRegion(int num)
{
	if (num < 10)
	{
		for (int i = 0;i < 3;i++)
			cout << " ";
	}
	else
	{
		for (int i = 0;i < 4;i++)
			cout << " ";
	}

	if (area[num].playerHere[0] == 1)
	{
		setTextColor(31);
		cout << "[A]";
		resetColor();

		if (area[num].playerHere[1] == 1)
		{
			setTextColor(32);
			cout << "[B]";
			resetColor();
		}
		else
			cout << "   ";
	}
	else if (area[num].playerHere[1] == 1)
	{
		setTextColor(32);
		cout << "[B]   ";
		resetColor();
	}
	else
		cout << "      ";

	if (num < 10)
	{
		for (int i = 0;i < 10;i++)
			cout << " ";
	}
	else
	{
		for (int i = 0;i < 9;i++)
			cout << " ";
	}

	cout << "|";
}

void regionLevel(int num)
{
	if (area[num].owner != 2)
	{
		if (area[num].owner == 0)
			setTextColor(31);
		else if (area[num].owner == 1)
			setTextColor(32);

		if (num < 10)
		{
			cout << "   Level 0         ";
		}
		else
		{
			cout << "    Level 0        ";
		}

		resetColor();
	}
	else
	{
		resetColor();

		if (num < 10)
		{
			cout << "   Vacancy         ";
		}
		else
		{
			cout << "    Vacancy        ";
		}
	}

	cout << "|";
}

void drawMap()
{
	drawEdge();

	cout << "|";regionName(0);regionName(1);regionName(2);regionName(3);regionName(4);regionName(5);regionName(6);regionName(7);cout << endl;
	cout << "|";playerInRegion(0);playerInRegion(1);playerInRegion(2);playerInRegion(3);playerInRegion(4);playerInRegion(5);playerInRegion(6);playerInRegion(7);cout << endl;
	cout << "|";blank();regionLevel(1);blank();regionLevel(3);blank();regionLevel(5);regionLevel(6);regionLevel(7);cout << endl;

	drawEdge();

	cout << "|";regionName(27);blank();blank();blank();blank();blank();blank();regionName(8);cout << endl;
	cout << "|";playerInRegion(27);blank();blank();blank();blank();blank();blank();playerInRegion(8);cout << endl;
	cout << "|";regionLevel(27);blank();blank();blank();blank();blank();blank();regionLevel(8);cout << endl;

	drawEdge();

	cout << "|";regionName(26);blank();blank();blank();blank();blank();blank();regionName(9);cout << endl;
	cout << "|";playerInRegion(26);blank();blank();blank();blank();blank();blank();playerInRegion(9);cout << endl;
	cout << "|";regionLevel(26);blank();blank();blank();blank();blank();blank();regionLevel(9);cout << endl;

	drawEdge();

	cout << "|";regionName(25);blank();blank();blank();blank();blank();blank();regionName(10);cout << endl;
	cout << "|";playerInRegion(25);blank();blank();blank();blank();blank();blank();playerInRegion(10);cout << endl;
	cout << "|";blank();blank();blank();blank();blank();blank();blank();regionLevel(10);cout << endl;

	drawEdge();

	cout << "|";regionName(24);blank();blank();blank();blank();blank();blank();regionName(11);cout << endl;
	cout << "|";playerInRegion(24);blank();blank();blank();blank();blank();blank();playerInRegion(11);cout << endl;
	cout << "|";regionLevel(24);blank();blank();blank();blank();blank();blank();blank();cout << endl;

	drawEdge();

	cout << "|";regionName(23);blank();blank();blank();blank();blank();blank();regionName(12);cout << endl;
	cout << "|";playerInRegion(23);blank();blank();blank();blank();blank();blank();playerInRegion(12);cout << endl;
	cout << "|";regionLevel(23);blank();blank();blank();blank();blank();blank();regionLevel(12);cout << endl;

	drawEdge();

	cout << "|";regionName(22);blank();blank();blank();blank();blank();blank();regionName(13);cout << endl;
	cout << "|";playerInRegion(22);blank();blank();blank();blank();;blank();blank();playerInRegion(13);cout << endl;
	cout << "|";regionLevel(22);blank();blank();blank();blank();;blank();blank();regionLevel(13);cout << endl;

	drawEdge();

	cout << "|";regionName(21);regionName(20);regionName(19);regionName(18);regionName(17);regionName(16);regionName(15);regionName(14);cout << endl;
	cout << "|";playerInRegion(21);playerInRegion(20);playerInRegion(19);playerInRegion(18);playerInRegion(17);playerInRegion(16);playerInRegion(15);playerInRegion(14);cout << endl;
	cout << "|";regionLevel(21);regionLevel(20);regionLevel(19);regionLevel(18);blank();blank();regionLevel(15);regionLevel(14);cout << endl;

	drawEdge();
}

void rollDice()
{

	int first = rand() % 6;
	int second = rand() % 6;

	for (int i = 0;i < 5;i++)
	{
		cout << dice[first][i] << "  " << dice[second][i] << endl;
	}

	twoDiceTotal = first + second + 2;
}

void walk(int who, int count)
{
	for (int i = count;i > 0;i--)
	{
		area[player[who].position].playerHere[who] = 0;
		player[who].position = (player[who].position + 1) % 16;
		area[player[who].position].playerHere[who] = 1;
		system("CLS");
		drawMap();
		startTime = clock();

		do
		{
			endTime = clock();
		} while (endTime - startTime < 150);
	}
}