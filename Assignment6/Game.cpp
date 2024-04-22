//
// Created by theco on 4/17/2024.
//
#include "Game.h"
#include <algorithm>

//CONSTRUCTOR
Game::Game(int wordLength, bool showWordCount, list<string> potWords) {
    this->wordLength = wordLength;
    this->showWordCount = showWordCount;
    this->potWords = potWords;
    for (int i = 0; i < wordLength; i++) {
        wordShowcase.push_back('_');
    }
}

void Game::GetInfo() {
    cout << "You have " << numGuesses << " guesses remaining." << endl;
    cout << "Letters Guessed: ";
    for (char letter : guessedLetters) {
        cout << (char)toupper(letter) << " ";
    }
    if (showWordCount == true) {
        cout << "\nWords Remaining: " << potWords.size() << endl;
    }
    for (char letters : wordShowcase) {
        cout << letters << " ";
    }
    cout << "\n";
}

void Game::Guess() {
    string guess;
    char trueGuess;
    cout << "Guess a Letter: ";
    getline (cin, guess);
    cout << "\n";
        while (guess.length() != 1 || find(guessedLetters.begin(), guessedLetters.end(), guess[0]) != guessedLetters.end()) {
            if (guess.length() != 1) {
                cout << "Please try again with a single letter." << endl;
                cout << "Guess a Letter: ";
                getline (cin, guess);
                cout << "\n";
            }
            if (find(guessedLetters.begin(), guessedLetters.end(), guess[0]) != guessedLetters.end()) {
                cout << "Already guessed that letter." << endl;
                cout << "Guess a Letter: ";
                getline (cin, guess);
                cout << "\n";
            }
        }
        trueGuess = guess[0];
        guessedLetters.push_back(trueGuess);
    WordFamily(trueGuess, potWords);
        numGuesses--;
}

void Game::WordFamily(char guess, list<string> words) {
    list<string> boiledWords;
    for (string word : words) {
        if (word.find(guess) != std::string::npos) {
            boiledWords.push_back(word);
        }
    }
    cout << "Num words: " << boiledWords.size() << endl;
    potWords = boiledWords;
}

