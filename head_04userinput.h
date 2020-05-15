#ifndef HEAD_04USERINPUT_H_INCLUDED
#define HEAD_04USERINPUT_H_INCLUDED
/*
int chooseKorong(int);
char chooseColour();
string getLine() ;
int getInteger() ;
int getInteger2() ;
void getChoice(int&, char&, int&, int);
void getChoice(int&, char&, int);
void getChoiceFal(int,int&);
bool validatePlayerName(string);
bool validateChoice2(Game*,char, int );
bool validateChoice(Game*,Korong*,Table*, char,int, int);
bool validateChoiceFal(Table*, int, int,bool&,bool&);
*/
int chooseKorong(int n){
    cout << "Melyik korongrol valasztasz? (0-" ;
    cout << n <<" 0:asztal): " ;
    while(true) { // Read input until user enters valid data
        int korong=-99 ;
        korong=getInteger() ;
        if(korong==-99) {cout << "Legalabb 1 korongot meg kell adni! Probald ujra!" ;}
        else if( korong<0 || korong>n ) {cout << "Csak a kovetkezo szamok valaszthatok: 0-"<<n<<", 0:asztal) ! Probald ujra!" ;}
        else {return korong ;}
    }
}

char chooseColour(){
    cout << "Melyik szint valasztod? (a,b,c,d,e): " ;
    while(true){
        string str=getLine() ;
        int cnt=0 ;
        while(str[cnt]!='\0') { cnt++ ;}
        if(str[0]=='\0'){cout << "Legalabb 1 szint meg kell adni! Probald ujra!" ;}
        else if(cnt>1)  {cout << "Csak 1 szin adhato meg! Probald ujra!" ;}
        else{
            for(char i=97;i<102;i++){
                if(str[0]==i) { return str[0] ;}
            }
            cout << "Csak a kovetkezo szinek valaszthatok: a,b,c,d,e ! Probald ujra!" ;
        }
    }
}

///https://www.keithschwarz.com/cs106l/fall2010/course-reader/Ch3_Streams.pdf
string getLine() {
    string result;
    getline(cin, result);
    return result;
}

int getInteger() {
    while(true) { // Read input until user enters valid data
        stringstream converter;
        converter << getLine();
        // Try reading an int, continue if we succeeded.
        int result;
        if(converter >> result) {
            char remaining;
            if(converter >> remaining) // Something's left, input is invalid
                cout << "Nem ismert karakter: " << remaining <<". Probald ujra!" ;
            else
                return result;
        } else
        cout << "Kerlek a megadott integerekbol valassz. Ujra: " ;
    }
}

/// same as above but in English - function only used to set nrPlayers
int getInteger2() {
    while(true) { // Read input until user enters valid data
        stringstream converter;
        converter << getLine();
        // Try reading an int, continue if we succeeded.
        int result;
        if(converter >> result) {
            char remaining;
            if(converter >> remaining) // Something's left, input is invalid
                cout << "Unkown character: " << remaining << endl;
            else
                return result;
        } else
        cout << "Please choose 2,3 or 4. Try again:" ;
    }
}

void getChoice(int& k, char& sz_c, int& m, int nrKorongs){
    /// valasztas rogzitese
    k = chooseKorong(nrKorongs);
    sz_c=chooseColour();
    cout << "Melyik sorra szeretned tenni a csempeket (1-5, 0 padlora teszi a csempet)? " ;
    m=getInteger() ;
}

void getChoice(int& k, char& sz_c, int nrKorongs){
    /// valasztas rogzitese
    k = chooseKorong(nrKorongs);
    sz_c = chooseColour();
}

void getChoiceFal(int row, int& col){
    /// valasztas rogzitese
    cout << "Melyik oszlopba szeretned tenni az "<<row+1<< ". mintasor csempeit (1-5)?" ;
    col = getInteger() ;
}

bool validatePlayerName(string name){
    int cnt=0;
    while(name[cnt]!='\0') { cnt++ ;}
    if(name[0]=='\0'){cout << "Please enter a name for the player!" ; return false ;}
    else if(cnt>8)  {cout << "Please enter a name less than 8 characters!" ; return false ;}
    else { return true ; }
}

bool validateChoice2(Game* g,char sz_c, int nKor){
    int sz_i=convertColourToInt(sz_c) ;

/// set number of tiles --> asztal and korong
    int sumtiles_desk=0;
    for(int i=0;i<5;i++){
        sumtiles_desk+=g->p_tiles_on_table[i] ;
    }
    int sumtiles_korongs=0;
    for(int i=0;i<g->nrKorongs;i++){
        for(int j=0;j<5;j++){
            sumtiles_korongs+=(g->p_Korongs+i)->tiles_on_korong[j] ;
        }
    }

    if(nKor==0){
        int sumtiles=0;
        for(int i=0;i<5;i++){
            sumtiles+=g->p_tiles_on_table[i] ;
        }
        if(g->p_tiles_on_table[sz_i]==0){
            cout << "A megadott szin nincs az asztalon! Probald ujra!\n";
            return false ;
        }
    }
    /// check szin and korong, if korong selected
    else if(nKor>=0 && nKor<=g->nrKorongs) {
        int sumtiles=0;
        for(int i=0;i<5;i++){
            sumtiles+=(g->p_Korongs+nKor-1)->tiles_on_korong[i] ;
        }
        if((g->p_Korongs+nKor-1)->tiles_on_korong[sz_i]==0){
            cout << "A megadott szin nincs a korongon! Probald ujra!\n";
            return false ;
        }
    }
    else {
        cout << nKor << "szamu asztal / korong nem letezik! Probald ujra!\n" ;
        return false ;
    }

    if(nKor==0 && sumtiles_desk==0 && sumtiles_korongs!=0){
        cout << "Asztalon mar nincs csempe, de a korongokon meg van. Probald ujra!\n" ;
        return false ;
    }
    else if(nKor!=0 && sumtiles_desk!=0 && sumtiles_korongs==0){
        cout << "Korongokon nincs csempe, de az asztalon meg van. Probald ujra!\n" ;
        return false ;
    }
    else { return true ;}

}

bool validateChoice(Game* g,Korong* k,Table* t, char sz_c,int nKor, int m){
    int sz_i=convertColourToInt(sz_c) ;

    int cntchosencolour=0; bool kezdoko=false;
    bool elemafalon=false;

/// check mintasor integer (m)
    if(!(0 <= m && m <= 5 )) {
        cout << "Nem ervenyes mintasor, padlo valasztas! Probald ujra!\n" ;
        return false ;
    }

/// check if tile already on fal - only if not padlo selected
    if(m>0){
        for(int i=0;i<5;i++){
            if(t->fal[m-1][i]==sz_c){
                elemafalon=true ;
            }
        }
    }

/// set number of selected tiles --> asztal or korong
    /// check szin and asztal, if asztal selected
    if(nKor==0){
        int sumtiles=0;
        for(int i=0;i<5;i++){
            sumtiles+=g->p_tiles_on_table[i] ;
        }
        if(sumtiles==0){
            cout << "Az asztal ures! Probald ujra!\n";
            return false ;
        }
        if(g->p_tiles_on_table[sz_i]==0){
            cout << "A megadott szin nincs az asztalon! Probald ujra!\n";
            return false ;
        }
        /// save number of tiles chosen, add correction if kezdoko still on desk
        /// and padlosor is chosen for allocation
        cntchosencolour=g->p_tiles_on_table[sz_i] ;
        if(g->p_tiles_on_table[5]!=0 && m==0) { kezdoko=true ;}
    }

    /// check szin and korong, if korong selected
    else {
        int sumtiles=0;
        for(int i=0;i<5;i++){
            sumtiles+=k->tiles_on_korong[i] ;
        }
        if(sumtiles==0){
            cout << "A megadott korong ures! Probald ujra!\n";
            return false ;
        }
        if(k->tiles_on_korong[sz_i]==0){
            cout << "A megadott szin nincs a korongon! Probald ujra!\n";
            return false ;
        }
        /// save number of tiles chosen
        cntchosencolour=k->tiles_on_korong[sz_i] ;
    }

/// check if chosen colour can be put to player's table at all
    /// check if colour fits to mintasor
    bool fittomintasor=false;int freeslotsonmintasor=0;
    for(int i=0;i<5;i++){
        if( ( t->mintasor[i][0]=='-' ) ||
            ( t->mintasor[i][0]==sz_c  && t->mintasor[i][i] == '-' )) {

            for(int j=0;j<=i;j++){
                if(t->mintasor[i][j]=='-'){freeslotsonmintasor++ ;}
            }
            if(freeslotsonmintasor>=cntchosencolour) {fittomintasor=true; }
        }
    }

    /// check if colour fits to padlo (padlon van (eleg) ures hely?)
    bool freepadlo=false; bool fittopadlo=false;int freeslotsonpadlo=0;
    for(int i=0;i<7;i++){
        if(t->tiles_on_padlo[0][i]=='-'){
            freepadlo=true ;freeslotsonpadlo++ ;
        }
    }
    cntchosencolour+=kezdoko ; /// kezdoko needs also slot on padlo
    if( freeslotsonpadlo>=cntchosencolour ) { fittopadlo = true ;}

    /// if selected tile does not fit anywhere --> drop (condition not needed)
    /*
    if(!fittomintasor && !fittopadlo) {
        cout << "A megadott szin nem helyezheto el, tele a padlo, mintasorba nem illik." << endl
             << "A csempe eldobasra kerul.\n" ;
        return true ;
    }
    */

/// if chosen tile fits either to mintasor or padlo (function still running, no return statement up to now)
    /// check padlo if padlo is chosen
    if(m==0){
        if (!freepadlo) {
            cout << "A padlo megtelt, mintasorba kell tenni az elemet! Probald ujra!\n" ;
            return false ;
        }
        if(!fittopadlo && fittomintasor){
            cout << "A padlora nem fer az osszes valasztott elem, mintasorba beleillenek! Probald ujra!\n" ;
            return false ;
        }
    }
    /// check mintasor if mintasor is chosen
    else {
        /// valasztott mintasor megtelt
        if(t->mintasor[m-1][0]==sz_c && t->mintasor[m-1][m-1]!='-' ){
            cout << "A megadott mintasor mar megtelt!\n" ;
            return false ;
        } /// valasztott mintasorban mas elemek vannak
        else if(t->mintasor[m-1][0]!= '-' && t->mintasor[m-1][0]!=sz_c){
            cout << "A megadott mintasorban mas szinu elemek vannak! Probald ujra!\n" ;
            return false ;
        }
        else if(elemafalon){
            cout << "A falon mar van ilyen szinu elem! Probald ujra!\n" ;
            return false ;
        }
        else {return true ;}
    }
    return true ;
}

bool validateChoiceFal(Table* t, int row, int col,bool& wallallocation,bool& padloallocation){
    char sz_c = t->mintasor[row][row] ;

    bool oszlopfoglalt=false, elemvanmaroszlop=false;

    /// check choice
    if(!(0<col && col<6) ) {
        cout << "Nem megfelelo oszlop! Probald ujra!\n" ;
        return false ;
    }

    /// check fal oszlop
    if( t->fal[row][col-1] != '.' ) {
        oszlopfoglalt=true ;
    }
    else {
        for(int i=0;i<5;i++){
            if( t->fal[i][col-1] ==sz_c ) {
                elemvanmaroszlop=true ;
            }
        }
    }

    /// message
    if(oszlopfoglalt){
        cout << "A kivalasztott oszlop mar foglalt. Probald ujra!\n" ;
        return false ;
    }
    else if(elemvanmaroszlop){
        cout << "A kivalasztott oszlopban mar szerepel ez a szin. "
             << "Valassz masik oszlopot!\n";
        return false ;
    }

    else {wallallocation=true; return true ;} ;
}

#endif // HEAD_04USERINPUT_H_INCLUDED
