#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include <fstream>
#include <sstream>
#include <iostream>

#include "Player.h"
#include "Board.h"
#include "TileBag.h"

#define MAX_PLAYERS 2
#define PLAYER_1 0
#define PLAYER_2 1
#define PLAYER_3 2
#define PLAYER_4 3
class Game {
public:
    //constructor for newGame
    Game(int playerCount, std::vector<std::string> playerNames);
    //constructor for loadGame
    Game(int playerCount, std::vector<Player*> players, Board *board, TileBag *tileBag);    Game(Game& other);
    ~Game();

    //method to implement gameplay for qwirkle
    //startingplayer - a string to indicate the player starting the game
    //useful for loading in player 2 to start from loading a game
    //newGame - boolean to provide different functionality to new games and loaded games
    void playGame(std::string startingPlayer, bool newGame);


private:

    //method for calculating the score of a players move choice
    void calculateScore(int row, int col, int player);

    //method for placing a tile on the board
    //player - the index of the current player
    //returns true if the board->placeTile() method is reached
    bool placeTile(int player);

    //check if adjacent tiles are of the same colour or shape
    //returns true if the adjacent tile is of the same colour or shape as player tile
    bool checkAdjacencies(Tile* playerTile, Tile* adjacentTile);

    //check if a qwirkle has already been made
    //returns true if no directions have a qwirkle
    bool qwirkleCheck(int row, int col);

    //method for saving a game
    //returns true if the game is saved successfully
    bool saveGame(std::string filename, std::string currentPlayer);

    //method for replacing a tile
    //returns true if a tile is replaced
    bool replaceTile(int player);

    //method for printing help menu for user input
    void printHelp();

    //a game consist of: 
    //2 players
    //a game board
    //a tile bag
    int playerCount;
    std::vector<Player*> players;
    Board* board;
    TileBag* tileBag;

};

#endif //ASSIGN2_GAME_H