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
    vector<char> guessedLetters;
    //char wordShowcase[wordLength];s
    void WordFamily(char letter, vector<string> words);
public:
    int numGuesses = 15;
    // list<char> wordShowcase;
    vector<char> wordShowcase;
    bool winGame = false;
    vector<string> potWords;

    Game(int wordLength, bool showWordCount, vector<string> potWords);

    void GetInfo();

    void Guess();
};

#endif //GAME_H