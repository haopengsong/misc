/*
 * virtualBoard.cpp
 */
#include "virtualBoard.h"

using namespace std;
virtualBoard::virtualBoard()
{
    
}
virtualBoard::~virtualBoard()
{
    
}
virtualBoard::virtualBoard(string virtualBoard_file_name, bool first)
{
	firsttime = first;
    ifstream virtualBoardFile (virtualBoard_file_name.c_str());
    string row;
    
    _x = _y = _startx = _starty = 0; // to appease compiler
    if (!virtualBoardFile.is_open())
        throw invalid_argument("Cannot open file: " + virtualBoard_file_name);
    getline (virtualBoardFile, row);
    stringstream s1 (row);
    s1 >> _x >> _y;
    getline (virtualBoardFile, row);
    stringstream s2 (row);
    s2 >> _startx >> _starty;
    _startx --;
    _starty --;  // coordinates from 0 in array
    
    // Anything else you need to initialize?
    board = new Square**[_x];
    for(int a=0;a<_y;a++)
    {
        board[a]=new Square*[_y];
        for(int b=0;b<_x;b++)
        {
            board[a][b]=new Square();
            board[a][b]->set_occupy(false);
            board[a][b]->set_used(false);
        }
    }
    
    for (int i = 0 ; i < _y; ++ i)
    {
        //cout << endl;
        //cout << setw(3)<< i+1 ;
        getline (virtualBoardFile, row);
        for (int j = 0; j < _x; ++ j)
        {
            
            // Fill in the following based on how you store the virtualBoard.
            if (i == _starty && j == _startx)
            {
                //cout << j;
                board[j][i]->set_row(i);
                board[j][i]->set_col(j);
                board[j][i]->set_multi("2W");
                board[j][i]->set_show("***");
                board[j][i]->set_previous("***");

                //cout << setw(4)<<virtualBoard[j][i] ;
            }
            else switch (row[j])
            {
                case '.' :
                {
                    board[j][i]->set_previous(" ...");
                    board[j][i]->set_row(i);
                    board[j][i]->set_col(j);
                    board[j][i]->set_multi(".");
                    board[j][i]->set_show(" ...");
                    //cout  <<setw(4)<<virtualBoard[j][i];
                }
                    break;
                case '2' :{
                    board[j][i]->set_previous(" 2L");
                    board[j][i]->set_row(i);
                    board[j][i]->set_col(j);
                    board[j][i]->set_multi("2L");
                    board[j][i]->set_show(" 2L");
                }
                    //cout << setw(4)<<virtualBoard[j][i];
                    break;
                case '3' :
                {
                    board[j][i]->set_previous(" 3L ");
                    board[j][i]->set_row(i);
                    board[j][i]->set_col(j);
                    board[j][i]->set_multi("3L");
                    board[j][i]->set_show(" 3L ");
                }   //cout << setw(4)<<virtualBoard[j][i];
                    break;
                case 'd' :
                {
                    board[j][i]->set_previous(" 2W ");
                    board[j][i]->set_row(i);
                    board[j][i]->set_col(j);
                    board[j][i]->set_multi("2W");
                    board[j][i]->set_show(" 2W ");
                }//cout <<setw(4)<< virtualBoard[j][i];
                    break;
                case 't' :
                {
                    board[j][i]->set_previous(" 3W ");
                    board[j][i]->set_row(i);
                    board[j][i]->set_col(j);
                    board[j][i]->set_multi("3W");
                    board[j][i]->set_show(" 3W ");
                }
                    //cout <<setw(4)<< virtualBoard[j][i];
                    break;
                default:
                    string error = "Improper character in virtualBoard file: ";
                    throw invalid_argument(error + row[j]);
            }
        }
    }
    virtualBoardFile.close ();
}
void virtualBoard::print_virtualBoard()
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
bool virtualBoard::addtiles(int row, int col, Tile * t)
{
	//cout <<"row, col : " << row << " ," << col << endl;
    if(board[row][col]->get_occupy()==false)
    {
        stringstream ss;
        char tovirtualBoard;
        board[row][col]->set_onboard_tile(t);
        tovirtualBoard=t->getLetter();
        //cout << "to virtualBoard " << tovirtualBoard << endl;
        ss<<tovirtualBoard;
        string tovirtualBoard_s;
        ss>>tovirtualBoard_s;
        //cout << "to virtualBoard s " << tovirtualBoard_s  << endl;
        board[row][col]->set_show(tovirtualBoard_s);
        board[row][col]->set_occupy(true);
    }
    else {
        cout << "You can not add tile to a spot that is occupied" << endl;
        return false;
    }
    return true;
}
Square * virtualBoard::get_square(int row, int col)
{
   return board[row][col];
}
bool virtualBoard::get_starvirtualBoard()
{
    return firsttime;
}
void virtualBoard::set_starvirtualBoard(bool oc)
{
    firsttime = oc;
}
bool virtualBoard::boardobserver(vector<Square*> tocompare)
{
    vector<Square*> valid_loc;
    for(int i =0;i<_x;i++)
    {
        for(int j=0;j<_y;j++)
        {
            if(board[i][j]->get_occupy())
            {
                //if sth in the square
                if(j+1<15)
                {
                    //check boundary
                    //right
                    if(!board[i][j+1]->get_occupy())
                    {
                        valid_loc.push_back(get_square(i, j+1));
                    }
                }
                if(j-1>=0)
                {
                    //left
                    if(!board[i][j-1]->get_occupy())
                    {
                        valid_loc.push_back(get_square(i, j-1));
                    }
                }
                if(i+1<15)
                {
                    //down
                    if(!board[i+1][j]->get_occupy())
                    {
                        valid_loc.push_back(get_square(i+1, j));
                    }
                }
                if(i-1>=0)
                {
                    //up
                    if(!board[i-1][j]->get_occupy())
                    {
                        valid_loc.push_back(get_square(i-1, j));
                    }
                }
            }
        }
    }
   // cout << " size  ????" << valid_loc.size() << endl;
    for(unsigned int k=0;k<tocompare.size();k++)
    {
        for(unsigned int m=0;m<valid_loc.size();m++)
        {
            if(tocompare.at(k)->get_row() == valid_loc.at(m)->get_row() && tocompare.at(k)->get_col() == valid_loc.at(m)->get_col())
            {
                return true;
            }
        }
    }
    return false;
    //return valid_loc;
}
void virtualBoard::blankcordinates(string horver,string words, int row, int col)
{
    int loc=0;
    for(unsigned int i=0;i<words.length();i++)
    {
        if(words[i] == '?')
        {
            loc = i;
        }
    }
    if(horver == "-")
    {
        if(board[row][col+loc]->get_shibushiblank())
        {
            board[row][col+loc]->set_shibushiblank(true);
        }
    }
    if(horver == "|")
    {
        if(board[row+loc][col]->get_shibushiblank())
        {
            board[row+loc][col]->set_shibushiblank(true);
        }
    }
}









