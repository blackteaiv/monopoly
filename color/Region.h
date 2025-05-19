#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

#pragma once
class Region
{
public:
	string name = "Meow";
	//if playerA is here, playerHere[0] = 1;if playerB is here, playerHere[1] = 1
	bool playerHere[2] = { 0,0 };
	//level 0 no house level 1 1house 2 upgrate1 3 upgrate2
	int level = 0;
	//playerA:0    playerB:1    nobody:2
	int owner = 2;
	//house
	int buyPrice = 0;

};