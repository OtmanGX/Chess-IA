#include "Piece.h"
#include "Cavalier.h"
#include "Roi.h"
#include "Tour.h"
#include "Dame.h"
#include "Pion.h"
#include "Fou.h"
#include "iostream"
//Window size and position
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_POS_X 50
#define WINDOW_POS_Y 50
using namespace std;

/**
    Real-time variables
*/
bool    inGame = false, verify = false;
int     selectedRow = 1, selectedCol = 1;
int     moveToRow = 1, moveToCol = 1;
bool    selected = false;
bool    board_rotating = true;
int     rotation = 0;
bool    check = false, checkMate = false;
bool    closeGame = false;
bool	needPromote = false;

/**
    Variables for perspective function
*/
GLfloat     fovy = 50.0, zNear = 0.1, zFar = 20.0;
/**
    Variables for managing view
*/
GLfloat     screen_ratio, zoomOut = 2;


float lpos[4] = {1,0.5,1,0};
int screen_width = 850,screen_height = 850;

//Some piece variables
Piece* board;
Piece* selected_piece = NULL;
GamePlay *game;


void showWord( int x, int y, string word)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-screen_width/2, screen_width/2, -screen_height/2, screen_height/2, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    int l,i;

    l=word.length(); // see how many characters are in text string.
    glRasterPos2i(x, y); // location to start printing text
    glColor3f(0,0,0);
    for( i=0; i < l; i++) // loop until i is greater then l
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, word[i]); // Print a character on the screen
    }
}

void mainMenu() {
    showWord(-150, 100, "** Appuyez sur N Pour commencer le jeu");
    showWord(-150, 50, "** Appuyez sur L Pour charger une partie");
    showWord(-150, 0, "** Appuyez sur X Pour sortir");
}

//helper function to print grid 2d array variable
void print_grid_pieces(void){
    for(int row = 0; row <= 7; row++){
        for(int col = 0; col <= 7; col++){
            int element = game->grid_pieces[row][col];
            if(element > 0){
                printf("[%i]",element);
            }else if(element == 0){
                printf("[0000]");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void loadPieces(){
    game->pieces.push_back(new Roi("data/models/king.dae","data/textures/white_king.jpg",0,'e',1, game, 'k'));
    game->pieces.push_back(new Roi("data/models/king.dae","data/textures/black_king.jpg",1,'e',8, game, 'k'));
    game->pieces.push_back(new Dame("data/models/queen.dae","data/textures/white_queen.jpg",2,'d',1, game, 'q'));
    game->pieces.push_back(new Dame("data/models/queen.dae","data/textures/black_queen.jpg",3,'d',8, game, 'q'));

    for(int i = 0; i <= 1; i++){
        game->pieces.push_back(new Tour("data/models/rook.dae","data/textures/white_rook.jpg",4,column[i*7],1, game, 'r'));           //white rooks
        game->pieces.push_back(new Tour("data/models/rook.dae","data/textures/black_rook.jpg",5,column[i*7],8, game, 'r'));           //black rooks
        game->pieces.push_back(new Fou("data/models/bishop.dae","data/textures/white_bishop.jpg",6,column[(i*3)+2],1, game, 'b')); //white bishops
        game->pieces.push_back(new Fou("data/models/bishop.dae","data/textures/black_bishop.jpg",7,column[(i*3)+2],8, game, 'b')); //black bishops
        game->pieces.push_back(new Cavalier("data/models/knight.dae","data/textures/white_knight.jpg",8,column[(i*5)+1],1, game, 'n')); //white knights
        game->pieces.push_back(new Cavalier("data/models/knight.dae","data/textures/black_knight.jpg",9,column[(i*5)+1],8, game, 'n')); //black knights
    }
    for(int i = 0; i <= 7; i++){
        game->pieces.push_back(new Pion("data/models/pawn.dae","data/textures/white_pawn.jpg",10,column[i],2, game, 'p'));            //white pawns
        game->pieces.push_back(new Pion("data/models/pawn.dae","data/textures/black_pawn.jpg",11,column[i],7, game, 'p'));            //black pawns
    }
    board = new Piece("data/models/board.dae","data/textures/board.jpg",12,'z',0, game, 'u');                                   //chess board
//    board = new Piece("data/models/chessBoard.mtl","data/textures/chessBoard.jpg",12,'z',0, game);                                   //chess board
    printf("loaded starting pieces\n");
}

void drawBoard(){
    board->draw();
}

void drawPieces(){
    for(int i = 0; i <= game->pieces.size()-1; i++){ //draw pieces on the board
        glLoadName(1+i);
        game->pieces.at(i)->draw();
    }
    int white_counter = 0, black_counter = 0;
    for(int j = 0; j < game->side_pieces.size(); j++){ //draw dead pieces on the side
        Piece* temp = game->side_pieces.at(j);
        if(temp->color == BLACK){
            if(black_counter <= 7){	//front row
                temp->draw(true, -11.3, 8-(2*black_counter));
            }else{			//back row
                temp->draw(true, -13.3, 8-(2*(black_counter-8)));
            }
            black_counter++;
        }else if(temp->color == WHITE){
            if(white_counter <= 7){	//front row
                temp->draw(true, 11.2, 8-(2*white_counter));
            }else{			//back row
                temp->draw(true, 13.2, 8-(2*(white_counter-8)));
            }
            white_counter++;
        }
    }
}


void newGame() {
    game->initDLs();
    loadPieces();
    game->gamestate = WHITE_TURN; //white starts first
    inGame = true;
}


void initGL(void){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(10);
}

void resize(int w, int h){
    if(h == 0)
        h = 1;
    float ratio = w*1.0f/h;
    screen_width = w;
    screen_height = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,w,h);
    gluPerspective(45,ratio,1,1000);
    glMatrixMode(GL_MODELVIEW);
}

void draw(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (inGame) {
    initGL();
    glLoadIdentity();
    gluLookAt(0,25,15,
    0,0,0,
    0,1,0);
    glLightfv(GL_LIGHT0,GL_POSITION,lpos);

    glLoadName(99);
    drawBoard();
    game->drawGrid();
    drawPieces();
    resize(screen_width, screen_height);

    } else mainMenu();
    glutSwapBuffers();
}

void keyEvents(unsigned char key, int x, int y){
    switch(key){
        case 27: //escape key
            glDetachShader(p,v);
            glDetachShader(p,f);
            glDeleteShader(v);
            glDeleteShader(f);
            glDeleteProgram(p);
            for(int i = 0; i < game->pieces.size(); i++){
                free(game->pieces.at(i));
            }
            printf("shaders freed\n");
            exit(0);
            break;
        case 'n':
        case 'N':
        if (!inGame) newGame();
        break;
        case 'x':
        case 'X':
        exit(0);
        break;

    }

}

void specialKeys(int key, int x, int y){
    //no events to handle here yet...
}


//calls pick function on the piece at the position specified
void pickPiece(int col, int row){
    Piece* piece = game->piece_at(col,row);
    if(piece != NULL){
        if((piece->color == BLACK && game->gamestate == BLACK_TURN) || (piece->color == WHITE && game->gamestate == WHITE_TURN)){
            for(int j = 0; j <= game->pieces.size()-1; j++){
                game->pieces.at(j)->unpick();
            }
            piece->pick();
            selected_piece = piece;
        }
    }
}

//swaps turns from white to black or black to white
void swap_turns(void){
    if(game->gamestate == WHITE_TURN){
        game->gamestate = BLACK_TURN;
    }else if(game->gamestate == BLACK_TURN){
        game->gamestate = WHITE_TURN;
    }
}

//processes which piece is clicked and which tile is clicked
void list_hits(GLint hits, GLuint *names){
    for(int i = 0; i <= game->pieces.size()-1; i++){
        game->pieces.at(i)->unpick();
    }
    bool move_pressed = false;
    for (int i = 0; i < hits; i++){
        int name = (GLubyte)names[i*4+3];
        if(name == 165){
            move_pressed = true;
            break;
        }
        if(name >= 101){
            name -= 100;
            grid_row = 9-(name%8);
            if(grid_row == 9)
                grid_row = 1;
            grid_col = ceil((float)name/8.0f);
            grid_column = column[grid_col-1];
            printf("row = %i col = %i name = %i\n",grid_row,grid_col,name);
        }
    }
    if(move_pressed){
        if((game->grid_pieces[grid_row-1][grid_col-1] == BLACK && game->gamestate == WHITE_TURN) || (game->grid_pieces[grid_row-1][grid_col-1] == WHITE && game->gamestate == BLACK_TURN)) //if the possible move is a capture move
            game->remove_piece(grid_col,grid_row); //... then remove the piece that's eaten
        selected_piece->move((unsigned int)grid_col,(unsigned int)grid_row);
        swap_turns();
        game->clearMovesList();
        selected_piece->unpick();
    }
    pickPiece(grid_col,grid_row);
}

//sets up gl select mode
void gl_select(int x, int y){
    GLuint buff[64] = {0};
    GLint hits, view[4];

    glSelectBuffer(64, buff);

    glGetIntegerv(GL_VIEWPORT, view);

    glRenderMode(GL_SELECT);

    glInitNames();

    glPushName(0);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix(x,y,1.0,1.0,view);
    gluPerspective(45,1.0,0.0001,1000.0);

    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
    draw();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    hits = glRenderMode(GL_RENDER);

    list_hits(hits,buff);

    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y){
    if(state == GLUT_DOWN){
        gl_select(x,screen_height-y);
    }
}


int main(int argc, char **argv){

    glutInit(&argc,argv);
    glutInitWindowPosition(-1,-1); //starts at the default position
    glutInitWindowSize(screen_width,screen_height);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(screen_width, screen_height);
//    glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
    glutInitContextVersion(2, 1);
    glutCreateWindow("Chess 3D");
//    inGame = true;
    glewExperimental = GL_TRUE;
    glewInit();
    initGL();
    game = new GamePlay;

//    glClearColor(0.8, 0.8, 0.8, 1);
    glClearColor(0.5f, 0.62f, 0.81f, 1.0f);
    glutDisplayFunc(draw);
    glutIdleFunc(draw);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyEvents);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 1;
}
