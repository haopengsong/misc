#include "tweet.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <cctype>
using namespace std;

Tweet::Tweet()
{
    
}
Tweet::Tweet(User* user, DateTime& time, string& text)
{
    muser=user;
    mtime=time;
    mtext=text;
}
DateTime const &Tweet::time () const
{
    return mtime;
}
string const & Tweet::text() const
{
    return mtext;
}
set<string> Tweet::hashTags() const
{
    //parse the tweet text
    stringstream ss;
    string text;
    vector<string> every_word;
    //store text into ss
    ss<<mtext;
    
    //split them
    while (ss>>text)
    {
        every_word.push_back(text);
    }
    ss.clear();
    //put # word into set
    set<string> hashtages;
    for(vector<string>::iterator it = every_word.begin(); it!=every_word.end();++it)
    {
        string word = *it;
        //check if it is a hashtage
        if (word[0]=='#')
        {
            //delete # sign
            string nosign = word.substr(1);
            //check if not exist in set
            if(hashtages.find(word) == hashtages.end())
            {
                //insert
                string upper = refineupper(nosign);
                hashtages.insert(upper);
            }
        }
    }
    return hashtages;
}
bool Tweet::operator<(const Tweet& other) const
{
    return mtime < other.mtime;
}

ostream& operator<<(ostream &os, const Tweet& t)
{
    return os << t.time() << t.muser->name() << t.text();
}

User* Tweet::user() const
{
    //get user
    return muser;
}
string Tweet::refineupper (string & torefine) const
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