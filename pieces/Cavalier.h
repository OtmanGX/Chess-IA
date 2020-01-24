#ifndef CAVALIER_H
#define CAVALIER_H
#include "Piece.h"

class Cavalier : public Piece{
    public:
        Cavalier(const char* modelFile, const char* textureFile,int textureNum,char col, int row, GamePlay *game, char type) : Piece(modelFile, textureFile, textureNum,col,row, game, type){
            printf("Knight loaded\n");
            value = 3;
            var_swag = 0.0f;
        };
        ~Cavalier();
        void draw(bool side_piece = false, float x = 0.0f, float y = 0.0f);
        void listMoves(void);
};

#endif // PION_H
