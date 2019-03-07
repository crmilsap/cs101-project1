//
//  class.hpp
//  project1
//
//  Created by Cory Milsap on 1/24/19.
//  Copyright © 2019 Cory Milsap. All rights reserved.
//

#ifndef class_hpp
#define class_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

#endif /* class_hpp */
class word {
public:
    int getCount() { return count; }
    void increaseCount() { count++; }
    void setWord(string word) { this->word = word; }
    string getWord() { return word; }
private:
    string word = "NULL";
    int count = 0;
};

class words {
public:
    void InputWords(string word);
    int findWordCount(string word);
    unsigned long getUniqueCount();
    int getTotalWordCount();
    int findWordIndex(string word);
    string getWordAtIndex(int index);
    void Print(int index);
    
private:
    vector<word> wordList;
};
