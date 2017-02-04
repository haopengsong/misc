#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "twiteng.h"
#include "datetime.h"
using namespace std;

void displayTweets(vector<Tweet*>& hits);
//make input upper case
string refineupper (string & torefine);
int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please provide the twitter data file" << endl;
        return 1;
    }
    TwitEng twit;

    if ( twit.parse(argv[1]) ) {
        cerr << "Unable to parse " << argv[1] << endl;
        return 1;
    }

    bool intoloop = true;
    while (intoloop)
    {
        cout << "=====================================" << endl;
        cout << "  Menu: " << endl;
        cout << "  AND term term ...                  " << endl;
        cout << "  OR term term ...                   " << endl;
        cout << "  TWEET username tweet_text" << endl;
        cout << "  QUIT (and write feed files)        " << endl;
        cout << "=====================================" << endl;
        string command;
        string option;
        stringstream ss2;
        getline(cin,command);
        ss2<<command;
        getline(ss2,option,' ');
        if (option == "AND")
        {
            vector<string> terms;
            string andorterm;
            stringstream ss(command);
            getline(ss,andorterm,' ');
            getline(ss,andorterm);
            stringstream ss1(andorterm);
            ss1<<andorterm;
            string tovector;
            vector<Tweet*> userset;
            while (ss1>>tovector)
            {
            	string upper = refineupper(tovector);
                terms.push_back(upper);
            }
            userset =  twit.search(terms,0);
            //output
            if(userset.size() == 0) {
                cout << "No matches"<< endl;
            }
            else {
                cout << userset.size() << " matches "<< endl;
            }
            for (int i=0; i<userset.size(); i++)
            {

                Tweet * t = userset.at(i);
                cout <<t->time() << " " << t->user()->name() << " "<< t->text()  << endl;
            }
            ss.clear();
            ss1.clear();
            terms.clear();
            userset.clear();
            //intoloop=false;
        }
        else if (option == "OR")
        {
            vector<string> terms;
            string andorterm;
            stringstream ss(command);
            getline(ss,andorterm,' ');
            getline(ss,andorterm);
            stringstream ss1(andorterm);
            ss1<<andorterm;
            string tovector;
            vector<Tweet*> userset;
            while (ss1>>tovector)
            {
            	string upper2 = refineupper(tovector);
                terms.push_back(upper2);
            }
            userset = twit.search(terms,1);
            //output
            if(userset.size() == 0) {
                cout << "No matches"<< endl;
            }
            else {
                cout << userset.size() << " matches "<< endl;
            }
            for (int i=0; i<userset.size(); i++)
            {

                Tweet * t = userset.at(i);
                cout <<t->time() << " "<<t->user()->name() << " " << t->text() << endl;
            }
            ss.clear();
            ss1.clear();
            terms.clear();
            userset.clear();
        }
        else if (option == "QUIT")
        {
            cout << "QUIT" << endl;
            twit.dumpFeeds();
            intoloop = false;
        }
        else if (option == "TWEET")
        {
            stringstream ss3;
            string line;
            ss3<<command;
            getline(ss3,line,' ');
            getline(ss3,line);
            stringstream ss4(line);
            string text;
            //vector to store the text
            vector<string> text_to_add;
            while (ss4>>text)
            {
                text_to_add.push_back(text);
            }
            //get username
            string username = text_to_add.at(0);
            string final_text;
            for (int i=1;i<text_to_add.size();i++)
            {
            	string addtext = text_to_add.at(i);
            	//add up text
            	final_text= final_text + " " + addtext;
            }
            DateTime dt;
            dt.currenttime();
            //add
            twit.addTweet(username,dt,final_text);
        }
        else {
        	intoloop = true;
        }
    }
    return 0;
}

string refineupper (string & torefine)
{
    string input;
    int i=0;
    while (torefine[i])
    {
        input += (char)toupper(torefine[i]);
        i++;
    }
    return input;
}