#ifndef PION_H
#define PION_H
#include "Piece.h"


class Pion : public Piece {
    public:
        bool firstMove = true;

        Pion(const char* modelFile, const char* textureFile,int textureNum,char col, int row, GamePlay *game, char type) : Piece(modelFile, textureFile, textureNum,col,row, game, type){
            printf("Pawn loaded\n");
            value = 1;
        };
        ~Pion();
        void listMoves(void);
        void move(unsigned int col, unsigned int row);
        void check_promotion(void);
        std::vector<Position*> getPossibleMoves();
};

#endif // PION_H
