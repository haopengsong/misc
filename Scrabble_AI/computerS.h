#ifndef computerS_h_
#define computerS_h_

#include "AbstractAI.h"
#include "Dictionary.h"
#include "Player.h"
#include "Board.h"
#include "Move.h"
#include "Square.h"
#include "Tile.h"
#include "Util.h"
#include "Game.h"
#include "Exceptions.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <cstring>
#include <map>
#include <fstream>
using namespace std;

class Tile;
class Move;
class Square;
class Dictionary;

class computerS : public AbstractAI
{
public:
	computerS();
	computerS(string n);
	~computerS();
	string getName();
	// returns the name by which the AI would like to be called
	void initialize (Dictionary* dict);
	  /* you can use this function to do pre-processing, such as 
     constructing maps for fast lookup.
     We will call initilalize on your AI before asking it for its first move. */
	Move getMove (const Board & board, const Player & player, std::map<char, int> initialTileCount);
	 /* This will be the main function doing the work.
     You will get the board and player, and have hopefully stored the dictionary.
     You also get a map giving you the initial number of each type of tiles in the bag.
     (The board class allows you to find out how many of each type have been placed.)
     You should return a Move object describing the move your AI wants to make.
  */
	set<string> allPrefix(set<string> allwords);
	//will generate all prefix of a dictionary

	string FindWord_word(string soFar, string rest, Dictionary d,string word_onboard);
	//findword for whole word on board

	string FindWord_letter(string soFar, string rest, Dictionary d,string mustHold);
	//backtracking search for words provide a string a letter

	bool check7letter_(int s_x, int s_y, const Board & board, string verhor);
	//look up if there is square on the way before place tiles

	bool CheckContent(string s,string mustHave);
	//check that the word must contain s inside

	void helper_Findstartlocation_word(const Board & board, int i_y,int j_x,string startword, const Player & player);
	//this function figure out all possible move and its score, store in a map(for word)

	void helper_Findstartlocation_letter(const Board & board, int i_y,int j_x,string startLetter, const Player & player,string s);
	//this function figure out all possible move and its score, store in a map(for single letter)

	void helper_Findstartlocation_letter_vertical(const Board & board, int i_y,int j_x,string startLetter, const Player & player,string s);
	//same function, vertical

	void helper_Findstartlocation_word_vertical(const Board & board, int row,int col,string startWord, const Player & player);
	//same function vertical

	Move maxScoreMove(const Player & p);
	//compute max score and move

	string checkForAI(string s);
	//figure out which AI it is

	string refineupper (string torefine);
	//refine to upper case

	bool checkLegal(vector<string> v);
	//check if the vector contains all legal words

	bool checkBoard(const Board & board);
	//return true if nothing on the board(need to place start square)

	void helper_start(const Board & board, const Player & player);
	//help place move when the game starts

	bool checkForBlank(string s,int & blank_pos);
	//this function returns true if there is a blank tiles in player's hand

	void blankTileOnFire(int blank_pos,string s1,string letter);
	//create all words formed by blank  tiles within a tiles

	string checkBlankLetter(string tiles, string word);
	//check for position of blank tiles with word formed and add ? before it

private:
	string name;
	set<string> prefix_set;
	Dictionary *dicT;
	set<string> v;
	int score;

	map<int,Move*> map_;
	map<int,Move*> letterLength_map_;

	
};

#endif