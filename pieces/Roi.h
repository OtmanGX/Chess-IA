#ifndef ROI_H
#define ROI_H
#include "Piece.h"

class Roi : public Piece{
    public:
        Roi(const char* modelFile, const char* textureFile,int textureNum,char col, int row, GamePlay* game, char type) : Piece(modelFile, textureFile, textureNum,col,row, game, type){
            printf("King loaded\n");
            value = 9999;
        };
        ~Roi();
        void listMoves(void);
        void move(unsigned int col, unsigned int row);
};

#endif // PION_H
