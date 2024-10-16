
#include "LinkedList.h"
#include "Tile.h"
#include "TileCodes.h"
#include "Game.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#define NEW_GAME "1"
#define LOAD_GAME "2"
#define CREDITS "3"
#define QUIT "4"

#define MENU_HELP 0
#define LOAD_GAME_HELP 1
#define PLAYER_NAME_HELP 2

#define MAX_PLAYERS 2

void showmenu();
void showStudentInfom();
std::string getUserInput();

void myFormatLoadGame(std::ifstream &input);
void loadGame(std::ifstream &input);
bool validateName(std::string playerName);

void printHelp(int help);

int main(void)
{

   std::string select;
   bool gameComplete = false;

   while (!gameComplete)
   {
      showmenu();
      select = getUserInput();

      if (select == NEW_GAME)
      {
         std::cout << std::endl;
         std::cout << "Starting a New Game" << std::endl;
         std::cout << std::endl;

         std::cout << "Enter the number of players for this game" << std::endl;
         int playerCount;
         bool validPlayerCount = false;

         while (!validPlayerCount)
         {
            std::cout << "> ";
            std::cin >> playerCount;

            if (playerCount >= 2 && playerCount <= 4)
            {
               validPlayerCount = true;
            }
            else if (std::cin.eof())
            {
               validPlayerCount = true;
               gameComplete = true;
            }
            else
            {
               std::cin.clear();
               std::cin.ignore();
               std::cout << "invalid player number : must be between 2-4 players" << std::endl;
            }
         }

         std::vector<std::string> players;

         if (validPlayerCount && !std::cin.eof())
         {
            for (int i = 0; i < playerCount; i++)
            {
               std::cout << "Enter a name for player " << i + 1 << " (uppercase characters only)" << std::endl;
               std::cout << "> ";

               std::string playerName;
               std::cin >> playerName;

               if (std::cin.eof())
               {
                  gameComplete = true;
                  i = playerCount;
               }
               else
               {
                  if (playerName == "help")
                  {
                     printHelp(PLAYER_NAME_HELP);
                     i--;
                  }
                  else if (!validateName(playerName))
                  {
                     std::cout << "Error - Invalid name " << std::endl;
                     std::cout << "Player name should be uppercase characters only" << std::endl;
                     i--;
                  }
                  else
                  {
                     players.push_back(playerName);
                  }
               }
            }
         }

         if (!std::cin.eof())
         {
            std::cout << std::endl;
            std::cout << "Let's Play!" << std::endl;

            Game *game = new Game(playerCount, players);
            game->playGame(players.at(PLAYER_1), true);
            delete game;

            gameComplete = true;
         }
      }
      else if (select == LOAD_GAME)
      {

         bool myFormat = false;

         std::ifstream loadFile;

         while (!loadFile.is_open() && !std::cin.eof())
         {
            //Get the user to type a filename
            std::string fileName;
            std::cout << std::endl;
            std::cout << "Enter the filename from which load a game" << std::endl;
            std::cout << "> ";
            std::cin >> fileName;

            //if the user did not press the EOF key, then try to load the filename
            if (!std::cin.eof())
            {
               if (fileName == "help")
               {
                  printHelp(LOAD_GAME_HELP);
               }
               else
               {

                  loadFile.open(fileName);

                  //if the filename provided did not open, then output error msg and try again
                  if (!loadFile.is_open())
                  {
                     std::cout << fileName << " not found" << std::endl;
                  }
                  //if a filename was found and opened, then check if the file is in the correct format of a save game file
                  else
                  {
                     std::string format;
                     getline(loadFile, format);

                     //if the file is not in the correct format, then close that file and try again
                     if (format == "#MyFormat")
                     {
                        myFormat = true;
                     }
                     else
                     {
                        //otherwise, refresh the file
                        loadFile.close();
                        loadFile.open(fileName);
                     } //end of correct format if statement

                  } //end of loadfile if statement

               } //end of EOF if statement

            } //end of while loop (re-evaluate)

            //load game when a file has been found in correct format
            //or exit if the EOF key is pressed
            if (loadFile.is_open() && !std::cin.eof() && myFormat)
            {
               myFormatLoadGame(loadFile);
               gameComplete = true;
            } else if (loadFile.is_open() && !std::cin.eof() && !myFormat) {
               loadGame(loadFile);
               gameComplete = true;
            }
         }
      }
      else if (select == CREDITS)
      {
         showStudentInfom();
      }
      else if (select == QUIT)
      {
         gameComplete = true;
      }
      else if (std::cin.eof())
      {
         gameComplete = true;
      }
      else if (select == "help")
      {
         printHelp(MENU_HELP);
      }
      else
      {
         std::cin.clear();
         std::cin.ignore();
         std::cout << std::endl;
         std::cout << "Invalid Input" << std::endl;
      }
   }

   std::cout << "\nGoodbye" << std::endl;

   return EXIT_SUCCESS;
}

void showmenu()
{
   std::cout << "Menu" << std::endl;
   std::cout << "----" << std::endl;
   std::cout << "1. New Game" << std::endl;
   std::cout << "2. Load Game" << std::endl;
   std::cout << "3. Credits (Show student information)" << std::endl;
   std::cout << "4. Quit\n"
             << std::endl;
}

std::string getUserInput()
{
   std::cout << "> "; // User prompt
   std::string userInput;

   std::cin >> userInput;

   return userInput;
};

void showStudentInfom()
{
   //Team CHKW
   std::cout << "\n-------------------------------------" << std::endl;
   //[Redacted]
   std::cout << "Name: [Redacted]" << std::endl;
   std::cout << "Student ID: [Redacted]" << std::endl;
   std::cout << "Email: [Redacted]\n"
             << std::endl;
   //[Redacted]
   std::cout << "Name: [Redacted]" << std::endl;
   std::cout << "Student ID: [Redacted]" << std::endl;
   std::cout << "Email: [Redacted]\n"
             << std::endl;
   //Kendrick Krause
   std::cout << "Name: Kendrick Krause" << std::endl;
   std::cout << "Student ID: [Redacted]" << std::endl;
   std::cout << "Email: [Redacted]\n"
             << std::endl;
   //[Redacted]
   std::cout << "Name: [Redacted]" << std::endl;
   std::cout << "Student ID: [Redacted]" << std::endl;
   std::cout << "Email: [Redacted]" << std::endl;
   std::cout << "-------------------------------------" << std::endl;
}

void myFormatLoadGame(std::ifstream &input)
{

   std::string playerName;
   std::string playerScore;
   std::string playerHand;

   std::string numPlayers;
   getline(input, numPlayers);
   int playerCount = numPlayers.at(0) - '0';

   std::vector<Player *> players;

   for (int i = 0; i < playerCount; i++)
   {
      getline(input, playerName);
      getline(input, playerScore);
      getline(input, playerHand);

      LinkedList *hand = new LinkedList();
      unsigned int tileCount = 0;

      for (int j = 0; j < MAX_NUMBER_OF_CARD_ON_HAND; j++)
      {
         std::string tile = playerHand.substr(tileCount, playerHand.find_first_of(",\n"));

         char colour = tile.at(0);
         int shape = tile.at(1) - '0';

         Tile *toAdd = new Tile(colour, shape);

         hand->addBack(toAdd);

         tileCount += tile.length() + 1;

      }

      int score = playerScore.at(0) - '0';
      players.push_back(new Player(playerName, score, hand));
   }

   std::string boardSize;
   getline(input, boardSize);

   std::string boardState;
   getline(input, boardState);

   unsigned int placementCount = 0;

   const char ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

   Board *board = new Board();

   while (placementCount < boardState.length())
   {
      std::string tilePlacement = boardState.substr(placementCount, boardState.find_first_of(",\0"));

      char colour = tilePlacement.at(0);
      int shape = tilePlacement.at(1) - '0';

      char row = tilePlacement.at(3);
      int col = tilePlacement.at(4) - '0';
      if (tilePlacement.length() == 6)
      {
         int col2 = tilePlacement.at(5) - '0';
         col = (col * 10) + col2;
      }

      int iRow = 0;
      for (int k = 0; k < MAX_BOARD_SIZE; k++)
      {
         if (row == ALPHABET[k])
         {
            iRow = k;
            k = MAX_BOARD_SIZE;
         }
      }

      Tile *toAdd = new Tile(colour, shape);
      board->placeTile(iRow, col, toAdd);

      placementCount += tilePlacement.length() + 2;
   }

   std::string tileBag;
   getline(input, tileBag);

   LinkedList *list = new LinkedList();
   const int MAX_TILE_CHAR_COUNT = 3;
   unsigned int tileCount = 0;
   int i = 1;
   while (tileCount < tileBag.length())
   {
      std::string tile = tileBag.substr(tileCount, playerHand.find_first_of(",\0"));

      char colour = tile.at(0);
      int shape = tile.at(1) - '0';

      Tile *toAdd = new Tile(colour, shape);

      list->addBack(toAdd);

      tileCount += MAX_TILE_CHAR_COUNT;
      std::cout << i << std::endl;
      i++;
   }

   TileBag *bag = new TileBag(list);

   std::string startingPlayer;
   getline(input, startingPlayer, ' ');

   Game *game = new Game(playerCount, players, board, bag);
   game->playGame(startingPlayer, false);

   delete game;
}

void loadGame(std::ifstream &input)
{
   std::vector<Player *> players;

   std::string playerName;
   std::string playerScore;
   std::string playerHand;

   for (int i = 0; i < MAX_PLAYERS; i++)
   {
      getline(input, playerName);
      getline(input, playerScore);
      getline(input, playerHand);

      LinkedList *hand = new LinkedList();
      unsigned int tileCount = 0;

      for (int j = 0; j < MAX_NUMBER_OF_CARD_ON_HAND; j++)
      {
         std::string tile = playerHand.substr(tileCount, playerHand.find_first_of(",\n"));

         char colour = tile.at(0);
         int shape = tile.at(1) - '0';

         Tile *toAdd = new Tile(colour, shape);

         hand->addBack(toAdd);

         tileCount += tile.length() + 1;
      }

      int score = playerScore.at(0) - '0';
      players.push_back(new Player(playerName, score, hand));
   }

   std::string boardSize;
   getline(input, boardSize);

   std::string boardState;
   getline(input, boardState);

   unsigned int placementCount = 0;

   const char ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

   Board *board = new Board();

   while (placementCount < boardState.length())
   {
      std::string tilePlacement = boardState.substr(placementCount, boardState.find_first_of(",\0"));

      char colour = tilePlacement.at(0);
      int shape = tilePlacement.at(1) - '0';

      char row = tilePlacement.at(3);
      int col = tilePlacement.at(4) - '0';
      if (tilePlacement.length() == 6)
      {
         int col2 = tilePlacement.at(5) - '0';
         col = (col * 10) + col2;
      }

      int iRow = 0;
      for (int k = 0; k < MAX_BOARD_SIZE; k++)
      {
         if (row == ALPHABET[k])
         {
            iRow = k;
            k = MAX_BOARD_SIZE;
         }
      }

      Tile *toAdd = new Tile(colour, shape);
      board->placeTile(iRow, col, toAdd);

      placementCount += tilePlacement.length() + 2;
   }

   std::string tileBag;
   getline(input, tileBag);

   LinkedList *list = new LinkedList();
   const int MAX_TILE_CHAR_COUNT = 3;
   unsigned int tileCount = 0;
   int i = 1;
   while (tileCount < tileBag.length())
   {
      std::string tile = tileBag.substr(tileCount, playerHand.find_first_of(",\0"));

      char colour = tile.at(0);
      int shape = tile.at(1) - '0';

      Tile *toAdd = new Tile(colour, shape);

      list->addBack(toAdd);

      tileCount += MAX_TILE_CHAR_COUNT;
      std::cout << i << std::endl;
      i++;
   }

   TileBag *bag = new TileBag(list);

   std::string startingPlayer;
   getline(input, startingPlayer, ' ');

   Game *game = new Game(MAX_PLAYERS, players, board, bag);
   game->playGame(startingPlayer, false);

   delete game;
}

bool validateName(std::string playerName)
{
   bool validName = false;
   // player name should be uppercase characters only
   for (size_t i = 0; i < playerName.length(); i++)
   {
      if (!isupper(playerName[i]) && isalnum(playerName[i]))
      {
         validName = false;
      }
      else
      {
         validName = true;
      }
   }
   return validName;
}

void printHelp(int help)
{
   if (help == MENU_HELP)
   {
      std::cout << "\n-------------------------------------" << std::endl;
      std::cout << "Help!" << std::endl;
      std::cout << "\nType '1' to play a new game" << std::endl;
      std::cout << "Type '2' to load a saved game" << std::endl;
      std::cout << "Type '3' to show the game credits" << std::endl;
      std::cout << "Type '4' to quit the game";
      std::cout << "\n-------------------------------------" << std::endl;
   }
   else if (help == LOAD_GAME_HELP)
   {
      std::cout << "\n-------------------------------------" << std::endl;
      std::cout << "Help!" << std::endl;
      std::cout << "Type the name of a savefile to load";
      std::cout << "\n-------------------------------------" << std::endl;
   }
   else if (help == PLAYER_NAME_HELP)
   {
      std::cout << "\n-------------------------------------" << std::endl;
      std::cout << "Help!" << std::endl;
      std::cout << "Create a name for your players, using uppercase letters only";
      std::cout << "\n-------------------------------------" << std::endl;
   }
}