#ifndef HEAD_03DISPLAY_H_INCLUDED
#define HEAD_03DISPLAY_H_INCLUDED
/*
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
*/

void displayKorongHeader(int initspace){
    char tiles[5]={'a','b','c','d','e'} ;
    string spaces ;
    for(int i=0;i<initspace;i++){
        spaces+=" " ;
    }
    for(int i=0;i<initspace;i++){cout << " " ;}
    for(int i=0;i<5;i++) { cout << tiles[i] << spaces ;}
    cout << endl ;
}

void displayHeader(int initspace){
    char tiles[6]={'a','b','c','d','e','k'} ;
    string spaces ;
    for(int i=0;i<initspace;i++){
        spaces+=" " ;
    }
    for(int i=0;i<6;i++) { cout << tiles[i] << spaces ;}
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
    cout << "Asztal :" ;
    for(int i=0;i<6;i++){
        cout <<"\t" << *(g->p_tiles_on_table+i) ;
    }
}

void displayTiles(int n,int* p_tiles, int initspaces){
    string spaces, spaces_long ;
    for(int i=0;i<initspaces;i++){
        spaces+=" " ;
    }
    for(int i=0;i<initspaces-1;i++){
        spaces_long+=" " ;
    }
    for(int i=0;i<n;i++){
        if(p_tiles[i]<10){
            cout << p_tiles[i] << spaces ;
        }
        else {
            cout << p_tiles[i] << spaces_long ;
        }
    }
    cout << endl ;
}

void displayAll(Game* g){
    cout << "tiles            " ;
    displayHeader(4);
    cout << endl ;
    cout << "tiles in zsak :  " ;
    displayTiles(5,g->p_tiles_in_zsak,4);
    cout << "tiles on table:  " ;
    displayTiles(6,g->p_tiles_on_table,4);
    cout << "dropped tiles :  ";
    displayTiles(5,g->p_tiles_dropped,4);
    cout << "===========================================\n" ;
    cout << "tiles on korongs:" << endl ;
    displayKorongHeader(4);
    for(int i=0;i<g->nrKorongs;i++){
        cout << i+1 << "   " ;
        displayTiles(5,(g->p_Korongs+i)->tiles_on_korong,4);
    }
    cout << "===========================================\n" ;
}

void display2Dint(int** p, int size_p){
    for(int i=0;i<size_p;i++){
        for(int j=0;j<i;j++){
            cout << p[i][j] << " " ;
        }
        cout << endl ;
    }
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
            cout << p[i][j] << "  " ;
        }
        cout << endl ;
    }
}

void displayPlayer(Player* p){
    cout << p->name << " tablaja:\n" ;
    string header="1 2 3 4 5     Pontok:" ;
    for (int i=0;i<21;i++){cout << header[i] ;}
    cout << p->points ;
    cout << endl ;

    for(int i=0;i<5;i++){
        for(int jf=0;jf<5;jf++){
            cout << p->p_table->fal[i][jf] << " " ;
        }
        cout << " " << i+1 << "  " ;
        int jm=0 ;
        do{
            cout << p->p_table->mintasor[i][jm] << " " ;
            jm++;
        }while(jm<=i);
        cout << endl ;
    }
    cout << endl ;
    displayXDfal(p->p_table->tiles_on_padlo,1,7) ;
    int points[7]={-1,-1,-2,-2,-2,-3,-3};
    for(int i=0;i<7;i++){cout << points[i] << " " ;}
    cout << endl ;
}

void displayResults(int nrPlayer,Results* r){
    cout << "Table of results:\n" ;
    cout << "nr" << "\t" << "pts" << "\t" << "rows" << "\t" << "rank\n" ;
    for(int i=0;i<nrPlayer;i++){
        cout << r->nr[i] << "\t" << r->pts[i] << "\t" << r->cntfullrows[i] << "\t" << r->rankp[i] << endl ;
    }
}

#endif // HEAD_03DISPLAY_H_INCLUDED
