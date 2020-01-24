#include "AlphaBetaPruning.h"
#include <iostream>
#include "evaluate.h"
#include <iostream>
using namespace std;
AlphaBetaPruning::AlphaBetaPruning(GamePlay& game, int& xdest, int& ydest){
	bestPosition = alphaBeta(game, xdest, ydest);
}


AlphaBetaPruning::~AlphaBetaPruning(){
}

Position* AlphaBetaPruning::alphaBeta(GamePlay& game, int& xdest, int& ydest){
	int bestValue = INT_MIN;
	int x = 0, y = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (game.piece_at(i, j) != nullptr && game.piece_at(i, j)) {
				for (Position* p : game.piece_at(i, j)->getPossibleMoves()) {
					GamePlay *b = new GamePlay(game);
					Piece* piece =b->piece_at(i, j);
					cout << "piece[1][1] = " <<game.piece_at(1,1)->color << endl;
					piece->move(p->x+1, p->y+1);
					int v = alphaBeta(*b, 2, INT_MIN, INT_MAX, false);
					if (v > bestValue) {
						bestValue = v;
						x = i;
						y = j;
						xdest = p->x;
						ydest = p->y;
					}
					delete &b;
				}
			}
		}
	}
	return new Position(x, y);
}


int AlphaBetaPruning::alphaBeta(GamePlay& game, int depth, int alpha, int beta, bool cpuTurn){

	if (depth <= 0) {
		return evaluateBoard(game);
	}

	if (cpuTurn) {
		int maxValue = INT_MIN;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (game.piece_at(i, j) != nullptr && game.piece_at(i, j)->color == BLACK) {
					for (Position* p : game.piece_at(i, j)->getPossibleMoves()) {
						GamePlay& gb = *new GamePlay(game);
						Piece* piece =gb.piece_at(i, j);
                        piece->move(p->x+1, p->y+1);
						int value = alphaBeta(gb, depth - 1, alpha, beta, !cpuTurn);
						maxValue = max(maxValue, value);
						alpha = max(alpha, value);
						delete &gb;
						if (beta <= alpha)
							break;
					}
				}
			}
		}
		return maxValue;
	}
	else {
		int minValue = INT_MAX;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (game.piece_at(i, j) != nullptr && game.piece_at(i, j)->color == WHITE) {
					for (Position* p : game.piece_at(i, j)->getPossibleMoves()) {
						GamePlay& gb = *new GamePlay(game);
						Piece* piece =gb.piece_at(i, j);
                        piece->move(p->x+1, p->y+1);
						int value = alphaBeta(gb, depth - 1, alpha, beta, !cpuTurn);
						minValue = min(minValue, value);
						beta = min(beta, value);
						delete &gb;
						if (beta <= alpha)
							break;
					}
				}
			}
		}
		return minValue;
	}
}



int AlphaBetaPruning::getAbsuluteValue(Piece* p,bool isWhite,int x,int y) {
    if (p->type=='p') return p->value*100+(isWhite ? wPawnTable[y][x]: bPawnTable[y][x]);
    else if (p->type=='r') return p->value*100+(isWhite ? wRookTable[y][x]: bRookTable[y][x]);
    else if (p->type=='n') return p->value*100+(isWhite ? wKnightTable[y][x]: bKnightTable[y][x]);
    else if (p->type=='b') return p->value*100+(isWhite ? wBishopTable[y][x]: bBishopTable[y][x]);
    else if (p->type=='q') return p->value*100+(isWhite ? wQueenTable[y][x]: bQueenTable[y][x]);
    else if (p->type=='k') return p->value*100+(isWhite ? wKingTableMid[y][x]: bKingTableMid[y][x]);
    return 0;
}

int AlphaBetaPruning::getPieceValue(Piece* p, int x, int y){
    int absoluteValue = this->getAbsuluteValue(p, p->color == WHITE,x, y);
    return p->color==WHITE?absoluteValue:-absoluteValue;
}

int AlphaBetaPruning::evaluateBoard(GamePlay& game){
    int totalEvaluation = 0;
    for (int i=0;i<8;i++)
    for (int j=0;j<8;j++) {
        if (game.piece_at(i,j)!= nullptr)
            totalEvaluation+= getPieceValue(game.piece_at(i, j), i, j);
    }
    return totalEvaluation;
}

int AlphaBetaPruning::max(int x, int y){
	return x >= y ? x : y;
}

int AlphaBetaPruning::min(int x, int y){
	return x <= y ? x : y;
}
//

