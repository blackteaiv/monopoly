#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include "Region.h"
#include "Player.h"

using namespace std;

void setTextColor(int textColor);
void setTextAndBackgroundColor(int textColor, int backgroundColor);
void resetColor();

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

Region area[16];
Player player[2];

clock_t startTime, endTime;

int main()
{
	srand(time(NULL));

	area[0].name = "Start";area[1].name = "USA";area[2].name = "Chance";area[3].name = "France";
	area[4].name = "Item Shop";area[5].name = "Germany";area[6].name = "Fate";area[7].name = "UK";
	area[8].name = "Chance";area[9].name = "Italy";area[10].name = "Hospital";area[11].name = "Russia";
	area[12].name = "Chance";area[13].name = "Canada";area[14].name = "Fate";area[15].name = "Japan";
	area[0].playerHere[0] = 1;area[0].playerHere[1] = 1;

	bool playerTurn = 0;
	string b;

	while (1)
	{
		system("CLS");
		drawMap();
		cout << "Player " << (playerTurn == 0 ? "A" : "B") << " turn" << endl;
		cout << "(choose to roll the dice or check the items)" << endl << "Enter any word to continue : ";
		cin >> b;
		rollDice();
		cout << twoDiceTotal << endl;
		cout << "(check the dice)" << endl << "Enter any word to move : ";
		cin >> b;
		walk(playerTurn, twoDiceTotal);
		cout << "Player " << (playerTurn == 0 ? "A" : "B") << " turn" << endl;
		cout << "(Trigger events or check the items)" << endl;
		cout << "(After the events triggered, change side)" << endl;
		cout << "Enter any word to continue : ";
		cin >> b;
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

void drawEdge()
{
	for (int i = 0; i < 100; i++)
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

	if (area[num].owner == 1)
		setTextColor(31);
	else if (area[num].owner == 2)
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
	}
	else
		cout << "   ";

	if (area[num].playerHere[1] == 1)
	{
		setTextColor(32);
		cout << "[B]";
		resetColor();
	}
	else
		cout << "   ";

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
	if (area->owner == 1)
		setTextColor(31);
	else if (area->owner == 2)
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
	cout << "|";
}

void drawMap()
{
	drawEdge();

	cout << "|";regionName(0);regionName(1);regionName(2);regionName(3);regionName(4);cout << endl;
	cout << "|";playerInRegion(0);playerInRegion(1);playerInRegion(2);playerInRegion(3);playerInRegion(4);cout << endl;
	cout << "|";blank();regionLevel(1);blank();regionLevel(3);blank();cout << endl;

	drawEdge();

	cout << "|";regionName(15);blank();blank();blank();regionName(5);cout << endl;
	cout << "|";playerInRegion(15);blank();blank();blank();playerInRegion(5);cout << endl;
	cout << "|";regionLevel(15);blank();blank();blank();regionLevel(5);cout << endl;

	drawEdge();

	cout << "|";regionName(14);blank();blank();blank();regionName(6);cout << endl;
	cout << "|";playerInRegion(14);blank();blank();blank();playerInRegion(6);cout << endl;
	cout << "|";blank();blank();blank();blank();blank();cout << endl;

	drawEdge();

	cout << "|";regionName(13);blank();blank();blank();regionName(7);cout << endl;
	cout << "|";playerInRegion(13);blank();blank();blank();playerInRegion(7);cout << endl;
	cout << "|";regionLevel(13);blank();blank();blank();regionLevel(7);cout << endl;

	drawEdge();

	cout << "|";regionName(12);regionName(11);regionName(10);regionName(9);regionName(8);cout << endl;
	cout << "|";playerInRegion(12);playerInRegion(11);playerInRegion(10);playerInRegion(9);playerInRegion(8);cout << endl;
	cout << "|";blank();regionLevel(11);blank();regionLevel(9);blank();cout << endl;

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