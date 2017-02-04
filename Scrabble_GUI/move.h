#ifndef MOVE_H_
#define MOVE_H_

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include "player.h"
#include "Tile.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Board.h"
#include "Square.h"
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QApplication>
#include <QLabel>
#include <QComboBox>
using namespace std;

 class player;
// class Tile;
// class Bag;

class Move {
public:
    Move();
    ~Move();
    //pass if true
    //1 for pass this turn
    bool pass(int num);
    
    //function for exchange
   // void exchange(string &tile_to_exchange, string& name);
    
    //helper for checking valid input for exchange
    //bool check_tiles(set<Tile*>& t, string letters);
    
    //get all players
    vector<player*> getplayer();
    
    //add player 
    void addplayer(player * p);

    //game observer
    //bool game_over_bag();
    bool game_over_player();
    
    //add to map
    void add_map(string name, set<Tile*> tiles);

    Bag* getbag();

    player* get_one_player(int num);
    
    map<string,set<Tile*> >& return_map();

    //bool makeMove(player &p, col row, &board);
 
    //Board * getboard();
    bool pass_over();
    
    void score_board();

private:
    //for pass
    //Board * bo;
    int topass;
    Bag *b;
    vector<player*> suoyouplayer;
    map<string,set<Tile*> > player_map;
    
};

#endif /* Move_H_ */
