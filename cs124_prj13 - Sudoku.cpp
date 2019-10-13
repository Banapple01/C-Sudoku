/***********************************************************************
* Program:
*    Project 13, Sudoku
*    Brother Manley, CS124
* Author:
*    Jonathan Wright
* Summary: 
*    This Program will allow the user to play Sudoku.
*    Before you begin working, estimate the time you think it will
*    take you to do the assignment and include it in this header block.
*    Before you submit the assignment include the actual time it took.
*
*    Estimated:  1.0 hr   
*    Actual:     1.5
*      Figuring out the tiny things I missed in order to make it
*      function properly.
************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

void display(int board[][9]);
void interact(int board[][9]);
void displayOptions();
int checkCrossValues(int value, const int numcolumn,
                     const int row, int board[][9]);
int checkSquareValues(int value, const int numcolumn,
                      const int row, int board[][9]);

//Get and read the file from the user.
int readFile()
{
   string filename;
   int board[9][9];
   
   cout << "Where is your board located? ";
   cin >> filename;
   
   ifstream fin(filename.c_str());
   if (fin.fail())
   {
      return -1;
   }

   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         fin >> board[i][j];
      }
   }
   
   fin.close();

   displayOptions();
   cout << "\n";
   display(board);
   interact(board);
   
   return 0;
}

//Display the board.
void display(int board[][9])
{
   cout << "   A B C D E F G H I\n";

   int values[81];
   int g = 0;
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         if (g < 81)
         {
            values[g] = board[i][j];
            g++;
         }
      }
   }
   
   for (int i = 0; i < 81; i++)
   {
      //Divisor every 3rd row.
      if ((i / 9) != 0 && (i / 9) % 3 == 0 && (i % 9) == 0)
      {
         cout << "   -----+-----+-----" << endl;
      }

      //Numbered rows.
      if (i % 9 == 0)
      {
         cout << ((i / 9) + 1) << " ";
      }

      //Divisor every 3rd Column.
      ((i % 9) != 0 && (i % 9) % 3 == 0) ? cout << "|" : cout << " ";

      //Space for each unknown value(0)
      if (board[0][i] == 0)
      {
         cout << " ";
      }

      else
      {
         cout << values[i];
      }

      if ((i + 1) % 9 == 0)
      {
         cout << endl;
      }
   }
}

//Ask for and check desired coordinates.
//Call check functions to check given value.
int computeValues(int board[][9])
{
   int row = 0;
   int row1 = 0;
   char column;
   int numcolumn = 0;
   int value = 0;

   cout << "What are the coordinates of the square: ";
   cin >> column >> row1;
   row = (row1 - 1);
   //Ascii table sorcery
   if (column == 'A' || 'B' || 'C'
      || 'D' || 'E' || 'F' || 'G'
      || 'H' || 'I')
   {
      numcolumn = (column - 'A');
   }
   //I'll be changing this if statement
   //later to give second chances
   if (board[row][numcolumn] > 0)
   {
      cout << "ERROR: Square '" << column
           << row1 << "' is filled\n";
      return 0;
   }
   else
   {
      //Get desired number
      cout << "What is the value at '"
           << column << row1 << "': ";
      cin >> value;
   }
   if (value < 1 || 9 < value)
   {
      cout << "ERROR: Value '" << value
           << "' in square '" << column
           << row1 << "' is invalid\n";
   }
   else
   {
   if (checkCrossValues(value, numcolumn, row, board) == true)
   {
      cout << "ERROR: Value '" << value
           << "' in square '" << column
           << row1 << "' is invalid\n";
   }
   else
   {
   if (checkSquareValues(value, numcolumn, row, board) == true)
   {
      cout << "ERROR: Value '" << value
           << "' in square '" << column
           << row1 << "' is invalid\n";
   }
   else
   {
      board[row][numcolumn] = value;
   }
   }
   }
   
   return 0;
}

// Check the row and columns of the given coordinates.
int checkCrossValues(int value, const int numcolumn,
                     const int row, int board[][9])
{
   for (int row2 = 0; row2 < 9; row2++)
   {
      if (value == board[row2][numcolumn])
      {
         return true;
      }
   }
   
   for (int numcolumn1 = 0; numcolumn1 < 9; numcolumn1++)
   {
      if (value == board[row][numcolumn1])
      {
         return true;
      }
   }

   return false;
}

// Check the square of the given coordinates.
int checkSquareValues(int value, const int numcolumn,
                      const int row, int board[][9])
{
   if (row <= 2)
   {
      if (numcolumn <= 2)
      {
         for (int i = 0; i <= 2; i++)
         {
            for (int j = 0; j <= 2; j++)
            {
               if (value == board[i][j])
               {
                  return true;
               }
            }
         }
      }
      if (2 < numcolumn && numcolumn <= 5)
      {
         for (int i = 0; i <= 2; i++)
         {
            for (int j = 3; j <= 5; j++)
            {
               if (value == board[i][j])
               {
                  return true;
               }
            }
         }
      }
      if (5 < numcolumn && numcolumn <= 8)
      {
         for (int i = 0; i <= 2; i++)
         {
            for (int j = 6; j <= 9; j++)
            {
               if (value == board[i][j])
               {
                  return true;
               }
            }
         }
      }
   }
   if (3 < row && row <= 5 )
   {
      if (numcolumn <= 2)
      {
         for (int i = 3; i <= 5; i++)
         {
            for (int j = 0; j <= 2; j++)
            {
               if (value == board[i][j])
               {
                  return true;
               }
            }
         }
      }
      if (2 < numcolumn && numcolumn <= 5)
      {
         for (int i = 3; i <= 5; i++)
         {
            for (int j = 3; j <= 5; j++)
            {
               if (value == board[i][j])
               {
                  return true;
               }
            }
         }
      }
      if (5 < numcolumn && numcolumn <= 8)
      {
         for (int i = 3; i <= 5; i++)
         {
            for (int j = 6; j <= 8; j++)
            {
               if (value == board[i][j])
               {
                  return true;
               }
            }
         }
      }
   }
   if (5 < row && row <= 8)
   {
      if (numcolumn <= 2)
      {
         for (int i = 6; i <= 9; i++)
         {
            for (int j = 0; j <= 2; j++)
            {
               if (value == board[i][j])
               {
                  return true;
               }
            }
         }
      }
      if (2 < numcolumn && numcolumn <= 5)
      {
         for (int i = 6; i <= 9; i++)
         {
            for (int j = 4; j <= 5; j++)
            {
               if (value == board[i][j])
               {
                  return true;
               }
            }
         }
      }
      if (5 < numcolumn && numcolumn <= 8)
      {
         for (int i = 6; i <= 9; i++)
         {
            for (int j = 6; j <= 8; j++)
            {
               if (value == board[i][j])
               {
                  return true;
               }
            }
         }
      }
   }
   return false;
}

void displayOptions()
{
   cout << "Options:\n"
        << setw(4) << "?" << "  Show these instructions\n"
        << setw(4) << "D" << "  Display the board\n"
        << setw(4) << "E" << "  Edit one square\n"
        << setw(4) << "S" << "  Show the possible values for a square\n"
        << setw(4) << "Q" << "  Save and Quit\n";
}

int saveGame(int board[][9])
{
   string filename;

   cout << "What file would you like to write your board to: ";
   cin >> filename;

   ofstream fout(filename.c_str());
   if (fout.fail())
   {
      cout << "Unable to open file "
           << filename << "\n";
      return 0;
   }

   int n = 0;
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         fout << board[i][j];
         n++;
         fout << " ";
         n++;
         if (n == 18)
         {
            fout << "\n";
            n = 0;
         }
      }
   }

   fout.close();

   cout << "Board written successfully\n";
   
   return 0;
}

int possibleValues(int board[][9])
{
   int row = 0;
   int row1 = 0;
   char column;
   int numcolumn = 0;
   int value = 0;

   cout << "What are the coordinates of the square: ";
   cin >> column >> row1;
   row = (row1 - 1);

   if (column == 'A' || 'B' || 'C'
      || 'D' || 'E' || 'F' || 'G'
      || 'H' || 'I')
   {
      numcolumn = (column - 'A');
   }
   if (board[row][numcolumn] > 0)
   {
      cout << "ERROR: Square '" << column
           << row1 << "' is filled\n";
      return 0;
   }
   else
   {
      int posValues[] = {0,0,0,0,0,0,0,0,0};
      int counter = 0;
      for (int i = 1; i < 10; i++)
      {
         value = i;
         if (checkCrossValues(value, numcolumn, row, board) == false)
         {
            if (checkSquareValues(value, numcolumn, row, board) == false)
            {
               posValues[counter] = i;
               counter++;
            }
         }
      }
      if (posValues[0] != 0)
      {
         cout << "The possible values for '"
              << column << row1 << "' are: ";
      }

      for (int i = 0; i < counter; i++)
      {
         if (posValues[i] == 0)
         {
            cout << "\n";
            return 0;
         }
         cout << posValues[i];
         if (posValues[i + 1] != 0)
         {
            cout << ", ";
         }
      }
   }
   return 0;
}

void interact(int board[][9])
{
   char input;

   cout << "\n" << "> ";
   cin >> input;
   if (islower(input))
   {
      input = toupper(input);
   }
   switch (input)
   {
      case '?':
         displayOptions();
         cout << "\n";
         interact(board);
         break;
      case 'D':
         display(board);
         interact(board);
         break;
      case 'E':
         computeValues(board);
         interact(board);
         break;
      case 'S':
         possibleValues(board);
         cout << "\n";
         interact(board);
         break;
      case 'Q':
         saveGame(board);
         break;
   }
}

int main()
{
   readFile();
   
   return 0;
}
