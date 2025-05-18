#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>

using namespace std;

#pragma once
class Player
{
public:
	char name = ' ';
	int position = 0, money = 100000;
	vector <string> card;
	vector <int> house;
};