#ifndef SQUARE_H_
#define SQUARE_H_


#include <string>
#include "player.h"
#include "Tile.h"
#include "Board.h"
#include "Bag.h"
#include "move.h"
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QApplication>
using namespace std;

class Tile;

class Square : public QPushButton
{
    Q_OBJECT
public:
    Square();
    Square(QString s ,QWidget* p);
    ~Square();
	Square(Tile * onboard, Tile * top, string multi);
    //setter
    void set_type(QString t);
    void set_show(string toshow);
    void set_onboard_tile(Tile *t);
    void set_multi(string mul);
    void set_occupy(bool oc);
    void set_row(int row);
    void set_col(int col);
    void set_used(bool b);
    void set_previous(string s);
    void set_shibushiblank(bool);
    //getter
    string get_previous();
    bool get_used();
    int get_row();
    int get_col();
    string get_show();
    string get_multi();
    Tile * get_onboard();
    Tile * get_top();
    bool get_occupy();
    bool get_shibushiblank();
    
private:
    QString type;
    Tile * m_onboard;
    Tile * m_top;
    string show;
    string previous;
    string multi;
    bool occupied;
    int m_row;
    int m_col;
    bool usedup;
    bool shibushiblank;
};
#endif /* SQUARE_H_ */
