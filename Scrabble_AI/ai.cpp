#include "Game.h"
#include "Move.h"
#include "Exceptions.h"
#include "computerS.h"
#include "Board.h"
#include "Player.h"
#include "Tile.h"
#include "Util.h"
#include "Bag.h"

#include <iostream>
#include <set>
#include <string>
#include <stdexcept>
#include <cctype>
#include <vector>

using namespace std;

//thins function checks if it is an AI
string checkForAI(string nameofplayer);
//convert input to uppercase word
string refineupper(string input);

int main(int argc, char const *argv[])
{
    //check input
    if(argc<2 || argc>2)
    {
        cout << "Invalid arguement"<<endl;
    }
    try {
        //start game
        Game* g = new Game(argv[1]);
        computerS * ai_S;
        computerS * ai_L;


        //asking number of player
        int number_player=0;
        cout << "\nEnter number of players(1-8)"<< ": ";
        cin >> number_player;

        //enter their name and add player
        string player_name;
        string player_name_upper;
        string * names = new string[number_player];
        for (int i=0; i<number_player; i++)
        {
            cout << "\nPlease enter the name of player " << i+1 <<": ";
            cin >> player_name;
            player_name_upper = refineupper(player_name);
            names[i]=player_name_upper;
            cin.ignore();
            //check if it is AI
            if(checkForAI(names[i]) == "CPUS")
            {
                //add as AI load AIs
                ai_S = new computerS(names[i]);
                ai_S->initialize(g->getDictionary());
                g->addPlayer(names[i]);
            }
            else if(checkForAI(names[i]) == "CPUL")
            {
                //add as AI load AIs
                ai_L = new computerS(names[i]);
                ai_L->initialize(g->getDictionary());
                g->addPlayer(names[i]);
            }
            else {
                //add as normal player
                g->addPlayer(names[i]);
            }
        }
        cout << endl;
        //create Move object
        //  Move * m = new Move;
        //start the game loop

        while(!g->isFinished())
        {

            //display board
            cout << g->getBoard()->getDisplay();
            //displayPLA
            Player * p = g->getCurrentPlayer();

            string playername = p->getName();
            cout << playername << " ,it's your turn" << endl;
            //TILES
            cout << "Your current tiles "<< endl;
            string tiles_player = p->getHand();
            cout << tiles_player << endl;
            cout << "current scores :" << endl;
            vector<pair<string,int> > scores = g->getScores();
            for(unsigned int j=0; j<scores.size(); j++)
            {
                cout << scores[j].first << ": "<<scores[j].second << endl;
            }
            //detect AI
            if(checkForAI(playername) == "CPUS" )
            {
                //int scoreForOneTurn=0;

                cout << "CPUS" << endl;
                Move ais_move=ai_S->getMove(*g->getBoard(),*p,g->initialTileCount());
                try {
                    g->makeMove(ais_move);
                    g->finalizeMove();
                }
                catch(MoveException & o)
                {
                    cout << o.getMessage() << endl;
                }
            }
            else if (checkForAI(playername) == "CPUL")
            {
                cout << "CPUL"<<endl;
                Move ail_move=ai_L->getMove(*g->getBoard(),*p,g->initialTileCount());
                //  g->makeMove(*m);
                //  g->finalizeMove();
                try {
                    g->makeMove(ail_move);
                    g->finalizeMove();
                }
                catch(MoveException & o)
                {
                    cout << o.getMessage() << endl;
                }
            }
            else {
                //type command
                cout << "TYPE command" << endl;
                cout << "1.EXCHANGE <string of tiles> \n2.PASS \n3.PLACE <dir> <row> <column> <string of tiles> \n";
                string command;
                getline(cin,command);
                Move player_move(command,*p);
                try
                {
                    g->makeMove(player_move);
                    //retrive the most recent score add to player
                    cout << "points : " << g->getRecentScore()<< endl;
                    //p->addPoints(g->getRecentScore());
                    g->finalizeMove();
                }
                catch(MoveException & o)
                {
                    cout << o.getMessage() << endl;
                }
            }
        }
        //finalsub
        //get winner
        //game done
        cout << "Game over" << endl;
        vector<pair<string,int> > finalsocre =  g->finalSubtraction();
        for(unsigned int j=0; j<finalsocre.size(); j++)
        {
            cout << finalsocre[j].first << ": "<<finalsocre[j].second << endl;
        }
        cout << "winner is : " <<endl;
        vector<string> winner = g->getWinners();
        for(unsigned int i=0; i<winner.size(); i++)
        {
            cout << winner[i] << endl;
        }


    }
    //EXCEPETION
    catch(ConfigParameterException & o)
    {
        cout << o.getMessage() << endl;
    }
    catch(FileException & o)
    {
        cout << o.getMessage() << endl;
    }
    catch(MoveException & o)
    {
        cout << o.getMessage() << endl;
    }

    return 1;
}
string checkForAI(string s)
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

string refineupper (string torefine)
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