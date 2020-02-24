#include <iostream>
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

/// functions
int* drawX(int n, int interval){
    int* nr = new int[n] ;
    for(int i=0;i<n;i++){
        nr[i]=rand()%interval;
    }
    return nr ;
}

int drawX1(int interval){
    int nr ;
    nr=rand()%interval;
    return nr ;
}

char drawCH_test(int* tile_cnt,int& test){
    int tile_sum=0;
    for(int i=0;i<5;i++){
        tile_sum+=tile_cnt[i];
    }
    int* n =drawX(1,tile_sum);

    cout << *n << " " ;

    bool valueOver=false ;
    int j=0 ;
    int tile_cumsum=0 ;
    while(!valueOver){
        tile_cumsum+=tile_cnt[j];
        valueOver=(*n<tile_cumsum);
        j++;
    }

    test=tile_cumsum ;

    /// decrease number of tiles in zsak
    tile_cnt[j-1]-=1;

    /// return character based on j
    switch(j){
    case 1: return 'a'; break ;
    case 2: return 'b'; break ;
    case 3: return 'c'; break ;
    case 4: return 'd'; break ;
    case 5: return 'e'; break ;
    default: return 'f' ;
    } ;
}

char drawCH(int* tile_cnt){
    int tile_sum=0;
    for(int i=0;i<5;i++){
        tile_sum+=tile_cnt[i];
    }
    int* n =drawX(1,tile_sum);

    //cout << *n << " " ;

    bool valueOver=false ;
    int j=0 ;
    int tile_cumsum=0 ;
    while(!valueOver){
        tile_cumsum+=tile_cnt[j];
        valueOver=(*n<tile_cumsum);
        j++;
    }

    //test=tile_cumsum ;

    /// decrease number of tiles in zsak
    tile_cnt[j-1]-=1;

    /// return character based on j
    switch(j){
    case 1: return 'a'; break ;
    case 2: return 'b'; break ;
    case 3: return 'c'; break ;
    case 4: return 'd'; break ;
    case 5: return 'e'; break ;
    default: return 'f' ;
    } ;
}

Korong* nrKorongForPlayers(int nrPlayer,int &nrKorongs){
    int nrKorong ;
    switch(nrPlayer){
    case 2: nrKorong=5;break;
    case 3: nrKorong=7;break;
    case 4: nrKorong=9;break;
    default: nrKorong=5;
    }
    nrKorongs=nrKorong ;
    Korong* p_Korong=new Korong[nrKorong] ;
    //cout << p_Korong << endl ;
    //cout << p_Korong+1 << endl ;
    //cout << p_Korong+2 << endl ;
    return p_Korong ;
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

void initKorong(Korong* p_korong, int* p_tiles_in_zsak){
    for(int i=0;i<5;i++){ p_korong->tiles_on_korong[i] = 0 ;}
    int j;
    for (int i=0;i<4;i++){
        switch(drawCH(p_tiles_in_zsak)){
        case 'a':j=0 ;break ;
        case 'b':j=1 ;break ;
        case 'c':j=2 ;break ;
        case 'd':j=3 ;break ;
        case 'e':j=4 ;break ;
        default: j=5 ;break ;
        }
        p_korong->tiles_on_korong[j]+=1 ;
    }
    for (int j=0;j<5;j++){ cout << p_korong->tiles_on_korong[j] << " " ;}
    cout << endl ;
}

Game initGame(int nrPlayer, int* p_tiles_in_zsak){
    Game newgame ;
    newgame.p_Korongs=nrKorongForPlayers(nrPlayer,newgame.nrKorongs) ;
    for(int i=0;i<newgame.nrKorongs;i++){
        initKorong(newgame.p_Korongs+i,p_tiles_in_zsak);
    }
    newgame.p_tiles_dropped=loadTilesConst(0,5);
    newgame.p_tiles_in_zsak=p_tiles_in_zsak;
    newgame.p_tiles_on_table=loadTilesConst(0,6);

    return newgame;
}

int main()
{
    srand(time(NULL)); /// initialize only once in an application!!!

    int tiles_in_zsak[5]={20,20,20,20,20} ; ///content of zsak
    int* p_tiles_in_zsak=tiles_in_zsak; ///pointer to zsak to modify with function
    int nrPlayer=3; /// number of players

    cout << "test random number generator" << endl ;
    int* nr = drawX(5,100) ;
    for(int i=0;i<5;i++){
        cout << nr[i] << " " ;
    }
    cout << endl ;

    cout << "feladat#1" << endl ;
    //int test ;
    //int t=0 ;
    /*
    while(t<10){
        cout << drawCH_test(p_tile_cnt,test)
             << " " << test << " tiles: "  ;
        for(int i=0;i<5;i++){
            cout << tile_cnt[i] << " " ;
        }
        cout << endl ;
        t++ ;
    }


    while(t<10){
        cout << drawCH(p_tiles_in_zsak)
             << " " << " tiles: "  ;
        for(int i=0;i<5;i++){
            cout << tiles_in_zsak[i] << " " ;
        }
        cout << endl ;
        t++ ;
    }

    cout << "feladat#2"<<endl ;
    int nrPlayer=3,nrKorongs;
    Korong* p_Korongs=nrKorongForPlayers(nrPlayer, nrKorongs) ;

    for(int i=0;i<nrPlayer;i++){
        cout << p_Korongs+i << " " ;
    }

    cout << endl ;
    cout << nrKorongs << endl ;
    */

    cout << "feladat#3"<<endl ;
    cout << "content of zsak: " ;
    for(int i=0;i<5;i++){
        cout << *(p_tiles_in_zsak+i) << " " ;
    }
    cout << endl ;
    Game ngame=initGame(nrPlayer,p_tiles_in_zsak) ;
    cout << "content of zsak after initialization: " ;
    for(int i=0;i<5;i++){
        cout << *(p_tiles_in_zsak+i) << " " ;
    }
    cout << endl ;
    cout << "nr of korongs: " << ngame.nrKorongs << endl ;


    /*
    cout << "dropped: " << endl ;
    for(int i=0;i<5;i++) {
        cout << ngame.p_tiles_dropped+i << " : " << *(ngame.p_tiles_dropped+i) << endl ;
    }
    cout << "zsak: " << endl ;
    for(int i=0;i<5;i++) {
        cout << ngame.p_tiles_in_zsak+i << " : " << *(ngame.p_tiles_in_zsak+i) << endl ;
    }

    cout << "table: " << endl ;
    for(int i=0;i<6;i++) {
        cout << ngame.p_tiles_on_table+i << " : " << *(ngame.p_tiles_on_table+i) << endl ;
    }
    */

    /// cleanup
    delete nr/*,p_Korongs*/;

    return 0;
}
