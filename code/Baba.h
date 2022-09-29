#ifndef Baba_hpp
#define Baba_hpp

#include "Object.h"
#include "algorithm"

class Baba{
private:
    int face = 4;
        //1 is toward up, 2 is toward down, 3 is toward left, 4 is toward right
    bool detectThing();
    bool hasWon = 0;
    
public:
    Object* YOU;
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    bool pushThing();
    const int direction(){return this->face;};
    void print();
    bool Call_Win();
    const bool WinOrNot(){return this->hasWon;};
};

bool Baba::Call_Win(){
    // cout<<"You Win!!!!!!!!!!!!!"<<endl;
    this->hasWon = 1;
}

//---------------------------------------
void Baba::moveUp(){
    int now_x = YOU->_x();
    int now_y = YOU->_y();
    if(!Position(now_x, now_y - 1).isAvailiblePos())
        return;
    if(grid[now_x][now_y - 1]->Determine_State() == 3){
        Call_Win();
        return;
    }
    // cout<<"grid = "<<grid[now_x][now_y - 1]->getname()<<endl;
    int move_time = MOVEABLE_W(grid[now_x][now_y]);
    // cout<<"move_time = "<<move_time<<endl;
    if(move_time <= 0)
        return;
    for(int i=0;i<move_time;i++){
        // cout<<"Success "<<grid[now_x][now_y - i]->getname()<<endl;
        // cout<<"YOU position "<<YOU->_y()<<endl;
        swap(grid[now_x][now_y - i], grid[now_x][now_y - move_time]);
        swap(grid[now_x][now_y - i]->Obj_pos, grid[now_x][now_y - move_time]->Obj_pos);
        // cout<<"Over swap "<<grid[now_x][now_y - i]->getname()<<endl;
        grid[now_x][now_y - i]->print_obj();
        grid[now_x][now_y - move_time]->print_obj();
    }
    YOU = grid[now_x][now_y - 1];
    YOU->print_obj();
    this->face = 1;
    // cout<<"YOU position "<<YOU->_y()<<" -------- face up"<<endl<< endl;
    
}

//---------------------------------------
void Baba::moveDown(){
    int now_x = YOU->_x();
    int now_y = YOU->_y();
    if(!Position(now_x, now_y + 1).isAvailiblePos())
        return;
    if(grid[now_x][now_y + 1]->Determine_State() == 3){
        Call_Win();
        return;
    }
    // cout<<"grid = "<<grid[now_x][now_y + 1]->getname()<<endl;
    int move_time = MOVEABLE_S(grid[now_x][now_y]);
    // cout<<"move_time = "<<move_time<<endl;
    if(move_time <= 0)
        return;
    for(int i=0;i<move_time;i++){
        // cout<<"Success "<<grid[now_x][now_y + i]->getname()<<endl;
        // cout<<"YOU position "<<YOU->_y()<<endl;
        swap(grid[now_x][now_y + i], grid[now_x][now_y + move_time]);
        swap(grid[now_x][now_y + i]->Obj_pos, grid[now_x][now_y + move_time]->Obj_pos);
        // cout<<"Over swap "<<grid[now_x][now_y + i]->getname()<<endl;
        grid[now_x][now_y + i]->print_obj();
        grid[now_x][now_y + move_time]->print_obj();
        // cout << endl;
    }
    YOU = grid[now_x][now_y + 1];
    YOU->print_obj();
    this->face = 2;
    // cout<<"YOU position "<<YOU->_y()<<" -------- face down"<<endl<< endl;
    
}

//---------------------------------------
void Baba::moveLeft(){
    int now_x = YOU->_x();
    int now_y = YOU->_y();
    if(!Position(now_x - 1, now_y).isAvailiblePos())
        return;
    if(grid[now_x - 1][now_y]->Determine_State() == 3){
        Call_Win();
        return;
    }
    // cout<<"grid = "<<grid[now_x - 1][now_y]->getname()<<endl;
    int move_time = MOVEABLE_A(grid[now_x][now_y]);
    // cout<<"move_time = "<<move_time<<endl;
    if(move_time <= 0)
        return;
    for(int i=0;i<move_time;i++){
        // cout<<"Success "<<grid[now_x - i][now_y]->getname()<<endl;
        // cout<<"YOU position "<<YOU->_y()<<endl;
        swap(grid[now_x - i][now_y], grid[now_x - move_time][now_y]);
        swap(grid[now_x - i][now_y]->Obj_pos, grid[now_x - move_time][now_y]->Obj_pos);
        // cout<<"Over swap "<<grid[now_x - i][now_y]->getname()<<endl;
        grid[now_x - i][now_y]->print_obj();
        grid[now_x - move_time][now_y]->print_obj();
    }
    YOU = grid[now_x - 1][now_y];
    YOU->print_obj();
    this->face = 3;
    // cout<<"YOU position "<<YOU->_y()<<" -------- face left"<<endl<< endl;    
}

//---------------------------------------
void Baba::moveRight(){
    int now_x = YOU->_x();
    int now_y = YOU->_y();
    if(!Position(now_x + 1, now_y).isAvailiblePos())
        return;
    if(grid[now_x + 1][now_y]->Determine_State() == 3){
        Call_Win();
        return;
    }
    int move_time = MOVEABLE_D(grid[now_x][now_y]);
    // cout<<"move_time = "<<move_time<<endl;
    if(move_time <= 0)
        return;
    for(int i=0;i<move_time;i++){
        swap(grid[now_x + i][now_y], grid[now_x + move_time][now_y]);
        swap(grid[now_x + i][now_y]->Obj_pos, grid[now_x + move_time][now_y]->Obj_pos);
        grid[now_x + i][now_y]->print_obj();
        grid[now_x + move_time][now_y]->print_obj();
    }
    YOU = grid[now_x + 1][now_y];
    YOU->print_obj();
    this->face = 4;
    // cout<<" -------- face right"<<endl<< endl;    
}

//---------------------------------------
bool Baba::detectThing(){
    return true;
}

//---------------------------------------
bool Baba::pushThing(){
    if(detectThing() == true)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

//---------------------------------------
void Baba::print(){
    cout << "Face: " << this->face;
    YOU->Obj_pos.print();
    cout << endl;
}

#endif /* Baba_hpp */
