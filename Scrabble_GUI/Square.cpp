#include "Square.h"

using namespace std;
Square::Square()
{
    shibushiblank = false;
}
Square::Square(QString t, QWidget * parent) : QPushButton(parent)
{
    type = t;
    setText(t);
}
Square::~Square()
{
    delete m_onboard;
    delete m_top;
}
Square::Square(Tile * on, Tile * up, string mul)
{
	//occupied = occ;
    m_onboard=on;
    m_top=up;
    multi=mul;
}

void Square::set_show(string toshow)
{
    show = toshow;
}
string Square::get_show()
{
    return show;
}
void Square::set_multi(string mul)
{
    multi=mul;
}
void Square::set_onboard_tile(Tile *t)
{
    m_onboard = t;
}
string Square::get_multi()
{
    return multi;
}
Tile * Square::get_onboard()
{
    return m_onboard;
}
Tile * Square::get_top()
{
    return m_top;
}
bool Square::get_occupy()
{
    return occupied;
}
void Square::set_occupy(bool oc)
{
    occupied = oc;
}
void Square::set_row(int row)
{
    m_row=row;
}
void Square::set_col(int col)
{
    m_col=col;
}
int Square::get_row()
{
    return m_row;
}
int Square::get_col()
{
    return m_col;
}
void Square::set_used(bool b)
{
    usedup=b;
}
bool Square::get_used()
{
    return usedup;
}
void Square::set_previous(string s)
{
    previous = s;
}
string Square::get_previous()
{
    return previous;
}
void Square::set_type(QString t)
{
    type = t;
}
void Square::set_shibushiblank(bool b)
{
    shibushiblank = b;
}
bool Square::get_shibushiblank()
{
    return shibushiblank;
}















