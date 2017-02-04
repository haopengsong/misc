/*
 * Dictionary.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <string>
#include <set>

using namespace std;
class Dictionary {
public:
	Dictionary (std::string dictionary_file_name);
    ~Dictionary();
	// what else will this need?
	//set<string>& return_set();
	bool checkword(string word);
	int get_set_size();
private:
	set<string> dict;
};


#endif /* DICTIONARY_H_ */
