//
// Created by theco on 4/17/2024.
//

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <list>
#include <array>
#include <vector>

using namespace std;

class Game {
private:
    bool showWordCount;
    //protected:
    int wordLength;
    // int numGuesses = 15;
    list<char> guessedLetters;
    //char wordShowcase[wordLength];
    list<string> potWords;
    void WordFamily(char letter, list<string> words);
public:
    int numGuesses = 15;
    // list<char> wordShowcase;
    vector<char> wordShowcase;

    Game(int wordLength, bool showWordCount, list<string> potWords);

    void GetInfo();

    void Guess();
};

#endif //GAME_H