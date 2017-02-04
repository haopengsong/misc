#include "user.h"
#include <iostream>
#include <string>
#include <set>
#include <list>
#include <vector>

using namespace std;

User::User()
{
    username="hehe";
}
User::User(string name)
{
    username=name;
}
User::~User()
{
    
}
string User::name() const
{
    return username;
}
set<User*> User::followers() const
{
    return mfollowers;
}
set<User*> User::following() const
{
    return mfollowing;
}
list<Tweet*> User::tweets() const
{
    return mtweets;
}
void User::addFollower(User* u)
{
    if(mfollowers.find(u) == mfollowers.end())
        mfollowers.insert(u);
}
void User::addFollowing(User* u)
{
    if(mfollowing.find(u) == mfollowing.end())
        mfollowing.insert(u);
}
void User::addTweet(Tweet* t)
{
    mtweets.push_back(t);
}
vector<Tweet*> User::getFeed()
{
    vector<Tweet*> alltweet;
    User tweet_user;
    //get user's tweet
    list<Tweet*> self_user_tweet;
    //get followed user's tweet
    list<Tweet*> followed_user_tweet;
    //get user's tweets
    for (list<Tweet*>::iterator it = mtweets.begin();it != mtweets.end();++it)
    {
        Tweet * cun = *it;
        //store user's tweet(pointer) to a list
        self_user_tweet.push_back(cun);
    }
    //get tweets from followed user
    for (set<User*>::iterator it = mfollowing.begin(); it != mfollowing.end(); ++it)
    {
        tweet_user = **it;
        followed_user_tweet = tweet_user.tweets();
        for (list<Tweet*>::iterator it1 = followed_user_tweet.begin(); it1 != followed_user_tweet.end(); ++it1)
        {
            Tweet * cuncun = *it1;
            //store followed user's tweet (pointer) to a list
            self_user_tweet.push_back(cuncun);
        }
    }
    //to sum up all tweets to a vector hehe
    for (list<Tweet*>::iterator it2 = self_user_tweet.begin(); it2 != self_user_tweet.end(); ++it2)
    {
        Tweet * cnm = *it2;
        alltweet.push_back(cnm);
    }
    return alltweet;
}