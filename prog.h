#pragma once

#include "init.h"

void fillZsak(Game*);
void dropAll(Game*);
void dropTilesFromArray(int*,char,int);
void dropTiles(Game*, int, char);
int  convertColourToInt(char) ;
int* drawX(int, int);
char drawCH(Game*);
bool checkEndOfRound(Game*);
bool checkEndOfGame(Player*,int);
void allocateTiles(Game*,bool&);
void chooseTiles(Game*,Player*);
void setValuesForAllocation(int&,bool&,int,int,Game*,Player*) ;
void putTilesToTable(Table*, char, int, int&, bool, int& );
void putTilesToWall(Game*, Player*);
void calcPoints(Player*,int,int);
int  countfullsor(Player*);
int  countfulloszlop(Player*);
int  countcolours5timesonwall(Player*);
void calcPointsBonus(Player*);
int  getMaxPoint(int, Player*);
int  getNrPlayerWithHighScore(int, Player*, int);
