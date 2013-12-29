/**************************************************
 * CHESS
 * This is the main hub of the game which calls and directs all of the other
 * functions and objects.
 ***************************************************************/
#ifndef CHESS_H
#define CHESS_H

#include <vector>
#include <string>
#include "board.h"
#include "move.h"

class Chess
{
  public:
   //Constructor
  Chess() : numMoves(0), fQuit(false) {};
   
   void interact(Move & move);
   void displayOptions();
   void displaySmith();

   // getters
   void getFileName() { cin >> fileName; };
   int getNumMoves() const { return numMoves; };

   void read();
   bool readFile();
   bool parse();
   void write();
   bool writeFile();
   bool quit()        { return fQuit;    };
   
   Chess & operator ++ (int postfix); // advance the game
   friend ostream & operator << (ostream & out, const Chess & rhs);
   //friend ostream & operator << (ostream & out, const Move & rhs)
   //  {
   //  out << rhs;
   //  return out;
   //};
   
   
  private:
   Board board;
   Move move;
   vector <Move> moves;
   int numMoves;
   string fileName;
   
   bool fQuit;
};

#endif //CHESS_H
