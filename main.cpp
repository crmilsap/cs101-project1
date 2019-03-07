//
//  main.cpp
//  project1
//
//  Created by Cory Milsap on 1/22/19.
//  CWID = 11875059
//

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstdio>
#include <sstream>
#include <vector>
#include <iterator>
#include "class.hpp"
using namespace std;

words addAllWords(string fileName);
bool stringIsAlpha(string word);
bool canOpenFile(string fileName);
string removeAllNonalphas(string text);
vector<string> seperateWords(string text);
void getWildCardMatches(words wordList, string wordWithWild);
bool wordsMatch(string wordInList, string checkedWord);
string lowerCase(string word);
bool onlyWildcardsRemaining(string word);


int main(int argc, const char * argv[]) \
{
        if (argc != 2) {
            cout << "Usage: ./a.out filename" << endl;
            return 1;
        }
            string fileName = argv[1];
            if (!canOpenFile(fileName)) {
                cout << "ERROR: Cannot open " << fileName << " for reading." << endl;
                return -1;
            }
            words wordList;
            wordList = addAllWords(fileName);
            cout << endl << "The number of words found in the file was " << wordList.getTotalWordCount() << endl;
            cout << "The number of unique words found in the file was " << wordList.getUniqueCount() << endl;
            string searchTerm;
            
            cout << endl << "Please enter a word: " << endl;
            while (getline(cin, searchTerm)) {
                if (searchTerm.find('?') != string::npos) {
                    getWildCardMatches(wordList, searchTerm);
                }
                else {
                    cout << "The word " << searchTerm << " appears " << wordList.findWordCount(searchTerm) << " times in the document" << endl;
                }
                cout << endl << "Please enter a word: " << endl;
            }
        return 0;
}

bool stringIsAlpha(string word)
{
    bool alpha = true;
    for (unsigned int i = 0; i < word.length(); i++) {
        if (!isalpha(word.at(i))) {
            alpha = false;
        }
    }
    return alpha;
}
            
words addAllWords(string fileName) {
    words wordList;
    ifstream inFile;
    inFile.open(fileName);
    string tempWord;
    vector<string> multTemps;
    while (inFile >> tempWord) {
        if (stringIsAlpha(tempWord)) {
            wordList.InputWords(lowerCase(tempWord));
        }
        else {
            multTemps = seperateWords(tempWord);
            for (unsigned int i = 0; i < multTemps.size(); i++) { //adds multTemps to wordList
                wordList.InputWords(lowerCase(multTemps.at(i)));
            }
        }
    }
    return wordList;
}
            
bool canOpenFile(string fileName) {
    ifstream inFile;
    inFile.open(fileName);
    if (!inFile) {
        return false;
        }
    else return true;
}

string removeAllNonalphas(string text)
{
    for (unsigned int i = 0; i < text.size(); i++) {
        if (!isalpha(text.at(i))) {
            text.replace(i, 1, " ");
        }
    }
    return text;
}
            
vector<string> seperateWords(string text) {
    text = removeAllNonalphas(text);
    istringstream iss(text);
    vector<string> results((istream_iterator<string>(iss)), istream_iterator<string>());
    return results;
}

void getWildCardMatches(words wordList, string wordWithWild) {
    bool flag = false;
    for (unsigned int i = 0; i < wordList.getUniqueCount(); i++) {
        if (wordsMatch(wordList.getWordAtIndex(i), wordWithWild)) {
            wordList.Print(i);
            flag = true;
        }
    }
    if (flag == false) cout << "The word " << wordWithWild << " appears 0 times in the document" << endl;

}
            
bool wordsMatch(string wordInList, string checkedWord) {
    if (wordInList.size() > checkedWord.size()) return false;
    if (checkedWord.at(0) != '?') { // the letter we are looking at is not a wildcard
        if (wordInList.at(0) == checkedWord.at(0)) { // the two letters we are looking at match
            if (wordInList.size() == 1) { // the size of the word we want to match is 1
                if (checkedWord.size() == 1) return true; // if the size of the checked word is also one then it is a match
                if (onlyWildcardsRemaining(checkedWord.substr(1, checkedWord.size() - 1))) { //it could still be a match if the remaining characters are only ?'s FIXME
                    return true;
                }
                else return false;
            }
            return wordsMatch(wordInList.substr(1, wordInList.size() - 1), checkedWord.substr(1, checkedWord.size() - 1));
        }
        return false;
    }
    else { // we will either replace the wildcard with a letter or skip it
        if (wordInList.size() == 1) {
            if (checkedWord.size() == 1) return true; // size of both words is one
            return wordsMatch(wordInList, checkedWord.substr(1, checkedWord.size() - 1)); // size of checked word is greater than one, move on to next character
        }
        if (wordInList.size() == checkedWord.size()) {// we can't skip the wildcard character because the strlen are the same
            return wordsMatch(wordInList.substr(1, wordInList.size() - 1), checkedWord.substr(1, checkedWord.size() - 1));
        }
        //wordInList must be shorter than checkedList
        if (wordsMatch(wordInList, checkedWord.substr(1, checkedWord.size() - 1))) { //if the word is able to match when skipping the character
            return true;
        }
        if (wordsMatch(wordInList.substr(1, wordInList.size() - 1), checkedWord.substr(1, checkedWord.size() - 1))) {
            return true;
        }
        return false;
    }
}
     
string lowerCase(string word) {
    string copy = word;
    for (unsigned int i = 0; i < word.size(); i++) {
        copy.at(i) = tolower(word.at(i));
    }
    return copy;
}
            
bool onlyWildcardsRemaining(string word) {
    for (unsigned int i = 0; i < word.size(); i++) {
        if (word.at(i) != '?') return false;
    }
    return true;
}

