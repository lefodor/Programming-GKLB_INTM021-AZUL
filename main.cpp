#include <iostream>
#include<stdlib.h>
#include<time.h>
//#include<cstdlib>
//#include<ctime>

#include "head_azul.h"
using namespace std;


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

char drawCH(int* tile_cnt,int& test){
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

int main()
{
    srand(time(NULL)); /// initialize only once in an application!!!

    int tile_cnt[5]={20,5,20,15,20} ; ///content of zsak
    int* p_tile_cnt=tile_cnt; ///pointer to zsak to modify with function

    cout << "test random number generator" << endl ;
    int* nr = drawX(5,100) ;
    for(int i=0;i<5;i++){
        cout << nr[i] << " " ;
    }
    cout << endl ;

    cout << "feladat#1" << endl ;
    int test ;
    int t=0 ;
    while(t<10){
        cout << drawCH(p_tile_cnt,test) << " " << test << " tiles: " ;
        for(int i=0;i<5;i++){
            cout << tile_cnt[i] << " " ;
        }
        cout << endl ;
        t++ ;
    }

    /// cleanup
    delete nr,tile_cnt ;

    return 0;
}
