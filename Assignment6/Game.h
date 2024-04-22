//
// Created by theco on 4/17/2024.
//

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <list>
#include <array>

using namespace std;

class Game {
private:
    bool showWordCount;
    //protected:
    int wordLength;
    // int numGuesses = 15;
    list<char> guessedLetters;
    //char wordShowcase[wordLength];
    list<char> wordShowcase;
    list<string> potWords;
    void WordFamily(char letter, list<string> words);
public:
    int numGuesses = 15;

    Game(int wordLength, bool showWordCount, list<string> potWords);

    void GetInfo();

    void Guess();
};

#endif //GAME_H