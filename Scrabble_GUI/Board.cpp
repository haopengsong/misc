/*
 * Board.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.
// haha
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "Board.h"
////
using namespace std;

Board::Board(string bg, string board_file_name, bool first, vector<string> pn, string dic_file_name)
{
    scorethisturn = 0;
    //set the bag
    bag_file_name = bg;
    thebag = inside_bag(bag_file_name);
    ///////////////
    

    //set current player
    currentplayer=0;
    //number/name of player
    suoyouplayer=pn;
    //virtualBoard
    vb = new virtualBoard(board_file_name,true);
    //dictionary
    dict = new Dictionary(dic_file_name);
    //initialize bag
    b = new Bag(bg,23);
    //create move
    _m = new Move;
    //first turn of the game
    firsttime = first;
    //score of player
    int initialscore = 0;

    //read board
    ifstream boardFile (board_file_name.c_str());
    string row;

    _x = _y = _startx = _starty = 0; // to appease compiler
    if (!boardFile.is_open())
        throw invalid_argument("Cannot open file: " + board_file_name);
    getline (boardFile, row);
    stringstream s1 (row);
    s1 >> _x >> _y;
    getline (boardFile, row);
    stringstream s2 (row);
    s2 >> _startx >> _starty;
    _startx --;
    _starty --;  // coordinates from 0 in array

    // Anything else you need to initialize?
    board = new Square**[_x];
    for(int a=0; a<_y; a++)
    {
        board[a]=new Square*[_y];
        for(int b=0; b<_x; b++)
        {
            board[a][b]=new Square();
            board[a][b]->setMaximumWidth(30);
            board[a][b]->setMaximumHeight(30);
            board[a][b]->set_occupy(false);
            board[a][b]->set_used(false);
        }
    }

    g = new QGridLayout;
    for (int i = 0 ; i < _y; ++ i)
    {
        
        getline (boardFile, row);
        for (int j = 0; j < _x; ++ j)
        {

            // Fill in the following based on how you store the board.
            if (i == _starty && j == _startx)
            {
                
                QString t = "*";
                board[j][i]=new Square(t,0);
                board[j][i]->setMaximumWidth(30);
                board[j][i]->setMaximumHeight(30);
                g->addWidget(board[j][i],j+1,i+1);
                QObject::connect(board[j][i], SIGNAL(clicked()), this, SLOT(act()));
                board[j][i]->set_row(i);
                board[j][i]->set_col(j);
                board[j][i]->set_multi("2W");
                board[j][i]->set_show("***");
                board[j][i]->set_previous("***");

              
            }
            else switch (row[j])
                {
                case '.' :
                {
                    board[j][i] = new Square;
                    board[j][i]->setMaximumWidth(30);
                    board[j][i]->setMaximumHeight(30);
                    g->addWidget(board[j][i],j+1,i+1);
                    QObject::connect(board[j][i], SIGNAL(clicked()), this, SLOT(act()));
                    board[j][i]->set_previous(" ...");
                    board[j][i]->set_row(i);
                    board[j][i]->set_col(j);
                    board[j][i]->set_multi(".");
                    board[j][i]->set_show(" ...");
                    //cout  <<setw(4)<<board[j][i];
                }
                break;
                case '2' : {
                    QString t = "2L";
                    board[j][i] = new Square(t,0);
                    board[j][i]->setMaximumWidth(30);
                    board[j][i]->setMaximumHeight(30);
                    g->addWidget(board[j][i],j+1,i+1);
                    QObject::connect(board[j][i], SIGNAL(clicked()), this, SLOT(act()));
                    board[j][i]->set_previous(" 2L");
                    board[j][i]->set_row(i);
                    board[j][i]->set_col(j);
                    board[j][i]->set_multi("2L");
                    board[j][i]->set_show(" 2L");
                }
                //cout << setw(4)<<board[j][i];
                break;
                case '3' :
                {
                    QString t = "3L";
                    board[j][i] = new Square(t,0);
                    board[j][i]->setMaximumWidth(30);
                    board[j][i]->setMaximumHeight(30);
                    g->addWidget(board[j][i],j+1,i+1);
                    QObject::connect(board[j][i], SIGNAL(clicked()), this, SLOT(act()));
                    board[j][i]->set_previous(" 3L ");
                    board[j][i]->set_row(i);
                    board[j][i]->set_col(j);
                    board[j][i]->set_multi("3L");
                    board[j][i]->set_show(" 3L ");
                }   //cout << setw(4)<<board[j][i];
                break;
                case 'd' :
                {
                    QString t = "2W";
                    board[j][i] = new Square(t,0);
                    board[j][i]->setMaximumWidth(30);
                    board[j][i]->setMaximumHeight(30);
                    g->addWidget(board[j][i],j+1,i+1);
                    QObject::connect(board[j][i], SIGNAL(clicked()), this, SLOT(act()));
                    board[j][i]->set_previous(" 2W ");
                    board[j][i]->set_row(i);
                    board[j][i]->set_col(j);
                    board[j][i]->set_multi("2W");
                    board[j][i]->set_show(" 2W ");
                }//cout <<setw(4)<< board[j][i];
                break;
                case 't' :
                {
                    QString t = "3W";
                    board[j][i] = new Square(t,0);
                    board[j][i]->setMaximumWidth(30);
                    board[j][i]->setMaximumHeight(30);
                    g->addWidget(board[j][i],j+1,i+1);
                    QObject::connect(board[j][i], SIGNAL(clicked()), this, SLOT(act()));
                    board[j][i]->set_previous(" 3W ");
                    board[j][i]->set_row(i);
                    board[j][i]->set_col(j);
                    board[j][i]->set_multi("3W");
                    board[j][i]->set_show(" 3W ");
                }
                //cout <<setw(4)<< board[j][i];
                break;
                default:
                    string error = "Improper character in Board file: ";
                    throw invalid_argument(error + row[j]);
                }
        }

    }
    //adding players
    for(unsigned int i=0; i<suoyouplayer.size(); i++)
    {
        set<Tile*> p_tiles = b->drawTiles(7);
        p = new player(suoyouplayer[i],p_tiles,initialscore);
        _m->addplayer(p);
    }
    //grab all players
    allplayer = _m->getplayer();


    ////player tile display
    //QString pTileDisplay =QString::fromStdString(vp[cnt]->tilestring());

    window = new QWidget;
    overWindow = new QWidget;

    gameover = new QWidget;
    gameoverlabel = new QLabel();
    gameoverlayout = new QVBoxLayout;
    gameoverlayout->addWidget(gameoverlabel);
    gameover->setWindowTitle("GameOver");
    gameover->setLayout(gameoverlayout);

    //SETup game over window
    overLayout = new QVBoxLayout;

    //game over window
    overLabel = new QLabel("All pass in one turn , Game over");
    overLayout->addWidget(overLabel);
    overWindow->setLayout(overLayout);

    //overall layout
    h1 = new QHBoxLayout;

    //board display layout
    v1 = new QVBoxLayout;
    h1->addLayout(v1);

    //board
    v1->addLayout(g);

    //tile display layout
    v2 = new QVBoxLayout;
    h1->addLayout(v2);

    //board show the first player's name
    string sfpn = suoyouplayer[currentplayer];
    string sfpt = allplayer[currentplayer]->tilestring();
    //cout << "sfpt   " << sfpt << endl;
    QString qsfpn = QString::fromStdString(sfpn);
    QString qsfpt = QString::fromStdString(sfpt);
    //SCORE
    QString qsquanbuscore = QString::fromStdString(playerscore());


    bigdata = new QLabel(qsfpn + " It's your turn, \n" +
                         " Your tiles are :  \n" + qsfpt + "\n" + "Current Score: \n" + qsquanbuscore);
   // allplayer[currentplayer]->set_pass(true);

    bigdata->setFrameStyle(QFrame::StyledPanel|QFrame::Sunken);
    bigdata->setAlignment(Qt::AlignCenter );
    bigdata->setWordWrap(true);
    //bigdata->setText("aaa");
    v2->addWidget(bigdata);

    //score earned for this turn
    score_earned = new QLabel("Running Score \n");
    v2->addWidget(score_earned);

    int numtiles = b->tilesRemaining();
    QString numT = QString::number(numtiles);
    bagRemain = new QLabel("tiles remaining : " + numT);
    v2->addWidget(bagRemain);

    //enter tile
    p_enter_tiles = new QLineEdit();
    v2->addWidget(p_enter_tiles);

    //add button layout
    buttonLayout = new QHBoxLayout;
    v2->addLayout(buttonLayout);

    //combo box
    combox = new QComboBox;
    buttonLayout->addWidget(combox);

    combox->addItem("vertical");
    combox->addItem("horizontal");
    buttonLayout->addWidget(combox);

    //add button
    Exchange = new QPushButton("Exchange");
    buttonLayout->addWidget(Exchange);
    QObject::connect (Exchange , SIGNAL(clicked()), this, SLOT(doExchange()));

    Pass = new QPushButton("Pass");
    buttonLayout->addWidget(Pass);
    QObject::connect (Pass , SIGNAL(clicked()), this, SLOT(doPass()));

    Place = new QPushButton("Place");
    buttonLayout->addWidget(Place);
    QObject::connect (Place , SIGNAL(clicked()), this, SLOT(doPlace()));


    window->setLayout(h1);
    window->setWindowTitle("Scrabble");
    window->show();
    boardFile.close ();
}
Board::~Board()
{
    for(int i=0; i<_x; i++)
    {
        for (int j=0; j<_y; j++) {
            delete board[i][j];
        }
        delete board[i];
    }
    delete board;
    delete g;
    delete Exchange;
    delete Pass;
    delete Place;
    delete dict;
    delete p;
    delete _m;
    delete b;
    delete p_enter_tiles;
    delete window;
    delete overWindow;
    delete overLabel;
    delete combox;
    delete score_earned;
}
string Board::playerscore()
{
    string score_info;
    for(unsigned int j=0; j<allplayer.size(); j++)
    {
        string temp;
        string sname = allplayer[j]->get_name();
        stringstream ss;
        int pscore = allplayer[j]->get_score();
        ss<<pscore;
        string sscore;
        ss>>sscore;
        temp = sname + ": " +sscore + " ";
        score_info+=temp;
    }
    return score_info;

}
void Board::print_board()
{
    cout << "    " ;
    for(int a=0; a<_x; a++)
    {
        cout << " ";
        cout <<setw(4)<< a+1 ;
    }
    cout << endl;
    for (int i = 0; i < _x; i++) {
        cout <<setw(5) <<  i+1 << " ";
        for (int j = 0; j < _y; j++) {
            cout <<setw(4) << board[i][j]->get_show() << " ";
            //cout <<setw(2) << " ";
        }
        cout << endl;
    }
    cout << endl;
}
bool Board::addtiles(int row, int col, Tile * t)
{
    //cout <<"row, col : " << row << " ," << col << endl;
    if(board[row][col]->get_occupy()==false)
    {
        stringstream ss;
        char toboard;
        board[row][col]->set_onboard_tile(t);
        toboard=t->getLetter();
        //cout << "to board " << toboard << endl;
        ss<<toboard;
        string toboard_s;
        ss>>toboard_s;
        //cout << "to board s " << toboard_s  << endl;
        board[row][col]->set_show(toboard_s);
        board[row][col]->set_occupy(true);
    }
    else {
        showPopup("You can not add tile to a spot that is occupied" );
       
        return false;
    }
    return true;
}
void Board::MrXiaoBridge()
{
    QString buttonlabel;
    for (int i = 0 ; i < _y; ++ i)
    {
        for (int j = 0; j < _x; ++ j)
        {
            buttonlabel = QString::fromStdString(vb->get_square(j,i)->get_show());
            board[j][i]->setText(buttonlabel);
        }
    }

}
Square * Board::get_square(int row, int col)
{
    return board[row][col];
}
bool Board::get_starboard()
{
    return firsttime;
}
void Board::set_starboard(bool oc)
{
    firsttime = oc;
}

void Board::act()
{
    //QString str = tiles->text();
    QPushButton *called = (QPushButton*) QObject::sender();

    for (int x = 0; x < _x; x++) {
        for (int y = 0; y < _y; y++) {
            if (board[x][y] == called) {
                c_x = x;
                c_y = y;
            }
        }
    }
    
}
map<char,int> Board::inside_bag(string bag_file_name)
{
    map<char,int> inbag;
    ifstream bagFile (bag_file_name.c_str());

    if (bagFile.is_open())
    {
        string line;
        while (getline (bagFile, line))
        {
            stringstream ss (line);
            char c;
            int points;
            int count;
            ss >> c >> points >> count;

            //cout << c <<" " << points <<endl;
            inbag.insert(make_pair(c, points));

        }
        bagFile.close ();
    }
    return inbag;
}
void Board::doPass()
{
    //game_watcher();
    //set current player to pass
   
    allplayer[currentplayer]->set_pass(true);
    if(_m->pass_over())
    {
        game_watcher();
        
    }
    if(currentplayer == int(allplayer.size()-1))
    {
        currentplayer=0;
    }
    currentplayer++;
    
    //refresh the board
    refreshTheBoard();
}
string Board::refineupper(string & torefine)
{
    //cout << " torefine " << torefine << endl;
    string input;
    char in;
    for(unsigned int i=0; i<torefine.length(); i++)
    {

        in = toupper(torefine[i]);
        //cout << " refine " << in << endl;
        input = input + in;
    }
    return input;
}
void Board::refreshTheBoard()
{
    stringstream ss;
    ss<<scorethisturn;
    string sthisturn;
    ss>>sthisturn;
    ss.clear();
   
   
    //update player name and tiles
    int playerIndex=currentplayer-1;
    if(playerIndex==-1)
    {
        playerIndex=0;
    }
    else if (playerIndex == int(suoyouplayer.size()))
    {
        playerIndex = suoyouplayer.size()-1;
    }
    else {
        playerIndex = currentplayer-1;
    }
     int pscore = allplayer[playerIndex]->get_score();
    //cout << " pscore " << pscore << endl;
    ss<<pscore;
    string pttscore ;
    ss>>pttscore;

    string sfpt = allplayer[currentplayer]->tilestring();
    QString qsfpt = QString::fromStdString(sfpt);
    QString qsquanbuscore = QString::fromStdString(playerscore());

    int numtiles = b->tilesRemaining();
    QString numT = QString::number(numtiles);
    bagRemain->setText("Tiles Remaining : " + numT);
    bigdata->setText(QString::fromStdString(suoyouplayer[currentplayer])+
                     " It's your turn, \n" + " Your tiles are :  \n" + qsfpt +"\n" + "Current Score: \n" + qsquanbuscore);
    score_earned->setText(QString::fromStdString(suoyouplayer[playerIndex]) + " you earned " +
                          QString::fromStdString(sthisturn) + "points on your move \n Your total score is : \n" +
                          QString::fromStdString(pttscore));
    MrXiaoBridge();

}
bool Board::check_tiles(player * p, string letters)
{


    if(letters.length()>7)
        return false;

    set<Tile*>::iterator it2;
    int *allfound = new int[letters.length()];
    for(unsigned int a=0; a<letters.length(); a++)
    {
        for(it2=p->tile_of_player().begin(); it2!=p->tile_of_player().end(); ++it2)
        {
            Tile * temp1 = *it2;
            if(temp1->getLetter() == letters[a])
            {
                allfound[a] = 1;
            }
        }
    }
    for (unsigned int c=0; c<letters.length(); c++)
    {
        if(allfound[c]!=1)
            return false;
    }
    set<Tile*>::iterator it1;
    bool found = false;

    int point_of_letter = -1;
    for(unsigned int k=0; k<letters.length(); k++)
    {
        for(it1=p->tile_of_player().begin(); it1!=p->tile_of_player().end(); ++it1)
        {
            found=false;
            Tile * temp = *it1;

            if(temp->getLetter() == letters[k])
            {
                point_of_letter=temp->getPoints();
                found = true;
                break;
            }
        }
        if(found)
        {
            char tofind=letters[k];

            Tile * tobag = new Tile(tofind,point_of_letter);
            b->addTile(tobag);
            //cout << " size bag new " << b.tilesRemaining() << endl;
            p->tile_of_player().erase(it1);
        }
        else {
            return false;
        }
    }
    return true;
}
void Board::update_tiles(int num, player * p)
{

    set<Tile*> drawed = b->drawTiles(num);

    if(p->tile_of_player().size() <= 7)
    {
        ////////////
        //cout << "aaaaaaaaaaaa" << endl;
        for(set<Tile*>::iterator it=drawed.begin(); it!=drawed.end(); ++it)
        {
            
           // cout << temp->getLetter() << endl;
            p->tile_of_player().insert(*it);
        }
    }
}
//blank tiles
string Board::scan(string wordspossibleBlank)
{
    for(unsigned int i=0; i<wordspossibleBlank.length(); i++)
    {
        if(wordspossibleBlank[i] == '?')
        {
            //erase the blank tiles
            wordspossibleBlank.erase(wordspossibleBlank.begin()+i);

        }
    }
    return wordspossibleBlank;
}
bool Board::checkforBlank(string wordspossibleBlank)
{
    for(unsigned int i=0; i<wordspossibleBlank.length(); i++)
    {
        if(wordspossibleBlank[i] == '?')
        {
            return true;
        }
    }
    return false;
}

void Board::doPlace()
{
    //game_watcher();
    string sss1 = p_enter_tiles->text().toStdString();
    string sss2 = scan(p_enter_tiles->text().toStdString());
    string ori = refineupper(sss1);
    string mod = refineupper(sss2);

    for(unsigned int i=0; i<ori.length(); i++)
    {
        if(ori[i] == '?' )
        {
            //erase the blank tiles
            ori.erase(i+1,1);
            //cout << "i  " << i << endl;
        }
    }
    
    // cout << "words ORI " << ori << endl;
    // cout << "words mod " << mod << endl;

    string vh = combox->currentText().toStdString();
    string verhor;
    if(vh == "vertical") {
        verhor = "|";
    }
    else if(vh == "horizontal")
    {
        verhor = "-";
    }

    //mark the blank tile's location
    if(checkforBlank(p_enter_tiles->text().toStdString()))
    {
        vb->blankcordinates(verhor, mod, c_x, c_y);
    }

    //place start
    if(vb->get_starvirtualBoard() && (c_x != 7 || c_y != 7))
    {
        currentplayer--;
       showPopup("the game must start at the star square, please try another move");
        //cout << "the game must start at the star square, please try another move" << endl;
        
    
    }
    else
    {
        vb->set_starvirtualBoard(false);

        //location
        vector<Square*> vs_ = all_location(mod, verhor, c_x, c_y);
        //if player used up all tiles in one turn and it
        //forms a word then 50 points bouns
        if(mod.length() == 7 && check_tiles_two(allplayer[currentplayer], mod , checkforBlank(ori), ori))
        {
            if(dict->checkword(mod))
            {
                allplayer[currentplayer]->set_score(50);
            }
        }
        if(!vb->boardobserver(vs_) && c_x!=7 && c_y!= 7)
        {
             currentplayer--;
            showPopup("at least one tile must be adjacent to a previously placed tile. try again");
           
        }
        else if(check_tiles_two(allplayer[currentplayer], mod, checkforBlank(ori), ori))
        {
            bool place_it = place_tiles(mod, verhor, c_x, c_y, dict);
            if(place_it == true)
            {
                check_tiles_three(allplayer[currentplayer], mod);
                update_tiles((int)mod.length(),allplayer[currentplayer]);

                //score
                scorethisturn = score(vs_);
               // cout << "score for this turn "<< scorethisturn << endl;

                allplayer[currentplayer]->set_score(scorethisturn);
            }
            if(!place_it) {
                currentplayer--;
      
                showPopup("wrong input try again");
               
            }
        }
        else 
        {

                currentplayer--;
            showPopup(" You do not have these letters ! try again" );
         
        }
    }
    //clear the input
    if(currentplayer == int(allplayer.size()-1))
    {
        currentplayer=0;
    }
    else {
        currentplayer++;
    }
    p_enter_tiles->setText("");
    ///////////
    //display virtualboard
    //vb->print_virtualBoard();
    refreshTheBoard();

}
void Board::doExchange()
{

//cout << "t "<<b->tilesRemaining() << endl;
    //game_watcher();
    //tiles user entered
    string tilestoexchange = p_enter_tiles->text().toStdString();
    string uppertilestoexchange = refineupper(tilestoexchange);

    bool check_for_exchange = check_tiles(allplayer[currentplayer], uppertilestoexchange);
    if(!check_for_exchange)
    {
        showPopup("NO SUCH TILES");
       // cout << "error " << endl;
        currentplayer--;
    }
    else {
        //redraw tiles for player
        update_tiles((int)uppertilestoexchange.length(),allplayer[currentplayer]);
    }

    //clear the input
    if(currentplayer == int(allplayer.size()-1))
    {
        currentplayer=0;
    }
    else {
        currentplayer++;
    }
    p_enter_tiles->setText("");
    refreshTheBoard();
}
//fill player with tiles

int Board::score(vector<Square*> vs)
{

    int toadd = 0;
    int total = 0;

    // for(unsigned int k=0; k<vs.size(); k++)
    // {
    //     cout << vs.at(k)->get_row() << " " << vs.at(k)->get_col() << endl;
    // }

    for(unsigned int i=0; i<vs.size(); i++)
    {
        if(!vs.at(i)->get_shibushiblank()) 
        {
            if((vs.at(i)->get_multi() == "2L") && (vs.at(i)->get_used() == false))
            {

                toadd = 2 * (vs.at(i)->get_onboard())->getPoints();
                vs.at(i)->set_used(true);
            }
            else if ((vs.at(i)->get_multi() == "3L") && (vs.at(i)->get_used() == false))
            {

                toadd = 3 * (vs.at(i)->get_onboard())->getPoints();

            }
            else
            {
                toadd = (vs.at(i)->get_onboard())->getPoints();

            }

        }
        else {
            toadd=0;
        }
        total = total + toadd;

    }
    for(unsigned int j=0; j<vs.size(); j++)
    {

        if((vs.at(j)->get_multi() == "3W") && (vs.at(j)->get_used() == false))
        {
            total = 3 * total;

        }
        if((vs.at(j)->get_multi() == "2W") && (vs.at(j)->get_used() == false))
        {
            total = 2 * total;

        }
    }
    return total;

}
bool Board::check_tiles_three(player * p, string letters)
{
    //player has tiles and erase it
    bool found = false;
    set<Tile*>::iterator it1;
    //int point_of_letter = -1;
    for(unsigned int k=0; k<letters.length(); k++)
    {
        for(it1=p->tile_of_player().begin(); it1!=p->tile_of_player().end(); ++it1)
        {
            found=false;
            Tile * temp = *it1;

            if(temp->getLetter() == letters[k])
            {

                found = true;
                break;
            }
        }
        if(found)
        {

            p->tile_of_player().erase(it1);
        }
        else {
            return false;
        }
    }
    return true;
}
bool Board::check_tiles_two(player * p, string mod, bool b, string ori)
{
    string letters;
    if(b)
    {
        letters = ori;
    }
    else {
        letters = mod;
    }
    //check if player has those tiles
    if(letters.length()>7)
        return false;

    set<Tile*>::iterator it2;
    int *allfound = new int[letters.length()];
    for(unsigned int a=0; a<letters.length(); a++)
    {
        for(it2=p->tile_of_player().begin(); it2!=p->tile_of_player().end(); ++it2)
        {
            Tile * temp1 = *it2;
            if(temp1->getLetter() == letters[a])
            {
                allfound[a] = 1;
            }
        }
    }
    for (unsigned int c=0; c<letters.length(); c++)
    {
        if(allfound[c]!=1)
            return false;
    }
    return true;
}
string Board::refinelower (string & torefine)
{
    //cout << " torefine " << torefine << endl;
    string input;
    char in;
    for(unsigned int i=0; i<torefine.length(); i++)
    {

        in = tolower(torefine[i]);
        //cout << " refine " << in << endl;
        input = input + in;
    }
    return input;
}
vector<Square*> Board::all_location(string words, string vert, int row, int col)
{
    //int count = 0;
    unsigned int count_ = 0;
    vector<Square*> location;
    if(vert == "-") {
        unsigned int length_ = words.length();
        // cout <<"length_  1 "<< length_ << endl;
        while(count_ < length_)
        {
            // cout <<"length_  2 "<< length_ << endl;
            // cout << "count " << count_ << endl;
            if(vb->get_square(row, col+count_)->get_occupy())
            {
                /////
                //cout << vb->get_square(row, col+count_)->get_occupy() << endl;
                length_++;
                //  continue;
            }
            else {
                location.push_back(vb->get_square(row, col+count_));
            }
            count_++;
        }
    }
    else if (vert == "|")
    {
        unsigned int length_ = words.length();
        while(count_ < length_)
        {

            if(vb->get_square(row+count_, col)->get_occupy())
            {
                length_++;
                //continue;
            }
            else {
                location.push_back(vb->get_square(row+count_, col));
            }
            count_++;
        }
    }
    return location;
}
bool Board::boardlookup(string words, string vert, int row, int col)
{
    //check if there is anything on the way
    //vector<Square*> location;
    if(vert == "-") {
        for(unsigned int i=0; i<words.length(); i++)
        {
            //location.push_back(vb->get_square(row, col+i));
            if(vb->get_square(row, col+i)->get_occupy()) {

                return false;
            }
        }
    }
    else if (vert == "|")
    {
        for(unsigned int i=0; i<words.length(); i++)
        {
            //location.push_back(vb->get_square(row+i, col));
            if(vb->get_square(row+i, col)->get_occupy()) {

                return false;
            }

        }
    }
    return true;
}
bool Board::place_tiles(string words, string vert, int row, int col, Dictionary * dict)
{
    string lower = refinelower(words);
    vector<Square*> tocheck = all_location(words, vert, row, col);
    if(words.length()>7)
    {
        showPopup("word too long !");
      
        return false;
    }
    if(vert =="-")
    {   //horizontally
        //cout << " vert " << vert << endl;
        if((col+words.length()) < 15)
        {
            // cout << "length " << col+words.length() << endl;
            //cout << " words " << lower << endl;
            //check word

            if(dict->checkword(lower))
            {   // word check and nothing on the way

                if(boardlookup(words, vert, row, col))
                {
                    for(unsigned int i=0; i<words.length(); i++)
                    {
                        char chartoadd;
                        chartoadd=lower.at(i);
                        // cout << " chart to board " << chartoadd << endl;
                        int points = thebag[chartoadd];
                        Tile * tiles1 = new Tile(chartoadd,points);
                        //b.place_tiles(row,col,tiles1,horver);
                        if(vb->addtiles(row,col+i, tiles1))
                        {
                            continue;
                        }
                        else return false;
                    }
                }
                else
                {
                    for(unsigned int i=0; i<words.length(); i++)
                    {
                        char chartoadd;
                        chartoadd=lower.at(i);
                        // cout << " chart to board " << chartoadd << endl;
                        int points = thebag[chartoadd];
                        Tile * tiles1 = new Tile(chartoadd,points);
                        //b.place_tiles(row,col,tiles1,horver);
                        if(vb->addtiles(tocheck.at(i)->get_col(), tocheck.at(i)->get_row(), tiles1))
                        {
                            continue;
                        }
                        else return false;
                    }
                    string word_checker="";
                    //check the word
                    int temp_col= col;
                    while(vb->get_square(row, temp_col)->get_occupy())
                    {
                        word_checker = word_checker + vb->get_square(row, temp_col)->get_show();
                        temp_col++;
                    }
                    if(!dict->checkword(word_checker))
                    {
                        string qq = word_checker +  " is not a legal word ";
                            showPopup( qq);
                        for(unsigned int y=0; y<tocheck.size(); y++)
                        {
                            /////remove
                            string yiqian = vb->get_square(tocheck.at(y)->get_col(), tocheck.at(y)->get_row())->get_previous();
                            vb->get_square(tocheck.at(y)->get_col(), tocheck.at(y)->get_row())->set_show(yiqian);
                        }
                        return false;
                    }
                }
            }
            else if (!(dict->checkword(lower)))
            {

                if(boardlookup(words, vert, row, col))
                {
                    showPopup("word not exist in dictionary ");
                   
                    return false;
                }
                else
                {
                    if(tocheck.size() == words.length())
                    {
                        for(unsigned int m=0; m<tocheck.size(); m++)
                        {
                            char chartoadd;
                            chartoadd=lower.at(m);
                            //cout << " chart to board " << chartoadd << endl;
                            int points = thebag[chartoadd];
                            //cout << " points " << points << endl;
                            Tile * tiles1 = new Tile(chartoadd,points);
                            if(vb->addtiles(tocheck.at(m)->get_col(), tocheck.at(m)->get_row(), tiles1))
                            {
                                continue;
                            }
                            else return false;
                        }
                        string word_checker="";
                        //check the word
                        int temp_col= col;
                        while(vb->get_square(row, temp_col)->get_occupy())
                        {
                            word_checker = word_checker + vb->get_square(row, temp_col)->get_show();
                            temp_col++;
                        }
                        if(!dict->checkword(word_checker))
                        {
                            string qq = word_checker +  " is not a legal word ";
                            showPopup( qq);
                            for(unsigned int y=0; y<tocheck.size(); y++)
                            {
                                /////remove
                                string yiqian = vb->get_square(tocheck.at(y)->get_col(), tocheck.at(y)->get_row())->get_previous();
                                vb->get_square(tocheck.at(y)->get_col(), tocheck.at(y)->get_row())->set_show(yiqian);
                            }
                            return false;
                        }

                    }
                }
            }
            else
            {
                showPopup("WORD invalid");
                
                return false;
            }
        }
        return true;
    }
    else if(vert == "|")
    {   //vertically
        if((row+words.length())<15)
        {
            //check
            if(dict->checkword(lower))
            {   // in dict
                if(boardlookup(words, vert, row, col))
                {   // no block
                    for(unsigned int j=0; j<words.length(); j++)
                    {
                        char chartoadd1;
                        chartoadd1=lower.at(j);
                        int points1 = thebag[chartoadd1];
                        Tile * tiles2 = new Tile(chartoadd1,points1);
                        //b.place_tiles(row,col,tiles1,horver);
                        if(vb->addtiles(row+j,col,tiles2))
                        {
                            continue;
                        }
                        else return false;
                    }
                }
                else {
                    for(unsigned int i=0; i<words.length(); i++)
                    {
                        char chartoadd;
                        chartoadd=lower.at(i);
                        // cout << " chart to board " << chartoadd << endl;
                        int points = thebag[chartoadd];
                        Tile * tiles1 = new Tile(chartoadd,points);
                        //b.place_tiles(row,col,tiles1,horver);
                        if(vb->addtiles(tocheck.at(i)->get_col(), tocheck.at(i)->get_row(), tiles1))
                        {
                            continue;
                        }
                        else return false;
                    }
                    string word_checker="";
                    //check the word
                    int temp_row= row;
                    while(vb->get_square(temp_row, col)->get_occupy())
                    {
                        word_checker = word_checker + vb->get_square(temp_row, col)->get_show();
                        temp_row++;
                    }
                    if(!dict->checkword(word_checker))
                    {
                         string qq = word_checker +  " is not a legal word ";
                            showPopup( qq);
                        
                        for(unsigned int y=0; y<tocheck.size(); y++)
                        {
                            /////remove
                            string yiqian = vb->get_square(tocheck.at(y)->get_col(), tocheck.at(y)->get_row())->get_previous();
                            vb->get_square(tocheck.at(y)->get_col(), tocheck.at(y)->get_row())->set_show(yiqian);
                        }
                        return false;
                    }
                }
            }
            else if (!(dict->checkword(lower)))
            {
                if(boardlookup(words, vert, row, col))
                {
                    showPopup("word not legal " );
                  
                    return false;
                }
                else {
                    if(tocheck.size() == words.length())
                    {
                        for(unsigned int m=0; m<tocheck.size(); m++)
                        {
                            char chartoadd;
                            chartoadd=lower.at(m);
                            // cout << " chart to board " << chartoadd << endl;
                            int points = thebag[chartoadd];
                            //cout << " points " << points << endl;
                            Tile * tiles1 = new Tile(chartoadd,points);
                            vb->addtiles(tocheck.at(m)->get_col(), tocheck.at(m)->get_row(), tiles1);
                        }

                        string word_checker="";
                        //check the word
                        int temp_row= row;
                        while(vb->get_square(temp_row, col)->get_occupy())
                        {
                            word_checker = word_checker + vb->get_square(temp_row, col)->get_show();
                            temp_row++;
                        }
                        if(!dict->checkword(word_checker))
                        {
                             string qq = word_checker +  " is not a legal word ";
                            showPopup( qq);
                          
                            for(unsigned int y=0; y<tocheck.size(); y++)
                            {
                                /////remove
                                string yiqian = vb->get_square(tocheck.at(y)->get_col(), tocheck.at(y)->get_row())->get_previous();
                                vb->get_square(tocheck.at(y)->get_col(), tocheck.at(y)->get_row())->set_show(yiqian);
                            }
                            return false;
                        }
                        else
                        {
                            showPopup("size mismatch" );
                           
                            return false;
                        }

                    }
                }
            }
            return true;
        }
    }
    return false;
}
void Board::showPopup(string error)
{
    QString qerror = QString::fromStdString(error);
    QMessageBox msgBox;
    msgBox.setWindowTitle("ERROR");
    msgBox.setText(qerror);
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Close);
  msgBox.exec();
}

   

void Board::game_watcher()
{

//cout << "t "<<b->tilesRemaining() << endl;
    if((b->tilesRemaining() < 1 && _m->game_over_player() )|| _m->pass_over())
    {
        string s1 ;
    for(unsigned int i =0;i<suoyouplayer.size();i++)
    {
        stringstream ss;
        int sc = allplayer.at(i)->get_score();
        ss<<sc;
        string s3;
        ss>>s3;
        string s2=allplayer.at(i)->get_name() +" " + s3;
        s1 = s2+ "\n" +s1;
    }

    int largest = 0; int temp1=0;
    for (unsigned int j = 0;j<suoyouplayer.size();j++)
    {
        temp1=allplayer.at(j)->get_score();
        while(temp1>largest){
            largest=temp1;
        }
    }
    string winner;
    for (unsigned int j = 0;j<suoyouplayer.size();j++)
    {
        if(largest == allplayer.at(j)->get_score()){
            winner = allplayer.at(j)->get_name();
        }
    }

    gameoverlabel->setText("Final Score : \n" + QString::fromStdString(s1) + "\n" +
        "Winner is : \n" + QString::fromStdString(winner));

        window->hide();
        gameover->show();
    }
}