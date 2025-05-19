//https://hackmd.io/@CPklPazPTGmhC46aFU17WQ/Hyrccwp6kl
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <cassert>
#include <algorithm>
#include "Region.h"
#include "Player.h"

using namespace std;

clock_t startTime, endTime;

//delay
void delay(int ms);
//color
void setTextColor(int textColor);
void setTextAndBackgroundColor(int textColor, int backgroundColor);
void resetColor();
//begin anime
void beginAnime();
//draw the map
void drawEdge();
void blank();
void regionName(int num);
void playerInRegion(int num);
void regionLevel(int num);
void drawMap();
//player's status
int lengthOfNumber(int num);
void statusEdge();
void playerStatus(int who);
void status();
//move
void walk(bool who, int count);
//game
void shootDragonDoor();
void horse();
//region
void chance();
void fate();
void house();


string dice[6][5] = { {"+-------+","|       |","|   ¡´   |","|       |","+-------+"},
					  {"+-------+","| ¡´     |","|       |","|     ¡´ |","+-------+"},
					  {"+-------+","| ¡´     |","|   ¡´   |","|     ¡´ |","+-------+"},
					  {"+-------+","| ¡´   ¡´ |","|       |","| ¡´   ¡´ |","+-------+"},
					  {"+-------+","| ¡´   ¡´ |","|   ¡´   |","| ¡´   ¡´ |","+-------+"},
					  {"+-------+","| ¡´   ¡´ |","| ¡´   ¡´ |","| ¡´   ¡´ |","+-------+"} };

//dice
int twoDiceTotal;
void rollDice();

Region area[28];
Player player[2];

//player A:0 player B:1
bool playerTurn = 0;
string input;


int main()
{
	srand(time(NULL));
	ifstream in;
	in.open("map.txt");

	for (int i = 0; i < 28; i++)
		in >> area[i].name;

	for (int i = 0; i < 28; i++)
		in >> area[i].buyPrice;

	in.close();
	area[0].playerHere[0] = 1; area[0].playerHere[1] = 1;
	//beginAnime();

	while (1)
	{
	turnBegin:
		system("CLS");
		drawMap();
		status();
		cout << "Player " << (playerTurn == 0 ? "A" : "B") << " turn" << endl;
		cout << "(choose to roll the dice or check the cards)" << endl;
		cout << "1.Roll the dice" << endl << "2.Check the cards" << endl << "Enter 1 or 2:";
	input1:
		cin >> input;

		if (input == "1")
		{
			//continue
		}
		else if (input == "2")
		{
			//print the cards
		}
		else
		{
			cout << "Wrong input, enter again:";
			goto input1;
		}

		rollDice();
		cout << twoDiceTotal << endl;
		cout << "(check the dice)" << endl << "Enter any word to move : ";
		cin >> input;
		walk(playerTurn, twoDiceTotal);
		cout << "Player " << (playerTurn == 0 ? "A" : "B") << " turn" << endl;
		cout << "(Trigger the event or check the cards)" << endl;
		cout << "1.Trigger the event" << endl << "2.Check the cards" << endl << "Enter 1 or 2:";
	input2:
		cin >> input;
		//trigger the event or check the cards
		if (area[player[playerTurn].position].name == "Start")
		{
			cout << "You get some money as reward\nYou get 1000 dollars\n";
			player[playerTurn].money += 1000;
			cout << "Enter any word to continue:";
			cin >> input;
		}
		else if (area[player[playerTurn].position].name == "Chance")
		{
			chance();
		}
		else if (area[player[playerTurn].position].name == "Fate")
		{
			fate();
		}
		else if (area[player[playerTurn].position].name == "Shop")
		{
			cout << "Shop" << endl;
			cout << "Enter any word to continue:";
			cin >> input;
		}
		else if (area[player[playerTurn].position].name == "Hospital")
		{
			cout << "Hospital" << endl;
			cout << "Enter any word to continue:";
			cin >> input;
		}
		else
		{
			house();
		}

		playerTurn = !playerTurn;
	}
}

void delay(int ms)
{
	startTime = clock();

	do
	{
		endTime = clock();
	} while (endTime - startTime < ms);
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

	for (int i = 0; i <= 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << endl;
		}

		for (int j = 0; j < 45; j++)
			cout << " ";

		setTextColor(color[i]);
		cout << "  /\\_/\\         ";
		resetColor();
		cout << i * 10 << "%" << endl;

		for (int j = 0; j < 45; j++)
			cout << " ";

		setTextColor(color[i]);
		cout << "=( ¡P£s¡P )=";
		resetColor();
		cout << "       [";
		setTextColor(32);

		for (int j = 0; j < i; j++)
		{
			cout << "#";
		}

		setTextColor(31);
		for (int j = 10 - i; j > 0; j--)
		{
			cout << "_";
		}

		resetColor();
		cout << "]" << endl;

		for (int j = 0; j < 45; j++)
			cout << " ";

		setTextColor(color[i]);
		cout << " / > < \\" << endl;
		resetColor();
		startTime = clock();
		delay(500);
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
	else if (area[num].name == "Shop")
		setTextAndBackgroundColor(30, 46);
	else if (area[num].name == "Hospital")
		setTextColor(41);
	else
		resetColor();

	cout << num << " " << area[num].name;

	resetColor();

	for (int i = length; i < 19; i++)
	{
		cout << " ";
	}

	cout << "|";
}

void playerInRegion(int num)
{
	if (num < 10)
	{
		for (int i = 0; i < 3; i++)
			cout << " ";
	}
	else
	{
		for (int i = 0; i < 4; i++)
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
		for (int i = 0; i < 10; i++)
			cout << " ";
	}
	else
	{
		for (int i = 0; i < 9; i++)
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
			cout << "   Level " << area[num].level << "         ";
		}
		else
		{
			cout << "    Level " << area[num].level << "        ";
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

	cout << "|"; regionName(0); regionName(1); regionName(2); regionName(3); regionName(4); regionName(5); regionName(6); regionName(7); cout << endl;
	cout << "|"; playerInRegion(0); playerInRegion(1); playerInRegion(2); playerInRegion(3); playerInRegion(4); playerInRegion(5); playerInRegion(6); playerInRegion(7); cout << endl;
	cout << "|"; blank(); regionLevel(1); blank(); regionLevel(3); blank(); regionLevel(5); regionLevel(6); regionLevel(7); cout << endl;

	drawEdge();

	cout << "|"; regionName(27); blank(); blank(); blank(); blank(); blank(); blank(); regionName(8); cout << endl;
	cout << "|"; playerInRegion(27); blank(); blank(); blank(); blank(); blank(); blank(); playerInRegion(8); cout << endl;
	cout << "|"; regionLevel(27); blank(); blank(); blank(); blank(); blank(); blank(); regionLevel(8); cout << endl;

	drawEdge();

	cout << "|"; regionName(26); blank(); blank(); blank(); blank(); blank(); blank(); regionName(9); cout << endl;
	cout << "|"; playerInRegion(26); blank(); blank(); blank(); blank(); blank(); blank(); playerInRegion(9); cout << endl;
	cout << "|"; regionLevel(26); blank(); blank(); blank(); blank(); blank(); blank(); regionLevel(9); cout << endl;

	drawEdge();

	cout << "|"; regionName(25); blank(); blank(); blank(); blank(); blank(); blank(); regionName(10); cout << endl;
	cout << "|"; playerInRegion(25); blank(); blank(); blank(); blank(); blank(); blank(); playerInRegion(10); cout << endl;
	cout << "|"; regionLevel(25); blank(); blank(); blank(); blank(); blank(); blank(); blank(); cout << endl;

	drawEdge();

	cout << "|"; regionName(24); blank(); blank(); blank(); blank(); blank(); blank(); regionName(11); cout << endl;
	cout << "|"; playerInRegion(24); blank(); blank(); blank(); blank(); blank(); blank(); playerInRegion(11); cout << endl;
	cout << "|"; blank(); blank(); blank(); blank(); blank(); blank(); blank(); regionLevel(11); cout << endl;

	drawEdge();

	cout << "|"; regionName(23); blank(); blank(); blank(); blank(); blank(); blank(); regionName(12); cout << endl;
	cout << "|"; playerInRegion(23); blank(); blank(); blank(); blank(); blank(); blank(); playerInRegion(12); cout << endl;
	cout << "|"; regionLevel(23); blank(); blank(); blank(); blank(); blank(); blank(); regionLevel(12); cout << endl;

	drawEdge();

	cout << "|"; regionName(22); blank(); blank(); blank(); blank(); blank(); blank(); regionName(13); cout << endl;
	cout << "|"; playerInRegion(22); blank(); blank(); blank(); blank();; blank(); blank(); playerInRegion(13); cout << endl;
	cout << "|"; regionLevel(22); blank(); blank(); blank(); blank();; blank(); blank(); regionLevel(13); cout << endl;

	drawEdge();

	cout << "|"; regionName(21); regionName(20); regionName(19); regionName(18); regionName(17); regionName(16); regionName(15); regionName(14); cout << endl;
	cout << "|"; playerInRegion(21); playerInRegion(20); playerInRegion(19); playerInRegion(18); playerInRegion(17); playerInRegion(16); playerInRegion(15); playerInRegion(14); cout << endl;
	cout << "|"; regionLevel(21); regionLevel(20); regionLevel(19); regionLevel(18); regionLevel(17); blank(); blank(); regionLevel(14); cout << endl;

	drawEdge();
	cout << endl;
}

int lengthOfNumber(int num)
{
	int count = 0;

	if (num == 0)
		return 1;

	while (num != 0)
	{
		num /= 10;
		count++;
	}

	return count;
}

void statusEdge()
{
	cout << "+---------------+----------+----------------------------------------------------+-----------------------------------------------------------+" << endl;
}

void playerStatus(int who)
{
	int count = player[who].house.size() * 2;
	cout << "| "; setTextColor(who + 31); cout << (who == 0 ? "[A]" : "[B]"); resetColor(); cout << " Player" << who + 1 << "   | ";
	cout << player[who].money;

	for (int i = lengthOfNumber(player[who].money); i < 9; i++)
		cout << " ";

	cout << "| ";//51

	for (int i = 0; i < player[who].house.size(); i++)
	{
		if (player[who].house[i] >= 10)
			count++;

		cout << player[who].house[i] << " ";
	}

	for (int i = count; i < 51; i++)
		cout << " ";

	cout << "| ";
	cout << "(Unfinished)";
	cout << "                                              ";
	cout << "|" << endl;
}

void status()
{
	statusEdge();
	cout << "| Player's name | Assets   | Property                                           | Cards                                                     |" << endl;
	statusEdge();

	playerStatus(0);
	playerStatus(1);

	cout << "| "; setTextColor(33); cout << "[C]"; resetColor();
	cout << " Player3   |DoNotExist| Player3 is used to check format                    | This line will be deleted after status() is completed     |" << endl;

	statusEdge();

	cout << endl;
}

void rollDice()
{

	int first = rand() % 6;
	int second = rand() % 6;

	for (int i = 0; i < 5; i++)
	{
		cout << dice[first][i] << "  " << dice[second][i] << endl;
	}

	twoDiceTotal = first + second + 2;
}

void walk(bool who, int count)
{
	for (int i = count; i > 0; i--)
	{
		area[player[who].position].playerHere[who] = 0;
		player[who].position = (player[who].position + 1) % 28;
		area[player[who].position].playerHere[who] = 1;
		system("CLS");
		drawMap();
		startTime = clock();

		delay(150);
	}

	status();
}

void shootDragonDoor()
{
	system("CLS");

	int card1, card2, card3, change, guess, stake;
	int stakelist[4] = { 500,1000,1500,2000 };
	string num[14] = { "0","A","2","3","4","5","6","7","8","9","10","J","Q","K" };
	card1 = rand() % 13 + 1;
	card2 = rand() % 13 + 1;
	card3 = rand() % 13 + 1;

	if (card1 > card2)
	{
		change = card1;
		card1 = card2;
		card2 = change;
	}

	cout << "Stake : 1. 500 dollars\n        2. 1000 dollars\n        3. 1500 dollars\n        4. 2000 dollars" << endl;
	cout << "Enter 1~4 :";
stakeSDD:
	cin >> stake;

	if (stake >= 1 && stake <= 4)
	{
		stake = stakelist[stake - 1];
	}
	else
	{
		cout << "Wrong input, enter again:";
		goto stakeSDD;
	}

	cout << "\nthe 1st card : " << num[card1];
	cout << "\nthe 2nd card : " << num[card2] << endl << endl;

	if (card1 == card2)
	{
		cout << "Guess if the next card is larger or smaller" << endl;
		cout << "1:larger\n2:smaller\nEnter 1 or 2 : ";
	reEnterGuess1:
		cin >> guess;

		if (guess == 1)
		{
			cout << "The next card is " << num[card3] << endl;

			if (card1 < card3)
			{
				cout << "You win" << endl;
				player[playerTurn].money += stake;
			}
			else if (card1 == card3)
			{
				goto skittles1;
			}
			else
			{
				cout << "You lose" << endl;
				player[playerTurn].money -= stake;
			}
		}
		else if (guess == 2)
		{
			cout << "The next card is " << num[card3] << endl;

			if (card1 < card3)
			{
				cout << "You lose" << endl;
				player[playerTurn].money -= stake;
			}
			else if (card1 == card3)
			{
				goto skittles1;
			}
			else
			{
				cout << "You win" << endl;
				player[playerTurn].money += stake;
			}
		}
		else
		{
			cout << "Wrong input, enter again:";
			goto reEnterGuess1;
		skittles1:
			cout << "Skittles, you lose stake * 3" << endl;
			player[playerTurn].money -= stake * 3;
		}
	}
	else
	{
		cout << "Guess if the next card is in or out if range" << endl;
		cout << "1:in\n2:out\nEnter 1 or 2 : ";
	reEnterGuess2:
		cin >> guess;

		if (guess == 1)
		{
			cout << "The next card is " << num[card3] << endl;

			if (card1 < card3 && card3 < card2)
			{
				cout << "You win" << endl;
				player[playerTurn].money += stake;
			}
			else if (card1 == card3 || card2 == card3)
			{
				goto skittles2;
			}
			else
			{
				cout << "You lose" << endl;
				player[playerTurn].money -= stake;
			}
		}
		else if (guess == 2)
		{
			cout << "\nThe next card is " << num[card3] << endl;

			if (card1 < card3 && card3 < card2)
			{
				cout << "You lose" << endl;
				player[playerTurn].money -= stake;
			}
			else if (card1 == card3 || card2 == card3)
			{
				goto skittles2;
			}
			else
			{
				cout << "You win" << endl;
				player[playerTurn].money += stake;
			}
		}
		else
		{
			cout << "Wrong input, enter again:";
			goto reEnterGuess2;
		skittles2:
			cout << "Skittles, you lose stake * 2" << endl;
			player[playerTurn].money -= stake * 2;
		}
	}

	cout << endl << "Enter any word to continue:";
	cin >> input;
}

void horse()
{
	system("CLS");

	int end = 0, stake;
	int stakelist[4] = { 500,1000,1500,2000 };
	int horse[4] = { 1,1,1,1 };
	int color[4] = { 31,33,32,36 };
	int horseNumber;

	cout << "Stake : 1. 500 dollars\n        2. 1000 dollars\n        3. 1500 dollars\n        4. 2000 dollars" << endl;
	cout << "Enter 1~4 :";
stakeHorse:
	cin >> stake;

	if (stake >= 1 && stake <= 4)
	{
		stake = stakelist[stake - 1];
	}
	else
	{
		cout << "Wrong input, enter again:";
		goto stakeHorse;
	}

	cout << endl << "Choose the horse from 1~4 : ";
chooseHorseNumber:
	cin >> horseNumber;

	if (horseNumber < 1 || horseNumber>4)
	{
		cout << "Wrong input, choose again : ";
		goto chooseHorseNumber;
	}

	horseNumber--;
	system("CLS");

	do
	{
		resetColor();
		cout << "                            |" << endl;

		for (int j = 0; j < 4; j++)
		{
			setTextColor(color[j]);
			cout << "horse " << j + 1 << " ";

			for (int k = 0; k < horse[j]; k++)
				cout << "-";

			for (int k = horse[j]; k < 20; k++)
				cout << " ";

			resetColor();
			cout << "|\n                            |" << endl;
		}

		for (int i = 0; i < 4; i++)
		{
			horse[i] += rand() % 3 + 1;

			if (horse[i] >= 20)
			{
				horse[i] = 20;
				end = 1;
			}
		}

		cout << endl << endl;
		startTime = clock();
		delay(500);
		system("CLS");
	} while (end != 1);

	cout << "                            |" << endl;

	for (int j = 0; j < 4; j++)
	{
		setTextColor(color[j]);
		cout << "horse " << j + 1 << " ";

		for (int k = 0; k < horse[j]; k++)
			cout << "-";

		for (int k = horse[j]; k < 20; k++)
			cout << " ";

		resetColor();
		cout << "|\n                            |" << endl;
	}

	startTime = clock();
	delay(500);
	resetColor();

	if (horse[horseNumber] == 20)
	{
		player[playerTurn].money += stake;
		cout << "\nyou win";
	}
	else
	{
		player[playerTurn].money -= stake;
		cout << "\nyou lose";
	}

	cout << "\n\nEnter any word to continue:";
	cin >> input;
}

void chance()
{
	int random = rand() % 2;

	if (random == 0)
	{
		random = (rand() % 4 + 1) * 500;
		player[playerTurn].money += random;
		cout << "It rains cats and dogs ... and money?" << endl;
		cout << "You get " << random << " dollars" << endl;
		cout << "Enter any word to continue:";
		cin >> input;
	}
	else
	{
		random = rand() % 2;

		if (random == 0)
		{
			cout << "Your friend invites you to play shoot dragon door" << endl;
			cout << "Enter any word to continue:";
			cin >> input;
			shootDragonDoor();
		}
		else
		{
			cout << "You decide to gamble on the horses" << endl;
			cout << "Enter any word to continue:";
			cin >> input;
			horse();
		}
	}
}

void fate()
{
	int random = rand() % 1;

	if (random == 0)
	{
		random = (rand() % 8 - 2) * 1000;
		player[playerTurn].money += random;

		if (random > 0)
		{
			cout << "You robbed the bank and got some money" << endl;
			cout << "You get " << random << " dollars" << endl;
		}
		else if (random == 0)
		{
			cout << "You work for 30 hours everyday and 10 days per week" << endl;
			cout << "But your boss forgot to paid you this month" << endl;
			cout << "Nothing happened" << endl;
		}
		else
		{
			cout << "You robbed the bank and got caught by the police" << endl;
			cout << "You lose " << -random << " dollars" << endl;
		}
	}

	cout << "Enter any word to continue:";
	cin >> input;
}

void house()
{
	if (area[player[playerTurn].position].level == 0)
	{
		cout << "buyPrices: " << area[player[playerTurn].position].buyPrice << endl;
		cout << "(choose to buy the house or pass)" << endl;
		cout << "1.buy the house" << endl << "2.pass" << endl << "Enter 1 or 2:";
	buyOrNotInput:
		cin >> input;

		if (input == "1")
		{
			if (player[playerTurn].money >= area[player[playerTurn].position].buyPrice)
			{
				area[player[playerTurn].position].owner = playerTurn;
				area[player[playerTurn].position].level = 1;
				player[playerTurn].money -= area[player[playerTurn].position].buyPrice;
				player[playerTurn].house.push_back(player[playerTurn].position);
				sort(player[playerTurn].house.begin(), player[playerTurn].house.end());
				cout << "buying sucessful" << endl;
				cout << "remain money: " << player[playerTurn].money << endl;
				cout << "Enter any word to continue:";
				cin >> input;
			}
			else
			{
				cout << "Not enough money to buy" << endl;
				cout << "Enter any word to continue:";
				cin >> input;
				goto buyOrNotInput;
			}
		}
		else if (input == "2")
		{
			return;
		}
		else
		{
			cout << "Wrong input, enter again:";
			goto buyOrNotInput;
		}
	}
	else
	{
		if (area[player[playerTurn].position].owner == playerTurn)
		{
			switch (area[player[playerTurn].position].level)
			{
			case 1:
				cout << "upgradePrices: " << area[player[playerTurn].position].buyPrice / 2 << endl;
				cout << "sellPrices: " << area[player[playerTurn].position].buyPrice * 1 << endl;
				cout << "(choose to upgrade the house,sell the house or pass)" << endl;
				cout << "1.buy the house" << endl << "2.sell the house" << endl << "3.pass" << endl << "Enter 1, 2 or 3:";
			upgradeOrSellInput1:
				cin >> input;

				if (input == "1")
				{
					if (player[playerTurn].money >= area[player[playerTurn].position].buyPrice / 2)
					{
						area[player[playerTurn].position].level = 2;
						player[playerTurn].money -= area[player[playerTurn].position].buyPrice / 2;
						cout << "upgrading sucessful" << endl;
						cout << "remain money: " << player[playerTurn].money << endl;
						cout << "Enter any word to continue:";
						cin >> input;
					}
					else
					{
						cout << "Not enough money to upgrade" << endl;
						cout << "Enter any word to continue:";
						cin >> input;
						goto upgradeOrSellInput1;
					}
				}
				else if (input == "2")
				{
					area[player[playerTurn].position].owner = 2;
					area[player[playerTurn].position].level = 0;
					player[playerTurn].money += area[player[playerTurn].position].buyPrice * 1;

					for (int i = 0; i < player[playerTurn].house.size(); i++)
					{
						if (player[playerTurn].house[i] == player[playerTurn].position)
						{
							player[playerTurn].house.erase(player[playerTurn].house.begin() + i);
							break;
						}
					}

				}
				else if (input == "3")
				{
					return;
				}
				else
				{
					cout << "Wrong input, enter again:";
					goto upgradeOrSellInput1;
				}
				break;
			case 2:
				cout << "upgradePrices: " << area[player[playerTurn].position].buyPrice << endl;
				cout << "sellPrices: " << area[player[playerTurn].position].buyPrice * 2 << endl;
				cout << "(choose to upgrade the house,sell the house or pass)" << endl;
				cout << "1.buy the house" << endl << "2.sell the house" << endl << "3.pass" << endl << "Enter 1, 2 or 3:";
			upgradeOrSellInput2:
				cin >> input;

				if (input == "1")
				{
					if (player[playerTurn].money >= area[player[playerTurn].position].buyPrice)
					{
						area[player[playerTurn].position].level = 3;
						player[playerTurn].money -= area[player[playerTurn].position].buyPrice;
						cout << "upgrading sucessful" << endl;
						cout << "remain money: " << player[playerTurn].money << endl;
						cout << "Enter any word to continue:";
						cin >> input;
					}
					else
					{
						cout << "Not enough money to upgrade" << endl;
						cout << "Enter any word to continue:";
						cin >> input;
						goto upgradeOrSellInput2;
					}
				}
				else if (input == "2")
				{
					area[player[playerTurn].position].owner = 2;
					area[player[playerTurn].position].level = 0;
					player[playerTurn].money += area[player[playerTurn].position].buyPrice * 2;
					for (int i = 0; i < player[playerTurn].house.size(); i++)
					{
						if (player[playerTurn].house[i] == player[playerTurn].position)
						{
							player[playerTurn].house.erase(player[playerTurn].house.begin() + i);
							break;
						}
					}

				}
				else if (input == "3")
				{
					return;
				}
				else
				{
					cout << "Wrong input, enter again:";
					goto upgradeOrSellInput1;
				}
				break;
			case 3:
				cout << "The highest level you can't upgrade" << endl;
				cout << "sellPrices: " << area[player[playerTurn].position].buyPrice * 3 << endl;
				cout << "(choose to sell the house or pass)" << endl;
				cout << "1.sell the house" << endl << "2.pass" << endl << "Enter 1 or 2:";
			upgradeOrSellInput3:
				cin >> input;

				if (input == "1")
				{
					area[player[playerTurn].position].owner = 2;
					area[player[playerTurn].position].level = 0;
					player[playerTurn].money += area[player[playerTurn].position].buyPrice * 3;
					for (int i = 0; i < player[playerTurn].house.size(); i++)
					{
						if (player[playerTurn].house[i] == player[playerTurn].position)
						{
							player[playerTurn].house.erase(player[playerTurn].house.begin() + i);
							break;
						}
					}
				}
				else if (input == "2")
				{
					return;
				}
				else
				{
					cout << "Wrong input, enter again:";
					goto upgradeOrSellInput3;
				}
				break;
			default:
				assert(0);
				break;
			}
		}
		else
		{
			cout << "You should pay the toll" << endl << "toll: " << area[player[playerTurn].position].buyPrice * area[player[playerTurn].position].level / 10 << endl;
			player[playerTurn].money -= area[player[playerTurn].position].buyPrice * area[player[playerTurn].position].level / 10;
			cout << "remain money: " << player[playerTurn].money << endl;
			cout << "Enter any word to continue:";
			cin >> input;
		}
	}
}
