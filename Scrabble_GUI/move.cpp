#include "move.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>


using namespace std;

Move::Move()
{
   
}
Move::~Move()
{
    
}
bool Move::pass(int num)
{
    return topass == num;
}
//add player
void Move::addplayer(player * p)
{
    suoyouplayer.push_back(p);
}
vector<player*> Move::getplayer()
{
    return suoyouplayer;
}

bool Move::game_over_player()
{
    for(unsigned int i=0;i<suoyouplayer.size();i++)
    {
        player * temp_p = suoyouplayer.at(i);
        if(temp_p->tiles_left() == 0)
        {
            return false;
        }
    }
    return true;
}
void Move::add_map(string name, set<Tile *> tiles)
{
    map<string,set<Tile*> >::iterator it;
    if(player_map.find(name) == player_map.end())
    {//not in map,add it
        player_map.insert(make_pair(name, tiles));
    }
}
map<string,set<Tile*> >& Move::return_map()
{
    return player_map;
}
Bag* Move::getbag()
{
    return b;
}
player* Move::get_one_player(int num)
{
    return suoyouplayer.at(num-1);
}

bool Move::pass_over()
{
    for (unsigned int i = 0;i<suoyouplayer.size();i++)
    {
        if(suoyouplayer.at(i)->get_pass() == false)
        {
            return false;
        }
    }
    return true;
}
void Move::score_board(){
    
    cout <<" Final Score : " << endl;
    for(unsigned int i =0;i<suoyouplayer.size();i++)
    {
        cout << suoyouplayer.at(i)->get_name() <<" ";
        cout << suoyouplayer.at(i)->get_score() << endl;
    }
    cout << "winner is :" << endl;
    int largest = 0; int temp1=0;
    for (unsigned int j = 0;j<suoyouplayer.size();j++)
    {
        temp1=suoyouplayer.at(j)->get_score();
        while(temp1>largest){
            largest=temp1;
        }
    }
    for (unsigned int j = 0;j<suoyouplayer.size();j++)
    {
        if(largest == suoyouplayer.at(j)->get_score()){
            cout << suoyouplayer.at(j)->get_name() << endl;
        }
    }
    cout << "thanks for playing! " <<endl;
}






