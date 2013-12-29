/***********************************************************************
* POSITION
* This is how each square and each piece knows where it is.
************************************************************************/

#include "position.h"
#include <cassert>
#include <iostream>
#include <sstream>
using namespace std;

/*********************************************************
 * IS VALID
 * This will tell if the position is withing the boound of
 * the board.
 ********************************************************/
bool Position::isValid() const
{
   //IF it's outside of the board...
   if (row > 7 || row < 0 ||
       col > 7 || row < 0)
      //FAIL
      return false;
   //ELSE
   else
      //WIN!
      return true;
}

/*********************************************************
 * OPERATOR >>
 *********************************************************/
istream & operator >> (istream & in, Position & pos)
{

   // I don't think this is getting called!!!
   int tempRow;
   char tempCol;
   cout << "called extraction opperator!\n";
   in >> tempCol >> tempRow;
   cout << tempRow << tempCol << endl;;

   pos.row = tempRow;
   pos.col = (int)tempCol;
   
   return in;
}

/************************************************************
 * INSERTION OPERATOR
 * This is used in WRITE FILE to make sure that the moves are 
 * being put into the file in smith notation
 ***********************************************************/
ostream & operator << (ostream & out, const Position & pos)
{
   //INSERT the coordinates
   out  << (char)(pos.getCol() + 'a') << pos.getRow() + 1;

   //I'm out!
   return out;
}

/*************************************************************
 * ASSIGNMENT OPERATOR
 * This allows us to compare and assign strings into ints so
 * so the program can work with it.
 ************************************************************/
Position & Position::operator = (const char *s)
{
   // reads the input into our position, the first number being the column
   // and the second into row
   col = (*s - 'a');
   row = (*(s+1) - '2');

   //I'd like to return this....
   return *this;
}

/***************************************************************
 * COMPARISON OPERATOR
 * This will return TRUE or FALSE, like any assignment operator should
 ***************************************************************/
bool Position::operator == (const Position & rhs) const
{
   //IF they are the same...
   if (col == rhs.col && row == rhs.row)
      //WIN!
      return true;
   //IF not
   else
      //FAIL
      return false;
}

