#ifndef ALPHABETAPRUNING_H
#define ALPHABETAPRUNING_H
#include "GamePlay.h"
#include "Position.h"

class AlphaBetaPruning{
public:
	AlphaBetaPruning(GamePlay& board, int& xdest, int& ydest);
	~AlphaBetaPruning();


	Position* getOptimalMove() {
		return bestPosition;
	}

private:
	Position* alphaBeta(GamePlay& board, int& xdest, int& ydest);
	int alphaBeta(GamePlay& board, int depth, int alpha, int beta, bool cpuTurn);
	Position* bestPosition;

	int max(int x, int y);
	int min(int x, int y);
};


#endif // ALPHABETAPRUNING_H
