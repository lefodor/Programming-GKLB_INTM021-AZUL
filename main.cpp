#include<iostream>
#include<stdlib.h>
#include<time.h>
//#include<cstdlib>
//#include<ctime>

#include "head_azul.h"
using namespace std;

/// structs
struct Korong{
    int tiles_on_korong[5] ;
};

struct Game{
    int nrKorongs ;
    Korong* p_Korongs ;
    int* p_tiles_in_zsak ;
    int* p_tiles_on_table ;
    int* p_tiles_dropped ;
};

struct Mintasor{
    int mintasor1[1] ;
    int mintasor2[2] ;
    int mintasor3[3] ;
    int mintasor4[4] ;
    int mintasor5[5] ;
};

struct Padlovonal{
    int points[7]={-1,-1,-2,-2,-2,-3,-3} ;
    int tiles_on_padlo[7];
};

struct Table{
    Mintasor* mintasor ;
    Padlovonal* padlovonal;
    int* fal[5][5] ;
};

struct Player{
    int points ;
    Table* table ;
};

/// functions
int* drawX(int n, int interval){
    int* nr = new int[n] ;
    for(int i=0;i<n;i++){
        nr[i]=rand()%interval;
    }
    return nr ;
}
void fillZsak(Game* g){
    for(int i=0;i<5;i++){
        g->p_tiles_in_zsak[i]=g->p_tiles_dropped[i] ;
        g->p_tiles_dropped[i]=0 ;
    }
}

void dropAll(Game* g){
    for(int i=0;i<5;i++){
        g->p_tiles_dropped[i]=g->p_tiles_in_zsak[i] ;
        g->p_tiles_in_zsak[i]=0 ;
    }
}

/// feladat#5
char drawCH(Game* g){
    int tile_sum=0;
    for(int i=0;i<5;i++){
        tile_sum+=g->p_tiles_in_zsak[i];
    }

    if(tile_sum==0){
        fillZsak(g) ;
        for(int i=0;i<5;i++){
            tile_sum+=g->p_tiles_in_zsak[i];
        }
    }

    int* n =drawX(1,tile_sum);

    //cout << *n << " " ;

    bool valueOver=false ;
    int j=0 ;
    int tile_cumsum=0 ;
    while(!valueOver){
        tile_cumsum+=g->p_tiles_in_zsak[j];
        valueOver=(*n<tile_cumsum);
        j++;
    }

    //test=tile_cumsum ;

    /// decrease number of tiles in zsak
    /// tile_cnt[j-1]-=1;
    g->p_tiles_in_zsak[j-1]-=1;

    /// return character based on j
    switch(j){
    case 1: return 'a'; break ;
    case 2: return 'b'; break ;
    case 3: return 'c'; break ;
    case 4: return 'd'; break ;
    case 5: return 'e'; break ;
    default: return 'f' ;

    /// cleanup
    delete n;
    } ;
}


int* loadTiles(int tiles[], int n ){
    int* p_tiles=new int[n] ;
    for(int i=0;i<n;i++){
        p_tiles[i]=tiles[i] ;
    }
    return p_tiles ;
}

int* loadTilesConst(int c, int n ){
    int* p_tiles=new int[n] ;

    if(n!=6){
        for(int i=0;i<5;i++){
            p_tiles[i]=c ;
        }
    }
    else {
        for(int i=0;i<5;i++){
            p_tiles[i]=c ;
        }
        p_tiles[5]=1 ;
    }

    return p_tiles ;
}

Korong* createKorongs(int nrPlayer,int &nrKorongs){
    //int nrKorong ;
    switch(nrPlayer){
    case 2: nrKorongs=5;break;
    case 3: nrKorongs=7;break;
    case 4: nrKorongs=9;break;
    default: nrKorongs=5;
    }
    //nrKorongs=nrKorong ;
    Korong* p_Korong=new Korong[nrKorongs] ;
    //cout << p_Korong << endl ;
    //cout << p_Korong+1 << endl ;
    //cout << p_Korong+2 << endl ;
    return p_Korong ;
}

Player* createPlayers(int nrPlayer){
    Player* p_Player=new Player[nrPlayer] ;
    return p_Player ;
}

void initKorong(Korong* p_korong, Game* g){
    for(int i=0;i<5;i++){ p_korong->tiles_on_korong[i] = 0 ;}
    int j;
    for (int i=0;i<4;i++){
        switch(drawCH(g)){
        case 'a':j=0 ;break ;
        case 'b':j=1 ;break ;
        case 'c':j=2 ;break ;
        case 'd':j=3 ;break ;
        case 'e':j=4 ;break ;
        default: j=5 ;break ;
        }
        p_korong->tiles_on_korong[j]+=1 ;
    }
    //for (int j=0;j<5;j++){ cout << p_korong->tiles_on_korong[j] << " " ;}
    //cout << endl ;
}

void initGame(int& nrPlayer, Game* g){
    g->p_tiles_dropped=loadTilesConst(0,5);
    g->p_tiles_in_zsak=loadTilesConst(20,5);
    g->p_tiles_on_table=loadTilesConst(0,6);

    g->p_Korongs=createKorongs(nrPlayer,g->nrKorongs) ;
    for(int i=0;i<g->nrKorongs;i++){
        initKorong(g->p_Korongs+i,g);
    }
}

void initPlayer(){

}

void displayKorongHeader(int initspace){
    char tiles[5]={'a','b','c','d','e'} ;
    for(int i=0;i<initspace;i++){cout << " " ;}
    for(int i=0;i<5;i++) { cout << tiles[i] << " " ;}
    cout << endl ;
}

void displayKorong(Game* g){
    displayKorongHeader(16);
    for(int i=0;i<g->nrKorongs;i++){
        cout << "Korong " << i+1 << ":" ;
        for(int j=0;j<5;j++){
            cout << "\t" << (g->p_Korongs+i)->tiles_on_korong[j] ;
        }
        cout << endl ;
    }
//    displayKorongHeader(16);
    cout << "Asztal :" ;
    for(int i=0;i<6;i++){
        cout <<"\t" << *(g->p_tiles_on_table+i) ;
    }
}

void displayTiles(int n,int* p_tiles){
    for(int i=0;i<n;i++){
        cout << p_tiles[i] << " " ;
    }
    cout << endl ;
}

void displayAll(Game* g){
    cout << "content of zsak after initialization: " ;
    displayTiles(5,g->p_tiles_in_zsak);
    cout << "tiles on table: " ;
    displayTiles(6,g->p_tiles_on_table);
    cout << "tiles on korongs:" << endl ;
    displayKorongHeader(0);
    for(int i=0;i<g->nrKorongs;i++){
        displayTiles(5,(g->p_Korongs+i)->tiles_on_korong);
    }
}

int main()
{
    srand(time(NULL)); /// initialize only once in an application!!!

    //int tiles_in_zsak[5]={20,20,20,20,20} ; ///content of zsak
    //int* p_tiles_in_zsak=tiles_in_zsak; ///pointer to zsak to modify with function
    int nrPlayer=3; /// number of players

    Game newgame;
    Game* p_newgame=&newgame;
    initGame(nrPlayer,p_newgame) ; displayAll(p_newgame) ;

    dropAll(p_newgame) ; displayTiles(5,p_newgame->p_tiles_in_zsak);

    fillZsak(p_newgame); displayTiles(5,p_newgame->p_tiles_in_zsak);

    Player* p_Player=createPlayers(nrPlayer) ; for(int i=0;i<nrPlayer;i++){ cout << p_Player+i <<" " ; }

    /// cleanup
    //delete nr,p_Korongs;
    //delete p_Korongs, p_Player ;

    return 0;
}
