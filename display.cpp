#include<iostream>
#include<string>
#include "init.h"
#include "display.h"

void displayKorongHeader(int initspace){
    char tiles[5]={'a','b','c','d','e'} ;
    std::string spaces ;
    for(int i=0;i<initspace;i++){
        spaces+=" " ;
    }
    for(int i=0;i<initspace;i++){std::cout << " " ;}
    for(int i=0;i<5;i++) { std::cout << tiles[i] << spaces ;}
    std::cout << std::endl ;
}

void displayHeader(int initspace){
    char tiles[6]={'a','b','c','d','e','k'} ;
    std::string spaces ;
    for(int i=0;i<initspace;i++){
        spaces+=" " ;
    }
    for(int i=0;i<6;i++) { std::cout << tiles[i] << spaces ;}
}

void displayKorong(Game* g){
    displayKorongHeader(16);
    for(int i=0;i<g->nrKorongs;i++){
        std::cout << "Korong " << i+1 << ":" ;
        for(int j=0;j<5;j++){
            std::cout << "\t" << (g->p_Korongs+i)->tiles_on_korong[j] ;
        }
        std::cout << std::endl ;
    }
    std::cout << "Asztal :" ;
    for(int i=0;i<6;i++){
        std::cout <<"\t" << *(g->p_tiles_on_table+i) ;
    }
}

void displayTiles(int n,int* p_tiles, int initspaces){
    std::string spaces, spaces_long ;
    for(int i=0;i<initspaces;i++){
        spaces+=" " ;
    }
    for(int i=0;i<initspaces-1;i++){
        spaces_long+=" " ;
    }
    for(int i=0;i<n;i++){
        if(p_tiles[i]<10){
            std::cout << p_tiles[i] << spaces ;
        }
        else {
            std::cout << p_tiles[i] << spaces_long ;
        }
    }
    std::cout << std::endl ;
}

void displayAll(Game* g){
    std::cout << "tiles            " ;
    displayHeader(4);
    std::cout << std::endl ;
    std::cout << "tiles in zsak :  " ;
    displayTiles(5,g->p_tiles_in_zsak,4);
    std::cout << "tiles on table:  " ;
    displayTiles(6,g->p_tiles_on_table,4);
    std::cout << "dropped tiles :  ";
    displayTiles(5,g->p_tiles_dropped,4);
    std::cout << "===========================================\n" ;
    std::cout << "tiles on korongs:" << std::endl ;
    displayKorongHeader(4);
    for(int i=0;i<g->nrKorongs;i++){
        std::cout << i+1 << "   " ;
        displayTiles(5,(g->p_Korongs+i)->tiles_on_korong,4);
    }
    std::cout << "===========================================\n" ;
}

void display2Dint(int** p, int size_p){
    for(int i=0;i<size_p;i++){
        for(int j=0;j<i;j++){
            std::cout << p[i][j] << " " ;
        }
        std::cout << std::endl ;
    }
}

void display2Dmintasor(char** p, int size_p){
    for(int i=0;i<size_p;i++){
        for(int j=0;j<=i;j++){
            std::cout << p[i][j] << " " ;
        }
        std::cout << std::endl ;
    }
}

void displayXDfal(char** p, int size_row,int size_col){
    for(int i=0;i<size_row;i++){
        for(int j=0;j<size_col;j++){
            std::cout << p[i][j] << "  " ;
        }
        std::cout << std::endl ;
    }
}

void displayPlayer(Player* p){
    std::cout << p->name << " tablaja:\n" ;
    std::string header="1 2 3 4 5     Pontok:" ;
    for (int i=0;i<21;i++){std::cout << header[i] ;}
    std::cout << p->points ;
    std::cout << std::endl ;

    for(int i=0;i<5;i++){
        for(int jf=0;jf<5;jf++){
            std::cout << p->p_table->fal[i][jf] << " " ;
        }
        std::cout << " " << i+1 << "  " ;
        int jm=0 ;
        do{
            std::cout << p->p_table->mintasor[i][jm] << " " ;
            jm++;
        }while(jm<=i);
        std::cout << std::endl ;
    }
    std::cout << std::endl ;
    displayXDfal(p->p_table->tiles_on_padlo,1,7) ;
    int points[7]={-1,-1,-2,-2,-2,-3,-3};
    for(int i=0;i<7;i++){std::cout << points[i] << " " ;}
    std::cout << std::endl ;
}

void displayResults(int nrPlayer,Results* r){
    std::cout << "Table of results:\n" ;
    std::cout << "nr" << "\t" << "pts" << "\t" << "rows" << "\t" << "rank\n" ;
    for(int i=0;i<nrPlayer;i++){
        std::cout << r->nr[i] << "\t" << r->pts[i] << "\t" << r->cntfullrows[i] << "\t" << r->rankp[i] << std::endl ;
    }
}
