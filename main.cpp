#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<sstream>
using namespace std;

#include "init.h"
#include "prog.h"
#include "display.h"
#include "userinp.h"

int main(){
    /// set random number generator
    srand(time(NULL)); /// initialize only once in application!!!

    while(true){

        string uinp_s ;
        do{
            cout <<"****************************************************\n"
                 <<"********** AZUL board game C implementation*********\n"
                 <<"program written by: Levente Fodor - mu1g7o *********\n"
                 << endl ;
            cout <<"1. Start game" << endl ;
            cout <<"2. Quit game" << endl ;

            stringstream uinp ;
            uinp << getLine() ;

            uinp >> uinp_s;

            if(uinp_s=="2") { cout << "Thanks for playing. Goodbye.\n" ; return EXIT_SUCCESS ;}
            else if(uinp_s=="1") { cout << "Start game\n" ;}
            else { cout << "Please choose 1 or 2 then hit Enter.\n" ; } ;
        }while(!(uinp_s=="1" || uinp_s=="2"));

        /// set number of players
        int nrPlayer ;
        do{
            cout << "Enter number of players (2,3 or 4): ";
            nrPlayer=getInteger2(); /// number of players 2,3,4
        }while( !( nrPlayer == 2 || nrPlayer == 3 || nrPlayer == 4 ) ) ;

        /// create game
        Game newgame;
        Game* p_newgame=&newgame;
        initGame(nrPlayer,p_newgame) ; /// createKorong (not initialized)
        /// create players
        Player* p0 = createPlayerList(nrPlayer) ; /// initPlayers --> initTable
        cout << endl ;

        bool endOfRound;
        bool endOfGame;
        bool errorflag=false;
        int round1stplayer=-1;
        endOfGame=checkEndOfGame(p0,nrPlayer);

        while(!endOfGame && !errorflag){

            /// initialize korongs
            /// allocate tiles accordingly - from zsak if zsak not empty otherwise from dropped
            /// set errorflag to true if tiles are gone (no in zsak, dropped, desk)
            allocateTiles(p_newgame,errorflag) ; /// initKorong

            if(!errorflag){

                /// end of round if no tiles on desk and korongs
                endOfRound=checkEndOfRound(p_newgame);
                /// rounds: csempek mintasorra korongrol v asztalrol
                while(!endOfRound){
                    /// loop on players to get their choices
                    if(round1stplayer==-1){round1stplayer=0;}
                    for(int i=round1stplayer;i<nrPlayer && !endOfRound;i++){
                        system("cls");

                        /// display game repo and player's table
                        displayAll(p_newgame) ;
                        for(int j=0;j<nrPlayer;j++){
                            displayPlayer(p0+j);
                        }

                        /// choose tiles from korong/asztal and puts to player's table
                        cout << "Ready " << (p0+i)->name << endl ;
                        chooseTiles(p_newgame, p0+i);
                        /// show player's table after tile allocation
                        cout << "Jatekos tablaja valasztas utan:\n" ;
                        displayPlayer(p0+i);

                        cout << "Press Enter to continue...\n";
                        getLine();

                        /// set round1stplayer flag
                        round1stplayer = 0 ;

                        /// check if round ended - all korongs empty, desk empty - other players cannot make selection
                        endOfRound=checkEndOfRound(p_newgame);
                        if(endOfRound) { cout << "Tobb valasztas nem lehetseges. Fordulo vege!" << endl ;}
                    }
                }

                /// display game repo and player's table for tiling
                system("cls") ;
                displayAll(p_newgame) ;
                for(int j=0;j<nrPlayer;j++){
                    displayPlayer(p0+j);
                }

                /// tiling: csempek falra
                for(int i=0;i<nrPlayer;i++){
                    /// set round1stplayer flag
                    for(int j=0;j<7;j++){
                        if( (p0+i)->p_table->tiles_on_padlo[0][j]=='k'){
                            round1stplayer=i ;
                        }
                    }
                    cout << "Ready player " << (p0+i)->name << endl ;
                    putTilesToWall(p_newgame,p0+i ) ;
                    system("cls");
                    displayAll(p_newgame) ;
                    for(int i=0;i<nrPlayer;i++){
                        displayPlayer(p0+i) ;
                    }
                }

                /// end of game if at least 1 player has 1 row full
                endOfGame=checkEndOfGame(p0,nrPlayer);

                /// end of game: add bonus points and announce winner
                if(endOfGame) {
                    /// calculate bonus points
                    cout << "Jatekosnak tele van egy sora! Jatek vege!" << endl ;
                    for(int i=0;i<nrPlayer;i++){
                        cout << "Jatekos " << (p0+i)->name << " teli sorok / oszlopok: "
                             << countfullsor(p0+i) << "/" << countfulloszlop(p0+i) << endl;
                        calcPointsBonus(p0+i);
                        cout << "Jatekos " << (p0+i)->name << " total score: " << (p0+i)->points << endl ;
                    }

                    /// announce winner
                    int highscore=getMaxPoint(nrPlayer,p0) ;
                    int highscoreplayer=getNrPlayerWithHighScore(nrPlayer,p0,highscore) ;
                    int highfullsor = 0 ;

                    int winnerlist[4]={0,0,0,0} ; /// 4 is maximum number of players, would be better dynamically
                    /// if highest score is attributed to only one player
                    if(highscoreplayer==1){
                        for(int i=0;i<nrPlayer;i++){
                            if((p0+i)->points==highscore) {
                                winnerlist[i] = 1 ;
                            }
                        }
                    }
                    /// else check number of full rows
                    else {
                        /// get maximum of full rows
                        for(int i=0;i<nrPlayer;i++){
                            if((p0+i)->points==highscore) {
                                if( highfullsor<countfullsor(p0+i) ) {
                                    highfullsor=countfullsor(p0+i) ;
                                }
                            }
                        }
                        /// check both highscore and highfullrow and set winnerlist
                        for(int i=0;i<nrPlayer;i++){
                            if((p0+i)->points==highscore && countfullsor(p0+i) == highfullsor ){
                                winnerlist[i] = 1;
                            }
                        }
                    }

                    /// count number of winners
                    int numberofwinners=0;
                    for(int i=0;i<4;i++){
                        numberofwinners+=winnerlist[i] ;
                    }

                    /// announce winner(s)
                    if(numberofwinners==1){ cout << "Winner is " ;}
                    else { cout << "Winners are " ;}
                    for(int i=0;i<4;i++){
                        if(winnerlist[i]==1) { cout << "\n\t" << (p0+i)->name ; } ;
                    }
                    cout << endl ;

                    /// announce full result table
                    Results res = initResults(nrPlayer,p0) ;
                    Results* p_res = &res ;
                    displayResults(nrPlayer,p_res) ;
                    deleteResults(p_res);
                }
                //system("cls");
            }
        }
    /// cleanup
        deleteAll(nrPlayer,p_newgame, p0) ;
    }
    return EXIT_SUCCESS;
}
