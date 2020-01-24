#ifndef ALPHABETAPRUNING_H
#define ALPHABETAPRUNING_H
#include "Position.h"
#include "Piece.h"

class GamePlay;

class AlphaBetaPruning{
public:
	AlphaBetaPruning(GamePlay& game, int& xdest, int& ydest);
	~AlphaBetaPruning();


	Position* getOptimalMove() {
		return bestPosition;
	}

	int getPieceValue(Piece* p, int x, int y);
	int getAbsuluteValue(Piece* p,bool isWhite,int x,int y);
	int evaluateBoard(GamePlay& game);

private:
    GamePlay game;
	Position* alphaBeta(GamePlay& game, int& xdest, int& ydest);
	int alphaBeta(GamePlay& game, int depth, int alpha, int beta, bool cpuTurn);
	Position* bestPosition;

	int max(int x, int y);
	int min(int x, int y);
};


#endif // ALPHABETAPRUNING_H
