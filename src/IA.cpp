#include "IA.h"

float pawnEvalWhite[8][8] = {
{0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
{5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0},
{1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0},
{0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5},
{0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0},
{0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5},
{0.5,  1.0, 1.0,  -2.0, -2.0,  1.0,  1.0,  0.5},
{0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}};

IA::IA()
{
    //ctor
}

IA::~IA()
{
    //dtor
}