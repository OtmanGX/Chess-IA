#ifndef TOUR_H
#define TOUR_H
#include "Piece.h"

class Tour : public Piece{
    public:
        Tour(const char* modelFile, const char* textureFile,int textureNum,char col, int row, GamePlay *game, char type) : Piece(modelFile, textureFile, textureNum,col,row, game, type){
            printf("Rook loaded\n");
            value = 5;
        };
        ~Tour();
        void listMoves(void);
};

#endif // PION_H
