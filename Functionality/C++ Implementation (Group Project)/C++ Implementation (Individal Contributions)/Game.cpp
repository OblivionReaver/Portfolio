#include "Game.h"

Game::Game(int playerCount, std::vector<std::string> playerNames)
{
    this->playerCount = playerCount;

    for (int i = 0; i < playerCount; i++)
    {
        players.push_back(new Player(playerNames.at(i), 0, new LinkedList()));
    }

    board = new Board();
    tileBag = new TileBag();
}

Game::Game(int playerCount, std::vector<Player*> players, Board *board, TileBag *tileBag) {
    this->playerCount = playerCount;
    this->players = players;
    this->board = board;
    this->tileBag = tileBag;
}

Game::Game(Game &other) :
    playerCount(other.playerCount)
{
    for (int i = 0; i < playerCount; i++)
    {
        this->players[i] = new Player(*other.players[i]);
    }

    this->board = new Board(*other.board);
    this->tileBag = new TileBag(*other.tileBag);
}

Game::~Game()
{
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        delete players[i];
        players[i] = nullptr;
    }

    delete board;
    delete tileBag;
}

void Game::playGame(std::string startingPlayer, bool newGame)
{
    bool saved = false;

    //index for starting player index
    //orignally start as player 1 index (0)
    //but will do check for loadGame and check if starting player is player 2
    int startingIndex = PLAYER_1;

    //if the game started is a new game, then generate a new tileBag
    //also fill each players hand with tiles (drawing and removing tiles from the front of the tileBag)
    if (newGame)
    {
        tileBag->generateBag();

        for (int i = 0; i < playerCount; i++)
        {
            players[i]->fillHand(tileBag);
        }
    }

    //check if starting player is player 2 (useful for loadGame)
    for(int i = 0; i < playerCount; i++) {
        if (startingPlayer == players[i]->getPlayerName())
            startingIndex = i;
    }

    //check for End of Game(EOG) condition
    bool gameActive = true;

    while (gameActive)
    {
        for (int i = startingIndex; i < playerCount; i++)
        {
            std::cout << players[i]->getPlayerName() << ", it's your turn" << std::endl;
            for(int j = 0; j < playerCount; j++)
                std::cout << "Score for " << players[j]->getPlayerName() << ": " << players[j]->getScore() << std::endl;

            board->displayBoard();

            std::cout << "Your hand is" << std::endl;

            LinkedList *playerHand = players[i]->getHand();
            for (unsigned int i = 0; i < playerHand->size(); i++)
            {
                Tile *tile = playerHand->getTile(i);

                if (i != playerHand->size() - 1)
                {
                    tile->printTile();
                    std::cout << "\u001b[0m, ";
                }
                else
                {
                    tile->printTile();
                    std::cout << "\u001b[0m" << std::endl;
                }
            }

            //validating if a turn taken was successful
            bool turnSuccessful = false;

            //if the first word in the input is place, then perform place function
            while (!turnSuccessful)
            {
                std::cout << "> ";

                //get the users input
                std::string firstWord;
                std::cin >> firstWord;

                if (firstWord == "place")
                {
                    turnSuccessful = placeTile(i);
                }
                else if (firstWord == "save")
                {
                    std::string saveFile;
                    std::cin >> saveFile;

                    turnSuccessful = saveGame(saveFile, players[i]->getPlayerName());

                    if (turnSuccessful)
                    {
                        gameActive = false;
                        saved = true;
                        i = MAX_PLAYERS;
                    }
                }
                else if (firstWord == "replace")
                {
                    turnSuccessful = replaceTile(i);
                }
                else if (std::cin.eof())
                {
                    turnSuccessful = true;
                    gameActive = false;
                    saved = true;
                    i = playerCount;
                }
                else if (firstWord == "help")
                {
                    this->printHelp();
                }

                if (!turnSuccessful && firstWord != "help")
                {
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "Invalid Input" << std::endl;
                }
            }

            if (tileBag->getTileBag()->size() == 0 && players[i]->getHand()->size() == 0)
            {
                gameActive = false;
                i = playerCount;
            }
        }

        startingIndex = 0;
    }

    //write the end of game statistics
    if (!saved)
    {

        int winnerScore = 0;
        std::string winningPlayer = " ";

        for(int i = 0; i < playerCount; i++) {
            if(players[i]->getScore() > winnerScore) {
                winnerScore = players[i]->getScore();
                winningPlayer = players[i]->getPlayerName();
            }
        }

        std::cout << "\nGame over";
        for(int i = 0; i < playerCount; i++) {
            std::cout << "\nScore for " << players[i]->getPlayerName() << ": " << players[i]->getScore();
        }

        std::cout << "\nPlayer " << winningPlayer << " won!";
    }
}

bool Game::placeTile(int player)
{
    bool retVal = false;

    //increasing scope of row and col to do scoring checks if tile is able to be placed
    unsigned int iRow = 0;
    unsigned int col;

    //get a tile from a players hand
    char handColour;
    int handShape;
    std::cin >> handColour;
    std::cin >> handShape;

    //create a reference tile based on the inputs
    Tile *handTile = new Tile(handColour, handShape);
    bool validTile = false;
    int handIndex = 0;

    LinkedList *playerHand = players[player]->getHand();

    //iterate through the players hand and check if the inputed tile matches any tiles in the players hand
    for (unsigned int k = 0; k < playerHand->size(); k++)
    {
        Tile *playerTile = playerHand->getTile(k);

        //if the inputed tile matches a tile in the players hand, then it is a valid tile
        if (playerTile->getColour() == handTile->getColour() && playerTile->getShape() == handTile->getShape())
        {
            handIndex = k;
            validTile = true;
            k = playerHand->size();
        }
    }

    delete handTile;

    if (validTile)
    {
        //check if the next word in the sentence is at (proper format check)
        std::string at;
        std::cin >> at;

        if (at == "at")
        {
            //get the coordinate to place the tile
            char row;

            std::cin >> row;
            std::cin >> col;

            const int ALPHABET_SIZE = 26;
            const char ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

            //iterate through the alphabet to get a corresponding coordinate (ie. convert char coordinate to int coordinate)
            for (int i = 0; i < ALPHABET_SIZE; i++)
            {
                if (row == ALPHABET[i])
                {
                    iRow = i;
                    i = ALPHABET_SIZE;
                }
            }

            //check if the row and column are within the bounds of the board
            if (iRow < ALPHABET_SIZE && col < ALPHABET_SIZE)
            {
                //check if the board is empty, ie. if it is the first turn and no tiles have been placed
                int emptySpaces = 0;

                for (int i = 0; i < MAX_BOARD_SIZE; i++)
                {
                    for (int j = 0; j < MAX_BOARD_SIZE; j++)
                    {
                        if (board->getTile(i, j) == nullptr)
                        {
                            emptySpaces++;
                        }
                    }
                }

                //if the board is empty, then the player can place the tile freely
                if (emptySpaces == MAX_BOARD_SIZE * MAX_BOARD_SIZE)
                {
                    board->placeTile(iRow, col, playerHand->getTile(handIndex));
                    players[player]->removeTile(handIndex);
                    players[player]->fillHand(tileBag);
                    retVal = true;
                }
                //if the board is not empty, then do checks for adjacent tiles
                else
                {
                    Tile *playerTile = playerHand->getTile(handIndex);
                    const int LINE_LENGTH = 6;

                    bool leftValid = false;
                    bool rightValid = false;
                    bool upValid = false;
                    bool downValid = false;

                    bool keepCountingLeft = true;
                    bool keepCountingRight = true;
                    bool keepCountingUp = true;
                    bool keepCountingDown = true;

                    for (int i = 0; i < LINE_LENGTH; i++)
                    {
                        //get adjacent tiles to check if a tile can be placed there
                        Tile *leftTile = board->getTile(iRow - (i + 1), col);
                        Tile *rightTile = board->getTile(iRow + (i + 1), col);
                        Tile *upTile = board->getTile(iRow, col - (i + 1));
                        Tile *downTile = board->getTile(iRow, col + (i + 1));

                        //if the adjacent tiles are not empty, then check they match the colour or shape of the tile trying to be placed
                        if (keepCountingLeft)
                        {
                            if (leftTile != nullptr)
                            {
                                leftValid = checkAdjacencies(playerTile, leftTile);
                            }
                            else
                            {
                                if (i == 0 || leftValid)
                                    leftValid = true;

                                keepCountingLeft = false;
                            }
                        }

                        if (keepCountingRight)
                        {
                            if (rightTile != nullptr)
                            {
                                rightValid = checkAdjacencies(playerTile, rightTile);
                            }
                            else
                            {
                                if (i == 0 || rightValid)
                                    rightValid = true;

                                keepCountingRight = false;
                            }
                        }

                        if (keepCountingUp)
                        {
                            if (upTile != nullptr)
                            {
                                upValid = checkAdjacencies(playerTile, upTile);
                            }
                            else
                            {
                                if (i == 0 || upValid)
                                    upValid = true;

                                keepCountingUp = false;
                            }
                        }

                        if (keepCountingDown)
                        {
                            if (downTile != nullptr)
                            {
                                downValid = checkAdjacencies(playerTile, downTile);
                            }
                            else
                            {
                                if (i == 0 || downValid)
                                    downValid = true;

                                keepCountingDown = false;
                            }
                        }
                    }

                    //if all adajacent tiles are null/empty, then the placement cannot occur (can not place in empty space)
                    if (board->getTile(iRow - 1, col) == nullptr && board->getTile(iRow + 1, col) == nullptr && board->getTile(iRow, col - 1) == nullptr && board->getTile(iRow, col + 1) == nullptr)
                    {
                        leftValid = false;
                        rightValid = false;
                        upValid = false;
                        downValid = false;
                        std::cout << "Error, this grid location is not legal. Please check" << std::endl;
                    }

                    //check if the placement isn't already part of a qwirkle (can not add to a line that is a qwirkle)
                    bool qwirkle = qwirkleCheck(iRow, col);

                    //if all conditions are met, then place tile
                    if (leftValid && rightValid && upValid && downValid && qwirkle)
                    {
                        board->placeTile(iRow, col, playerHand->getTile(handIndex));
                        players[player]->removeTile(handIndex);
                        players[player]->fillHand(tileBag);
                        retVal = true;
                    }
                }
            }
        }
    }
    else
    {
        std::cout << "Error,this tile is not in your hand. Please check" << std::endl;
    }

    if (retVal)
    {
        calculateScore(iRow, col, player);
    }

    return retVal;
}

void Game::calculateScore(int row, int col, int player)
{
    //increase a players score by 1 (awarded just for placing a tile)
    players[player]->setScore(1);

    //constants for reference
    const int QWIRKLE_COUNT = 6;
    const int LEFT = 0;
    const int RIGHT = 1;
    const int UP = 2;
    const int DOWN = 3;

    int qwirkleCount = 0;

    for (int i = 0; i < DOWN + 1; i++)
    {
        bool keepCounting = true;
        int count = 1;

        if (i == LEFT)
        {

            //iterate to the left, keep going until the count has reached the max line length of a qwirkle (6). Or, the line reaches an empty space
            while (count < QWIRKLE_COUNT && keepCounting)
            {
                if (board->getTile(row - count, col) != nullptr)
                {
                    count++;
                }
                else
                {
                    keepCounting = false;
                }
            }

            //if the count reached the qwirkle length, then update qwirkle count
            if (count == QWIRKLE_COUNT)
            {
                std::cout << "QWIRKLE!!!" << std::endl;
                qwirkleCount++;
            }

            //increase player score by the line length
            players[player]->setScore(count - 1);
        }
        else if (i == RIGHT)
        {
            //iterate to the right, keep going until the count has reached the max line length of a qwirkle (6). Or, the line reaches an empty space
            while (count < QWIRKLE_COUNT && keepCounting)
            {
                if (board->getTile(row + count, col) != nullptr)
                {
                    count++;
                }
                else
                {
                    keepCounting = false;
                }
            }

            //if the count reached the qwirkle length, then update qwirkle count
            if (count == QWIRKLE_COUNT)
            {
                std::cout << "QWIRKLE!!!" << std::endl;
                qwirkleCount++;
            }

            //increase player score by the line length
            players[player]->setScore(count - 1);
        }
        else if (i == UP)
        {
            //iterate upwards, keep going until the count has reached the max line length of a qwirkle (6). Or, the line reaches an empty space
            while (count < QWIRKLE_COUNT && keepCounting)
            {
                if (board->getTile(row, col - count) != nullptr)
                {
                    count++;
                }
                else
                {
                    keepCounting = false;
                }
            }

            //if the count reached the qwirkle length, then update qwirkle count
            if (count == QWIRKLE_COUNT)
            {
                std::cout << "QWIRKLE!!!" << std::endl;
                qwirkleCount++;
            }

            //increase player score by the line length
            players[player]->setScore(count - 1);
        }
        else if (i == DOWN)
        {
            //iterate downwards, keep going until the count has reached the max line length of a qwirkle (6). Or, the line reaches an empty space
            while (count < QWIRKLE_COUNT && keepCounting)
            {
                if (board->getTile(row, col + count) != nullptr)
                {
                    count++;
                }
                else
                {
                    keepCounting = false;
                }
            }

            //if the count reached the qwirkle length, then update qwirkle count
            if (count == QWIRKLE_COUNT)
            {
                std::cout << "QWIRKLE!!!" << std::endl;
                qwirkleCount++;
            }

            //increase player score by the line length
            players[player]->setScore(count - 1);
        }
    }

    //award bonus points for each qwirkle found in the for loop
    if (qwirkleCount > 0)
    {
        players[player]->setScore(QWIRKLE_COUNT * qwirkleCount);
    }

    //if the players hand is empty, then award 6 bonus points as per the rules
    //using QWIRKLE_COUNT as increaser, since same number
    if (players[player]->getHand()->size() == 0)
    {
        players[player]->setScore(QWIRKLE_COUNT);
    }
}

bool Game::checkAdjacencies(Tile *playerTile, Tile *adjacentTile)
{
    bool retVal = false;

    if (playerTile->getColour() == adjacentTile->getColour() || playerTile->getShape() == adjacentTile->getShape())
    {
        retVal = true;
    }

    return retVal;
}

bool Game::qwirkleCheck(int row, int col)
{
    bool retVal = false;

    //some const for references
    const int QWIRKLE_NUM = 6;
    const int LEFT = 0;
    const int RIGHT = 1;
    const int UP = 2;
    const int DOWN = 3;

    //a count that will increase each time a qwirkle if found
    int qwirkleCount = 0;

    for (int i = 0; i < DOWN + 1; i++)
    {
        int tileCount = 0;

        //check if a qwirkle is made in the left direction
        if (i == LEFT)
        {
            for (int j = 1; j <= QWIRKLE_NUM; j++)
            {
                if (board->getTile(row - j, col) != nullptr)
                {
                    tileCount++;
                }
            }

            if (tileCount == QWIRKLE_NUM)
            {
                qwirkleCount++;
            }
        }
        //check if a qwirkle is made in the right direction
        else if (i == RIGHT)
        {
            for (int j = 1; j <= QWIRKLE_NUM; j++)
            {
                if (board->getTile(row + j, col) != nullptr)
                {
                    tileCount++;
                }
            }

            if (tileCount == QWIRKLE_NUM)
            {
                qwirkleCount++;
            }
        }
        //check if a qwirkle is made in the up direction
        else if (i == UP)
        {
            for (int j = 1; j <= QWIRKLE_NUM; j++)
            {
                if (board->getTile(row, col - j) != nullptr)
                {
                    tileCount++;
                }
            }

            if (tileCount == QWIRKLE_NUM)
            {
                qwirkleCount++;
            }
        }
        //check if a qwirkle is made in the down direction
        else if (i == DOWN)
        {
            for (int j = 1; j <= QWIRKLE_NUM; j++)
            {
                if (board->getTile(row, col + j) != nullptr)
                {
                    tileCount++;
                }
            }

            if (tileCount == QWIRKLE_NUM)
            {
                qwirkleCount++;
            }
        }
    }

    //if no qwirkles were found, then the move is valid
    if (qwirkleCount == 0)
    {
        retVal = true;
    }

    return retVal;
}

bool Game::saveGame(std::string filename, std::string currentPlayer)
{
    //create a new file to output to
    std::ofstream saveFile(filename + ".txt");

    const char ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if(playerCount > 2) {
        saveFile << "#MyFormat" << std::endl;
        saveFile << playerCount << std::endl;
    }

    //save the player names, scores and hands
    for (int i = 0; i < playerCount; i++)
    {
        saveFile << players[i]->getPlayerName() << std::endl;
        saveFile << players[i]->getScore() << std::endl;

        for (unsigned int j = 0; j < players[i]->getHand()->size(); j++)
        {
            Tile *tile = players[i]->getHand()->getTile(j);

            if (j != players[i]->getHand()->size() - 1)
            {
                saveFile << tile->getColour() << tile->getShape() << ",";
            }
            else
            {
                saveFile << tile->getColour() << tile->getShape() << std::endl;
            }
        }
    }

    //save the board state
    int boardSize = board->getBoardSize();
    saveFile << boardSize << "," << boardSize << std::endl;

    //iterate through the rows and columns of the board and output the tile and coordinate to the savefile
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            Tile *current = board->getTile(j, i);

            if (board->getTile(j, i) != nullptr)
            {
                if (i != boardSize - 1 && j != boardSize - 1)
                {
                    saveFile << current->getColour() << current->getShape() << "@" << ALPHABET[j] << i << ", ";
                }
                else
                {
                    saveFile << current->getColour() << current->getShape() << "@" << ALPHABET[j] << i << std::endl;
                }
            }
        }
    }

    saveFile << std::endl;

    //iterate through the tilebag and output its contents to the save file
    LinkedList *bag = tileBag->getTileBag();
    for (unsigned int i = 0; i < bag->size(); i++)
    {
        Tile *current = bag->getTile(i);

        if (i != bag->size() - 1)
        {
            saveFile << current->getColour() << current->getShape() << ",";
        }
        else
        {
            saveFile << current->getColour() << current->getShape() << std::endl;
        }
    }

    saveFile << currentPlayer;

    saveFile.close();

    bool saveSuccess = false;

    if (!saveFile.is_open())
    {
        saveSuccess = true;
    }

    return saveSuccess;
}

bool Game::replaceTile(int player)
{
    bool retVal = false;

    //get a tile from a players hand
    char handColour;
    int handShape;
    std::cin >> handColour;
    std::cin >> handShape;

    //create a reference tile based on the inputs
    Tile *handTile = new Tile(handColour, handShape);
    bool validTile = false;
    int handIndex = 0;

    LinkedList *playerHand = players[player]->getHand();

    //iterate through the players hand and check if the inputed tile matches any tiles in the players hand
    for (unsigned int k = 0; k < playerHand->size(); k++)
    {
        Tile *playerTile = playerHand->getTile(k);

        //if the inputed tile matches a tile in the players hand, then it is a valid tile
        if (playerTile->getColour() == handTile->getColour() && playerTile->getShape() == handTile->getShape())
        {
            handIndex = k;
            validTile = true;
            k = playerHand->size();
        }
    }

    if (validTile)
    {
        tileBag->addToBag(handTile);
        playerHand->removeAt(handIndex);
        players[player]->fillHand(tileBag);
        retVal = true;
    }
    else
    {
        std::cout << "Error,this tile is not in your hand. Please check" << std::endl;
    }

    return retVal;
}

void Game::printHelp()
{
    std::cout << "\n-------------------------------------" << std::endl;
    std::cout << "Help!" << std::endl;
    std::cout << "\nType: place <tile> at <grid location> - to place a tile at a location on the grid" << std::endl;
    std::cout << "\nType: replace <tile> - to replace a tile from your hand to the tile bag" << std::endl;
    std::cout << "\nType: save <filename> - to save the current game state and exit the game";
    std::cout << "\n-------------------------------------" << std::endl;
}