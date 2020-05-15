#ifndef HEAD_0XOTHER_H_INCLUDED
#define HEAD_0XOTHER_H_INCLUDED
/*
void setKorongs(Game*);
void setMintasor(Game*, Player*);
void setAsztal(Game*);
void setFal(Player*);
void testAll(Game*, Player*, int);
*/

void setKorongs(Game* g){
    for(int i=0;i<g->nrKorongs;i++){
        for (int j=0;j<5;j++){
            (g->p_Korongs+i)->tiles_on_korong[j]=0;
        }
    }
}

void setMintasor(Player* p){
    char sz_c;
    for(int i=0;i<5;i++){
        int sz=rand()%5 ;
        for(int j=0;j<=i;j++){
            switch(sz){
            case 0:sz_c='a';break ;
            case 1:sz_c='b';break ;
            case 2:sz_c='c';break ;
            case 3:sz_c='d';break ;
            default:sz_c='e';break ;
            }
            p->p_table->mintasor[i][j]=sz_c ;
        }
    }
}

void setAsztal(Game* g){
    for(int i=0;i<6;i++){
        g->p_tiles_on_table[i]=0 ;
    }
    //g->p_tiles_on_table[4]=15 ;
    g->p_tiles_on_table[3]=1 ;
}

void setFal(Player* p,int var){
    char sz_c;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            bool valid=true ;
            do{
                valid=true ;
                int sz=rand()%10 ;
                switch(sz){
                case 0:sz_c='a';break ;
                case 1:sz_c='b';break ;
                case 2:sz_c='c';break ;
                case 3:sz_c='d';break ;
                case 4:sz_c='e';break ;
                default:sz_c='.';break ;
                }
                for(int k=0;k<j;k++){
                    if(sz_c!='.' && sz_c==p->p_table->fal[i][k]) {valid=false ;}
                }
            }while(!valid);
            p->p_table->fal[i][j]=sz_c ;
        }

        if(var==1||var==3){
            p->p_table->fal[0][0]='a' ;
            p->p_table->fal[0][1]='b' ;
            p->p_table->fal[0][2]='c' ;
            p->p_table->fal[0][3]='d' ;
            p->p_table->fal[0][4]='.' ;
            p->p_table->mintasor[0][0]='e';

            for(int j=0;j<5;j++){
                p->p_table->fal[j][4]='.' ;
            }
/*
            p->p_table->fal[1][0]='c' ;
            p->p_table->fal[1][1]='.' ;
            p->p_table->fal[1][2]='b' ;
            p->p_table->fal[1][3]='.' ;
            p->p_table->fal[1][4]='.' ;
            p->p_table->mintasor[1][0]='e';
            p->p_table->mintasor[1][1]='-';

            p->p_table->fal[2][0]='d' ;
            p->p_table->fal[2][1]='c' ;
            p->p_table->fal[2][2]='a' ;
            p->p_table->fal[2][3]='.' ;
            p->p_table->fal[2][4]='.' ;
            p->p_table->mintasor[2][0]='e';
            p->p_table->mintasor[2][1]='e';
            p->p_table->mintasor[2][2]='e';

            p->p_table->fal[3][0]='b' ;
            p->p_table->fal[3][1]='a' ;
            p->p_table->fal[3][2]='.' ;
            p->p_table->fal[3][3]='e' ;
            p->p_table->fal[3][4]='.' ;
            p->p_table->mintasor[3][0]='e';
            p->p_table->mintasor[3][1]='e';
            p->p_table->mintasor[3][2]='e';
            p->p_table->mintasor[3][3]='e';

            p->p_table->fal[4][0]='e' ;
            p->p_table->fal[4][1]='.' ;
            p->p_table->fal[4][2]='.' ;
            p->p_table->fal[4][3]='.' ;
            p->p_table->fal[4][4]='.' ;
            p->p_table->mintasor[4][0]='b';
            p->p_table->mintasor[4][1]='b';
            p->p_table->mintasor[4][2]='b';
            p->p_table->mintasor[4][3]='b';
            p->p_table->mintasor[4][4]='-';
        }
        else {
            for(int i=0;i<7;i++){
                p->p_table->tiles_on_padlo[0][i]='a';
            }
        }
*/
    }
    for(int i=0;i<3;i++){
        p->p_table->tiles_on_padlo[0][i]='a';
    }
}
}

void testAll(Game* g, Player* p, int nrPlayer){
    /// testing purposes pre-fill tables
        setKorongs(g) ;
        setAsztal(g) ;

        /// set zsak
        for(int i=0;i<5;i++){
            g->p_tiles_in_zsak[i]=0;
        }

        /// set players table
        for(int i=0;i<nrPlayer;i++){
            setMintasor(p+i);
            setFal(p+i,i);
/*
            (p)->p_table->fal[0][0] = '.' ; /// manually set back to -

            (p)->p_table->fal[1][0] = '.' ; /// manually set back to -
            (p)->p_table->fal[1][1] = '.' ; /// manually set back to -
            (p)->p_table->fal[1][2] = 'd' ; /// manually set back to -
            (p)->p_table->fal[1][3] = '.' ; /// manually set back to -
            (p)->p_table->fal[1][4] = 'a' ; /// manually set back to -

            (p)->p_table->fal[2][0] = 'e' ; /// manually set back to -
            (p)->p_table->fal[3][0] = 'd' ; /// manually set back to -
            (p)->p_table->fal[4][0] = 'b' ; /// manually set back to -

            (p)->p_table->mintasor[1][0] = 'e' ; /// manually set back to -
            (p)->p_table->mintasor[1][1] = 'e' ; /// manually set back to -
*/
            ///
/*
            (p)->p_table->fal[0][0] = '.' ; /// manually set back to -
            (p)->p_table->fal[0][1] = 'd' ; /// manually set back to -
            (p)->p_table->fal[0][2] = 'a' ; /// manually set back to -
            (p)->p_table->fal[0][3] = 'e' ; /// manually set back to -
            (p)->p_table->fal[0][4] = 'b' ; /// manually set back to -

            (p)->p_table->fal[1][0] = '.' ; /// manually set back to -
            (p)->p_table->fal[1][1] = '.' ; /// manually set back to -
            (p)->p_table->fal[1][2] = 'd' ; /// manually set back to -
            (p)->p_table->fal[1][3] = '.' ; /// manually set back to -
            (p)->p_table->fal[1][4] = 'a' ; /// manually set back to -

            (p)->p_table->fal[2][0] = 'e' ; /// manually set back to -
            (p)->p_table->fal[2][1] = '.' ; /// manually set back to -
            (p)->p_table->fal[2][2] = 'b' ; /// manually set back to -
            (p)->p_table->fal[2][3] = 'e' ; /// manually set back to -
            (p)->p_table->fal[2][4] = '.' ; /// manually set back to -

            (p)->p_table->fal[3][0] = 'd' ; /// manually set back to -
            (p)->p_table->fal[3][1] = 'b' ; /// manually set back to -
            (p)->p_table->fal[3][2] = '.' ; /// manually set back to -
            (p)->p_table->fal[3][3] = '.' ; /// manually set back to -
            (p)->p_table->fal[3][4] = 'c' ; /// manually set back to -

            (p)->p_table->fal[4][0] = 'b' ; /// manually set back to -
            (p)->p_table->fal[4][1] = 'a' ; /// manually set back to -
            (p)->p_table->fal[4][2] = 'e' ; /// manually set back to -
            (p)->p_table->fal[4][3] = 'b' ; /// manually set back to -
            (p)->p_table->fal[4][4] = '.' ; /// manually set back to -

            (p)->p_table->mintasor[0][0] = 'b' ; /// manually set back to -

            (p)->p_table->mintasor[1][0] = 'e' ; /// manually set back to -
            (p)->p_table->mintasor[1][1] = 'e' ; /// manually set back to -

            (p)->p_table->mintasor[2][0] = 'e' ; /// manually set back to -
            (p)->p_table->mintasor[2][1] = 'e' ; /// manually set back to -
            (p)->p_table->mintasor[2][2] = 'e' ; /// manually set back to -

            (p)->p_table->mintasor[3][0] = 'a' ; /// manually set back to -
            (p)->p_table->mintasor[3][1] = 'a' ; /// manually set back to -
            (p)->p_table->mintasor[3][2] = 'a' ; /// manually set back to -
            (p)->p_table->mintasor[3][3] = 'a' ; /// manually set back to -

            (p)->p_table->mintasor[4][0] = 'd' ; /// manually set back to -
            (p)->p_table->mintasor[4][1] = 'd' ; /// manually set back to -
            (p)->p_table->mintasor[4][2] = 'd' ; /// manually set back to -
            (p)->p_table->mintasor[4][3] = 'd' ; /// manually set back to -
            (p)->p_table->mintasor[4][4] = 'd' ; /// manually set back to -

            ///
            (p+1)->p_table->fal[0][0] = '.' ; /// manually set back to -
            (p+1)->p_table->fal[0][1] = '.' ; /// manually set back to -
            (p+1)->p_table->fal[0][2] = '.' ; /// manually set back to -
            (p+1)->p_table->fal[0][3] = 'd' ; /// manually set back to -
            (p+1)->p_table->fal[0][4] = '.' ; /// manually set back to -

            (p+1)->p_table->fal[1][0] = '.' ; /// manually set back to -
            (p+1)->p_table->fal[1][1] = '.' ; /// manually set back to -
            (p+1)->p_table->fal[1][2] = 'c' ; /// manually set back to -
            (p+1)->p_table->fal[1][3] = '.' ; /// manually set back to -
            (p+1)->p_table->fal[1][4] = 'e' ; /// manually set back to -

            (p+1)->p_table->fal[2][0] = '.' ; /// manually set back to -
            (p+1)->p_table->fal[2][1] = 'c' ; /// manually set back to -
            (p+1)->p_table->fal[2][2] = '.' ; /// manually set back to -
            (p+1)->p_table->fal[2][3] = '.' ; /// manually set back to -
            (p+1)->p_table->fal[2][4] = '.' ; /// manually set back to -

            (p+1)->p_table->fal[3][0] = 'b' ; /// manually set back to -
            (p+1)->p_table->fal[3][1] = 'c' ; /// manually set back to -
            (p+1)->p_table->fal[3][2] = 'e' ; /// manually set back to -
            (p+1)->p_table->fal[3][3] = '.' ; /// manually set back to -
            (p+1)->p_table->fal[3][4] = 'd' ; /// manually set back to -

            (p+1)->p_table->fal[4][0] = '.' ; /// manually set back to -
            (p+1)->p_table->fal[4][1] = '.' ; /// manually set back to -
            (p+1)->p_table->fal[4][2] = 'b' ; /// manually set back to -
            (p+1)->p_table->fal[4][3] = '.' ; /// manually set back to -
            (p+1)->p_table->fal[4][4] = '.' ; /// manually set back to -

            (p+1)->p_table->mintasor[0][0] = 'c' ; /// manually set back to -
            (p+1)->p_table->mintasor[1][0] = 'c' ; /// manually set back to -
            (p+1)->p_table->mintasor[1][1] = 'c' ; /// manually set back to -

            (p+1)->p_table->mintasor[2][0] = 'c' ; /// manually set back to -
            (p+1)->p_table->mintasor[2][1] = 'c' ; /// manually set back to -
            (p+1)->p_table->mintasor[2][2] = 'c' ; /// manually set back to -

            (p+1)->p_table->mintasor[3][0] = 'c' ; /// manually set back to -
            (p+1)->p_table->mintasor[3][1] = 'c' ; /// manually set back to -
            (p+1)->p_table->mintasor[3][2] = 'c' ; /// manually set back to -
            (p+1)->p_table->mintasor[3][3] = 'c' ; /// manually set back to -

            (p+1)->p_table->mintasor[4][0] = 'c' ; /// manually set back to -
            (p+1)->p_table->mintasor[4][1] = 'c' ; /// manually set back to -
            (p+1)->p_table->mintasor[4][2] = 'c' ; /// manually set back to -
            (p+1)->p_table->mintasor[4][3] = 'c' ; /// manually set back to -
            (p+1)->p_table->mintasor[4][4] = 'c' ; /// manually set back to -
*/
        }

        displayAll(g) ;
        for(int i=0;i<nrPlayer;i++){
            displayPlayer(p+i) ;
        }
    /// end of testing
}

#endif // HEAD_0XOTHER_H_INCLUDED
