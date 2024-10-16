
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape) {
    this->colour = colour;
    this->shape = shape;
}

Tile::Tile(Tile &other):
    colour(other.colour),
    shape(other.shape)
{
}

Tile::~Tile() {

}

Colour Tile::getColour(){
    return colour;
}

Shape Tile::getShape() {
    return shape;
}

void Tile::printTile() {

    if(colour == RED) {
        std::cout << "\u001b[31m" << colour << shape;
    } else if(colour == ORANGE) {
        std::cout << "\u001b[31;1m" << colour << shape;
    } else if(colour == YELLOW) {
        std::cout << "\u001b[33m" << colour << shape;
    } else if(colour == GREEN) {
        std::cout << "\u001b[32m" << colour << shape;
    } else if(colour == BLUE) {
        std::cout << "\u001b[34m" << colour << shape;
    } else if(colour == PURPLE) {
        std::cout << "\u001b[35m" << colour << shape;
    }

}