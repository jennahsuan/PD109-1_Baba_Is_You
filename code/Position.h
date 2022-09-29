#ifndef Position_hpp
#define Position_hpp

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

unsigned int MAP_X_BOUND;
unsigned int MAP_Y_BOUND;

class Position{
private:
    Vector2i pos;
public:
    Position() {Position(0, 0);}
    Position(int x, int y)  {pos.x = x; pos.y = y;}//constructor
    Position(Vector2i pos) {this->pos = pos;}
    Vector2i get_pos() {return pos;}
    bool isAvailiblePos();
    bool setNewPosition(int newX, int newY);
    void print();
};

//---------------------------------------
bool Position::setNewPosition(int newX, int newY){
    if((newX >= 0) && (newX < MAP_X_BOUND) && (newY >= 0) && newY < MAP_Y_BOUND){
        pos.x = newX;
        pos.y = newY;
        return true;
    }
    else{
        cout << "Invalid new position, cannot move" << endl;
        return false;
    }
}

//---------------------------------------
bool Position::isAvailiblePos(){
    if(pos.x >= 0 && pos.x < MAP_X_BOUND && pos.y >= 0 && pos.y < MAP_Y_BOUND)
        return true;
    else
        return false;
}



//---------------------------------------
void Position::print(){
    cout << "(" << pos.x << ", " << pos.y << ")";
}
#endif /* Position_hpp */
