#ifndef DATAWINDOW2_H
#define DATAWINDOW2_H

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
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <QListWidget>
#include "Dictionary.h"
#include "Bag.h"
#include "Board.h"
#include "Tile.h"


using namespace std;

//class player;

class datawindow2 : public QWidget
{
    Q_OBJECT
    
public:
    datawindow2(int numplayer, string bg, string bf, string dic);
    ~datawindow2();
    //vector<string>& all_player_name();
    void showPopup(string);
    
    public slots:
    //void gotoboard();
    void SaveButton();
    void displayplayer(int n);
    void confirmpressed();
private:
    
    QHBoxLayout * secondWinLayout;
    QVBoxLayout * playernameDisplayLayout;
    QVBoxLayout * formlayout;
    
    QListWidget * playerListWidget;
    QLabel * playerDisplay;
    
    QLineEdit * namePlayer;
    QLabel * namePlayerLabel;
   // Qlabel * numberPlayer;
    //buttons
    QPushButton * confirm;
    QPushButton * secondSaveButton;
    int num_player;
    //player * p;
    vector<string> playername;
    string dict;
    string boardfile;
    //Bag  bag_next;
    string bagfile;

    Board * sboard;
    
};

#endif
