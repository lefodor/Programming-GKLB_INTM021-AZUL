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
    /// set random number generator
    srand(time(NULL)); /// initialize only once in application!!!

    /// set number of players
    int nrPlayer=3; /// number of players

    /// create game
    Game newgame;

    Game* p_newgame=&newgame;
    initGame(nrPlayer,p_newgame) ;
    //displayAll(p_newgame) ;

    //dropAll(p_newgame) ; //displayTiles(5,p_newgame->p_tiles_in_zsak);
    //fillZsak(p_newgame); //displayTiles(5,p_newgame->p_tiles_in_zsak);

    /// create players
    Player* p0 = createPlayerList(nrPlayer) ;
    cout << endl ;

    //setKorongs(p_newgame) ;
    bool endOfRound=checkEndOfRound(p_newgame);
    while(!endOfRound){
    for(int i=0;i<nrPlayer,!endOfRound;i++){
        system("cls");

        /*
        for(int i=0;i<7;i++){
            p0->p_table->tiles_on_padlo[0][i]='e';
            (p0+1)->p_table->tiles_on_padlo[0][i]='e';
            (p0+2)->p_table->tiles_on_padlo[0][i]='e';
        }
        */
        /// display game repo and player's table
        displayAll(p_newgame) ;
        displayPlayer(p0+i);

        cout << "Ready player " << i+1 << endl ;
        /// choose tiles from korong
        chooseTiles(p_newgame, p0+i);

        /// show player's table after tile allocation
        cout << "Jatekos tablaja valasztas utan:\n" ;
        displayPlayer(p0+i);

        ///https://www.dreamincode.net/forums/topic/185297-press-any-key-to-continue/
        cout << "Press ESC to exit. Press any other key to continue...\n";
        cin.clear();cin.sync();cin.get();cin.clear() ;
        //if(cin.get()==27) {return 0 ;}
        endOfRound=checkEndOfRound(p_newgame);
        if(endOfRound) { cout << "Nincs tobb csempe a korongokon. Fordulo vege!" << endl ;}
    }
    }
    /// cleanup
/*
    delete2Dint(p_rows,7) ;
    delete2Dchar(p_chars,5);
    delete2Dchar(p_chars2,1);
    delete2Dchar(p_chars3,5);
*/
    //for(int i=0;i<5;i++) cout << p_rows[i] << " " ;
    //delete nr,p_Korongs;
    //delete p_Korongs, p_Player ;

    return 0;
}
