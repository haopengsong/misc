#ifndef PLAYER_H_
#define PLAYER_H_
#include "Tile.h"
#include "Bag.h"
#include "Board.h"
#include "Square.h"
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
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

class Tile;


class player {
public:
    //user profile
    //constructor
    player();
    player (string name, set<Tile*> tiles, int score);
    ~player ();
    
    //get player's name
    string get_name() const;
    
   // void set_score(int s);
    //get current score
    int get_score();
    
    //get tiles of the player
    set<Tile*>& tile_of_player();
    
    //add score
    void set_score(int points);
    
    //tiles left
    int tiles_left();
    
    bool hastiles(string words);
    
    void set_pass(bool b);
    bool get_pass();
    
    string tilestring();
            
private:
    //Board * b;
    string m_name;
    int m_score;
    //int m_totalscore;
    set<Tile*> m_tiles;
    bool m_turn;
    string tile;
    
};


#endif /* PLAYER_H_ */
