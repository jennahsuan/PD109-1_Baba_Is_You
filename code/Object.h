#ifndef Object_hpp
#define Object_hpp

#include "Position.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
using namespace std;
using namespace sf;
extern const int MAX_X = 20;
extern const int MAX_Y = 20;

class Object;
vector<pair<string, string>> compare;
string cmp(string);
map<string, int> str_to_int;
void set_up_meaning();
const string images[17]{
    "C:\\babaimage\\baba_E.png",
    "C:\\babaimage\\flag.png",
    "C:\\babaimage\\wall.png",
    "C:\\babaimage\\rock.png",
    "C:\\babaimage\\baba_word.png",
    "C:\\babaimage\\flag_word.png",
    "C:\\babaimage\\wall_word.png",
    "C:\\babaimage\\rock_word.png",
    "C:\\babaimage\\push_word.png",
    "C:\\babaimage\\win_word.png",
    "C:\\babaimage\\you_word.png",
    "C:\\babaimage\\stop_word.png",
    "C:\\babaimage\\is_word.png",
    "C:\\babaimage\\win_blackBG.png",
    "C:\\babaimage\\baba_N.png",
    "C:\\babaimage\\baba_S.png",
    "C:\\babaimage\\baba_W.png"
};
int string_to_int(string);




class Object{
private:
    string Obj_name = "Default";
    Position Obj_pos;
    int meaning = str_to_int[Obj_name];
    friend class Baba;
public:
    Object() {Object(0, 0, "Default", Texture());}
    Object(int x, int y) {Object(x, y, "Default", Texture());}
    Object(Position pos, string name, Texture Tex): Obj_pos(pos), Obj_name(name), t(Tex)    {}
    Object(int x, int y, string name, Texture Tex)  {Object(Position(x, y), name, Tex);}
    string Get_State();
        // code:    0,    1,    2,    3,    4,   5,   6,    7,    8,  9
        // meaning: BABA, ROCK, WALL, FLAG, YOU, WIN, STOP, PUSH, IS, WORD
    int Determine_State();
        // code:  0,    1,    2,    3
        // state: PASS, PUSH, STOP, WIN
    string getname()    {return Obj_name;}
    Position get_objpos()  {return Obj_pos;}
    void set_objpos(int x, int y)   {Obj_pos = Position(x, y);}
    void set_name(string str)   {Obj_name = str;}
    int means()      {return meaning;}
    bool empty;
    Sprite s;
    const Texture t;
    int _x() {return this->get_objpos().get_pos().x;}
    int _y() {return this->get_objpos().get_pos().y;}
    bool refreshMap(Position, Position);
    void print_obj();
};

vector<Object> SUBJECTS;
vector<Object*> WORDBLOCK_SUB;
vector<Object*> WORDBLOCK_IS;
vector<Object*> WORDBLOCK_ADJ;
Object* grid[MAX_X][MAX_Y];

string cmp(string str){
    for(int i=0;i<compare.size();i++){
        if(compare[i].first == str)
            return compare[i].second;
        if(compare[i].second == str)
            return compare[i].first;
    }
    return "False";
}

void set_up_meaning(){
    str_to_int["BABA"] = 0;
    str_to_int["FLAG"] = 1;
    str_to_int["WALL"] = 2;
    str_to_int["ROCK"] = 3;
    str_to_int["W_BABA"] = 4;
    str_to_int["W_FLAG"] = 5;
    str_to_int["W_WALL"] = 6;
    str_to_int["W_ROCK"] = 7;
    str_to_int["W_PUSH"] = 8;
    str_to_int["W_WIN"] = 9;
    str_to_int["W_YOU"] = 10;
    str_to_int["W_STOP"] = 11;
    str_to_int["W_IS"] = 12;
}

int string_to_int(string str){
    int total = 0;
    unsigned long int len = str.length();
    while(len > 0){
        total += pow(10, len-1) * ((int)str[str.length()-len]-48);
        len--;
    }
    return total;
}


int Object::Determine_State(){
    if(this->empty)
        return 2;
    string str = Get_State();
    // cout<<"get_name() = "<<getname()<<endl;
    // cout<<"Get_State() = "<<str<<endl;
    if(str == "W_PUSH")
        return 1;
    else if(str == "W_STOP"){
        // cout<<"BE STOPED"<<endl;
        return 2;
    }
    else if(str == "W_WIN")
        return 3;
    if(this->getname()[1] == '_')
        return 1;
    else    //PASS
        return 0;
}


// check if any subject and "is" word blocks are in correct sequence with the object


string Object::Get_State(){
    for(int i=0;i<WORDBLOCK_SUB.size();i++){
        if(WORDBLOCK_SUB[i]->getname() == cmp(Obj_name)){
            int x = WORDBLOCK_SUB[i]->_x();
            int y = WORDBLOCK_SUB[i]->_y();
            if(y >= 2)
                if(grid[x][y + 1]->getname() == "W_IS")
                    return grid[x][y + 2]->empty ? "Default" : grid[x][y + 2]->getname();
            if(x < MAP_X_BOUND-2){
                
                if(grid[x + 1][y]->getname() == "W_IS"){
                   
                    return grid[x + 2][y]->empty ? "Default" : grid[x + 2][y]->getname();
                }
            }
        }
    }
    return "Default";
}


bool Object::refreshMap(Position old_pos, Position new_pos)
{
    Object *tempObjptr=grid[old_pos.get_pos().x][old_pos.get_pos().y];
    grid[old_pos.get_pos().x][old_pos.get_pos().y]=grid[new_pos.get_pos().x][new_pos.get_pos().y];
    grid[new_pos.get_pos().x][new_pos.get_pos().y]=tempObjptr;
    return true;
}

void Object::print_obj(){
    cout<<"obj_name "<<Obj_name<<endl;
    cout<<"obj_pos "<<_x()<<" "<<_y()<<endl;
    cout<<"empty "<<empty<<endl;
}


int MOVEABLE_W(Object* obj){
    // cout<<"obj = "<<obj->getname()<<endl;
    while(true){
        
        int _x = obj->_x();
        int _y = obj->_y() - 1;
        if(grid[_x][_y]->empty){
            return 1;
        }
        // cout<<_x<<" "<<_y<<endl;
        int next_state = grid[_x][_y]->Determine_State();
        if(next_state == 2)
            return -1*0x3f3f3f3f;
        else if(next_state == 1)
            return MOVEABLE_W(grid[_x][_y]) + 1;
        else if(next_state == 3)
            return -1*0x3f3f3f3f;
        else
            return 1;
    }
}

int MOVEABLE_S(Object* obj){
    // cout<<"obj = "<<obj->getname()<<endl;
    while(true){
        
        int _x = obj->_x();
        int _y = obj->_y() + 1;
        if(grid[_x][_y]->empty){
            return 1;
        }
        // cout<<_x<<" "<<_y<<endl;
        int next_state = grid[_x][_y]->Determine_State();
        if(next_state == 2)
            return -1*0x3f3f3f3f;
        else if(next_state == 1)
            return MOVEABLE_S(grid[_x][_y]) + 1;
        else if(next_state == 3)
            return -1*0x3f3f3f3f;
        else
            return 1;
    }
}

int MOVEABLE_A(Object* obj){
    // cout<<"obj = "<<obj->getname()<<endl;
    while(true){
        
        int _x = obj->_x() - 1;
        int _y = obj->_y();
        if(grid[_x][_y]->empty){
            return 1;
        }
        // cout<<_x<<" "<<_y<<endl;
        int next_state = grid[_x][_y]->Determine_State();
        if(next_state == 2)
            return -1*0x3f3f3f3f;
        else if(next_state == 1)
            return MOVEABLE_A(grid[_x][_y]) + 1;
        else if(next_state == 3)
            return -1*0x3f3f3f3f;
        else
            return 1;
    }
}

int MOVEABLE_D(Object* obj){
    while(true){
        int _x = obj->_x() + 1;
        int _y = obj->_y();
        if(grid[_x][_y]->empty)
            return 1;
        int next_state = grid[_x][_y]->Determine_State();
        if(next_state == 2)
            return -1*0x3f3f3f3f;
        else if(next_state == 1)
            return MOVEABLE_D(grid[_x][_y]) + 1;
        else if(next_state == 3)
            return -1*0x3f3f3f3f;
        else
            return 1;
    }
}
#endif /* Object_hpp */
