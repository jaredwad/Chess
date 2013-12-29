/****************************************************************
 * board header file
 ***************************************************************/
#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "move.h"

class Board
{
  public:
  Board() : test(false), allocated(false) {resetBoard();};
   Piece & getPiece();

   // swaps two pieces on the board, and kills a piece
   void swap(Move & move);

   // pretty obvious...
   void resetBoard();

   void freeBoard();

   // getters
   bool getTest()           const { return test;};

   // a lonely setter
   bool setTest() { test = (!test); return test;};

   // Operators!!!
   Piece & operator [] (const Position & pos)
   {return *square[pos.getCol()][pos.getRow()];};
   friend ostream & operator << (ostream & out, const Board & rhs);

  private:
   bool test;
   bool allocated;
   Piece * square[8][8];
};

#endif //BOARD_H
