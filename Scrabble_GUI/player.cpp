#include "player.h"


using namespace std;

player::player()
{
    
}
player::~player()
{
    
}
player::player(string name, set<Tile*> tiles, int score)
{
    m_name = name;
    m_tiles = tiles;
    m_score = score;
}
string player::get_name() const
{
    return m_name;
}
int player::get_score()
{
   
    return m_score;
}
void player::set_score(int point)
{
    m_score = m_score + point;
}
set<Tile*>& player::tile_of_player()
{
    return m_tiles;
}
int player::tiles_left()
{
    return m_tiles.size();
}
bool player::hastiles(string letters)
{
    
    set<Tile*>::iterator it2;
    int *allfound = new int[letters.length()];
    for(unsigned int a=0; a<letters.length(); a++)
    {
        for(it2=m_tiles.begin(); it2!=m_tiles.end(); ++it2)
        {
            Tile * temp1 = *it2;
            //////
           // cout << temp1->getLetter() << endl;
            if(temp1->getLetter() == letters[a])
            {
                allfound[a] = 1;
            }
        }
    }
    for (unsigned int c=0;c<letters.length();c++)
    {
        if(allfound[c]!=1)
            return false;
    }
    return true;
}
void player::set_pass(bool b)
{
    m_turn = b;
}
bool player::get_pass()
{
    return m_turn;
}
string player::tilestring()
{
    string retval;
    
    for(set<Tile*>::iterator it=m_tiles.begin(); it!=m_tiles.end(); ++it)
    {
        //show tile
        string cancate;
        string charstring;
        stringstream ss;
        Tile * temp_tile = *it;
        int num = temp_tile->getPoints();
        ss<<num;
        string numstring;
        ss>>numstring;
        numstring = numstring + "]";
        ss.clear();
        char letter = temp_tile->getLetter();
        ss<<letter;
        ss>>charstring;
        charstring="["+charstring;
        cancate = charstring + numstring;
        retval = retval + cancate;
        
    }
    return retval;
}
