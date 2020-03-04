#ifndef HEAD_AZUL_H_INCLUDED
#define HEAD_AZUL_H_INCLUDED

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

struct Table{
    char** mintasor;
    char** fal ;
    char** tiles_on_padlo;
};

struct Player{
    int points ;
    Table table ;
    Table* p_table=&table ;
};

/// function proto
int** init2Dint(int);
char** init2Dmintasor(int);
char** initXDfal(int,int,char);
void initTable(Table*);
void initPlayer(Player*);
void initKorong(Korong*, Game*);
void initGame(int&, Game*);

Player* createPlayerList(int);
Korong* createKorongs(int ,int&) ;

int* drawX(int, int);
void fillZsak(Game*);
void dropAll(Game*);
char drawCH(Game*);
int* loadTiles(int[], int);
int* loadTilesConst(int, int);
string getLine() ;
int getInteger() ;
int chooseTiles(Game*, Player*);

void displayKorongHeader(int);
void displayKorong(Game*);
void displayTiles(int,int*);
void displayAll(Game*);
void display2Dint(int**, int);
void display2Dmintasor(char** , int);
void displayXDfal(char**, int,int);
void displayPlayer(Player*);

void delete2Dint(int**, int);
void delete2Dchar(char** p, int size_p);

/// functions
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
            p[i][j] = '-' ;
            //cout << "p["<<i<<"]["<<j<<"]:"<<p[i][j] << " " ;
            j++;
        }
        //cout << endl ;
    }
    return p ;
}

char** initXDfal(int size_row,int size_col,char c){
    char** p=new char*[size_row];
    for(int i=0;i<size_row;i++){
        p[i] = new char[i+1] ;
        int j=0;
        while(j<size_col){
            p[i][j] = c ;
            //cout << "p["<<i<<"]["<<j<<"]:"<<p[i][j] << " " ;
            j++;
        }
        //cout << endl ;
    }
    return p ;
}

void initTable(Table* t){
    t->mintasor=init2Dmintasor(5) ;
    t->fal=initXDfal(5,5,'.');
    t->tiles_on_padlo=initXDfal(1,7,'-');
}

void initPlayer(Player* p){
    p->points=0;
    initTable(p->p_table);
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

/// creates an array with pointers to objects of Player
Player* createPlayerList(int nrPlayers){
    Player* p=new Player[nrPlayers] ;
    for(int i=0;i<nrPlayers;i++){
        //cout << p+i << " " ;
        initPlayer(p+i) ;
        //if(i<nrPlayers) {p[i].nextplayer=p[i+1];}
        //else {p[i].nextplayer=nullptr ;}
    }
    //initPlayer(p_player) ;
    return p ;
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

int chooseTiles(Game* p_game, Player* p_player){
    while(true) { // Read input until user enters valid data
        cout << "Melyik korongrol valasztasz? (0-" ;
        cout << p_game->nrKorongs<<" 0:asztal): " ;
        stringstream converter;
        converter << getLine();
        /* Try reading an int, continue if we succeeded. */
        int korongvalaszt;
        if(converter >> korongvalaszt) {
            char remaining;
            if(converter >> remaining) // Something's left, input is invalid
                cout << "Nem ertelmezheto karakter: " << remaining << endl << "Probald ujra! " << endl ;
            else if(korongvalaszt>p_game->nrKorongs||korongvalaszt<0){
                cout << "Kerlek a megadott korongszamokbol valassz. ";
                cout << "Probald ujra! " << endl ;
            }
            else
                return korongvalaszt;
        }
        else {
            //cout << "Kerlek a megadott korongszamokbol valassz. ";
            string invalid_input ; invalid_input=converter.str() ;
            cout << "Nem ertelmezheto karakter: " << invalid_input << endl ;
            cout << "Probald ujra! " << endl ;
        }
    }
}

///https://www.keithschwarz.com/cs106l/fall2010/course-reader/Ch3_Streams.pdf
string getLine() {
    string result;
    getline(cin, result);
    return result;
}

int getInteger_orig() {
    while(true) { // Read input until user enters valid data
        stringstream converter;
        converter << getLine();
        /* Try reading an int, continue if we succeeded. */
        int result;
        if(converter >> result) {
            char remaining;
            if(converter >> remaining) // Something's left, input is invalid
                cout << "Unexpected character: " << remaining << endl;
            else
                return result;
        } else
        //cout << "Please enter an integer." << endl;
        cout << "Please enter an integer." << endl;
        cout << "Retry: " ;
    }
}

int getInteger() {
    while(true) { // Read input until user enters valid data
        stringstream converter;
        converter << getLine();
        /* Try reading an int, continue if we succeeded. */
        int result;
        if(converter >> result) {
            char remaining;
            if(converter >> remaining) // Something's left, input is invalid
                cout << "Nem ismert karakter: " << remaining << endl;
            else
                return result;
        } else
        cout << "Kerlek a megadott korongszamokbol valassz." << endl;
        cout << "Ujra: " ;
    }
}


void delete2Dint(int** p, int size_p){
    for(int i=0;i<size_p;i++){
        delete []p[i] ;
    }
    delete []p ;
}

void delete2Dchar(char** p, int size_p){
    for(int i=0;i<size_p;i++){
        delete []p[i] ;
    }
    delete []p ;
}


#endif // HEAD_AZUL_H_INCLUDED
