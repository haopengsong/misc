#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include "datawindow2.h"
#include "Dictionary.h"
#include "Bag.h"
#include "Board.h"
#include "Tile.h"

using namespace std;
class mainwindow : public QWidget
{
    Q_OBJECT

public:
    mainwindow(string dic, string bg, string bf);
    ~mainwindow();
    //void increment(int n);
    //void all_player_name();
public slots:
    void opendatawindow2();
    void doclose();
    //void dotransfer();

private:
    //first window asking for number of players
    QHBoxLayout * firstWinlayout;
    QLineEdit * numberPlayer;
    QLabel * numPlayerLabel;
    //buttons
    QPushButton * done;
    QPushButton * firstSaveButton;
    //second window to store each players name
    datawindow2 * newdatawindow;
    vector<string> playernames;
    string dict;
    string boardfile;
    string bagfile;
    //Bag bag_next;
    
    //int num_player;

};

#endif // MAINWINDOW_H
