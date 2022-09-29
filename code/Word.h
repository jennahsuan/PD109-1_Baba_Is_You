#ifndef Word_h
#define Word_h

#include <vector>
using namespace std;

// set all subject word and "is" word blocks
class Word{
private:
    Position word_pos;
    int meaning;
    // integers stand for different meanings
    // 1:"is", 2:"flag", 3:"rock"...
public:
    Word()  {Word(0, 0, 0);}
    Word(int x, int y, int content);
    
    int means(){return meaning;}
    Vector2i get_pos(){return word_pos.get_pos();}
};

vector<Word> Sub;
vector<Word> IS;
vector<Word> Adj;

Word::Word(int x, int y, int content){
    word_pos = Position(x, y);
    meaning = content;
}




#endif /* Word_h */
