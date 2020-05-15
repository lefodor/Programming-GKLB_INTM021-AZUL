#ifndef HEAD_01STRUCT_H_INCLUDED
#define HEAD_01STRUCT_H_INCLUDED

/// structs
struct Korong{
    int tiles_on_korong[5] ;
    int korong_index ;
};

struct Game{
    int nrKorongs ;
    Korong* p_Korongs ;
    int* p_tiles_in_zsak ;
    int* p_tiles_on_table ;
    int* p_tiles_dropped ;
    char** pattern ;
};

struct Table{
    char** mintasor;
    char** fal ;
    char** tiles_on_padlo;
};

struct Player{
    int points ;
    string name ;
    bool mintasorfull=false;
    Table table ;
    Table* p_table=&table ;
};

struct Results{
    int* nr ;
    int* pts ;
    int* cntfullrows;
    int* rankp ;
};

#endif // HEAD_01STRUCT_H_INCLUDED
