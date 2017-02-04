#include "mainwindow.h"
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

using namespace std;

mainwindow::mainwindow(string d, string bg, string bf)
{
    //pass pointers
    // d_next = d;
    // b_next = b;
    // bag_next = bag;
    bagfile=bg;
    boardfile = bf;
    dict = d;
    firstWinlayout = new QHBoxLayout;

    //form add
    numPlayerLabel = new QLabel("Please enter the number of players(1-8): ");
    firstWinlayout->addWidget(numPlayerLabel);

    //number players
    numberPlayer = new QLineEdit();
    firstWinlayout->addWidget(numberPlayer);

    firstSaveButton = new QPushButton("&Save");
    firstWinlayout->addWidget(firstSaveButton);
  

   QObject::connect (firstSaveButton , SIGNAL(clicked()), this, SLOT(opendatawindow2()));
   QObject::connect (firstSaveButton , SIGNAL(clicked()), this, SLOT(doclose()));
    setLayout(firstWinlayout);
}
mainwindow::~mainwindow()
{
    
}
void mainwindow::opendatawindow2()
{
    int n= numberPlayer->text().toInt();
    newdatawindow = new datawindow2(n,bagfile,boardfile,dict);
    newdatawindow->setWindowTitle("user info");
    newdatawindow->show();
    // vector<string> temp = newdatawindow->all_player_name();
    // cout << temp.size() << endl;
    // for (unsigned int i=0;i<temp.size();i++)
    // {
    //     cout << temp[i] << endl;
    // }

}
void mainwindow::doclose()
{
	hide();
}
// void mainwindow::all_player_name()
// {
//     vector<string> temp = newdatawindow->all_player_name();
//     cout << temp.size() << endl;
//     for (unsigned int i=0;i<temp.size();i++)
//     {
//         cout << temp[i] << endl;
//     }
// }
