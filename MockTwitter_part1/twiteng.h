#ifndef TWITENG_H
#define TWITENG_H
#include <map>
#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <string>
#include "user.h"
#include "datetime.h"
#include "tweet.h"
#include <cctype>

class TwitEng
{
public:
    TwitEng();
    ~TwitEng();
    /**
     * Parses the Twitter database and populates internal structures
     * @param filename of the database file
     * @return true if there is an error, false if successful
     */
    bool parse(char* filename);
    
    /**
     * Allocates a tweet from its parts and adds it to internal structures
     * @param username of the user who made the tweet
     * @param timestamp of the tweet
     * @param text is the actual text of the tweet as a single string
     */
    void addTweet(std::string& username, DateTime& time, std::string& text);
    
    /**
     * Searches for tweets with the given words and strategy
     * @param words is the hashtag terms in any case without the '#'
     * @param strategy 0=AND, 1=OR
     * @return the tweets that match the search
     */
    std::vector<Tweet*> search(std::vector<std::string>& terms, int strategy);
    
    /**
     * Dump feeds of each user to their own file
     */
    void dumpFeeds();
    
    //compare two hashtages case insensitive
    bool compare(std::string s1, std::string s2);
    
    //to creative intersection of two sets
    //return a vector of tweet* if they have equal element
    std::set<Tweet*> intertweets( std::set<Tweet*> & other2,std::set<Tweet*> & other1) ;
    /* You may add other member functions */
private:
    /* Add any other data members or helper functions here  */
    //store each lines of the input file
    std::vector<std::string> zhengewenjian;
    //user pointers
    std::vector<User*> suoyouusers;
    //map hashtages, quick access to related tweets
    std::map<std::string,std::set<Tweet*> > hashtage_map;
};


#endif
