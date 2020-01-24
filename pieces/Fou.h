#ifndef FOU_H
#define FOU_H
#include "Piece.h"

class Fou : public Piece{
    public:
        Fou(const char* modelFile, const char* textureFile,int textureNum,char col, int row, GamePlay *game, char type) : Piece(modelFile, textureFile, textureNum,col,row, game, type){
            printf("Bishop loaded\n");
            value = 3;
        };
        ~Fou();
        void listMoves(void);
};

#endif // PION_H
