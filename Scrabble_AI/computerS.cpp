#include "computerS.h"

using namespace std;

computerS::computerS()
{

}
computerS::computerS(string n)
{
    name = n;
}
computerS::~computerS()
{

}
string computerS::getName()
{
    return name;
}

//look up if there is square on the way before place tiles
bool computerS::check7letter_(int s_x, int s_y, const Board & board, string verhor)
{
    //col row
    if(verhor == "-") {
        //horizontally
        for(int i=1; i<=7; i++)
        {

            if(s_x+i<15 && board.getSquare(s_x+i,s_y)->isOccupied())
            {
                //within 7 square, if the square is occupied
                return false;
            }
        }
    }
    else if (verhor == "|")
    {
        //downward upward
        for(int i=1; i<=7; i++)
        {
            if(s_y+i<15 && board.getSquare(s_x,s_y+i)->isOccupied())
            {
                //within 7 square, if the square is occupied
                return false;
            }
            if(s_y-i>=0 && board.getSquare(s_x,s_y-i)->isOccupied())
            {
                //within 7 square, if the square is occupied
                return false;
            }
        }

    }
    return true;
}
//find max score
Move computerS::maxScoreMove(const Player & player)
{
    //start find the maximum score
    Move m;
    int max=0;
    int count = 0;
    //iterator
    map<int, Move*>::iterator itmap;
    map<int, Move*>::iterator maxit;
    //for cpus
    if(checkForAI(player.getName()) == "CPUS")
    {
        //FIND THE MAX SCORE
        for(itmap=map_.begin(); itmap!=map_.end(); ++itmap)
        {
            count++;
            //cout <<"score: "<< itmap->first << endl;
            if(itmap->first > max)
            {
                max = itmap->first;
                maxit = itmap;
            }
        }
        if(map_.size() == 0)
        {
            //no move for this turn
            //should pass
           // cout << "pass move" << endl;
            Move* m_pass = new Move("PASS",player);
            return *m_pass;
        }
        else {
            m = *maxit->second;
            // cout <<"best move row ,col :" << m.y() << " " << m.x() << endl;
            // cout << "max " << maxit->first<< " counter "<< count << endl;
        }


    }
    //to check for CPUL
    else if (checkForAI(player.getName()) == "CPUL")
    {
        //reset counter
        count=0;
        //FIND THE LONGEST WORD FORMED BY CURRENT TILES
        for(itmap=letterLength_map_.begin(); itmap!=letterLength_map_.end(); ++itmap)
        {
            count++;
            //cout <<"length: "<< itmap->first << endl;
            if(itmap->first > max)
            {
                max = itmap->first;
                maxit = itmap;
            }
        }
        //cout <<"map size: " << map_.size() << endl;
        if(map_.size() == 0)
        {
            //cout << "pass move" << endl;
            //no move for this turn
            //should pass
            Move* m_pass = new Move("PASS",player);
            return *m_pass;
        }
        else
        {
            m = *maxit->second;
            //tile of the move
            vector<Tile*> vT = m.tileVector();
            // for(unsigned int i=0; i<vT.size(); i++)
            // {
            //     cout << vT[i]->getLetter() << endl;
            // }
            // cout <<"longest move row ,col :" << m.y() << " " << m.x() << endl;
            // cout << "number letters: " << maxit->first<< "counter "<< count << endl;
        }

    }
    return m;
}
bool computerS::checkLegal(vector<string> vv)
{
    vector<string>::iterator vecit1;
    for(vecit1=vv.begin(); vecit1!=vv.end(); ++vecit1)
    {
        if(!dicT->isLegalWord(*vecit1))
            return false;
    }
    return true;
}
//this function figure out all possible move and its score, store in a map(for word)
void computerS::helper_Findstartlocation_word(const Board & board, int row,int col,string startWord, const Player & player)
{
    //incrememnt row, col index
    ++row;
    ++col;
    string s1 = "PLACE";
    string s2 = "-";
    string s_col,s_row;
    string s3;
    set<string>::iterator it1;
    for(it1=v.begin(); it1!=v.end(); ++it1)
    {
        //words to be checked
        string word = *it1;
        s3 = word.substr(startWord.length());
        // cout << "word :" << word << endl;
        // cout << "word mod: "<<s3 << endl;
        //check boundary before place
        //row stays the same, col increment
        if(col+word.length()<15)
        {
            //place word
            Move * temp_move = new Move(col+startWord.length(),row,true,s3,player);
            //cout << s1+" "+s2+" "<<row<<" "<<col+startWord.length()<<" "+s3 << endl;
            vector<string> v_board = board.getWords(*temp_move,score);
            int word_length = s3.length();
            //check if there is a legal move before insert to map
            if(checkLegal(v_board)) {
                //FOR CPUS
                //store move into map along with its score
                map_.insert(std::make_pair(score,temp_move));
                //for CPUL
                letterLength_map_.insert(std::make_pair(word_length,temp_move));
            }
        }


    }

}

void computerS::helper_Findstartlocation_word_vertical(const Board & board, int row,int col,string startWord, const Player & player)
{
    //incrememnt row, col index
    ++row;
    ++col;
    string s1 = "PLACE";
    string s2 = "|";
    string s_col,s_row;
    string s3;

    set<string>::iterator it1;
    for(it1=v.begin(); it1!=v.end(); ++it1)
    {
        //words to be checked
        string word = *it1;
        s3 = word.substr(startWord.length());
        //cout << "word :" << word << endl;
        //cout << "word mod: "<<s3 << endl;
        //check boundary before place
        //row stays the same, col increment
        if(row+word.length()<15)
        {
            //place word
            Move * temp_move = new Move(col,row+startWord.length(),false,s3,player);
            //cout << s1+" "+s2+" "<<row+startWord.length()<<" "<<col<<" "+s3 << endl;
            vector<string> v_board = board.getWords(*temp_move,score);
            int word_length = s3.length();
            //check if there is a legal move before insert to map
            if(checkLegal(v_board)) {
                //FOR CPUS
                //store move into map along with its score
                map_.insert(std::make_pair(score,temp_move));
                //for CPUL
                letterLength_map_.insert(std::make_pair(word_length,temp_move));
            }
        }
    }
}
//this function figure out all possible move and its score, store in a map(for single letter)
void computerS::helper_Findstartlocation_letter_vertical(const Board & board, int row,int col,string startLetter, const Player & player,string tiles)
{
    // ++i_y; // row
    // ++j_x; // col
    string s1 = "PLACE";
    string s2 = "|";
    string s3;
    //go over the set
    set<string>::iterator it1;
    for(it1=v.begin(); it1!=v.end(); ++it1)
    {
        //words to be checked
        string word = *it1;
        //make sure that AI won't place itself
        if(word != startLetter) {
            //locate the letter
            std::size_t found = word.find(startLetter);
            if (found!=std::string::npos)
            {
                s3 = word.substr(0,found)+word.substr(found+1);
            }
            // cout << "word :" << word << endl;
            // cout << "word mod: "<<s3 << endl;
            // cout << "found :" << found << endl;
            //if the letter is the start letter
            if(found == 0 && row + s3.length() <15)
            {   //col  row
                if(col+1<=15 && col+1 >= 1 && row+1<=15 && row+1>=1)
                {
                    Move * temp_move;
                    int temp;
                    //make sure there is a blank tiles in player's tiles
                    if(checkForBlank(tiles,temp))
                    {
                        string mod_tiles_blank = checkBlankLetter(tiles,word);
                   temp_move = new Move(col+1,row+1+1,false,mod_tiles_blank,player);
                }
                else {
                    temp_move = new Move(col+1,row+1+1,false,s3,player);
                }
                    //row    col
                    //cout << board.getDisplay();
                   // cout << s1+" "+s2+" "<<row+1+1<<" "<<col+1<<" "+s3 << endl;
                    vector<string> v_board = board.getWords(*temp_move,score);
                    //check if there is a legal move before insert to map
                    int word_length = s3.length();
                    //check if there is a legal move before insert to map
                    if(checkLegal(v_board))
                    {
                        //FOR CPUS
                        //store move into map along with its score
                        map_.insert(std::make_pair(score,temp_move));
                        //for CPUL
                        letterLength_map_.insert(std::make_pair(word_length,temp_move));
                    }
                }
            }
            else if(found !=0 && row + s3.length() <15) {
                //construct a move
                //cout << "if found is not 0" << endl;
                if(col+1<=15 && col+1 >= 1 && row+1-found<=15 && row+1-found >=1)
                {   
                    Move * temp_move;
                     int temp;
                    //make sure there is a blank tiles in player's tiles
                    if(checkForBlank(tiles,temp))
                    {
                        string mod_tiles_blank = checkBlankLetter(tiles,word);
                  temp_move = new Move(col+1,1+row-found,false,mod_tiles_blank,player);
                }
                else {
                  temp_move = new Move(col+1,1+row-found,false,s3,player);
                }
                    //cout << board.getDisplay();
                    //cout << s1+" "+s2+" "<<row-found+1<<" "<<col+1<<" "+s3 << endl;
                    vector<string> v_board = board.getWords(*temp_move,score);
                    //vector<string>::iterator vecit2;
                    // for(vecit2=v_board.begin(); vecit2!=v_board.end(); ++vecit2)
                    // {
                    //     cout << *vecit2<<endl;
                    // }
                    int word_length = s3.length();
                    //check if there is a legal move before insert to map
                    if(checkLegal(v_board)) {
                        //FOR CPUS
                        //store move into map along with its score
                        map_.insert(std::make_pair(score,temp_move));
                        //for CPUL
                        letterLength_map_.insert(std::make_pair(word_length,temp_move));
                    }
                }
            }
        }
    }
}
//check for position of blank tiles with word formed and add ? before it
string computerS::checkBlankLetter(string tiles, string word)
{
    string temp = word;
    string retval;
    for(unsigned int i=0;i<word.size();i++)
    {

         std::size_t found = tiles.find(word[i]);
        
         if(found!=std::string::npos)
         {
            //cout << found << endl;
            //if tiles has the letter
            //erase
            tiles.erase(tiles.begin()+found);
         }
         else {
            temp.insert(i,"?");
         }
    }

    retval = temp;
    return retval;

}
//create all the move with a single letter
void computerS::helper_Findstartlocation_letter(const Board & board, int i_y,int j_x,string startLetter, const Player & player, string tiles)
{
    //incrememnt row, col index
    ++i_y;
    ++j_x;
    string s1 = "PLACE";
    string s2 = "-";
    string col,row;
    string s3;
    //if there are letters
    //go over the set
    set<string>::iterator it1;
    for(it1=v.begin(); it1!=v.end(); ++it1)
    {
        //words to be checked
        string word = *it1;
        //make sure that AI won't place itself
        if(word != startLetter) {
            //locate the letter
            std::size_t found = word.find(startLetter);
            if (found!=std::string::npos)
            {
                s3 = word.substr(0,found)+word.substr(found+1);
            }
            // cout << "word :" << word << endl;
            // cout << "word mod: "<<s3 << endl;
            // cout << "found :" << found << endl;
            //if the letter is the start letter
            if(found == 0 && i_y+1 + s3.length() <15)
            {   //col  row
                //making sure the starting location is valid
                if(!board.getSquare(i_y,j_x-1)->isOccupied())
                {
                    Move * temp_move;
                    int temp;
                    //make sure there is a blank tiles in player's tiles
                    if(checkForBlank(tiles,temp))
                    {
                        string mod_tiles_blank = checkBlankLetter(tiles,word);
                       temp_move = new Move(i_y+1,j_x,true,mod_tiles_blank,player);
                    }
                    else {
                  temp_move = new Move(i_y+1,j_x,true,s3,player);
                }
                    //row    col
                    // cout << s1+" "+s2+" "<<j_x<<" "<<i_y+1<<" "+s3 << endl;
                    // cout << board.getDisplay();
                    vector<string> v_board = board.getWords(*temp_move,score);
                    //check the length of the main word
                    int word_length = s3.length();
                    //check if there is a legal move before insert to map
                    if(checkLegal(v_board))
                    {
                        //FOR CPUS
                        //store move into map along with its score
                        map_.insert(std::make_pair(score,temp_move));
                        //for CPUL
                        letterLength_map_.insert(std::make_pair(word_length,temp_move));
                    }
                }
            }
            else if(found !=0 && i_y-found + s3.length() <15) {
                //construct a move
                // cout << "if found is not 0" << endl;
                if(!board.getSquare(i_y-found-1,j_x-1)->isOccupied())
                {
                    Move * temp_move;
                    //cout << i_y-found-1 << " " <<j_x-1 << endl;
                     int temp;
                    //make sure there is a blank tiles in player's tiles
                    if(checkForBlank(tiles,temp))
                    {
                        string mod_tiles_blank = checkBlankLetter(tiles,word);
                   temp_move = new Move(i_y-found,j_x,true,mod_tiles_blank,player);
                }
                else {
                  temp_move = new Move(i_y-found,j_x,true,s3,player);
                }
                    // cout << s1+" "+s2+" "<<j_x<<" "<<i_y-found<<" "+s3 << endl;
                    //cout << board.getDisplay();
                    vector<string> v_board = board.getWords(*temp_move,score);
                    int word_length = s3.length();
                    //vector<string>::iterator vecit2;
                    // for(vecit2=v_board.begin(); vecit2!=v_board.end(); ++vecit2)
                    // {
                    //     //cout << *vecit2<<endl;
                    // }
                    if(checkLegal(v_board)) {
                        //store move into map along with its score
                        //CPUS
                        map_.insert(std::make_pair(score,temp_move));
                        //for CPUL
                        letterLength_map_.insert(std::make_pair(word_length,temp_move));
                    }
                }
            }
        }
    }
}
//this function returns true if there is a blank tiles in player's hand
bool computerS::checkForBlank(string s,int & blank_pos)
{
    std::size_t found = s.find("?");
    blank_pos = found;
    if (found!=std::string::npos)
    {
        return true;
    }
    return false;
}
void computerS::blankTileOnFire(int blank_pos, string s1,string letter)
{

    string allletter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for(unsigned int i=0; i<allletter.length(); i++)
    {
        //delete blank tile
        string s2 = s1.substr(0,blank_pos) + s1.substr(blank_pos+1);
        //add one option
        s2=s2+allletter[i];
        //run findword
        string sofar="";
        FindWord_letter(sofar,s2,*dicT,letter);
    }
}
Move computerS::getMove (const Board & board, const Player & player, std::map<char, int> initialTileCount)
{

    //get AI's tiles
    set<Tile*> AI_tile = player.getHandTiles();
    //for a string of tile only with letters
    string s_AI_tile;
    set<Tile*>::iterator it;
    for(it=AI_tile.begin(); it!=AI_tile.end(); ++it)
    {
        char letter = (*it)->getLetter();
        string s_letter;
        stringstream ss;
        ss<<letter;
        ss>>s_letter;
        s_AI_tile+=s_letter;
    }
    //cout <<"ai tiles :" <<s_AI_tile << endl;
    //string to select horizontal or vertical
    string hor = "-";
    string ver = "|";
    //get cols and rows
    int col = board.getColumns();
    int row = board.getRows();
    //exhaustive search every square
    //if there are tiles on board
    if(!checkBoard(board))
    {
        for(int j=0; j<row; j++)
        {
            for(int i=0; i<col; i++)
            {
                Square * sq = board.getSquare(i,j);
                //if there is a letter on the square
                if(sq->isOccupied())
                {
                    // cout<< "col " << i << endl;
                    // cout << "row " << j << endl;
                    //check bourdary
                    //check if it is a single letter
                    //horizontal
                    if(i+1<col && !board.getSquare(i+1,j)->isOccupied() && i-1>=0 && !board.getSquare(i-1,j)->isOccupied())
                    {
                        //this is a single letter
                        //and there is no letter present is in 7 squares
                        if(check7letter_(i,j,board,hor))
                        {
                            //cast letter to string
                            char letter = sq->getLetter();
                            string s_letter;
                            stringstream ss;
                            ss<<letter;
                            ss>>s_letter;
                            //cout <<" letter :"<< s_letter << endl;
                            //for each subset of tiles, combine with the letter
                            //lookup all possible combination
                            string rest = s_AI_tile+s_letter;
                            //add one letter to ai tiles and produce all possible words
                            string sofar_find="";
                            int blank_position;
                            if(checkForBlank(s_AI_tile,blank_position))
                            {
                                blankTileOnFire(blank_position,s_AI_tile,s_letter);
                            }
                            else {
                                string possible_word = FindWord_letter(sofar_find,rest,*dicT,s_letter);
                            }
                            //cout << "size :" << v.size()<< endl;
                            helper_Findstartlocation_letter(board,i,j,s_letter,player,s_AI_tile);
                            v.clear();
                        }
                    }
                    //if it is not a single letter, then there must be a whole word onboard
                    else if(i+1<col && board.getSquare(i+1,j)->isOccupied() && i-1>=0 && !board.getSquare(i-1,j)->isOccupied())
                    {

                        //first try grab the whole word into a string
                        string theword;
                        //start counting
                        int count=0;
                        while(board.getSquare(i+count,j)->isOccupied())
                        {
                            char makeword = board.getSquare(i+count,j)->getLetter();
                            stringstream ss;
                            ss<<makeword;
                            string s_makeword;
                            ss>>s_makeword;
                            theword+=s_makeword;
                            count++;
                        }
                       // cout << "theword " << theword << endl;
                        if(dicT->isLegalWord(theword))
                        {
                            //RUN findword on the whole word
                            string sofar_find="";

                            string possible_word = FindWord_word(sofar_find,s_AI_tile,*dicT,theword);
                           // cout << "size :" << v.size()<< endl;
                            helper_Findstartlocation_word(board,j,i,theword, player);
                            v.clear();
                        }
                    }
                    //vertical
                    //for vertical placement,
                    //need a function to check
                    //check boundary
                    //if the square has no up and down neighbor in 7 square
                    if(j+1<15 && j-1>=0 && check7letter_(i,j,board,ver))
                    {
                       // cout << "v1" << endl;
                        char letter = sq->getLetter();
                        string s_letter;
                        stringstream ss;
                        ss<<letter;
                        ss>>s_letter;
                       // cout <<" letter :"<< s_letter << endl;
                        //for each subset of tiles, combine with the letter
                        //lookup all possible combination
                        string rest = s_AI_tile+s_letter;
                        //add one letter to ai tiles and produce all possible words
                         string sofar_find="";
                         int blank_position;
                            if(checkForBlank(s_AI_tile,blank_position))
                            {
                                blankTileOnFire(blank_position,s_AI_tile,s_letter);
                            }
                            else {
                                string possible_word = FindWord_letter(sofar_find,rest,*dicT,s_letter);
                            }
                        helper_Findstartlocation_letter_vertical( board,j,i,s_letter, player,s_AI_tile);//j is row, i is col
                        v.clear();

                    }
                    else if(j+1<15 && !board.getSquare(i,j-1)->isOccupied() && j-1>=0 && board.getSquare(i,j+1)->isOccupied())
                    {
                        //cout << "v2" << endl;
                        //first try grab the whole word into a string
                        string theword;
                        //start counting
                        int count=0;
                       // cout << "row col :" << j+count << " " << i << endl;

                        while(j+count < 15 && board.getSquare(i,j+count)->isOccupied() == 1)
                        {
                            // cout << board.getSquare(i,j+count)->isOccupied() << endl;
                            // cout << board.getSquare(i,j+count)->getLetter()<< endl;
                            char makeword = board.getSquare(i,j+count)->getLetter();
                            stringstream ss;
                            ss<<makeword;
                            string s_makeword;
                            ss>>s_makeword;
                            theword+=s_makeword;
                            count++;
                            if(j+count+1 == 15)
                                break;

                        }
                        if(dicT->isLegalWord(theword))
                        {
                           // cout << "theword " << theword << endl;
                            string sofar_find="";
                            string possible_word = FindWord_word(sofar_find,s_AI_tile,*dicT,theword);
                            //cout << "size :" << v.size()<< endl;
                            helper_Findstartlocation_word_vertical(board,j,i,theword, player);
                            v.clear();
                        }
                    }
                }
            }
        }
        Move m = maxScoreMove(player);
        map_.clear();
        letterLength_map_.clear();
        return m;
    }
    else
    {
        //nothing on board
        string empty_square = "";
        string rest = s_AI_tile+empty_square;
        //add one letter to ai tiles and produce all possible words
        string sofar_find="";
        string possible_word = FindWord_letter(sofar_find,rest,*dicT,empty_square);
        //helper_Findstartlocation_letter(board,7,7,s_letter,player);
        helper_start(board,player);
        v.clear();
        Move m_start = maxScoreMove(player);
        map_.clear();
        letterLength_map_.clear();
        return m_start;
    }
}
void computerS::helper_start(const Board & board, const Player & player)
{
    set<string>::iterator it1;
    for(it1=v.begin(); it1!=v.end(); ++it1)
    {
        //words to be checked
        string word = *it1;
        Move * temp_move = new Move(8,8,true,word,player);
        vector<string> v_board = board.getWords(*temp_move,score);
        //check the length of the main word
        int word_length = word.length();
        //check if there is a legal move before insert to map
        if(checkLegal(v_board))
        {
            //FOR CPUS
            //store move into map along with its score
            map_.insert(std::make_pair(score,temp_move));
            //for CPUL
            letterLength_map_.insert(std::make_pair(word_length,temp_move));
        }
    }
}
void computerS::initialize(Dictionary* d)
{
    //STORE ALL PREFIXS
    prefix_set = allPrefix(d->allWords());
    dicT = d;
}
set<string> computerS::allPrefix(set<string> allwords)
{
    set<string> prefix;
    set<string>::iterator it;
    //to split every words to prefixs
    for(it=allwords.begin(); it!=allwords.end(); ++it)
    {
        string word = *it;
        for(unsigned int i=0; i<word.length()+1; i++)
        {
            //insert prefix to set
            prefix.insert(word.substr(0,i));
        }
    }
    return prefix;
}
//findword for whole word on board
string computerS::FindWord_word(string soFar, string rest, Dictionary d, string word_onboard)
{
    if (rest.empty()) {
        if (d.isLegalWord(soFar))
        {
            return "finished!";
        }
        else return "";
    } else {
        for (unsigned int i = 0; i < rest.length(); i++)
        {
            string remain = rest.substr(0, i) + rest.substr(i+1);
            string found;
            //cout << "pre check : " <<word_onboard + soFar+rest[i] << endl;
            if(prefix_set.find(word_onboard + soFar+rest[i])!=prefix_set.end() ||
                    prefix_set.find(soFar+rest[i] + word_onboard)!=prefix_set.end())
            {
                if(d.isLegalWord(word_onboard + soFar+rest[i]))
                {
                    //store all possible words to a vector
                    // cout << "words on the road : " <<word_onboard + soFar+rest[i] << endl;
                    v.insert(word_onboard + soFar+rest[i]);
                }
                if(d.isLegalWord(soFar+rest[i] + word_onboard))
                {
                    // cout << "words on the road : " << soFar+rest[i] + word_onboard<< endl;
                }
                //recursive
                found = FindWord_word(soFar + rest[i], remain, d,word_onboard);
                if (!found.empty()) return found;
            }
            else {
                continue;
            }
        }
    }
    return "";
}
//findword for single letter on board
string computerS::FindWord_letter(string soFar, string rest, Dictionary d,string mustHold)
{
    if (rest.empty()) {
        if (d.isLegalWord(soFar))
        {
            return "finished!";
        }
        else return "";
    } else {
        for (unsigned int i = 0; i < rest.length(); i++)
        {
            string remain = rest.substr(0, i) + rest.substr(i+1);
            string found;
            if(prefix_set.find(soFar+rest[i])!=prefix_set.end())
            {
                if(mustHold != "")
                {
                    //if the start square is occupied
                    if(d.isLegalWord(soFar+rest[i]) && CheckContent(soFar+rest[i],mustHold) && v.find(soFar+rest[i])==v.end())
                    {
                        //store all possible words to a vector
                       // cout << soFar+rest[i] << endl;
                        v.insert(soFar+rest[i]);
                    }
                }
                else if(mustHold == "") {
                    //if the start square is not occupied
                    if(d.isLegalWord(soFar+rest[i]) && v.find(soFar+rest[i])==v.end())
                    {
                        v.insert(soFar+rest[i]);
                    }
                }
                //recursive
                found = FindWord_letter(soFar + rest[i], remain, d,mustHold);
                if (!found.empty()) return found;
            }
            else {
                continue;
            }
        }
    }
    return "";
}
//check that the word must contain s inside
bool computerS::CheckContent(string ss,string mustHave)
{
    int count = 0;

    for(unsigned int i=0; i<ss.length(); i++)
    {
        stringstream sss;
        sss<<ss[i];
        string tocheck;
        sss>>tocheck;
        if(tocheck == mustHave)
        {
            count++;
        }
    }
    if(count == 0)
    {
        return false;
    }
    return true;
}
string computerS::checkForAI(string s)
{
    string cpus = "CPUS";
    string cpul = "CPUL";
    string notAI = "NOTAI";
    //grab the first 4 letters
    string tocheck = refineupper(s);
    //check length
    if(s.length() >= 4)
    {
        string first_four="";
        for(int i=0; i<4; i++)
        {
            char toadd = tocheck[i];
            first_four+=toadd;
        }
        if(first_four == "CPUS")
        {
            return cpus;
        }
        else if (first_four == "CPUL")
        {
            return cpul;
        }
    }
    return notAI;
}

string computerS::refineupper (string torefine)
{
    string input;
    char in;
    for(unsigned int i=0; i<torefine.length(); i++)
    {

        in = (char)toupper(torefine[i]);
        input = input + in;
    }
    return input;
}
//return true if nothing on the board(need to place start square)
bool computerS::checkBoard(const Board & board)
{
    int col = board.getColumns();
    int row = board.getRows();
    for(int j=0; j<row; j++)
    {
        for(int i=0; i<col; i++)
        {
            if(board.getSquare(j,i)->isOccupied())
            {
                return false;
            }
        }
    }
    return true;
}