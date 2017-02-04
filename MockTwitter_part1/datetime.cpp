#include "datetime.h"
#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include <ctime>
using namespace std;

DateTime::DateTime()
{
    
}
DateTime::DateTime(int hh,int mm, int ss, int yr, int mh, int dy)
{
    hour=hh;
    min=mm;
    sec=ss;
    year=yr;
    month=mh;
    day=dy;
}
bool DateTime::operator<(const DateTime & other) const
{
    if (year != other.year) {
        return (year < other.year);
    }
    else if (month != other.month) {
        return (month < other.month);
    }
    else if (day != other.day) {
        return (day < other.day);
    }
    else if (hour != other.hour) {
        return (hour < other.hour);
    }
    else if (min != other.min) {
        return (min < other.min);
    }
    else if (sec != other.sec) {
        return (sec < other.sec);
    } 
    else {
        return false;
        
    }
}
void DateTime::currenttime()
{
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    int yyy,mmm,ddd,hhh,miiin,secc;
    yyy=timeinfo->tm_year+1900;
    mmm=timeinfo->tm_mon;
    ddd=timeinfo->tm_mday;
    hhh=timeinfo->tm_hour;
    miiin=timeinfo->tm_min;
    secc=timeinfo->tm_sec;
    stringstream ss;
    //year
    ss<<yyy;
    ss>>year;
    ss.clear();
    //month
    ss<<mmm;
    ss>>month;
    ss.clear();
    //day
    ss<<ddd;
    ss>>day;
    ss.clear();
    //hour
    ss<<hhh;
    ss>>hour;
    ss.clear();
    //min
    ss<<miiin;
    ss>>min;
    ss.clear();
    //sec
    ss<<secc;
    ss>>sec;
    ss.clear();
    
}
ostream& operator<<(ostream & os, const DateTime& other)
{
    os << other.year << "-" << other.month << "-" << other.day << " " << other.hour << ":" << other.min << ":" << other.sec ;
    return os;
}
istream & operator >> (istream & is, DateTime & dt)
{
    
    //stringstream to hold the stream
    stringstream ss;
    //store content
    string s;
    getline(is,s,'-');
    if (is.fail())
    {
        dt.currenttime();
        return is;
    }
    ss.str(s);
    ss>>dt.year;
    ss.clear();
    
    getline(is,s,'-');
    if (is.fail())
    {
        dt.currenttime();
        return is;
    }
    ss.str(s);
    ss>>dt.month;
    ss.clear();
    
    getline(is,s,' ');
    if (is.fail())
    {
        dt.currenttime();
        return is;
    }
    ss.str(s);
    ss>>dt.day;
    ss.clear();
    
    getline(is,s,':');
    if (is.fail())
    {
        dt.currenttime();
        return is;
    }
    ss.str(s);
    ss>>dt.hour;
    ss.clear();
    
    getline(is,s,':');
    if (is.fail())
    {
        dt.currenttime();
        return is;
    }
    ss.str(s);
    ss>>dt.min;
    ss.clear();
    
    getline(is,s);
    if (is.fail())
    {
        dt.currenttime();
        return is;
    }
    ss.str(s);
    ss>>dt.sec;
    
    return is;
}

