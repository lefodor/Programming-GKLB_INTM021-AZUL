#pragma once

/// structs
struct Korong{
    int tiles_on_korong[5] ;
    int korong_index ;
};

struct Game{
    int nrKorongs ;
    Korong* p_Korongs ;
    int* p_tiles_in_zsak ;
    int* p_tiles_on_table ;
    int* p_tiles_dropped ;
    char** pattern ;
};

struct Table{
    char** mintasor;
    char** fal ;
    char** tiles_on_padlo;
};

struct Player{
    int points ;
    std::string name ;
    bool mintasorfull=false;
    Table table ;
    Table* p_table=&table ;
};

struct Results{
    int* nr ;
    int* pts ;
    int* cntfullrows;
    int* rankp ;
};

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

