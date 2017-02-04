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
#include <sstream>
#include <string>
#include "datawindow2.h"
using namespace std;

datawindow2::datawindow2(int num,  string bg, string bf, string d)
{
    //pass pointers
    // d_next=d;
    // b_next=b;
    // bag_next=bag;
    dict = d;
    bagfile=bg;
    num_player = num;
    boardfile = bf;
    secondWinLayout = new QHBoxLayout;
    
    //display
    playernameDisplayLayout = new QVBoxLayout();
    secondWinLayout->addLayout(playernameDisplayLayout);
    
    playerDisplay = new QLabel(" ");
    playernameDisplayLayout->addWidget(playerDisplay);
    
    playernameDisplayLayout->addStretch();
    
    //list of player
    playerListWidget = new QListWidget();
    QObject::connect(playerListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(displayplayer(int)));
    secondWinLayout->addWidget(playerListWidget);
    
    
    //form to add player
    formlayout = new QVBoxLayout();
    secondWinLayout->addLayout(formlayout);
    QString nump = QString::number(num);
    QString str = "Please enter " + nump + " player's name: ";
    namePlayerLabel = new QLabel(str);
    formlayout->addWidget(namePlayerLabel);
    
    namePlayer = new QLineEdit();
    formlayout->addWidget(namePlayer);
    
    //add button
    secondSaveButton = new QPushButton("&Save");
    confirm = new QPushButton("&Confirm");
    QObject::connect(confirm, SIGNAL(clicked()), this, SLOT(confirmpressed()));
    QObject::connect(secondSaveButton, SIGNAL(clicked()), this, SLOT(SaveButton()));
    formlayout->addWidget(secondSaveButton);
    formlayout->addWidget(confirm);
    setLayout(secondWinLayout);
}
datawindow2::~datawindow2()
{
    
}
//void datawindow2::gotoboard()
void datawindow2::SaveButton()
{
    int size_pn = playername.size();
    if(size_pn >= num_player)
    {
        showPopup("too many players ! ");
       
        hide();
        close();
    }
    else {
        playername.push_back(namePlayer->text().toStdString());
    }
    //create a list with person's name
    playerListWidget->addItem(namePlayer->text());
    namePlayer->setText("");
}
void datawindow2::displayplayer(int n)
{
    QString pName;
    pName = " " + QString::fromStdString(playername[n]);
    playerDisplay->setText(pName);
}
// vector<string>& datawindow2::all_player_name()
// {
//     return playername;
// }
void datawindow2::confirmpressed()
{
   // cout << playername.size() << endl;

    sboard = new Board(bagfile,boardfile,true,playername,dict);
    //sboard->show();
    hide();
}
void datawindow2::showPopup(string error)
{
    QString qerror = QString::fromStdString(error);
    QMessageBox msgBox;
    msgBox.setWindowTitle("ERROR");
    msgBox.setText(qerror);
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Close);
  msgBox.exec();
}

