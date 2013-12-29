/**************************************************
 * PIECE
 * This contains the whole PIECE family, the parent PIECE
 * class, as well as the children classes, PAWN, KING, QUEEN, ROOK,
 * BISHOP, KNIGHT, and SPACE. Each knows if it's white or black, where
 * it is on the board, and what char it needs to display on the screen.
 * These pieces are smart.
 ***************************************************************/
#ifndef PIECE_H
#define PIECE_H

#include "position.h"
#include <vector>

#define WHITE_WHITE "\E[31;47m" // white square white piece
#define WHITE_BLACK "\E[30;47m" // white square black piece
#define BLACK_WHITE "\E[37;41m" // black square white piece
#define BLACK_BLACK "\E[30;41m" // black square black piece
#define RETURN      "\E[0m"     // returns to normal colors

/****************************
 *
 ***************************
struct Delta
{
   int row;
   int col;
};
*/
/****************************************************************
 * The mother of all pieces, she taught them well, told them how
 * use their operators, and put them to sleep at night. they just
 * grow up so fast!
 ***************************************************************/
class Piece
{
  public:
   Piece() {};
  Piece(bool white, int row, int col, char letter) :
   pos(row, col), letter(letter), fWhite(white) {};

   // basic display function called to set the pieces to the right
   // case in the test display
   void display() const
   {
      if (!fWhite)
         cout << (char)toupper(getLetter()); // to upper to make all
                                             // black pieces uppercase
      else
         cout << (char)tolower(getLetter()); // to lower to make all
                                             // white pieces lowercase
   };

   // getters
   char getLetter() const { return letter;       };
   virtual void getScore() = 0;
   virtual void getMoves() = 0;
   bool getColor()  const {return isWhiteSquare;};
   bool isWhite()   const {return fWhite;};


//   bool isValid(Delta & pMove);

   // tells the the piece which color square its on
   void setSquareColor(int row, int col)
   {
      isWhiteSquare = ((row + col) % 2 ? false : true);
    }
   
//   Position & operator = (const Delta * pMoves);
   
   // operators
   friend ostream & operator << (ostream & out, const Piece & rhs);

  protected:
//   vector <Delta> posMoves;
   Position pos;
   bool isWhiteSquare;
   char letter;
   bool fWhite;
//   Delta pMoves[10];
};

/****************************************************************
 * Classic pawn, the "grunt" piece, not worthless though. many a
 * game is won or lost due to good pawn placement
 ***************************************************************/
class Pawn : public Piece
{
  public:
  Pawn(bool white, int row, int col) :
   Piece(white, row, col, 'p') {};
   void getMoves() {};
   void getScore() {};
  private:
   bool fMoved;
};

/****************************************************************
 * Rooks are very valuable pieces. They move along in straight lines,
 * and can very easily change the dynamics of the game
 ***************************************************************/
class Rook : public Piece
{
  public:
  Rook(bool white, int row, int col) :
   Piece(white, row, col, 'R') {};
//   void getMoves();
   void getMoves() {};
   void getScore() {};
  private:
   bool fMoved;
//   delta pMoves[];
};

/****************************************************************
 * Knights, the gentlemen of the game. renowned for their chicivalry
 * the knights move in an "L" formation along the board
 ***************************************************************/
class Knight : public Piece
{
  public:
   Knight(bool white, int row, int col) :
   Piece(white, row, col, 'N') {};
   void getMoves() {};
   void getScore() {};
};

/****************************************************************
 * Bishops bring religion into the sport, converting their enemy
 * to death, a terrible way to die. they move in diagonal lines
 ***************************************************************/
class Bishop : public Piece
{
  public:
  Bishop(bool white, int row, int col) :
   Piece(white, row, col, 'B') {};
   void getMoves() {};
   void getScore() {};
};

/****************************************************************
 * The queen is the crowned jewel of the fleet. she can move in
 * straight lines in any direction.
 ***************************************************************/
class Queen : public Piece
{
  public:
  Queen(bool white, int row, int col) :
   Piece(white, row, col, 'Q') {};
   char getLetter() const { return letter;       };
   void getMoves() {};
   void getScore() {};
};

/****************************************************************
 * The king is the most important part of the game. if he dies its
 * game over jack. he can move one space in any direction
 ***************************************************************/
class King : public Piece
{
  public:
  King(bool white, int row, int col) :
   Piece(white, row, col, 'K') {};
   void getMoves()             {};
   void getScore()             {};
  private:
   bool fMoved;
};

/****************************************************************
 * SPACE! the final frontier. an empty piece, used to take up
 * space, and keep track of the board
 ***************************************************************/
class Space : public Piece
{
  public:
   Space() {};
   Space(bool white, int row, int col) :
   Piece(white, row, col, ' ') {};
   void getMoves()        {};
   void getScore()        {};
};

#endif //PIECE_H
