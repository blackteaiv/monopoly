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
#include <cctype>
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
void hospital();
void shopItem();
void shop();
//card
void rocketCard(int deleteIndex);
void barrierCard(int deleteIndex);
void controllDiceCard(int deleteIndex);
void destroyCard(int deleteIndex);
void fateCard(int deleteIndex);
int changeStringToNumber(string str);
void selectCard();
//command
bool move();
void get();
void give();
void card();
void list();
void minigame();

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
	for (int i = 0; i < 2; i++)
	{
		player[i].card.push_back("B");//barrier
		player[i].card.push_back("Di");//dice
		player[i].card.push_back("De");//destroy
		player[i].card.push_back("F");//fate
		player[i].card.push_back("R");//rocket
	}
	//beginAnime();

	while (1)
	{
	turnBegin:
		system("CLS");
		drawMap();
		status();
		cout << "Player " << (playerTurn == 0 ? "A" : "B") << " turn" << endl;

		if (player[playerTurn].injured == 0)
		{
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
				selectCard();
				goto turnBegin;
			}
			else if (input == "/move")
			{
				if (move())
				{
					goto triggerBegin;
				}
				else
				{
					goto turnBegin;
				}
			}
			else if (input == "/get")
			{
				get();
				goto turnBegin;
			}
			else if (input == "/give")
			{
				give();
				goto turnBegin;
			}
			else if (input == "/card")
			{
				card();
				goto turnBegin;
			}/*
			else if (input == "/gamestate")
			{

			}
			else if (input == "/info")
			{

			}*/
			else if (input == "/refresh")
			{
				goto turnBegin;
			}
			else if (input == "/list" || input == "/help")
			{
				list();
				goto turnBegin;
			}
			else if (input == "/minigame")
			{
				minigame();
				goto turnBegin;
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
		}
		else
		{
			cout << "You are injured" << endl;
		}

	triggerBegin:
		system("CLS");
		drawMap();
		status();
		if (area[player[playerTurn].position].barrier == 1)
			cout << "You are blocked by barrier" << endl;
		cout << "Player " << (playerTurn == 0 ? "A" : "B") << " turn" << endl;
		cout << "(Trigger the event or check the cards)" << endl;
		cout << "1.Trigger the event" << endl << "2.Check the cards" << endl << "Enter 1 or 2:";
	input2:
		cin >> input;
		//trigger the event or check the cards
		if (input == "1")
		{
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
				shop();
			}
			else if (area[player[playerTurn].position].name == "Hospital")
			{
				cout << endl;
				hospital();
			}
			else
			{
				house();
			}

			area[player[playerTurn].position].barrier = 0;
			playerTurn = !playerTurn;
		}
		else if (input == "2")
		{
			selectCard();
			goto triggerBegin;
		}
		else if (input == "/move")
		{
			move();
			goto triggerBegin;
		}
		else if (input == "/get")
		{
			get();
			goto triggerBegin;
		}
		else if (input == "/give")
		{
			give();
			goto triggerBegin;
		}
		else if (input == "/card")
		{
			card();
			goto triggerBegin;
		}/*
		else if (input == "/gamestate")
		{

		}
		else if (input == "/info")
		{

		}*/
		else if (input == "/refresh")
		{
			goto triggerBegin;
		}
		else if (input == "/list" || input == "/help")
		{
			list();
			goto triggerBegin;
		}
		else if (input == "/minigame")
		{
			minigame();
			goto triggerBegin;
		}
		else
		{
			cout << "Wrong input, enter again:";
			goto input2;
		}
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
	//    lighter:+60
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
		for (int i = 0; i < 2; i++)
			cout << " ";
	}
	else
	{
		for (int i = 0; i < 3; i++)
			cout << " ";
	}

	setTextColor(96);
	cout << (area[num].barrier == 1 ? "#" : " ");

	if (area[num].playerHere[0] == 1)
	{
		setTextColor(31);
		cout << "[A]";

		if (area[num].playerHere[1] == 1)
		{
			setTextColor(32);
			cout << "[B]";
		}
		else
			cout << "   ";
	}
	else if (area[num].playerHere[1] == 1)
	{
		setTextColor(32);
		cout << "[B]   ";
	}
	else
		cout << "      ";

	resetColor();

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
	int count1 = player[who].house.size() * 2, count2 = player[who].card.size() * 2;
	cout << "| "; setTextColor(who + 31); cout << (who == 0 ? "[A]" : "[B]"); resetColor(); cout << " Player" << who + 1 << "   | ";
	cout << player[who].money;

	for (int i = lengthOfNumber(player[who].money); i < 9; i++)
		cout << " ";

	cout << "| ";//51

	for (int i = 0; i < player[who].house.size(); i++)
	{
		if (player[who].house[i] >= 10)
			count1++;

		cout << player[who].house[i] << " ";
	}

	for (int i = count1; i < 51; i++)
		cout << " ";

	cout << "| ";

	for (int i = 0; i < player[who].card.size(); i++)
	{
		if (player[who].card[i].length() > 1)
			count2++;

		cout << player[who].card[i] << " ";
	}

	for (int i = count2; i < 58; i++)
		cout << " ";

	cout << "|" << endl;
}

void status()
{
	statusEdge();
	cout << "| Player's name | Assets   | Property                                           | Cards                                                     |" << endl;
	statusEdge();

	playerStatus(0);
	playerStatus(1);

	cout << "| "; setTextColor(93); cout << "[C]"; resetColor();
	cout << " Player3   |DoNotExist| Player3 is used to check format                    |                                                           |" << endl;
	cout << "| "; setTextColor(94); cout << "[D]"; resetColor();
	cout << " Player4   |DoNotExist| Player4 is used to check format                    |                                                           |" << endl;

	statusEdge();

	cout << endl;
}

void rollDice()
{
	int first = rand() % 6;
	int second = rand() % 6;

	if (player[playerTurn].nextdice != 0)
	{
		if (player[playerTurn].nextdice % 2 == 0)
		{
			first = player[playerTurn].nextdice / 2 - 1;
			second = player[playerTurn].nextdice / 2 - 1;
		}
		else
		{
			first = player[playerTurn].nextdice / 2;
			second = player[playerTurn].nextdice / 2 - 1;
		}

		player[playerTurn].nextdice = 0;
	}

	for (int i = 0; i < 5; i++)
	{
		cout << dice[first][i] << "  " << dice[second][i] << endl;
	}

	twoDiceTotal = first + second + 2;
}

void walk(bool who, int count)
{
	if (area[player[who].position].barrier == 0)
	{
		for (int i = count; i > 0; i--)
		{
			if (area[player[who].position].barrier == 1)
				break;

			area[player[who].position].playerHere[who] = 0;
			player[who].position = (player[who].position + 1) % 28;
			area[player[who].position].playerHere[who] = 1;
			system("CLS");
			drawMap();
			delay(150);
		}
	}
	else
	{
		system("CLS");
		drawMap();

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
			player[!playerTurn].money += area[player[playerTurn].position].buyPrice * area[player[playerTurn].position].level / 10;
			cout << "remain money: " << player[playerTurn].money << endl;
			cout << "Enter any word to continue:";
			cin >> input;
		}
	}
}

void hospital()
{
	if (player[playerTurn].injured == 0)
	{
		cout << "You want to sleep in the hospital" << endl;
		cout << "But you get ejected from the hospital" << endl;
		cout << "Enter any word to continue:";
		cin >> input;
	}
	else
	{
		cout << "You still have " << player[playerTurn].injured << " turn(s) to leave" << endl;
		cout << "Do you want to paid some money to leave earlier by chance?\n";
		cout << "1.Yes\n2.No\nEnter 1 or 2:";
	inputHospital:
		cin >> input;

		if (input == "1")
		{
			player[playerTurn].money -= 5000;
			int random = rand() % 6;
			cout << "You can leave the hospital if the number on the dice is larger than 4\n";
			cout << "Enter any word to roll the dice:";
			cin >> input;
			cout << endl;

			for (int i = 0; i < 5; i++)
				cout << dice[random][i] << endl;

			cout << endl;

			if (random + 1 > 4)
			{
				cout << "Fortunately, you're recovered, you're free!" << endl;
				player[playerTurn].injured = 0;
			}
			else
			{
				cout << "Unfortunately, the doctor wasn't in the mood for curing you\n";
				cout << "Nothing happens" << endl;
				player[playerTurn].injured--;
			}
		}
		else if (input == "2")
		{
			cout << "You decide to stay since the meals here are free" << endl;
			player[playerTurn].injured--;
		}
		else
		{
			cout << "Wrong input, enter again:";
			goto inputHospital;
		}

		cout << "Enter any word to continue:";
		cin >> input;
	}
}

void shopItem()
{
	cout << "+-----+--------------+--------------------------------------------+\n";
	cout << "| No. | Card Name    | Effect                                     |\n";
	cout << "+-----+--------------+--------------------------------------------+\n";
	cout << "|  1  | Barrier Card | Place a barrier on a tile to block players |\n";
	cout << "|  2  | Dice Card    | Choose the number you roll on the dice     |\n";
	cout << "|  3  | Destroy Card | Destroy another player's property          |\n";
	cout << "|  4  | Fate Card    | Trigger a fate event                       |\n";
	cout << "|  5  | Rocket Card  | Send a player to the hospital for 3 turns  |\n";
	cout << "+-----+--------------+--------------------------------------------+\n";
	cout << endl;
}

void shop()
{
	shopItem();
	cout << "Enter the number of the card you want to buy (or enter 0 to exit): ";
buyInput:
	cin >> input;

	if (input == "1")
	{
		if (player[playerTurn].money >= 1500)
		{
			player[playerTurn].money -= 1500;
			player[playerTurn].card.push_back("B");
		}
		else
		{
			cout << " You don't have enough money to buy [Barrier Card]. Your balance: $200, but the card costs $1500." << endl;
			cout << "Enter any word to continue:";
			cin >> input;
		}
	}
	else if (input == "2")
	{
		if (player[playerTurn].money >= 2000)
		{
			player[playerTurn].money -= 2000;
			player[playerTurn].card.push_back("Di");
		}
		else
		{
			cout << " You don't have enough money to buy [Barrier Card]. Your balance: $200, but the card costs $1500." << endl;
			cout << "Enter any word to continue:";
			cin >> input;
		}
	}
	else if (input == "3")
	{
		if (player[playerTurn].money >= 2500)
		{
			player[playerTurn].money -= 2500;
			player[playerTurn].card.push_back("De");
		}
		else
		{
			cout << " You don't have enough money to buy [Barrier Card]. Your balance: $200, but the card costs $1500." << endl;
			cout << "Enter any word to continue:";
			cin >> input;
		}
	}
	else if (input == "4")
	{
		if (player[playerTurn].money >= 1000)
		{
			player[playerTurn].money -= 1000;
			player[playerTurn].card.push_back("F");
		}
		else
		{
			cout << " You don't have enough money to buy [Barrier Card]. Your balance: $200, but the card costs $1500." << endl;
			cout << "Enter any word to continue:";
			cin >> input;
		}
	}
	else if (input == "5")
	{
		if (player[playerTurn].money >= 3000)
		{
			player[playerTurn].money -= 3000;
			player[playerTurn].card.push_back("R");
		}
		else
		{
			cout << " You don't have enough money to buy [Barrier Card]. Your balance: $200, but the card costs $1500." << endl;
			cout << "Enter any word to continue:";
			cin >> input;
		}

	}
	else if (input == "0")
	{
		return;
	}
	else
	{
		cout << "Wrong input, enter again:";
		goto buyInput;
	}
}

void rocketCard(int deleteIndex)
{
	area[player[!playerTurn].position].playerHere[!playerTurn] = 0;
	player[!playerTurn].position = 15;
	area[15].playerHere[!playerTurn] = 1;
	player[!playerTurn].injured += 3;
	player[playerTurn].card.erase(player[playerTurn].card.begin() + deleteIndex);
}

void barrierCard(int deleteIndex)
{
	int pos;
	cout << "Choose a place to place barrier (0 ~ 27):";

	while (cin >> pos)
	{
		if (pos < 0 || pos >27)
			cout << "Wrong input, enter again:";
		else if (area[pos].barrier == 1)
			cout << "There is already barrier placed here, enter again:";
		else
			break;
	}

	area[pos].barrier = 1;
	player[playerTurn].card.erase(player[playerTurn].card.begin() + deleteIndex);
}

void controllDiceCard(int deleteIndex)
{

	if (player[playerTurn].nextdice != 0)
	{
		cout << "You chose the dice already!Do you want to change it?(enter y or n)";
	changeInput:
		cin >> input;

		if (input == "y")
		{
			cout << "Enter the dice you want to choose(2 ~ 12): " << endl;
		nextdiceInput1:
			cin >> input;

			if (input == "2" || input == "3" || input == "4" || input == "5" || input == "6" || input == "7" || input == "8" || input == "9" || input == "10" || input == "11" || input == "12")
			{
				int nextdice = 0;

				if (input.size() == 1)
				{
					nextdice = input[0] - '0';
				}
				else	if (input.size() == 2)
				{
					nextdice = input[1] - '0' + 10;
				}
				else
				{
					assert(0);
				}

				player[playerTurn].nextdice = nextdice;
			}
			else
			{
				cout << "Wrong input, enter again:";
				goto nextdiceInput1;
			}
		}
		else if (input == "n")
		{
			return;
		}
		else
		{
			cout << "Wrong input, enter again:";
			goto changeInput;
		}
	}
	else
	{
		cout << "Enter the dice you want to choose(2 ~ 12): " << endl;
	nextdiceInput2:
		cin >> input;

		if (input == "2" || input == "3" || input == "4" || input == "5" || input == "6" || input == "7" || input == "8" || input == "9" || input == "10" || input == "11" || input == "12")
		{
			int nextdice = 0;

			if (input.size() == 1)
			{
				nextdice = input[0] - '0';
			}
			else	if (input.size() == 2)
			{
				nextdice = input[1] - '0' + 10;
			}
			else
			{
				assert(0);
			}

			player[playerTurn].nextdice = nextdice;
		}
		else
		{
			cout << "Wrong input, enter again:";
			goto nextdiceInput2;
		}
	}

	player[playerTurn].card.erase(player[playerTurn].card.begin() + deleteIndex);
}

void destroyCard(int deleteIndex)
{
	cout << "Enter the player you want to destroy" << endl;

	if (playerTurn == 0)
	{
		cout << "1.player2" << endl;
	}
	else
	{
		cout << "1.player1" << endl;
	}
playerinput:
	cin >> input;

	if (input == "1")
	{
		if (player[!playerTurn].house.size() == 0)
		{
			cout << "No house exit" << endl;
			cout << "Enter any word to continue:";
			cin >> input;
			return;
		}

		cout << "Enter the house you want to destroy one level" << endl;

		for (int i = 0; i < player[!playerTurn].house.size(); i++)
		{
			cout << i + 1 << "." << area[player[!playerTurn].house[i]].name << endl;
		}
	houseinput:
		cin >> input;

		int destroyhouse = 0;

		if (input.size() == 1)
		{
			if (isdigit(input[0]))
			{
				destroyhouse = input[0] - '0';
			}
			else
			{
				cout << "Wrong input, enter again:";
				goto houseinput;
			}
		}
		else if (input.size() == 2)
		{

			if (isdigit(input[0]) && isdigit(input[1]))
			{
				destroyhouse = input[1] - '0' + (input[0] - '0') * 10;
			}
			else
			{
				cout << "Wrong input, enter again:";
				goto houseinput;
			}
		}
		else
		{
			cout << "Wrong input, enter again:";
			goto houseinput;
		}

		if (destroyhouse >= 1 && destroyhouse <= player[!playerTurn].house.size())
		{
			area[player[!playerTurn].house[destroyhouse - 1]].level -= 1;

			if (area[player[!playerTurn].house[destroyhouse - 1]].level == 0)
			{
				area[player[!playerTurn].house[destroyhouse - 1]].owner = 2;

				player[!playerTurn].house.erase(player[!playerTurn].house.begin() + destroyhouse - 1);
			}
		}
		else
		{
			cout << "Wrong input, enter again:";
			goto houseinput;
		}
	}
	else
	{
		cout << "Wrong input, enter again:";
		goto playerinput;
	}

	player[playerTurn].card.erase(player[playerTurn].card.begin() + deleteIndex);
}

void fateCard(int deleteIndex)
{
	fate();
	player[playerTurn].card.erase(player[playerTurn].card.begin() + deleteIndex);
}

int changeStringToNumber(string str)
{
	int num = 0;

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			num = num * 10 + str[i] - '0';
		}
		else
		{
			num = -1;
			break;
		}
	}

	return num;
}

void selectCard()
{
	int cardSize = player[playerTurn].card.size(), read;
	string card[5] = { {"  | Barrier Card | Place a barrier on a tile to block players |\n"},
					   {"  | Dice Card    | Choose the number you roll on the dice     |\n"},
					   {"  | Destroy Card | Destroy another player's property          |\n"},
					   {"  | Fate Card    | Trigger a fate event                       |\n"},
					   {"  | Rocket Card  | Send a player to the hospital for 3 turns  |\n"} };

	if (cardSize == 0)
	{
		cout << "no card exist" << endl;
		cout << "Enter any word to continue:";
		cin >> input;
		return;
	}

	cout << "+-----+--------------+--------------------------------------------+\n";
	cout << "| No. | Card Name    | Effect                                     |\n";
	cout << "+-----+--------------+--------------------------------------------+\n";

	for (int i = 0; i < cardSize; i++)
	{
		cout << "|  " << i + 1;

		if (player[playerTurn].card[i] == "B")
			cout << card[0];
		else if (player[playerTurn].card[i] == "Di")
			cout << card[1];
		else if (player[playerTurn].card[i] == "De")
			cout << card[2];
		else if (player[playerTurn].card[i] == "F")
			cout << card[3];
		else if (player[playerTurn].card[i] == "R")
			cout << card[4];
		else
			cout << "Error\n";
	}

	cout << "+-----+--------------+--------------------------------------------+\n\n";
	cout << "Enter the number of the card to use (or enter 0 to exit): ";
cardInput:
	cin >> input;
	read = changeStringToNumber(input);

	if (read == 0)
	{
		return;
	}

	if (read > cardSize || read == -1)
	{
		cout << "Wrong input, enter again:";
		goto cardInput;
	}

	if (player[playerTurn].card[read - 1] == "B")
	{
		barrierCard(read - 1);
	}
	else if (player[playerTurn].card[read - 1] == "Di")
	{
		controllDiceCard(read - 1);
	}
	else if (player[playerTurn].card[read - 1] == "De")
	{
		destroyCard(read - 1);
	}
	else if (player[playerTurn].card[read - 1] == "F")
	{
		fateCard(read - 1);
	}
	else if (player[playerTurn].card[read - 1] == "R")
	{
		rocketCard(read - 1);
	}
}


bool move()
{
	char seeinput = cin.peek();

	if (seeinput == ' ')
	{
		cin.ignore();
		cin >> input;

		if (input == "to")
		{
			seeinput = cin.peek();

			if (seeinput == ' ')
			{
				cin.ignore();
				cin >> input;

				for (int i = 0; i < 28; i++)
				{
					if (input == area[i].name)
					{
						i -= player[playerTurn].position;


						if (i < 0)
						{
							i += 28;
						}

						walk(playerTurn, i);
						return true;
					}
				}


				if (input.size() < 3)
				{
					if (input.size() == 1)
					{
						if (!isdigit(input[0]))
						{
							cout << "Error: Invalid location. Please enter a valid number (0-27) or a named location (USA, START, etc.)." << endl;
							cout << "Invalid command.Type / list to see available commands." << endl;
							cout << "Enter any word to continue:";
							cin >> input;
							return false;
						}

						int location = input[0] - '0';

						location -= player[playerTurn].position;

						if (location < 0)
						{
							location += 28;
						}

						walk(playerTurn, location);
						return true;
					}
					else if (input.size() == 2)
					{
						if (!isdigit(input[0]) || !isdigit(input[1]))
						{
							cout << "Error: Invalid location. Please enter a valid number (0-27) or a named location (USA, START, etc.)." << endl;
							cout << "Invalid command.Type / list to see available commands." << endl;
							cout << "Enter any word to continue:";
							cin >> input;
							return false;
						}
						int location = (input[0] - '0') * 10 + input[1] - '0';

						if (location > 27)
						{
							cout << "Error: Invalid location. Please enter a valid number (0-27) or a named location (USA, START, etc.)." << endl;
							cout << "Invalid command.Type / list to see available commands." << endl;
							cout << "Enter any word to continue:";
							cin >> input;
							return false;
						}

						location -= player[playerTurn].position;

						if (location < 0)
						{
							location += 28;
						}

						walk(playerTurn, location);
						return true;
					}
					else
					{
						cout << "Error: Invalid location. Please enter a valid number (0-27) or a named location (USA, START, etc.)." << endl;
						cout << "Invalid command.Type / list to see available commands." << endl;
						cout << "Enter any word to continue:";
						cin >> input;
						return false;
					}
				}
				else
				{
					cout << "Error: Invalid location. Please enter a valid number (0-27) or a named location (USA, START, etc.)." << endl;
					cout << "Invalid command.Type / list to see available commands." << endl;
					cout << "Enter any word to continue:";
					cin >> input;
					return false;
				}
			}
			else
			{
				cout << "Error: Invalid location. Please enter a valid number (0-27) or a named location (USA, START, etc.)." << endl;
				cout << "Invalid command.Type / list to see available commands." << endl;
				cout << "Enter any word to continue:";
				cin >> input;
				return false;
			}
		}
		else
		{
			for (int i = 0; i < 28; i++)
			{
				if (input == area[i].name)
				{
					i -= player[playerTurn].position;


					if (i < 0)
					{
						i += 28;
					}

					walk(playerTurn, i);
					return true;
				}
			}


			if (input.size() < 3)
			{
				if (input.size() == 1)
				{
					if (!isdigit(input[0]))
					{
						cout << "Error: Invalid location. Please enter a valid number (0-27) or a named location (USA, START, etc.)." << endl;
						cout << "Invalid command.Type / list to see available commands." << endl;
						cout << "Enter any word to continue:";
						cin >> input;
					}

					int location = input[0] - '0';

					location -= player[playerTurn].position;

					if (location < 0)
					{
						location += 28;
					}

					walk(playerTurn, location);
					return true;
				}
				else if (input.size() == 2)
				{
					if (!isdigit(input[0]) || !isdigit(input[1]))
					{
						cout << "Error: Invalid location. Please enter a valid number (0-27) or a named location (USA, START, etc.)." << endl;
						cout << "Invalid command.Type / list to see available commands." << endl;
						cout << "Enter any word to continue:";
						cin >> input;
						return false;
					}

					int location = (input[0] - '0') * 10 + input[1] - '0';

					if (location > 27)
					{
						cout << "Error: Invalid location. Please enter a valid number (0-27) or a named location (USA, START, etc.)." << endl;
						cout << "Invalid command.Type / list to see available commands." << endl;
						cout << "Enter any word to continue:";
						cin >> input;
						return false;
					}

					location -= player[playerTurn].position;

					if (location < 0)
					{
						location += 28;
					}

					walk(playerTurn, location);
					return true;
				}
				else
				{
					cout << "Error: Invalid location. Please enter a valid number (0-27) or a named location (USA, START, etc.)." << endl;
					cout << "Invalid command.Type / list to see available commands." << endl;
					cout << "Enter any word to continue:";
					cin >> input;
					return false;
				}
			}
			else
			{
				cout << "Error: Invalid location. Please enter a valid number (0-27) or a named location (USA, START, etc.)." << endl;
				cout << "Invalid command.Type / list to see available commands." << endl;
				cout << "Enter any word to continue:";
				cin >> input;
				return false;
			}
		}
	}
	else
	{
		cout << "Usage: / move[location] or /move to[0 - 27]" << endl;
		cout << "Invalid command.Type / list to see available commands." << endl;
		cout << "Enter any word to continue:";
		cin >> input;
		return false;
	}
}

void get()
{
	char seeinput = cin.peek();

	if (seeinput == ' ')
	{
		cin.ignore();
		cin >> input;

		if (input == "Player1")
		{
			seeinput = cin.peek();

			if (seeinput == ' ')
			{
				cin.ignore();
				cin >> input;

				int money = changeStringToNumber(input);

				if (money == -1)
				{
					cout << "Error: Invalid amount. Please enter a valid number." << endl;
					cout << "Invalid command.Type / list to see available commands." << endl;
					cout << "Enter any word to continue:";
					cin >> input;
				}
				else
				{
					player[0].money += money;
				}
			}
			else
			{
				cout << "Error: Invalid location. Please enter a valid number (0-27) or a named location (USA, START, etc.)." << endl;
				cout << "Invalid command.Type / list to see available commands." << endl;
				cout << "Enter any word to continue:";
				cin >> input;
			}
		}
		else if (input == "Player2")
		{
			if (seeinput == ' ')
			{
				cin.ignore();
				cin >> input;

				int money = changeStringToNumber(input);

				if (money == -1)
				{
					cout << "Error: Invalid amount. Please enter a valid number." << endl;
					cout << "Invalid command.Type / list to see available commands." << endl;
					cout << "Enter any word to continue:";
					cin >> input;
				}
				else
				{
					player[1].money += money;
				}
			}
			else
			{
				cout << "Error: Invalid location. Please enter a valid number (0-27) or a named location (USA, START, etc.)." << endl;
				cout << "Invalid command.Type / list to see available commands." << endl;
				cout << "Enter any word to continue:";
				cin >> input;
			}
		}
		else
		{
			int money = changeStringToNumber(input);

			if (money == -1)
			{
				cout << "Error: Invalid amount. Please enter a valid number." << endl;
				cout << "Invalid command.Type / list to see available commands." << endl;
				cout << "Enter any word to continue:";
				cin >> input;
			}
			else
			{
				player[playerTurn].money += money;
			}
		}
	}
	else
	{
		cout << "Usage: / get[playerName][money] or /get[money]" << endl;
		cout << "Invalid command.Type / list to see available commands." << endl;
		cout << "Enter any word to continue:";
		cin >> input;
	}
}

void give()
{
	char seeinput = cin.peek();

	if (seeinput == ' ')
	{
		cin.ignore();
		cin >> input;

		if (input == "Player1")
		{
			seeinput = cin.peek();

			if (seeinput == ' ')
			{
				cin.ignore();
				cin >> input;

				int money = changeStringToNumber(input);

				if (money == -1)
				{
					cout << "Error: Invalid amount. Please enter a valid number." << endl;
					cout << "Invalid command.Type / list to see available commands." << endl;
					cout << "Enter any word to continue:";
					cin >> input;
				}
				else
				{
					if (player[playerTurn].money < money)
					{
						cout << "Not enough money" << endl;
						cout << "Enter any word to continue:";
						cin >> input;
					}
					else
					{
						player[playerTurn].money -= money;
						player[0].money += money;

					}
				}
			}
			else
			{
				cout << "Usage: / give[playerName][money]" << endl;
				cout << "Invalid command.Type / list to see available commands." << endl;
				cout << "Enter any word to continue:";
				cin >> input;
			}
		}
		else if (input == "Player2")
		{
			if (seeinput == ' ')
			{
				cin.ignore();
				cin >> input;

				int money = changeStringToNumber(input);

				if (money == -1)
				{
					cout << "Error: Invalid amount. Please enter a valid number." << endl;
					cout << "Invalid command.Type / list to see available commands." << endl;
					cout << "Enter any word to continue:";
					cin >> input;
				}
				else
				{
					if (player[playerTurn].money < money)
					{
						cout << "Not enough money" << endl;
						cout << "Enter any word to continue:";
						cin >> input;
					}
					else
					{
						player[playerTurn].money -= money;
						player[1].money += money;

					}
				}
			}
			else
			{
				cout << "Usage: / give[playerName][money]" << endl;
				cout << "Invalid command.Type / list to see available commands." << endl;
				cout << "Enter any word to continue:";
				cin >> input;
			}
		}
		else
		{
			cout << "Usage: / give[playerName][money]" << endl;
			cout << "Invalid command.Type / list to see available commands." << endl;
			cout << "Enter any word to continue:";
			cin >> input;
		}
	}
	else
	{
		cout << "Usage: / give[playerName][money]" << endl;
		cout << "Invalid command.Type / list to see available commands." << endl;
		cout << "Enter any word to continue:";
		cin >> input;
	}
}


void card()
{
	char seeinput = cin.peek();

	if (seeinput == ' ')
	{
		cin.ignore();
		cin >> input;

		if (input == "Barrier")
		{
			seeinput = cin.peek();

			if (seeinput == ' ')
			{
				cin.ignore();
				cin >> input;

				if (input == "Card")
				{
					player[playerTurn].card.push_back("B");
				}
				else
				{
					cout << "Available cards name :" << endl << "1. Barrier Card" << endl << "2. Dice Card" << endl << "3. Destroy Card" << endl << "4. Fate Card" << endl << "5. Rocket Card" << endl;
					cout << "Invalid command.Type / list to see available commands." << endl;
					cout << "Enter any word to continue:";
					cin >> input;
				}
			}
			else
			{
				cout << "Available cards name :" << endl << "1. Barrier Card" << endl << "2. Dice Card" << endl << "3. Destroy Card" << endl << "4. Fate Card" << endl << "5. Rocket Card" << endl;
				cout << "Invalid command.Type / list to see available commands." << endl;
				cout << "Enter any word to continue:";
				cin >> input;
			}
		}
		else if (input == "Dice")
		{
			seeinput = cin.peek();

			if (seeinput == ' ')
			{
				cin.ignore();
				cin >> input;

				if (input == "Card")
				{
					player[playerTurn].card.push_back("Di");
				}
				else
				{
					cout << "Available cards name :" << endl << "1. Barrier Card" << endl << "2. Dice Card" << endl << "3. Destroy Card" << endl << "4. Fate Card" << endl << "5. Rocket Card" << endl;
					cout << "Invalid command.Type / list to see available commands." << endl;
					cout << "Enter any word to continue:";
					cin >> input;
				}
			}
			else
			{
				cout << "Available cards name :" << endl << "1. Barrier Card" << endl << "2. Dice Card" << endl << "3. Destroy Card" << endl << "4. Fate Card" << endl << "5. Rocket Card" << endl;
				cout << "Invalid command.Type / list to see available commands." << endl;
				cout << "Enter any word to continue:";
				cin >> input;
			}
		}
		else if (input == "Destroy")
		{
			seeinput = cin.peek();

			if (seeinput == ' ')
			{
				cin.ignore();
				cin >> input;

				if (input == "Card")
				{
					player[playerTurn].card.push_back("De");
				}
				else
				{
					cout << "Available cards name :" << endl << "1. Barrier Card" << endl << "2. Dice Card" << endl << "3. Destroy Card" << endl << "4. Fate Card" << endl << "5. Rocket Card" << endl;
					cout << "Invalid command.Type / list to see available commands." << endl;
					cout << "Enter any word to continue:";
					cin >> input;
				}
			}
			else
			{
				cout << "Available cards name :" << endl << "1. Barrier Card" << endl << "2. Dice Card" << endl << "3. Destroy Card" << endl << "4. Fate Card" << endl << "5. Rocket Card" << endl;
				cout << "Invalid command.Type / list to see available commands." << endl;
				cout << "Enter any word to continue:";
				cin >> input;
			}
		}
		else if (input == "Fate")
		{
			seeinput = cin.peek();

			if (seeinput == ' ')
			{
				cin.ignore();
				cin >> input;

				if (input == "Card")
				{
					player[playerTurn].card.push_back("F");
				}
				else
				{
					cout << "Available cards name :" << endl << "1. Barrier Card" << endl << "2. Dice Card" << endl << "3. Destroy Card" << endl << "4. Fate Card" << endl << "5. Rocket Card" << endl;
					cout << "Invalid command.Type / list to see available commands." << endl;
					cout << "Enter any word to continue:";
					cin >> input;
				}
			}
			else
			{
				cout << "Available cards name :" << endl << "1. Barrier Card" << endl << "2. Dice Card" << endl << "3. Destroy Card" << endl << "4. Fate Card" << endl << "5. Rocket Card" << endl;
				cout << "Invalid command.Type / list to see available commands." << endl;
				cout << "Enter any word to continue:";
				cin >> input;
			}
		}
		else if (input == "Rocket")
		{
			seeinput = cin.peek();

			if (seeinput == ' ')
			{
				cin.ignore();
				cin >> input;

				if (input == "Card")
				{
					player[playerTurn].card.push_back("R");
				}
				else
				{
					cout << "Available cards name :" << endl << "1. Barrier Card" << endl << "2. Dice Card" << endl << "3. Destroy Card" << endl << "4. Fate Card" << endl << "5. Rocket Card" << endl;
					cout << "Invalid command.Type / list to see available commands." << endl;
					cout << "Enter any word to continue:";
					cin >> input;
				}
			}
			else
			{
				cout << "Available cards name :" << endl << "1. Barrier Card" << endl << "2. Dice Card" << endl << "3. Destroy Card" << endl << "4. Fate Card" << endl << "5. Rocket Card" << endl;
				cout << "Invalid command.Type / list to see available commands." << endl;
				cout << "Enter any word to continue:";
				cin >> input;
			}
		}
		else
		{
			cout << "Available cards name :" << endl << "1. Barrier Card" << endl << "2. Dice Card" << endl << "3. Destroy Card" << endl << "4. Fate Card" << endl << "5. Rocket Card" << endl;
			cout << "Invalid command.Type / list to see available commands." << endl;
			cout << "Enter any word to continue:";
			cin >> input;
		}
	}
	else
	{
		cout << "Usage : / card[card_name]" << endl;
		cout << "Invalid command.Type / list to see available commands." << endl;
		cout << "Enter any word to continue:";
		cin >> input;
	}
}

void list()
{
	char seeinput = cin.peek();

	if (seeinput == ' ')
	{
		cin.ignore();
		cin >> input;

		if (input == "-a")
		{
			cout << "¯D«Ç¨Ó°µ";
			cout << "Enter any word to continue:";
			cin >> input;
		}
		else
		{
			cout << "/card - Retrieve a specific card by name." << endl << "/gamestate - Change the game state." << endl << "/get - Get money from the system." << endl << "/give - Give money to another player." << endl << "/info - Display information about all players." << endl << "/minigame - Enter a minigame." << endl << "/move - Move to a specific position on the board." << endl << "/refresh - Refresh the game board." << endl;
			cout << "Enter any word to continue:";
			cin >> input;
		}
	}
	else
	{
		cout << "/card - Retrieve a specific card by name." << endl << "/gamestate - Change the game state." << endl << "/get - Get money from the system." << endl << "/give - Give money to another player." << endl << "/info - Display information about all players." << endl << "/minigame - Enter a minigame." << endl << "/move - Move to a specific position on the board." << endl << "/refresh - Refresh the game board." << endl;
		cout << "Enter any word to continue:";
		cin >> input;
	}
}

void minigame()
{
	cout << "Please choose (1~3):" << endl;
chooseMnigame:
	cin >> input;

	if (input == "1")
	{
		shootDragonDoor();
	}
	else if (input == "2")
	{
		horse();
	}
	else if (input == "3")
	{
		return;
	}
	else
	{
		cout << "Please enter 1-3:";
		goto chooseMnigame;
	}
}
