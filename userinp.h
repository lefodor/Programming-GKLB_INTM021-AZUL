#pragma once

#include "init.h"

int chooseKorong(int);
char chooseColour();
std::string getLine() ;
int getInteger() ;
int getInteger2() ;
void getChoice(int&, char&, int&, int);
void getChoice(int&, char&, int);
void getChoiceFal(int,int&);
bool validatePlayerName(std::string);
bool validateChoice2(Game*,char, int );
bool validateChoice(Game*,Korong*,Table*, char,int, int);
bool validateChoiceFal(Table*, int, int,bool&,bool&);
