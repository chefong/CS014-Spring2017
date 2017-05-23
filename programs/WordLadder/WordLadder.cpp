#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <stack>
#include <string>

using namespace std;

#include "WordLadder.h"

// void printStack(stack<string> s) {
//     while(!s.empty()) {
//         cout << s.top() << ",";
//         s.pop();
//     }
//     cout << endl;
// }

WordLadder::WordLadder(const string & filename) {
    ifstream inFS;
    string word;

    inFS.open(filename.c_str()); // opens file name passed in
    if (!inFS.is_open()) {
        cout << "Error" << endl;
        return;
    }

    while (inFS >> word) {
        if (word.size() == 5) { // pushes back all words that are size 5
            dict.push_back(word);
        }
        else {
            cout << "Error" << endl; // output error and return if word is 5 letters
            return;
        }
    }

    inFS.close();
}

bool WordLadder::oneLetterDifference(const string &word1, const string &word2) {
    int numLetter = 0;
    for (unsigned i = 0; i < word1.size(); i++) {
        if (word1.at(i) != word2.at(i)) {
            numLetter++; // counts how many letters are different
        }
    }

    if (numLetter > 1) {
        return false; // more than 1 letter is different
    }
    else {
        return true; // only 1 letter is different
    }
}

bool WordLadder::wordExists(const string &word) {
    for (list<string>::iterator i = dict.begin(); i != dict.end(); ++i) {
        if (*i == word) {
            return true;
        }
    }
    return false;
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
    string topWord;
    ofstream outFS;
    outFS.open(outputFile.c_str());

    if (!outFS.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }

    if (!wordExists(start) || !wordExists(end)) {
        cout << "Word(s) not in dictionary" << endl;
        return;
    }

    if (start == end) { // outputs to file if same word
        outFS << start << endl;
        outFS.close();
        return;
    }

    stack<string> stack1; // creates a stack of strings
    stack1.push(start); // stack now contains first word

    queue<stack<string> > wordLadder; // creates a queue of stacks of strings
    wordLadder.push(stack1); // enqueues first stack

    while (!wordLadder.empty()) {
        topWord = wordLadder.front().top();
        for (list<string>::iterator i = dict.begin(); i != dict.end(); ++i) {
            if (oneLetterDifference(topWord, *i)) { // checks if theres a 1 letter difference
                stack<string> copyStack(wordLadder.front());
                copyStack.push(*i);
                if (*i == end) {
                    stack<string> reverseStack;
                    while (!copyStack.empty()) { // makes a new stack and reverses order
                        reverseStack.push(copyStack.top());
                        copyStack.pop();
                    }
                    while (!reverseStack.empty()) { // outputs word ladder to file
                        outFS << reverseStack.top() << endl;
                        reverseStack.pop();
                    }
                    outFS.close();
                    return;
                }
                else {
                    wordLadder.push(copyStack); // enqueues new stack
                    dict.erase(i); // erases word from dictionary
                    i--;
                }
            }
        }
        wordLadder.pop(); // dequeues front stack
    }
    outFS << "No Word Ladder Found." << endl;
    outFS.close();
    return;
}
