#ifndef IA_H
#define IA_H
#include "GamePlay.h"
extern float pawnEvalWhite[8][8];

class IA
{
    public:
        GamePlay *game;
        IA();
        void minimaxRoot() {
        }
        void minimax (int depth,float alpha,float beta, bool isMaximisingPlayer) {
        }

        void evaluateBoard() {
        }
        virtual ~IA();

    protected:

    private:
};

#endif // IA_H
