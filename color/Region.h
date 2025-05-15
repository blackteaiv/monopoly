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
	int level = 0;
	//nobody:0    playerA:1    playerB:2
	int owner = 0;
};