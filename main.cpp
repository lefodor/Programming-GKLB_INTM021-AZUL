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
    char* mintasor1=new char[1] ;
    char* mintasor2=new char[2] ;
    char* mintasor3=new char[3] ;
    char* mintasor4=new char[4] ;
    char* mintasor5=new char[5] ;
};

struct Padlovonal{
    int points[7]={-1,-1,-2,-2,-2,-3,-3} ;
    char** tiles_on_padlo;
};

struct Table{
    char** mintasor;
    char** fal ;
    char** tiles_on_padlo;
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

char* initCharPoint(int n){
    char* out=new char[n] ;
    for(int i=0;i<n;i++){
        out[i]='.';
    }
    return out ;
}
/*
void initPadlo(Padlovonal* pv){
    pv->tiles_on_padlo=initCharPoint(7) ;
    //pv->points={-1,-1,-2,-2,-2,-3,-3} ;
}

char* initFal(int row, int col){
    char* out=new char[row] ;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            out[i][j]='.';
        }
    }
    return out ;
}

char* initMintasor(int row, int col){
    char* out[row][col];
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(j<=i) {out[i][j]='.' ; } ;
            else {out[i][j]=' ' ;}
        }
    }
    return out;
}

char* initMintasor(int,int) ;
char* initFal(int,int) ;
*/

int** init2Dint(int p_size1){
    int** p=new int*[p_size1];
    for(int i=0;i<p_size1;i++){
        p[i] = new int[i] ;
        for(int j=0;j<i;j++){
            p[i][j] = j ;
        }
    }
    return p ;
}

char** init2Dmintasor(int p_size){
    char** p=new char*[p_size];
    for(int i=0;i<p_size;i++){
        p[i] = new char[i+1] ;
        int j=0;
        while(j<=i){
            p[i][j] = '.' ;
            //cout << "p["<<i<<"]["<<j<<"]:"<<p[i][j] << " " ;
            j++;
        }
        //cout << endl ;
    }
    return p ;
}

char** initXDfal(int size_row,int size_col){
    char** p=new char*[size_row];
    for(int i=0;i<size_row;i++){
        p[i] = new char[i+1] ;
        int j=0;
        while(j<size_col){
            p[i][j] = '.' ;
            //cout << "p["<<i<<"]["<<j<<"]:"<<p[i][j] << " " ;
            j++;
        }
        //cout << endl ;
    }
    return p ;
}

void initTable(Table* t){
    t->mintasor=init2Dmintasor(5) ;
    t->fal=initXDfal(5,5);
    t->tiles_on_padlo=initXDfal(1,7);
}

void initPlayer(Player* p){
    p->points=0;
    initTable(p->table);
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

void display2Dint(int** p, int size_p){
    for(int i=0;i<size_p;i++){
        for(int j=0;j<i;j++){
            cout << p[i][j] << " " ;
        }
        cout << endl ;
    }
}

void delete2Dint(int** p, int size_p){
    for(int i=0;i<size_p;i++){
        delete []p[i] ;
    }
    delete []p ;
}

void display2Dmintasor(char** p, int size_p){
    for(int i=0;i<size_p;i++){
        for(int j=0;j<=i;j++){
            cout << p[i][j] << " " ;
        }
        cout << endl ;
    }
}

void displayXDfal(char** p, int size_row,int size_col){
    for(int i=0;i<size_row;i++){
        for(int j=0;j<size_col;j++){
            cout << p[i][j] << " " ;
        }
        cout << endl ;
    }
}

void delete2Dchar(char** p, int size_p){
    for(int i=0;i<size_p;i++){
        delete []p[i] ;
    }
    delete []p ;
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


    cout << endl ;

    int** p_rows=init2Dint(7) ;
    char** p_chars=init2Dmintasor(5) ;
    char** p_chars2=initXDfal(1,5) ;
    char** p_chars3=initXDfal(5,5) ;

    //display2Dint(p_rows,7) ;
    cout << endl ;
    display2Dmintasor(p_chars,5) ;
    cout << endl ;
    displayXDfal(p_chars2,1,5) ;
    cout << endl ;
    displayXDfal(p_chars3,5,5) ;
    cout << endl ;

    delete2Dint(p_rows,7) ;
    delete2Dchar(p_chars,5);
    delete2Dchar(p_chars2,1);
    delete2Dchar(p_chars3,5);

    //display2Dint(p_rows,7) ;

/*
    cout << endl ;
    for(int i=0;i<5;i++){
        int* t=new int[i] ;
        p_rows[i] = t[0] ;//new int[i] ;
    }
    cout << endl ;

    for(int i=0;i<5;i++){
        for(int j=0;j<i;j++){
            //p_rows[i]+j = 0;
            cout << p_rows[i]+0 << " " ;
        }
        cout << endl ;
    }
*/
    //for(int i=0;i<5;i++) cout << p_rows[i] << " " ;
    /// cleanup
    //delete nr,p_Korongs;
    //delete p_Korongs, p_Player ;

    return 0;
}
