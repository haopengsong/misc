/*
 * Board.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <cctype>
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
#include <QMessageBox>
#include <set>
#include <map>
#include <QString>

#include "move.h"
#include "Bag.h"
#include "Square.h"
#include "player.h"
#include "Tile.h"
#include "virtualBoard.h"
#include "Dictionary.h"
using namespace std;

class Move;
class Square;
class player;
class virtualBoard;
class Dictionary;

class Board : public QWidget
{
    Q_OBJECT
public:
    Board (string bg,string board_file_name, bool first,vector<string> pn, string dic_file_name);
    ~Board();
    void print_board();
    //place tiles
    //void place_tiles(int row, int col, Tiles* _tiles, int horver);
    bool addtiles(int row, int col, Tile * t);
    bool addtiles_style(int row_occ, int col_occ, int row, int col, Tile * t);
    Square * get_square(int row, int col);
    bool get_starboard();
    void set_starboard(bool bo);
    
    map<char,int> inside_bag(string bag_file_name);
    void refreshTheBoard();
    string refineupper (string & torefine);
    bool check_tiles(player * p, string letters);
    void MrXiaoBridge();
    bool place_tiles(string words, string vert, int row, int col,  Dictionary * dict);
    string refinelower (string & torefine);
    bool boardlookup(string words, string vert, int row, int col);
    bool check_tiles_two(player * p, string letters, bool b, string ori);
    bool check_tiles_three(player * p, string letters);
    void update_tiles( int num, player * p);
    int score(vector<Square*> vs);
    vector<Square*> all_location(string words, string vert, int row, int col);
    string playerscore();

    string scan(string wordspossibleBlank);
    bool checkforBlank(string wordspossibleBlank);
    void showPopup(string);
    void game_watcher();


public slots:
    void act();
    void doPass();
    void doExchange();
    void doPlace();



private:
    int currentplayer;
    int c_x,c_y;
    int _x, _y;
    int _startx, _starty;
    Square ***board;
    bool firsttime;

    QGridLayout *g;
    QVBoxLayout *v1;
    QVBoxLayout *v2;
    QHBoxLayout *h1;
    QVBoxLayout *overLayout;
    QHBoxLayout *buttonLayout;
    QComboBox * combox;
    QVBoxLayout *gameoverlayout;

    QLabel *overLabel;
    QLabel * bigdata;
    QLabel *score_earned;
    QLabel *bagRemain;
    QLabel *gameoverlabel;


    QWidget *overWindow;
    QWidget *window;
    QWidget *gameover;

    QPushButton *Exchange;
    QPushButton *Pass;
    QPushButton *Place;

    QLineEdit *p_enter_tiles;

    player * p;
    Move * _m;
    Bag * b;
    Dictionary *dict;
    virtualBoard * vb;

    int scorethisturn;
    string bag_file_name;
    string dic_file_name;
    vector<string> suoyouplayer;
    vector<player*> allplayer;
    map<char,int> thebag;


};


#endif /* BOARD_H_ */
