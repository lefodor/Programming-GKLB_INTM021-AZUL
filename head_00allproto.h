#ifndef HEAD_00ALLPROTO_H_INCLUDED
#define HEAD_00ALLPROTO_H_INCLUDED

/// head_0xother.h - test functions, not used in final version
void setKorongs(Game*);
void setMintasor(Game*, Player*);
void setAsztal(Game*);
void setFal(Player*);
void testAll(Game*, Player*, int);

/// head_01prog.h - functions called from main - game commanding functions
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

/// head_02init.h - functions to initialize & destruct objects
/// a.k.a. constructors/destructors of some sort
Player* createPlayerList(int);
Korong* createKorongs(int,int&);
char** init2Dmintasor(int);
char** initXDfal(int,int,char);
void initTable(Table*);
void deleteTable(Table*);
void initPlayer(Player*);
void initKorong(Korong*, Game*,int);
void initGame(int&, Game*);
void deleteGame(Game*);
//int* loadTiles(int[], int);
int* loadTilesConst(int, int);
Results initResults(int,Player*);
void deleteResults(Results*);
void deleteAll(int,Game*,Player*);

/// head_03display.h - functions to visualise objects
void displayKorongHeader(int);
void displayHeader(int);
void displayKorong(Game*);
void displayTiles(int,int*,int);
void displayAll(Game*);
void display2Dint(int**, int);
void display2Dmintasor(char**, int);
void displayXDfal(char**, int,int);
void displayPlayer(Player*);
void displayResults(int,Results*);

/// head_04userinput.h - functions to get and validate user inputs
int chooseKorong(int);
char chooseColour();
string getLine() ;
int getInteger() ;
int getInteger2() ;
void getChoice(int&, char&, int&, int);
void getChoice(int&, char&, int);
void getChoiceFal(int,int&);
bool validatePlayerName(string);
bool validateChoice2(Game*,char, int );
bool validateChoice(Game*,Korong*,Table*, char,int, int);
bool validateChoiceFal(Table*, int, int,bool&,bool&);

#endif // HEAD_00ALLPROTO_H_INCLUDED
