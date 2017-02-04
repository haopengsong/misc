
#include <map>
#include <string>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "twiteng.h"
#include <cctype>
using namespace std;

TwitEng::TwitEng() {
    
}
TwitEng::~TwitEng() {
    
}
bool TwitEng::parse(char * filename) {
    ifstream ifile(filename);
    User * the_user;
    User * user_fo;
    User * userfortweet = NULL;
    
    if(ifile.fail()) {
        cout << "no files" << endl;
        return true;
    }
    //read the files line by line
    //number of users
    int usershuliang=-1;
    string meihangzi;
    ifile>>usershuliang;
    if(ifile.fail()) {
        cout << "no number users" << endl;
        return true;
    }
    
    //count how many lines
    int yigongjihang=0;
    while(getline(ifile,meihangzi))
    {
        zhengewenjian.push_back(meihangzi);
        meihangzi.clear();
        yigongjihang++;
    }
    //read users and people they are following
    //for each line only grab the first words
    //skip tweets lines for now
    for (int i=1; i<usershuliang+1; i++)
    {
        string temp = zhengewenjian.at(i);
        stringstream ss(temp);
        string linshiname;
        //stop at first ws
        getline(ss,linshiname,' ');
        if(ss.fail())
        {
            cout << "read fails"<<endl;
            return true;
        }
        User * newuser = new User(linshiname);
        suoyouusers.push_back(newuser);
        ss.clear();
        temp.clear();
    }
    //get followings
    //using deliminter
    for(int i=1; i<usershuliang+1; i++)
    {
        string temp1 = zhengewenjian.at(i);
        stringstream ss1(temp1);
        string qudiaodiyige;
        //store except first word
        getline(ss1,qudiaodiyige,' ');
        getline(ss1,qudiaodiyige);
        ss1.clear();
        stringstream ss0(qudiaodiyige);
        string temp2;
        //hold, store
        vector<string> following;
        while(ss0>>temp2)
        {
            following.push_back(temp2);
        }
        //for each following user add to following
        the_user = suoyouusers.at(i-1);
       
        for (int j=0; j<following.size(); j++)
        {
            //user about to addfollowing
            string username = following.at(j);
           
            for (int k=0; k<suoyouusers.size(); k++)
            {
                //store a pointer to that user
                user_fo = suoyouusers.at(k);
            
                //if the user is in the list
                if (user_fo->name() == username)
                {
                    the_user->addFollowing(user_fo);
                    break;
                }
            }
        }
        following.clear();
    }
    
    //get tweets
    //split up the words
    for (int m=usershuliang+1; m<zhengewenjian.size(); m++)
    {
        
        string aline,alinewithword;
        vector<string> tweets;
        aline = zhengewenjian.at(m);
        stringstream ss2(aline);
        while(ss2>>alinewithword)
        {
            tweets.push_back(alinewithword);
            alinewithword.clear();
        }
        
        //get pointer to the user
        //get the user name
        string username = tweets.at(2);
        //find the user whose tweet is in that line
        for (int i=0; i<suoyouusers.size(); i++)
        {
            the_user = suoyouusers.at(i);
            //find the user
            if (the_user->name() == username)
            {
                userfortweet = the_user;
                break;
            }
        }
        ss2.clear();
        //timestamp
        DateTime dt;
        //get time
        string timestamp = tweets.at(0) + " " + tweets.at(1);
        stringstream ss3(timestamp);
        ss3>>dt;
        ss3.clear();
        
        //read tweets
        //tweets start at index 3
        string tweetssss;
        string tweetword;
        stringstream ss4;
        for (int j=3; j<tweets.size(); j++)
        {
            //add each word together
            ss4<<tweets.at(j);
            ss4>>tweetword;
            tweetssss += ' ';
            tweetssss += tweetword;
            //clean up
            ss4.clear();
            tweetword.clear();
        }
        //new tweet
        Tweet * newtweet = new Tweet(userfortweet,dt,tweetssss);
        
        //store all hashtaged word into the map
        set<string> hashtage_set;
        hashtage_set = newtweet->hashTags();
      
        //if the tweet has hashtages
        if (hashtage_set.size() > 0)
        {
            //set to store all tweets of the hashtage
            set<Tweet*> tweet_with_hashtages;
            tweet_with_hashtages.insert(newtweet);
            
            for (set<string>::iterator it8 = hashtage_set.begin(); it8 != hashtage_set.end();++it8)
            {
                //check if the hashtage is not exist in the map
                if (hashtage_map.find(*it8) == hashtage_map.end())
                {
                    //add key to the map along with value
                    hashtage_map.insert(make_pair(*it8, tweet_with_hashtages));
                }
                //if in map
                else if (hashtage_map.find(*it8) != hashtage_map.end())
                {
                    map<string,set<Tweet*> >::iterator it9 =hashtage_map.find(*it8);
                    it9->second.insert(newtweet);
                    
                }
            }
            tweet_with_hashtages.clear();
            // no hashtage do nothing
        }
        //add tweet
        userfortweet->addTweet(newtweet);
        //clean up
        for (int k=0; k<tweets.size(); k++)
        {
            tweets.erase(tweets.begin());
        }
    }

    return false;
}
void TwitEng::addTweet(string& username, DateTime& time, string& text)
{
    //check if the user exist
    for (int i=0;i<suoyouusers.size();i++)
    {
        //store the name of user in the vector
        string u = suoyouusers.at(i)->name();
        //compare
        if(username==u)
        {
            //query the current time
            time.currenttime();
            //allocate new space for new tweet
            Tweet * newtweet_add = new Tweet(suoyouusers.at(i),time,text);
            //add the new tweet
            suoyouusers.at(i)->addTweet(newtweet_add);
            //find any hashtages and add them to map
            set<string> add_new_hashs = newtweet_add->hashTags();
            //if there are hashtages
            if (add_new_hashs.size()>0)
            {
                set<string>::iterator it;
                for (it=add_new_hashs.begin();it!=add_new_hashs.end();++it)
                {
                    //find if the key is in the map
                    
                    if(hashtage_map.find(*it) != hashtage_map.end())
                    {
                       
                        //key already in the map
                        map<string,set<Tweet*> >::iterator it1;
                        it1 = hashtage_map.find(*it);
                        //find the set of given key
                        //add new tweet to the set
                        it1->second.insert(newtweet_add);
                    }
                    //if not in map
                    else if(hashtage_map.find(*it) == hashtage_map.end())
                    {
                       
                        //create a new set of tweet*
                        set<Tweet*> toadd;
                        //add the tweet to the set
                        toadd.insert(newtweet_add);
                        //insert to map
                        hashtage_map.insert(make_pair(*it, toadd));
                    }
                }
            }
        }
    }
}
vector<Tweet*> TwitEng::search(vector<string>& terms, int strategy)
{
    vector<Tweet*> tweets;
    set<Tweet*> set_of_tweet;
    if (strategy == 1)
    {
        //to perform OR search
        for (int i=0;i<terms.size();i++)
        {
            string possible = terms.at(i);
            //go through all hashtages and all their tweets to a vector
            map<string,set<Tweet*> >::iterator it1;
            //go through the set of tweet* of the given term
            it1 = hashtage_map.find(possible);
            //and add each one to the vector
            set<Tweet*>::iterator it2;
            set<Tweet*> matches = it1->second;
            //store tweets to the vector
            for (it2 = matches.begin(); it2 != matches.end();++it2)
            {
                 set<Tweet*>::iterator it3;
                it3=set_of_tweet.find(*it2);
                //not in set
                if(it3 == set_of_tweet.end())
                {
                    set_of_tweet.insert(*it2);
                    tweets.push_back(*it2);
                }
            }
        }
    }
    else if (strategy == 0)
    {
        
        map<string,set<Tweet*> >::iterator it=hashtage_map.find(terms.at(0));
        //interset
        set<Tweet*> interset = it->second;
        for (int j=0;j<terms.size();j++)
        {
            //go through the entire set one by one
            map<string,set<Tweet*> >::iterator it1;
            it1 = hashtage_map.find(terms.at(j));
            //perform the intersect function
            set<Tweet*> tointer = it1->second;
            interset = intertweets(interset,tointer);
            if(interset.size() == 0)
            {
                //cout << "NO MATCHES.!"<< endl;
                tweets.clear();
                return tweets;
            }
        }
        //store to vector
        set<Tweet*>::iterator it2;
        for (it2=interset.begin();it2!=interset.end();++it2)
        {
            tweets.push_back(*it2);
        }
    }
    sort(tweets.begin(),tweets.end(),TweetComp());
    return tweets;
    
}
void TwitEng::dumpFeeds() {
    for (int i=0;i<suoyouusers.size();i++)
    {
        //get all users name
        User * outputfeed_user = suoyouusers.at(i);
        //output file name
        string filename = outputfeed_user->name() + ".feed";
        ofstream ofile(filename.c_str());
        //store feeds of a given user
        vector<Tweet*> thefeed = outputfeed_user->getFeed();
        ofile << outputfeed_user->name() << endl;
        //sort the feed
        sort(thefeed.begin(), thefeed.end(), TweetComp());
        for (int j=0;j<thefeed.size();j++)
        {
            Tweet * tweet = thefeed.at(j);
            User * user = tweet->user();
            ofile<< tweet->time() << " " << user->name()<< " " << tweet->text() << endl;
        }
    }
}
bool TwitEng::compare(string s1, string s2)
{
    //make them both upper case
    int i=0;
    int j=0;
    string ss1,ss2;
    while (s1[i])
    {
        ss1+=(char)toupper(s1[i]);
        i++;
    }
    while (s2[j])
    {
        ss2+=(char)toupper(s2[j]);
        j++;
    }
    //compare them
    return (ss1==ss2);
}
set<Tweet*> TwitEng::intertweets(set<Tweet*> & theset, set<Tweet*> & tointer)
{
    //store the element
    set<Tweet*> intertweet;
    string s1,s2;
    set<Tweet*>::iterator it;
    for(it=theset.begin();it!=theset.end();++it)
    {
        //compare
        s1 = (*it)->text();
        // cout << "s1 " << s1 << endl;
        set<Tweet*>::iterator it2;
        for(it2=tointer.begin();it2!=tointer.end();++it2)
        {
            s2 = (*it2)->text();
            // cout << "s2 " << s2 << endl;
            //if equal, add to intersect
            if (s1 == s2)
            {
                intertweet.insert(*it);
            }
        }
    }
    return intertweet;
}
