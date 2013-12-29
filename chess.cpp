/***********************************************************************
* CHESS
* This is the main hub of the game which calls and directs all of the other
* functions and objects.
************************************************************************/

#include "board.h"
#include "move.h"
#include "piece.h"
#include "chess.h"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream> //For reading files
//using namespace std;

/**********************************************************
 * READ
 * This function calls all necessary read functions, such as
 * readFile(), parse(), and getFileName(). That's right, we
 * taught a program to read.
 *********************************************************/
void Chess::read()
{
   board.resetBoard();
   numMoves = 0;
   //PROMPT for the file names
   cout << "FileName: ";
   getFileName();
   //Re-initialize the board
   board.resetBoard();
   //If reading is successfull...
   if (readFile())
   {
      //IF it fails the pasrsing...
      if (parse()); // left empty because its the most common case
      else
         //DISPLAY error message
         cout << "Error parsing file " << fileName << endl;
   }
   //IF reading fails...
   else
   {
      //SEND to summer school
      cout << "Error reading file " << fileName << endl;
   }
}


/********************************************************
 * READ FILE
 * This will open the file specified by the user and read
 * in the moves into a vector of moves the class type 'move'
 *******************************************************/
bool Chess::readFile()
{
   //OPEN the file
   ifstream fin(fileName.c_str());
   //IF it won't open...
   if (fin.fail())
   {
      //DISPLAY an error message
      cout << "Error reading file: \'"
           << fileName
           << "\'\n";
      //Mission failure
      return false;
   }

   // Sets moves equal to the read in input line by line
   while (fin >> move)
   {
      //Load the mvoe itnto the vector
      moves.push_back (move);
      //INCREMENT the nukber of moves
      numMoves++;
   }
   //CLOSE the file (important!)
   fin.close();

   //Mission accomplished
   return true;
}

/*********************************************************
 * PARSE
 * Sends each move one by one to move() and checks to make
 * sure each move is legal.
 ********************************************************/
bool Chess::parse()
{
   //Go through each move
   for (int i = 0; i < numMoves; i++)
   {
      Position source = moves[i].getSrc();
      Position dest   = moves[i].getDes();
      // Checks source coordinates
      if (!source.isValid())
      {
         //DISPLAY error message
         cout << "Error parsing file " << fileName
              << " with move \'"        << moves[i]
              << "\': Invalid format of source coordinates\n";
         numMoves = 0;
         //FAIL
         return false;
      }

      // Checks the destination coordinates
      else if (!dest.isValid())
      {
         //DISPLAY error message
         cout << "Error parsing file "  << fileName
              << " with move \'"        << moves[i]
              << "\': Invalid format of destination coordinates\n";
         numMoves = 0;
         //FAIL
         return false;
      }
      else
      {
         //Let's try implementing it
         try
         {
            // Runs each move through the move function
            board.swap(moves[i]);
         }
         //If something goes wrong...
         catch (char key)
         {
            //DISPLAY error message
            cout << "Error parsing file "  << fileName
                 << " with move \'"        << moves[i];
            switch (key)
            {
               case 's':
                  cout << "\': No piece in the source "
                       << "coordinates position\n";
                  numMoves = 0;
                  break;
               case 'e':
                  cout << "\': Unknown promotion piece specification\n";
                  numMoves = 0;
                  break;
            }
            //FAIL
            return false;
         }
      }
   }
   //WIN! High fives all around!
   return true;
}
/********************************************************
 * WRITE
 * Prompts the user for a file to write then writes the
 * moves into it using smith notation.
 *******************************************************/
void Chess::write()
{
   //PROMPT for the filename
   cout << "To save a game, please specify the filename.\n"
        << "    To quit without saving a file, just press <enter>\n";
   //GET  the file name
   getFileName();
   //IF there's something
   if (fileName != " ")
   {
      if (writeFile()); // most common case first
      else
         cout << "Error saving file\n";
   }
}

/*******************************************************
 * WRITE FILE 
 * Writes the file as a list of smith notation moves
 ******************************************************/
bool Chess::writeFile()
{
   //OPEN the file!
   ofstream fout(fileName.c_str());

   //IF opening the file doesn't work
   if (fout.fail())
      //FAIL!
      return false;

   //FOR every move...
   for (int i = 0; i < numMoves; i++)
   {
      //WRITE the moves to the file
      fout << moves[i]     << ' ';
      fout << moves[i + 1] << endl;
      i++;
   }

   //CLOSE the file.
   fout.close();

   //WIN!
   return true;
}

/*********************************************************
 * DISPLAY OPTIONS
 * This will show the user the possible options he or she has.
 * This is really nothing more thna a big fancy "hello world".
 ********************************************************/
void Chess::displayOptions()
{
   //DISPLAY the options
   cout << "Options: \n"
        << "?       Display these options\n"
        << "b2b4    Specify a move using the Smith notation\n"
        << "read    Read a saves game from a file\n"
        << "help    Display all possible moves for a given piece\n"
        << "test    Simple display for test purposes\n"
        << "rank    Who is winning? What is the rank\n"
        << "quit    Leave the game. You will be prompted to save\n"
        << "smith   A brief explanation of smith notation\n";
          // ^ Extra feature!
}

/***********************************************************
 * DISPLAY SMITH
 * Not everyone knows what smith notation is. In order to make our
 * game more user friendly, we included some simple instructions
 * on how smith notation works in relation to the program.
 * Again, this is just a big "hello world".
 **********************************************************/
void Chess::displaySmith()
{
   //DISPLAY the instructions
   cout << "Smith notation works by specifying the source and destination\n"
        << "coordinates for any given piece (such as 'b2b4' to move a pawn).\n"
        << "For convienience, the coordinates have been labeled on the\n"
        << "margins of the board.\n\n"
        << "Sometimes you may want to execute a special move such as\n"
        << "castling. In Smith notation, it is declared by adding a letter\n"
        << "to the end of the coordinates (such as 'e1b1c').\n"
        << "here is a list of the special moves and their corresponding\n"
        << "letters for smith notation:\n"
        << "Castling:       c\n"
        << "En-passant:     e\n"
        << "Pawn promotion: p\n"
        << "Capturing takes the letter of the target piece\n\n"
        << "Have fun, and good luck! -Adam Harris and Jared Wadsworth\n";
}

/******************************************************************
 * INTERACT
 * This is where the user input get sorted into which function CHESS
 * will use.
 *****************************************************************/
void Chess::interact(Move & move)
{
   //The user input...
   string option;
   //GET IT!
   cin >> option;

   //For the switch statement
   char m;

   //Depending on the user input, 'm' will change
   if (option == "?")
      m = '?';
   if (option == "read")
      m = 'r';
   if (option == "help")
      m = 'h';
   if (option == "test")
      m = 't';
   if (option == "rank")
      m = 'R';
   if (option == "quit")
      m = 'q';
   if (option == "smith")
      m = 's';
   else
   {
      //By default, turn option into a move
      move = option;
   }
   //Depending on what 'm' turned into...
   switch (m)
   {
      case '?':
      {
         //DISPLAY the options
         displayOptions();
         break;
      }
      case 'r':
      {
         //READ the saved game
         read();
         //DISPLAY the board
         cout << board;
         break;
      }
      case 'q':
      {
         //SAVE the current game
         write();
         //fQuit is true
         fQuit = true;
         bool theChurch = true;
         break;
      }
      case 'h':
      {
         cout << "This option still in development\n";
         break;
      }
      case 't':
      {
         //SET it to test mode
         board.setTest();
         cout << *this; //This will re-display the board
         break;
      }
      case 'R':
      {
         //Work in progress....
         cout << "This option still in development\n";
         break;
      }
      case 's':
      {
         //DISPLAY smith notation instructions
         displaySmith();
         break;
      }
      //DEFAULT
      default:
      {
         //INCREEMENT numMoves
         numMoves++;
         //Add to the vector
         moves.push_back(move);
         //SWAP the pieces!
         board.swap(move);
         cout << *this; //This will re-display the board
      }
   }
}

/*************************************************
 * OPERATOR++
 * This is how the game will advance, called in main()
 ************************************************/
Chess & Chess::operator ++(int postfix)
{
   //PROMPT depending on whose turn it is.
   cout << (getNumMoves() % 2 ? "Black: " : "White: ");

   //INTERACT
   interact(move);

   return *this;
}

/***************************************************************
 * INSERTION OPERATOR
 * This makes displaying the board much simpler.
 **************************************************************/
ostream & operator << (ostream & out, const Chess & rhs)
{
   //DISPLAY the board
   out << rhs.board;
   //RETURN out. (Important!)
   return out;
};

/************************************************************************
 * MAIN
 * Every program has one. This will basically get thing started before
 * every other object takes over.
 ***********************************************************************/
int main()
{
   Chess chess;

   //DISPLAY the board
   cout << chess;

   //As long as we havn't quite yet...
   while(!chess.quit())
   {
      //ADVANCE the game
      chess++;
   }

   //...and they all died happily ever after.
   return 0;
}
