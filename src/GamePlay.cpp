#include "GamePlay.h"
#include "Piece.h"

GLuint p,f,v,tile;

GamePlay::GamePlay(bool ia)
{
this->ia = ia;
}

GamePlay::GamePlay(const GamePlay& T)
{
gamestate = T.gamestate;
pieces = T.pieces;
for (int i=0;i<8;i++)
for (int j=0;j<8;j++) board[i][j]=T.board[i][j];
}

void GamePlay::initDLs(void){
    printf("%i\n",A);
    tile = glGenLists(1);
    glNewList(tile,GL_COMPILE);
    glBegin(GL_QUADS);
        glVertex3f(1,0,1);
        glVertex3f(-1,0,1);
        glVertex3f(-1,0,-1);
        glVertex3f(1,0,-1);
    glEnd();
    glEndList();
}

void GamePlay::drawGrid(void){
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glColor4f(1,1,1,0);
    int counter = 0;
    for(int i = 0; i <= 7; i++){
        for(int j = 0; j <= 7; j++){
            counter++;
            glLoadName(100+counter);
            glPushMatrix();
            glColor4f(1,1,1,0);
            glTranslatef(-7+(i*2),-0.97,(-7+(j*2)));
            glCallList(tile);
            glPopMatrix();
        }
    }
    for(int k = 0; k < sizeof(highlighted_tiles)/sizeof(highlighted_tiles[0]); k++){
        if(highlighted_tiles[k] != 0){
            int row = highlighted_tiles[k][0]-1;
            int col = highlighted_tiles[k][1]-1;
            if(col >= 0 && col >= 0 && col <= 7 && col <= 7){
                glLoadName(165);
                glPushMatrix();
                glColor4f(1,0,0,0.5);
                glTranslatef(-7+(col*2),-0.96,-(-7+(row*2)));
                glCallList(tile);
                glColor4f(1,0,0,1);
                glBegin(GL_LINES);
                glVertex3f(1,0,1);
                glVertex3f(0.4,0,1);
                glVertex3f(1,0,-0.9);
                glVertex3f(0.4,0,-0.9);
                glVertex3f(-1,0,1);
                glVertex3f(-0.4,0,1);
                glVertex3f(-1,0,-0.9);
                glVertex3f(-0.4,0,-0.9);
                glVertex3f(-0.9,0,1);
                glVertex3f(-0.9,0,0.4);
                glVertex3f(-0.9,0,-1);
                glVertex3f(-0.9,0,-0.4);
                glVertex3f(0.9,0,1);
                glVertex3f(0.9,0,0.4);
                glVertex3f(0.9,0,-1);
                glVertex3f(0.9,0,-0.4);
                glEnd();
                glPopMatrix();
            }
        }
    }
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void setShaders(void){
    char *vs = NULL,*fs = NULL;

    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);

    vs = textFileRead("shaders/swag.vert");
    fs = textFileRead("shaders/swag.frag");

    const char *vv = vs;
    const char *ff = fs;

    glShaderSource(v,1,&vv,NULL);
    glShaderSource(f,1,&ff,NULL);

    free(vs);free(fs);

    glCompileShader(v);
    glCompileShader(f);

    p = glCreateProgram();

    glAttachShader(p,f);
    glAttachShader(p,v);

    glLinkProgram(p);
    glUseProgram(p);
}

Piece* GamePlay::piece_at(int col, int row){
    for(int i = 0; i <= pieces.size()-1; i++){
        if(pieces.at(i)->c_Row == row && pieces.at(i)->c_Col == col){
            return pieces.at(i);
        }
    }
}

void GamePlay::remove_piece(int col, int row){
    Piece* temp = piece_at(col, row);
    auto it = std::find(pieces.begin(), pieces.end(), temp);
    side_pieces.push_back(temp);
    if(it != pieces.end()){
        pieces.erase(it);
        board[row-1][col-1] = 0;
    }
}


bool GamePlay::checkSquare(int col, int row){
    if(board[row-1][col-1] >= 1){
        return true;
    }
    return false;
}

int GamePlay::get_index(int col, int row){
    auto it = std::find(pieces.begin(), pieces.end(), piece_at(col,row));
    if (it == pieces.end()){
        return -1;
    }else{
        return std::distance(pieces.begin(), it);
    }
}

void GamePlay::highlight_tile(int col, int row,unsigned int tile, bool captured_mode){
    if((col <= 8 && row <= 8 && col > 0 && row > 0) && ((gamestate == WHITE_TURN && board[row-1][col-1] != WHITE) ||(gamestate == BLACK_TURN && board[row-1][col-1] != BLACK))){
        highlighted_tiles[tile][0] = row;
        highlighted_tiles[tile][1] = col;
    }
}

void GamePlay::highlight_tile_k(int col, int row,unsigned int tile, bool captured_mode){
    highlight_tile(col, row, tile, captured_mode);
}

void GamePlay::clearMovesList(void){
    memset(highlighted_tiles,0,sizeof(highlighted_tiles[0][0])*(sizeof(highlighted_tiles)/sizeof(highlighted_tiles[0]))*2); //clear the array
}

bool GamePlay::isCheckMate() {
    int count = 0;
	Piece* actPiece;
	for(int row =0; row <=7; row++)
	{
		for(int col =0;col <=7; col++)
		{
			if(this->checkSquare(col, row))
			{
				actPiece = this->piece_at(col, row);
				if(actPiece->color == WHITE && this->gamestate==WHITE_TURN | actPiece->color == BLACK && this->gamestate==BLACK_TURN)
				{
					count+=actPiece->getPossibleMoves().size();
				}
			}
		}
	}
	if (count==0) return true;
	return false;
}


GamePlay::~GamePlay()
{
    //dtor
}
