/*
 * Dictionary.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include "Dictionary.h"


using namespace std;

Dictionary::Dictionary (string dictionary_file_name)
{
	ifstream dictFile (dictionary_file_name.c_str());
	string word;

	if (dictFile.is_open())
	{
		while (getline (dictFile, word))
		{
			word.erase(word.length()); // remove end-of-line character

			_words.push_back(word);
		}
		sort(_words.begin(), _words.end()); //sort unordered list
		dictFile.close ();
	}
	else throw invalid_argument("Cannot open file: " + dictionary_file_name);
}

//binary search on vector to check if word(s) exist
bool Dictionary::checkValid(string word)
{
	int min = 0;
	int max = _words.size()-1;
	int index = (max+min)/2;
	while(min <= max){
		if (word.compare(_words[index]) == 0){
			return true;
		}
		else if (word.compare(_words[index]) > 0){
			min = index + 1;
			index = (max+min)/2;
		}
		else if(word.compare(_words[index]) < 0){
			max = index - 1;
			index = (max+min)/2;
		}
	}
	return false;
}
