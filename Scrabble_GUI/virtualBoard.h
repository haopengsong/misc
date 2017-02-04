/*
 * virtualBoard.h
 */


#ifndef virtualBoard_H_
#define virtualBoard_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <cctype>
#include <iomanip>

#include "Square.h"
#include "player.h"
#include "Tile.h"
#include "Board.h"
using namespace std;

class Square;

class virtualBoard {
public:

    virtualBoard();
    virtualBoard (std::string virtualBoard_file_name, bool first);
    ~virtualBoard();
    void print_virtualBoard();
    //place tiles
    //void place_tiles(int row, int col, Tiles* _tiles, int horver);
    bool addtiles(int row, int col, Tile * t);
    bool addtiles_style(int row_occ, int col_occ, int row, int col, Tile * t);
    Square * get_square(int row, int col);
    
    bool get_starvirtualBoard();
    void set_starvirtualBoard(bool bo);

    bool boardobserver(vector<Square*> tocompare);
    void blankcordinates(string horver, string words, int row, int col);


private:
    int _x, _y;
    int _startx, _starty;
    Square ***board;
    bool firsttime;
};


#endif /* virtualBoard_H_ */
