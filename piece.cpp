#include<iostream>
#include"piece.h"
using namespace std;

// overladed to ease displaying the board
ostream & operator << (ostream & out, const Piece & rhs)
{
   if (rhs.isWhite() && rhs.getColor())
      out << WHITE_WHITE                    << ' '
//          << (char)toupper(rhs.getLetter()) << ' ';
          << rhs.getLetter() << ' ';
   else if (rhs.isWhite() && !rhs.getColor())
      out << BLACK_WHITE     << ' '
          << rhs.getLetter() << ' ';
   else if (!rhs.isWhite() && rhs.getColor())
      out << WHITE_BLACK     << ' '
          << rhs.getLetter() << ' ';
   else if (!rhs.isWhite() && !rhs.getColor())
      out << BLACK_BLACK     << ' '
          << rhs.getLetter() << ' ';
   out << RETURN;
   return out;
}
/*
bool Piece::isValid(Delta & pMove)
{
   pMove.row += pos.getRow();
   pMove.col += pos.getCol();
   if (pMove.row <= 7 &&
       pMove.row >= 0 &&
       pMove.col <= 7 &&
       pMove.col >= 0 
       
       )

      
//       fWhite != isWhite)
      return true;
   else
      return false;
       
}
*/
/*
void Rook::getMoves(Delta pMoves[], int & numPmoves)
{
   pMoves[0] = {0, 1};
   pMoves[1] = {-1,0};
   pMoves[2] = {1, 0};
   pMoves[3] = {0,-1};
   numPmoves = 4;
   for (int i = 0; i < 4; i++)
   {
      if(isValid(pMoves[i]));
   }
}
*/
