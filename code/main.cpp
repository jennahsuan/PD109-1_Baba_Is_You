#include "Baba.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

void readfile();
void __init(){
    for(int i=0;i<MAX_X;i++)
        for(int j=0;j<MAX_Y;j++){
            grid[i][j] = new Object;
            grid[i][j]->set_objpos(i, j);
            grid[i][j]->empty = true;
            grid[i][j]->set_name("Default");
        }
    set_up_meaning();
    readfile();
    for(int i=0;i<WORDBLOCK_IS.size();i++)
        cout<<WORDBLOCK_IS[i].getname()<<" ";
    compare.push_back(make_pair("WALL", "W_WALL"));
    compare.push_back(make_pair("BABA", "W_BABA"));
    compare.push_back(make_pair("FLAG", "W_FLAG"));
    compare.push_back(make_pair("ROCK", "W_ROCK"));
}


int main(int argc, const char * argv[])
{
    sf::Music music;
    if (!music.openFromFile("C:\\babaimage\\babaBGM.wav"))
		std::cout << "Can't load music" << std::endl;
    music.setLoop(true);
    music.setVolume(10);
    music.play();

    ios::sync_with_stdio(0);
    cin.tie(0);
    __init();
    RenderWindow window(VideoMode(MAP_X_BOUND*30, MAP_Y_BOUND*30), "Baba is You");
    Baba testBaba;

    for(int i=0;i<WORDBLOCK_ADJ.size();i++)
        if(WORDBLOCK_ADJ[i].getname() == "W_YOU"){
            int x = WORDBLOCK_ADJ[i]._x();
            int y = WORDBLOCK_ADJ[i]._y();
            if(y >= 2){
                if(grid[x][y - 1]->getname() == "W_IS")
                    if(grid[x][y - 2]->getname() == "W_BABA")
                        for(int j=0;j<SUBJECTS.size();j++)
                            if(SUBJECTS[j].getname() == "BABA")
                                testBaba.YOU = &SUBJECTS[j];
            }
            if(x < MAP_X_BOUND-2){
                if(grid[x + 1][y]->getname() == "W_IS")
                    if(grid[x - 2][y]->getname() == "W_BABA")
                        for(int j=0;j<SUBJECTS.size();j++)
                            if(SUBJECTS[j].getname() == "BABA")
                                testBaba.YOU = &SUBJECTS[j];
            }
        }


    while (window.isOpen()) {
        
        Event e;
        while(window.pollEvent(e))
        {
            if(e.type == Event::Closed)
                window.close();
            if(e.type == Event::KeyPressed){
                if(e.key.code == Keyboard::Up || e.key.code == Keyboard::W)
                    testBaba.moveUp();
                else if(e.key.code == Keyboard::Down || e.key.code == Keyboard::S)
                    testBaba.moveDown();
                else if(e.key.code == Keyboard::Left || e.key.code == Keyboard::A)
                    testBaba.moveLeft();
                else if(e.key.code == Keyboard::Right || e.key.code == Keyboard::D)
                    testBaba.moveRight();
                else if(e.key.code == Keyboard::T)
                    window.close();
                else
                    cout << "Invalid input" << endl;
            }
            //testBaba.print();
            
        }
        window.clear();
        for(int i=0;i<MAP_X_BOUND;i++)
            for(int j=0;j<MAP_Y_BOUND;j++){
                if(grid[i][j]->empty)
                    continue;
                Texture t;

                if(grid[i][j]->means() == 0 and testBaba.direction()!=4){
                    int F = testBaba.direction();
                    t.loadFromFile(images[F + 13]);
                }
                else
                    t.loadFromFile(images[grid[i][j]->means()]);

                grid[i][j]->s.setTexture(t);
                grid[i][j]->s.setPosition(grid[i][j]->_x()*30, grid[i][j]->_y()*30);
                window.draw(grid[i][j]->s);
            }
        if(testBaba.WinOrNot()){
            
            Texture t ;
            t.loadFromFile(images[13]);  // congradulations  
            Sprite congrats(t);
            congrats.setPosition(MAP_X_BOUND*15-138, MAP_Y_BOUND*15-56);
            window.draw(congrats);
        }
        
       
        window.display();
        
    }
    return 0;
}

void readfile(){
    ifstream ifs ( "C:\\babaimage\\BABA IS YOU lv. 2.txt" , ifstream::in ); // 依自己電腦匯入 
    string str;
    Object* gtemp[18][18];
    while (ifs >> str){
        if(str == "WIDTH"){
            ifs >> str;
            MAP_X_BOUND = string_to_int(str);
        }
        else if(str == "HEIGHT"){
            ifs>> str;
            MAP_Y_BOUND = string_to_int(str);
        }
        else if(str == "OBJECTS:"){
            while(ifs >> str){
                string name = str;
                int x = 0, y = 0;
                ifs >> str;
                x = string_to_int(str);
                ifs >> str;
                y = string_to_int(str);
                Texture t;
                t.loadFromFile(images[str_to_int[name]]);
                Object* obj = new Object(Position(x, y), name, t);
                if(str_to_int[name] < 4 ){
                    SUBJECTS.push_back(*obj);
                    grid[x][y] = obj;
                }
                else if(str_to_int[name] >= 4 && str_to_int[name] <= 7){
                    WORDBLOCK_SUB.push_back(*obj);
                    grid[x][y] = obj;
                    gtemp[x][y] = obj;
                }
                else if(str_to_int[name] >= 8 && str_to_int[name] <= 11){
                    WORDBLOCK_ADJ.push_back(*obj);
                    grid[x][y] = obj;
                }
                else if(str_to_int[name] == 12 ){
                    WORDBLOCK_IS.push_back(*obj);
                    grid[x][y] = obj;
                }
                else
                grid[x][y]->empty = false;
            }
        }
        else
            cout<<"ERROR"<<endl;
    }
    ifs.close();
}


