#ifndef HEAD_02INIT_H_INCLUDED
#define HEAD_02INIT_H_INCLUDED
/*
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
void deleteAll(int,Game*,Player*);
*/

/// creates an array with pointers to objects of Player
Player* createPlayerList(int nrPlayers){
    Player* p=new Player[nrPlayers] ;
    for(int i=0;i<nrPlayers;i++){
        cout << "Enter name of player#"<<i+1 <<endl ;
        initPlayer(p+i) ;
    }
    return p ;
}

Korong* createKorongs(int nrPlayer,int &nrKorongs){
    switch(nrPlayer){
    case 2: nrKorongs=5;break;
    case 3: nrKorongs=7;break;
    case 4: nrKorongs=9;break;
    default: nrKorongs=5;
    }

    Korong* p_Korong=new Korong[nrKorongs] ;
    return p_Korong ;
}

char** init2Dmintasor(int p_size){
    char** p=new char*[p_size];
    for(int i=0;i<p_size;i++){
        p[i] = new char[i+1] ;
        int j=0;
        while(j<=i){
            p[i][j] = '-' ;
            j++;
        }
    }
    return p ;
}

char** initXDfal(int size_row,int size_col,char c){
    char** p=new char*[size_row];
    for(int i=0;i<size_row;i++){
        p[i] = new char[size_col] ;
        int j=0;
        while(j<size_col){
            p[i][j] = c ;
            j++;
        }
    }
    return p ;
}

void initTable(Table* t){
    t->mintasor=init2Dmintasor(5) ;
    t->fal=initXDfal(5,5,'.');
    t->tiles_on_padlo=initXDfal(1,7,'-');
}

void deleteTable(Table* t){
    ///delete mintasor
    for(int i=0;i<5;i++){
        delete[] t->mintasor[i];
    }
    delete[] t->mintasor ;
    ///delete fal
    for(int i=0;i<5;i++){
        delete[] t->fal[i];
    }
    delete[] t->fal ;
    ///delete padlo
    for(int i=0;i<1;i++){
        delete[] t->tiles_on_padlo[i];
    }
    delete[] t->tiles_on_padlo ;
}

void initPlayer(Player* p){
    p->points=0;
    do{
        p->name = getLine() ;
    }while(!validatePlayerName(p->name)) ;
    initTable(p->p_table);
}

void initKorong(Korong* p_korong, Game* g,int index){
    p_korong->korong_index=index;
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
        if(j<5){
            p_korong->tiles_on_korong[j]+=1 ;
        }
    }
}

void initGame(int& nrPlayer, Game* g){
    g->p_tiles_dropped=loadTilesConst(0,5);
    g->p_tiles_in_zsak=loadTilesConst(20,5);
    g->p_tiles_on_table=loadTilesConst(0,6);
    g->p_Korongs=createKorongs(nrPlayer,g->nrKorongs) ;

    g->pattern=initXDfal(5,5,'.'); /// pattern not used in this implementation
    char chars[5]={'a','b','c','d','e'} ;
    int row=0;
    for(int i=4;i>=0;i--){
        for(int j=0;j<5;j++){
            int z= (i+j+1)%5 + (j)/5 ;
            g->pattern[row][j] = chars[z] ;
        }
        row++ ;
    }
}

void deleteGame(Game* g){
    delete[] g->p_Korongs ;
    delete[] g->p_tiles_dropped ;
    delete[] g->p_tiles_in_zsak ;
    delete[] g->p_tiles_on_table ;
    ///delete pattern
    for(int i=0;i<5;i++){
        delete[] g->pattern[i];
    }
    delete[] g->pattern ;
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
        p_tiles[5]=1 ; /// used to initialize kezdoko on desk
    }

    return p_tiles ;
}

Results initResults(int nrPlayer,Player* p){
    Results res ;
    res.nr=new int[nrPlayer] ;
    res.pts=new int[nrPlayer] ;
    res.cntfullrows=new int[nrPlayer];
    res.rankp=new int[nrPlayer];

    /// load result table in order of players
    for(int i=0;i<nrPlayer;i++){
        res.nr[i]=i ;
        res.pts[i]=(p+i)->points ;
        res.cntfullrows[i]=countfullsor(p+i) ;
        res.rankp[i]=0;
    }

    /// order result table first by points then by number of full rows
    /// bubblesorting - pts
    for(int i=0;i<nrPlayer-1;i++){
        for(int j=nrPlayer-1;j>i;j--){
            if(res.pts[j]>res.pts[j-1]){

                /// save temporarily
                int nr=res.nr[j-1] ; int pts=res.pts[j-1] ;
                int cntfullrows=res.cntfullrows[j-1] ;

                /// overwrite
                res.nr[j-1]=res.nr[j] ;
                res.pts[j-1]=res.pts[j] ;
                res.cntfullrows[j-1]=res.cntfullrows[j] ;

                /// replace
                res.nr[j]=nr ;
                res.pts[j]=pts;
                res.cntfullrows[j]=cntfullrows;
            }
        }
    }

    /// bubblesorting - rows
    for(int i=0;i<nrPlayer-1;i++){
        int i_pts=res.pts[i];
        int j=0 ;
        int k=0 ;
        do{ if(res.pts[i+j]==i_pts){ j++; }; k++ ; }while(i+k<nrPlayer );/// how many have same points
        if(j>1){
            for(int i2=i;i2<(i+j-1);i2++){
                for(int j2=i+j-1;j2>i2;j2--){
                    if(res.cntfullrows[j2] > res.cntfullrows[j2-1]){
                        /// save temporarily
                        int nr=res.nr[j2-1] ; int pts=res.pts[j2-1] ;
                        int cntfullrows=res.cntfullrows[j2-1] ;
                        /// overwrite
                        res.nr[j2-1]=res.nr[j2] ;
                        res.pts[j2-1]=res.pts[j2] ;
                        res.cntfullrows[j2-1]=res.cntfullrows[j2] ;
                        /// replace
                        res.nr[j2]=nr ;
                        res.pts[j2]=pts;
                        res.cntfullrows[j2]=cntfullrows;
                    }
                }
            }
        }

    }

    /// set rank
    for(int i=0;i<nrPlayer;i++){
        if(i==0){res.rankp[i]=1 ;}
        else if(res.pts[i-1]>res.pts[i]) {res.rankp[i]=res.rankp[i-1]+1;}
        else if(res.cntfullrows[i-1]>res.cntfullrows[i]) {res.rankp[i]=res.rankp[i-1]+1;}
        else {res.rankp[i]=res.rankp[i-1] ;}
    }

    return res ;
}

void deleteResults(Results* r){
    delete[] r->nr;delete[] r->pts; delete[] r->cntfullrows ; delete[] r->rankp ;
}

void deleteAll(int nrPlayer,Game* g,Player* p){
/// cleanup
    /// delete players' table elements
    for(int i=0;i<nrPlayer;i++){
        deleteTable((p+i)->p_table) ;
    }

    /// delete list of players
    delete[] p ;

    /// delete game
    deleteGame(g) ; /// delete game
}

#endif // HEAD_02INIT_H_INCLUDED
