#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<sstream>
//#include<cstdlib>
//#include<ctime>

using namespace std;
#include "head_azul.h"

int main()
{
    srand(time(NULL)); /// initialize only once in application!!!

    //int tiles_in_zsak[5]={20,20,20,20,20} ; ///content of zsak
    //int* p_tiles_in_zsak=tiles_in_zsak; ///pointer to zsak to modify with function
    int nrPlayer=3; /// number of players

    Game newgame;
    Game* p_newgame=&newgame;
    initGame(nrPlayer,p_newgame) ; displayAll(p_newgame) ;

    //dropAll(p_newgame) ; //displayTiles(5,p_newgame->p_tiles_in_zsak);

    //fillZsak(p_newgame); //displayTiles(5,p_newgame->p_tiles_in_zsak);

    Player* p0 = createPlayerList(nrPlayer) ;
    cout << endl ;

    ///display players' tables
    /*
    for(int i=0;i<nrPlayer;i++){
        cout << "player " << i+1 << ":" << endl ;
        displayPlayer(p0+i) ;
    }
    */
    /// testing
    /*
    string result ;
    stringstream converter;
    getline(cin, result);
    converter << result;
    */



    chooseTiles(p_newgame, p0);
    //int t=GetInteger();

/*
    delete2Dint(p_rows,7) ;
    delete2Dchar(p_chars,5);
    delete2Dchar(p_chars2,1);
    delete2Dchar(p_chars3,5);
*/
    //for(int i=0;i<5;i++) cout << p_rows[i] << " " ;
    /// cleanup
    //delete nr,p_Korongs;
    //delete p_Korongs, p_Player ;

    return 0;
}
