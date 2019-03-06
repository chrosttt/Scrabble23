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
#include <vector>
#include <map>


#include <string>

class Dictionary {
public:
	Dictionary (std::string dictionary_file_name);
	bool checkValid(std::string word);

	private:
	std::vector<std::string> _words;
	//std::map<std::string,int> _words;

	// what else will this need?
};


#endif /* DICTIONARY_H_ */
