/***********************************************************************
 * this simply keeps track of the board, and all the pieces in each square
************************************************************************/

#include "board.h"
#include <cassert>
#include <cstdlib>

void Board::freeBoard()
{
   if (allocated == true)
   {
      for (int i = 0; i < 8; i++)
      {
         for (int p = 0; p < 8; p++)
         {
            delete square[i][p];
         }
      }
   }
}

/************************************************************************
 * Board::resetBoard() resets the board, both at the begining of the game,
 * and when a file is read in. a fresh start at life.
 ***********************************************************************/
void Board::resetBoard()
{
   // just to be sure
//   freeBoard();

   // for all middle rows
   for (int i = 2; i < 6; i++)
   {
      // for all columns
      for (int p = 0; p < 8; p++)
         square[i][p] = new Space(false, i, p); // create a new pawn
   }
   // for each column
   for (int i = 0; i < 8; i++)
   {

      square[6][i] = new Pawn(false,  1, i); // white pawn
      square[1][i] = new Pawn(true, 6, i); // black pawn
   }
   square[7][0] = new Rook  (false, 0, 0); // white rook
   square[7][1] = new Knight(false, 0, 1); // white knight
   square[7][2] = new Bishop(false, 0, 2); // white bishop
   square[7][3] = new King  (false, 0, 3); // white king
   square[7][4] = new Queen (false, 0, 4); // white queen
   square[7][5] = new Bishop(false, 0, 5); // white bishop
   square[7][6] = new Knight(false, 0, 6); // white knight
   square[7][7] = new Rook  (false, 0, 7); // white rook

   square[0][0] = new Rook  (true, 7, 0); // black rook
   square[0][1] = new Knight(true, 7, 1); // black knight
   square[0][2] = new Bishop(true, 7, 2); // black bishop
   square[0][3] = new King  (true, 7, 3); // black king
   square[0][4] = new Queen (true, 7, 4); // black queen
   square[0][5] = new Bishop(true, 7, 5); // black bishop
   square[0][6] = new Knight(true, 7, 6); // black knight
   square[0][7] = new Rook  (true, 7, 7); // black rook

   allocated = true;
}
/************************************************************************
 * operator << overloaded to allow a much simpler way to output the board
 ***********************************************************************/
ostream & operator << (ostream & out, const Board & rhs)
{
   system("clear");

   // test display
   if (rhs.test == true)
   {
   // display the header for the board
      out << "  abcdefgh\n";
      for (int i = 7; i >= 0; i--)
      {
         out << i+1 << ' ';
         for ( int p = 0; p < 8; p++)
         {
            rhs.square[i][p]->display();
         }
         out << endl;
      }
   }

   // real display
   else if (rhs.test == false)
   {
      // header
      out << "   a  b  c  d  e  f  g  h \n";

      // for every row
      for (int row = 7; row >= 0; row--)
      {
         out << row + 1 << ' ';

         // for every column
         for ( int col = 0; col < 8; col++)
         {
            // gets the color of the square behind the piece...
            rhs.square[row][col]->setSquareColor(row, col);

            // and outputs it
            out << * rhs.square[row][col];
         }
         out << ' ' << row+1 << endl;
      }
      out << "   a  b  c  d  e  f  g  h \n";
   }
   return out;
}

/************************************************************************
 * Board::swap() Puts the source piece into the destination and destroys the
 * destination piece, initializing a new space at the source location
 ***********************************************************************/
void Board::swap(Move & move)
{
   // new piece created to preform the swap
   Piece *tempPiece = square[move.getDes().getRow()]
      [move.getDes().getCol()];

   //Capturing
   if (tempPiece->getLetter() != ' ')
   {
      // MURDER!!!
      square[move.getDes().getRow()][move.getDes().getCol()] =
         square[move.getSrc().getRow()][move.getSrc().getCol()];

      // from the ashes rises a shiny new piece
      square[move.getSrc().getRow()][move.getSrc().getCol()]
         = new Space(false,move.getSrc().getRow(),move.getSrc().getCol() );
   }
   //Normal move, simple swap
   else
   {
   square[move.getDes().getRow()][move.getDes().getCol()] =
      square[move.getSrc().getRow()][move.getSrc().getCol()];
   
   square[move.getSrc().getRow()][move.getSrc().getCol()] = tempPiece;
   }
}
