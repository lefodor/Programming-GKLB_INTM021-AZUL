#include<iostream>
#include<string>
#include "prog.h"
#include "userinp.h"

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

void dropTilesFromArray(int* a,char m,int s){
    convertColourToInt(m) ;
    a[convertColourToInt(m)]+=s;
}

void dropTiles(Game* g, int tilesToDrop, char sz_c){
    int sz=convertColourToInt(sz_c);
    for(int i=0;i<5;i++){
        if(i==sz) {g->p_tiles_dropped[i]+=tilesToDrop ;} ;
    }
}

int convertColourToInt(char sz_c){
    int sz ;
        switch(sz_c){
        case 'a':sz=0 ;break ;
        case 'b':sz=1 ;break ;
        case 'c':sz=2 ;break ;
        case 'd':sz=3 ;break ;
        default: sz=4 ;break ;
        }
    return sz ;
}

/// draw n element with given interval
int* drawX(int n, int interval){
    int* nr = new int[n] ;
    for(int i=0;i<n;i++){
        nr[i]=rand()%interval;
    }
    return nr ;
}

/// call drawX and change number of elements in zsak
char drawCH(Game* g){

    /// count total of tiles
    int tile_sum=0;
    for(int i=0;i<5;i++){
        tile_sum+=g->p_tiles_in_zsak[i];
    }

    /// generate single element(drawX) from interval of tile_sum and change zsak accordingly
    int j=0 ;
    if(tile_sum>0){

        int* n=drawX(1,tile_sum);

        /// set index j to the element to be decremented
        bool valueOver=false ;
        int tile_cumsum=0 ;
        while(!valueOver && j<5){
            tile_cumsum+=g->p_tiles_in_zsak[j]; /// get cumulated tiles up to point j
            valueOver=(*n<tile_cumsum);/// if drawn tile is below cumulated, set valueover and finish loop
            j++;
        }

        /// use index j to decrease number of tiles in zsak
        /// decrement and return only if not below or equal to 0
        if(g->p_tiles_in_zsak[j-1]>0){
            g->p_tiles_in_zsak[j-1]-=1;
        }

        /// cleanup
        delete[] n;
    }
    /// no element in zsak, return f as false from switch - should not ever happen
    else { j=6; }

    /// return character based on j
    switch(j){
    case 1: return 'a'; break ;
    case 2: return 'b'; break ;
    case 3: return 'c'; break ;
    case 4: return 'd'; break ;
    case 5: return 'e'; break ;
    default: return 'f' ;
    }
}

bool checkEndOfRound(Game* g){
    int sumTilesOnKorongs=0;
    int sumTilesOnDesk=0;
    for(int i=0;i<(g->nrKorongs);i++){
        for (int j=0;j<5;j++){
            sumTilesOnKorongs+=(g->p_Korongs+i)->tiles_on_korong[j];
        }
    }
    for(int i=0;i<5;i++){
        sumTilesOnDesk+=g->p_tiles_on_table[i];
    }
    if(sumTilesOnKorongs==0 && sumTilesOnDesk==0){return true;}
    else{return false;} ;
}

bool checkEndOfGame(Player* p0, int p){
    for(int i=0;i<p;i++){
        for(int j=0;j<5;j++){
            bool falsorafull=true ;
            for (int k=0;k<5;k++){
                if((p0+i)->p_table->fal[j][k]=='.' ) {falsorafull=false ;} ;
            }
            if(falsorafull){return true ;}
        }
    }
    return false ;
}

void allocateTiles(Game* g,bool& error){
    /// count tiles in zsak, dropped, desk
    int cumsum_zsak=0;
    for(int i=0;i<5;i++){ cumsum_zsak+=(g->p_tiles_in_zsak[i]) ;}

    int cumsum_dropped=0 ;
    for(int i=0;i<5;i++){ cumsum_dropped+=(g->p_tiles_dropped[i]) ;}

    int cumsum_desk=0;
    for(int i=0;i<5;i++){ cumsum_desk+=(g->p_tiles_on_table[i]) ;}

    /// no tiles anywhere - csempek eltuntek - should not ever happen - testing purposes
    if(cumsum_zsak==0 && cumsum_dropped==0 && cumsum_desk==0){
        std::cout << "Tiles are gone, play Cluedo instead and find the thief! "
             << "Press enter to exit...\n" ;
        getLine() ;
        error=true;
    }

    /// if zsak not empty, call drawCH via initKorong
    else if(cumsum_zsak!=0){
        for(int i=0;i<g->nrKorongs;i++){
            initKorong(g->p_Korongs+i,g,i+1);
        }
    }
    /// otherwise put all dropped tiles to zsak and then call drawCH via initKorong
    else {
        fillZsak(g) ; /// put from dropped to zsak
        for(int i=0;i<(g->nrKorongs);i++){
            initKorong(g->p_Korongs+i,g,i+1);
        }
    }
    /// set kezdoko to 1
    g->p_tiles_on_table[5]=1;
}

void chooseTiles(Game* g, Player* p){
    int k ;
    char sz_c ;
    int m=0 ;

    /// check mintasor first, if there is still available slot
    bool freemintasor=false;
    for(int i=0;i<5;i++){
        if(p->p_table->mintasor[i][i]=='-'){freemintasor=true;}
    }

    /// check padlo, if there are free slots
    bool freepadlo=false ;
    for(int i=0;i<7;i++){
        if( p->p_table->tiles_on_padlo[0][i]=='-' ){
            freepadlo=true ;
        } ;
    }

    /// record and validate user choice
    if(freemintasor) {
        do{
            getChoice(k,sz_c,m,g->nrKorongs) ;
        }while(!(validateChoice2(g,sz_c,k) && validateChoice(g,g->p_Korongs+k-1,p->p_table,sz_c,k,m))) ;
    }
    else if(!freemintasor && freepadlo){
        do{
            getChoice(k,sz_c,g->nrKorongs) ;
        }while(!validateChoice2(g,sz_c,k));
        std::cout << "Nincs szabad mintasor, csak padlora mehet!" << std::endl ;
    }
    else {
        do{
            getChoice(k,sz_c,g->nrKorongs) ;
        }while(!validateChoice2(g,sz_c,k)) ;
        std::cout << "Nincs szabad mintasor, tele a padlo, csak eldobni lehet!" << std::endl ;
    }

    int sz = convertColourToInt(sz_c);

    int choosentiles_cnt=0 ;bool kezdoko=false;
    /// count number of tiles to be allocated, sets kezdoko flag,...
    /// sets nr of tiles on asztal and korong to 0
    setValuesForAllocation(choosentiles_cnt,kezdoko,k,sz,g,p);

    int tilesToDrop=0;
    /// put tiles to padlo or mintasor and return number of tiles remaining --> to be dropped
    putTilesToTable(p->p_table,sz_c,m,choosentiles_cnt,kezdoko,tilesToDrop);

    /// put still remaining tiles to dropped array
    dropTiles(g,tilesToDrop,sz_c);
}

void setValuesForAllocation(int& choosentiles_cnt, bool& kezdoko, int korong_v_asztal,int sz, Game* g, Player* p){

    if(korong_v_asztal!=0){
        /// save number of tiles from colour sz on korong
        choosentiles_cnt=(g->p_Korongs+korong_v_asztal-1)->tiles_on_korong[sz] ;

        /// set chosen colour to 0
        (g->p_Korongs+korong_v_asztal-1)->tiles_on_korong[sz]=0;

        for(int j=0;j<5;j++){
            (g->p_tiles_on_table[j])+=((g->p_Korongs+korong_v_asztal-1)->tiles_on_korong[j]); /// put all other colours to desk
            (g->p_Korongs+korong_v_asztal-1)->tiles_on_korong[j]=0;/// set all colours to 0
        }
    }
    else {/// desk is chosen
        choosentiles_cnt=g->p_tiles_on_table[sz] ;
        kezdoko = (g->p_tiles_on_table[5]>0) ;
        g->p_tiles_on_table[5]=0 ; /// set kezdoko to 0
        g->p_tiles_on_table[sz]=0; /// set colours to 0
    }
}

void putTilesToTable(Table* t, char sz_c, int m, int& tilesToBeAllocated, bool kezdoko, int& unallocated){
    /// sort out kezdoko
    if(kezdoko){
        int kezdokohelye=0;
        while(kezdokohelye<7 && t->tiles_on_padlo[0][kezdokohelye]!='-'){kezdokohelye++;}; /// loop to slot where padlo has first '-'
        if(kezdokohelye<7){t->tiles_on_padlo[0][kezdokohelye]='k';}
        else { std::cout << "Padlo tele, kezdoko nem leteheto!\n" ; }
    }
    /// put tiles to mintasor
    int j=0 ;
    if (m!=0){
        if( t->mintasor[m-1][0]==sz_c || t->mintasor[m-1][0]=='-' ){
            while(tilesToBeAllocated>0 && j<m){
                if(t->mintasor[m-1][j]=='-' ){
                    t->mintasor[m-1][j]=sz_c;
                    tilesToBeAllocated--;
                }
                j++;
            }
        }
    }
    j=0;
    /// put tiles to padlo
    while(tilesToBeAllocated>0 && j<7){
        if(t->tiles_on_padlo[0][j]=='-'){ /// start filling padlo where '-' occurs
            t->tiles_on_padlo[0][j]=sz_c;
            tilesToBeAllocated--;
        }
        j++;
    }
    /// save number of tiles to be dropped
    unallocated=tilesToBeAllocated;//-allocated ;
}

void putTilesToWall(Game* g, Player* p){
    int i=0; /// used to loop on rows of mintasor
    int col=0 ;
    for( ;i<5;i++){
        bool wallallocation=false,padloallocation=false ;

        /// check if i.row is full
        if(p->p_table->mintasor[i][i]!='-'){
            char sz_c = p->p_table->mintasor[i][i] ;

            /// check fal sor
            bool falsorafull = true, elemvanmarsor=false, padlofull=true ;
            for(int j=0;j<5;j++){

                if( p->p_table->fal[i][j] == '.' ) {
                    falsorafull=false ;
                }
                if( p->p_table->fal[i][j] == sz_c ) {
                    elemvanmarsor= true ;
                }
            }

            /// check padlo if there are enough free slots
            for(int j=0;j<7;j++){
                if(p->p_table->tiles_on_padlo[0][j]=='-'){
                    padlofull=false ;
                }
            }

            /// check if tile can be put to fal - kulonleges eset
            int cntvalidoszlop=0 ;
            for(int j=0;j<5;j++){
                /// count columns where tile can be put
                if( p->p_table->fal[i][j] == '.' ) {
                    cntvalidoszlop++; /// increment nr valid oszlop
                    for(int k=0;k<5;k++){
                        /// loop on elements in given oszlop and decrement if colour is already present
                        if( p->p_table->fal[k][j] == sz_c ) { cntvalidoszlop-- ; k=5;}
                    }
                }
            }

            if(falsorafull && !padlofull){
                std::cout << i+1 << ". sor mar tele van, csak padlosorra mehet.\n" ;
                int allocated=0 ;
                /// put tiles to padlo
                int j=0 ;
                while(allocated<=i && j<7){
                    if(p->p_table->tiles_on_padlo[0][j]=='-'){ /// start filling padlo where '-' occurs
                        p->p_table->tiles_on_padlo[0][j]=sz_c;
                        allocated++;
                    }
                    j++;
                }
                /// save number of tiles to be dropped
                int unallocated=(i+1)-allocated ;
                dropTilesFromArray(g->p_tiles_dropped,sz_c,unallocated);
            }
            else if(falsorafull && padlofull){
                std::cout << i+1 << ". sor mar tele van, padlo is megtelt, elemek eldobasra kerulnek.\n" ;
                int allocated=0 ;
                /// put tiles to padlo
                int j=0 ;
                while(allocated<=i && j<7){
                    if(p->p_table->tiles_on_padlo[0][j]=='-'){ /// start filling padlo where '-' occurs
                        p->p_table->tiles_on_padlo[0][j]=sz_c;
                        allocated++;
                    }
                    j++;
                }
                /// save number of tiles to be dropped
                int unallocated=(i+1)-allocated ;
                dropTilesFromArray(g->p_tiles_dropped,sz_c,unallocated);
            }
            else if(elemvanmarsor && !padlofull){
                std::cout << i+1 << ". sorban mar szerepel ez a szin, csak padlosorra mehet.\n" ;
                int allocated=0 ;
                /// put tiles to padlo
                int j=0 ;
                while(allocated<=i && j<7){
                    if(p->p_table->tiles_on_padlo[0][j]=='-'){ /// start filling padlo where '-' occurs
                        p->p_table->tiles_on_padlo[0][j]=sz_c;
                        allocated++;
                    }
                    j++;
                }
                /// save number of tiles to be dropped
                int unallocated=(i+1)-allocated ;
                dropTilesFromArray(g->p_tiles_dropped,sz_c,unallocated);
            }
            else if(elemvanmarsor && padlofull){
                std::cout << i+1 << ". sorban mar szerepel ez a szin, a padlo megtelt, elemek eldobasra kerulnek.\n" ;
                int allocated=0 ;
                /// put tiles to padlo
                int j=0 ;
                while(allocated<=i && j<7){
                    if(p->p_table->tiles_on_padlo[0][j]=='-'){ /// start filling padlo where '-' occurs
                        p->p_table->tiles_on_padlo[0][j]=sz_c;
                        allocated++;
                    }
                    j++;
                }
                /// save number of tiles to be dropped
                int unallocated=(i+1)-allocated ;
                dropTilesFromArray(g->p_tiles_dropped,sz_c,unallocated);
            }
            else if(cntvalidoszlop<1){ /// kulonleges eset, nem elhelyezheto a falon --> mindet eldobni
                int allocated=0 ;
                /// put tiles to padlo
                int j=0 ;
                while(allocated<=i && j<7){
                    if(p->p_table->tiles_on_padlo[0][j]=='-'){ /// start filling padlo where '-' occurs
                        p->p_table->tiles_on_padlo[0][j]=sz_c;
                        allocated++;
                    }
                    j++;
                }
                /// save number of tiles to be dropped
                int unallocated=(i+1)-allocated ;
                dropTilesFromArray(g->p_tiles_dropped,sz_c,unallocated);
                std::cout << i+1 << ". sorbol nem lehet tablara helyezni elemeket, osszes elem padlora kerul.\n" ;
            }
            else {
                /// record and validate user choice
                do{
                    getChoiceFal(i,col) ;
                }while(!validateChoiceFal(p->p_table,i,col,wallallocation,padloallocation));

                /// put to table
                if(wallallocation){
                    p->p_table->fal[i][col-1]=p->p_table->mintasor[i][i];
                    /// calc points
                    calcPoints(p,i,col-1) ;
                }
                /// add to padlosor
                else if(padloallocation){
                    int j=0 ;
                    while(p->p_table->tiles_on_padlo[0][j]!='-'){
                        j++ ;
                    }
                    p->p_table->tiles_on_padlo[0][j]=p->p_table->mintasor[i][0];
                }
                /// add to drop unallocated part of mintasor
                dropTilesFromArray(g->p_tiles_dropped,p->p_table->mintasor[i][0],i);
            }
            /// set mintasor back to '-'
            for(int j=0;j<=i;j++){
                p->p_table->mintasor[i][j] = '-' ;
            }
        }
    }
    /// take care of padlosor and negative point due to kezdoko
    /// add points from padlo
    int points[7]={-1,-1,-2,-2,-2,-3,-3};
    for(int j=0;j<7;j++){
        if(p->p_table->tiles_on_padlo[0][j] != '-') {
            p->points+=points[j] ;
            /// add to drop
            if( p->p_table->tiles_on_padlo[0][j] != 'k' ) {
                dropTilesFromArray(g->p_tiles_dropped,p->p_table->tiles_on_padlo[0][j],1);
            }
        }
        /// set back to '-'
        p->p_table->tiles_on_padlo[0][j] = '-' ;
    }
    /// set back points to 0 if below
    if(p->points<0){p->points=0;}
    std::cout << "end of Fal tiling\n" ;
    std::cout << "Press Enter to continue...\n";
    getLine() ;
}

void calcPoints(Player* p, int row, int col){
    int i=row;int j=col;
    bool inrow=false, incol=false;
    /// move left
    while(j>0 && p->p_table->fal[i][j-1]!='.'){ j-- ; inrow=true;}
    p->points+=col-j;

    /// move right
    j=col;
    while(j<4 && p->p_table->fal[i][j+1]!='.'){ j++ ; inrow=true;}
    p->points+=j-col;

    /// move up
    while(i>0 && p->p_table->fal[i-1][col]!='.'){ i-- ; incol=true;}
    p->points+=row-i;

    /// move down
    i=row;
    while(i<4 && p->p_table->fal[i+1][col]!='.'){ i++ ;incol=true;}
    p->points+=i-row;

    /// + for set tile
    if(inrow && incol) {p->points+=2;}
    else {p->points+=1 ;}
}

int countfullsor(Player* p){
    int cntfullsor=0 ;
    for(int i=0;i<5;i++){
        bool isfullsor=true ;
        for(int j=0;j<5;j++){
            if(p->p_table->fal[i][j]=='.'){ isfullsor=false ; j=5;}
        }
        cntfullsor+=isfullsor;
    }
    return cntfullsor ;
}

int countfulloszlop(Player* p){
    int cntfulloszlop=0 ;
    for(int i=0;i<5;i++){
        bool isfulloszlop=true ;
        for(int j=0;j<5;j++){
            if(p->p_table->fal[j][i]=='.'){ isfulloszlop=false ; j=5;}
        }
        cntfulloszlop+=isfulloszlop;
    }
    return cntfulloszlop ;
}

int countcolours5timesonwall(Player* p){
    int cntcolours[5]={0,0,0,0,0};
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cntcolours[convertColourToInt(p->p_table->fal[i][j])]++;
        }
    }
    int cntcolour5times=0 ;
    for(int i=0;i<5;i++){
        if(cntcolours[i]==5){ cntcolour5times++ ; }
    }
    return cntcolour5times ;
}

void calcPointsBonus(Player* p){
    int cntfullsor=countfullsor(p);
    int cntfulloszlop=countfulloszlop(p);
    int cntcolour5times=countcolours5timesonwall(p);
    p->points+=cntfullsor*2; std::cout << "Bonus for full rows:" << cntfullsor*2 << std::endl ;
    p->points+=cntfulloszlop*7; std::cout << "Bonus for full columns:" << cntfulloszlop*7 << std::endl ;
    p->points+=cntcolour5times*10; std::cout << "Bonus for colours 5 times on wall:" << cntcolour5times*10 << std::endl ;
}

int getMaxPoint(int n, Player* p){
    int highscore=0 ;
    for(int i=0;i<n;i++){
        if(i==0){
            highscore=(p+i)->points ;
        }
        else if ( highscore<(p+i)->points ) {
            highscore=(p+i)->points ;
        }
    }
    return highscore ;
}

int getNrPlayerWithHighScore(int n, Player* p, int highscore){
    int highscoreplayer=0 ;
    for(int i=0;i<n;i++){
        if( (p+i)->points == highscore ) { highscoreplayer++; }
    }
    return highscoreplayer ;
}

