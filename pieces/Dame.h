#ifndef DAME_H
#define DAME_H
#include "Piece.h"

class Dame : public Piece{
    public:
        Dame(const char* modelFile, const char* textureFile,int textureNum,char col, int row, GamePlay *game, char type) : Piece(modelFile, textureFile, textureNum,col,row, game, type){
            printf("Queen loaded\n");
            value = 9;
        };
        ~Dame();
        void listMoves(void);
};

#endif // PION_H
