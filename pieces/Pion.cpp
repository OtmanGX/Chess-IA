#include "Pion.h"
#include "Dame.h"


void Pion::check_promotion(void){
    Dame* temp = NULL;
    int index = game->get_index(c_Col,c_Row);
    if(index < 0)
        return;
    if(color == BLACK && c_Row == 1){
        temp = new Dame("data/models/queen.dae","data/textures/black_queen.jpg",3,c_Column,c_Row, game, 'q');
        game->pieces.at(index) = temp;
    }else if(color == WHITE && c_Row == 8){
        temp = new Dame("data/models/queen.dae","data/textures/white_queen.jpg",2,c_Column,c_Row, game, 'q');
        game->pieces.at(index) = temp;
    }
}


void Pion::move(unsigned int col, unsigned int row){
    Piece::move(col,row);
    if(color == WHITE){
        if(game->grid_pieces[row-2][col-1] == BLACK && game->piece_at(col,row-1)->en_passant){
            game->remove_piece(col,row-1);
        }
    }else if(color == BLACK){
        if(game->grid_pieces[row][col-1] == WHITE && game->piece_at(col,row+1)->en_passant){
            game->remove_piece(col,row+1);
        }
    }
    for(int i = 0; i <= game->pieces.size()-1; i ++){
        game->pieces.at(i)->en_passant = false;
    }
    if(firstMove){
        firstMove = false;
        en_passant = true;
        printf("1st move\n");
    }
    has_moved = true;
    check_promotion();
}


void Pion::listMoves(void){
    game->clearMovesList();
    if(color == BLACK){
        if(!game->checkSquare(c_Col, c_Row-1)){ //if no piece is in front than space is free to move
            game->highlight_tile(c_Col, c_Row-1, 0);
            if(firstMove && !game->checkSquare(c_Col, c_Row-2)) //first move is the only time pawn can move two squares
                game->highlight_tile(c_Col, c_Row-2, 1);
        }
        //diagonal capture moves
        if(game->grid_pieces[c_Row-2][c_Col-2] == WHITE){
            game->highlight_tile(c_Col-1, c_Row-1, 2, true);
        }
        if(game->grid_pieces[c_Row-2][c_Col] == WHITE){
            game->highlight_tile(c_Col+1, c_Row-1, 3, true);
        }
        //en passant
        if(game->grid_pieces[c_Row-1][c_Col-2] == WHITE){
            if(game->piece_at(c_Col-1,c_Row)->value == 1 && game->piece_at(c_Col-1,c_Row)->en_passant){ //if it's a pawn after first move
                game->highlight_tile(c_Col-1, c_Row-1, 4, true);
            }
        }
        if(game->grid_pieces[c_Row-1][c_Col] == WHITE){
            if(game->piece_at(c_Col+1,c_Row)->value == 1 && game->piece_at(c_Col+1,c_Row)->en_passant){
                game->highlight_tile(c_Col+1, c_Row-1, 4, true);
            }
        }
    }else if(color == WHITE){
        if(!game->checkSquare(c_Col, c_Row+1)){
            game->highlight_tile(c_Col, c_Row+1, 0);
            if(firstMove && !game->checkSquare(c_Col, c_Row+2))
                game->highlight_tile(c_Col, c_Row+2, 1);
        }
        if(game->grid_pieces[c_Row][c_Col-2] == BLACK){
            game->highlight_tile(c_Col-1, c_Row+1, 2, true);
        }
        if(game->grid_pieces[c_Row][c_Col] == BLACK){
            game->highlight_tile(c_Col+1, c_Row+1, 3, true);
        }
        //en passant
        if(game->grid_pieces[c_Row-1][c_Col-2] == BLACK){
            if(game->piece_at(c_Col-1, c_Row)->value == 1 && game->piece_at(c_Col-1,c_Row)->en_passant){
                game->highlight_tile(c_Col-1, c_Row+1, 4, true);
            }
        }
        if(game->grid_pieces[c_Row-1][c_Col] == BLACK){
            if(game->piece_at(c_Col+1, c_Row)->value == 1 && game->piece_at(c_Col+1,c_Row)->en_passant){
                game->highlight_tile(c_Col+1, c_Row+1, 4, true);
            }
        }
    }
}
