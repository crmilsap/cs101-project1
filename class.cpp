//
//  class.cpp
//  project1
//
//  Created by Cory Milsap on 1/24/19.
//  Copyright © 2019 Cory Milsap. All rights reserved.
//

#include "class.hpp"

void words::InputWords(string word) {
    int index = findWordIndex(word);
    if (index == -1) {
        class word newWord;
        newWord.setWord(word);
        newWord.increaseCount();
        wordList.push_back(newWord);
    }
    else {
        wordList.at(index).increaseCount();
    }
}

int words::findWordIndex(string word) {
    class word currWord;
    for (unsigned int i = 0; i < wordList.size(); i++) {
        currWord = wordList.at(i);
        if (word == currWord.getWord()) return i;
    }
    return -1;
}

int words::findWordCount(string word) { //given a word, finds in list and returns count
    int index = findWordIndex(word);
    if (index == -1) return 0;
    return wordList.at(index).getCount();
}

unsigned long words::getUniqueCount() {
    return wordList.size();
}

int words::getTotalWordCount() {
    int sum = 0;
    for (unsigned int i = 0; i < wordList.size(); i++) {
        sum += wordList.at(i).getCount();
    }
    return sum;
}

string words::getWordAtIndex(int index) {
    return wordList.at(index).getWord();
}

void words::Print(int index) {
    cout << "The word " << wordList.at(index).getWord() << " appears " << wordList.at(index).getCount() << " times in the document" << endl;
}
