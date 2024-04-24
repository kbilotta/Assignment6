//
// Created by theco on 4/17/2024.
//
#include "Game.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <map>

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
    if (showWordCount) {
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
        cout << trueGuess << "\n";
        guessedLetters.push_back(trueGuess);
    WordFamily(trueGuess, potWords);
        numGuesses--;
}

void Game::WordFamily(char guess, list<string> words) {
    int WordFam[wordLength+1]; //tracks number of words in each category - guess in each index, then no guess
    list<string> boiledWords; //tracks words that contain the letter
    list<string> emptyWords; //tracks words that don't contain the letter
    list<string> returnWords; //The list of strings we'll return
    map <string, list<string>> wordFamilies; //improved version of WordFam, will track all words with same "index find string"
    string indexKey; //key that will be used in the dictionary
    for (int i = 0; i < wordLength+1; i++) {
        WordFam[i] = 0;
    }
    for (string word : words) {
        // int Found = word.find(guess);
        // if (Found != string::npos) {
        //     boiledWords.push_back(word);
        //     WordFam[Found] += 1;
        // } else {
        //     emptyWords.push_back(word);
        //     WordFam[wordLength] += 1;
        // }
        for (int i  = 0; i < word.length()-1; i++) { //use i for indexing
            //resets the word family indexes at each new word
            if (i == 0) {
                indexKey.clear();
            }
            //marks where the letter shows up in the word
            if (word[i] == tolower(guess)) {
                indexKey.append(to_string(i));
            }
            //okay this next part is kinda messy and can probably be improved later
            //at last char, places word in map
            if (i + 1 >= word.length()-1) {
                if (indexKey.empty()) {
                    emptyWords.push_back(word);
                    continue;
                }
                //that should be fine for words that are empty, right?
                wordFamilies[indexKey].push_back(word);
                //this above code will push into the temp list of strings for that value
            }
        }
    }
    int maxWords = 0;
    string selectedFamily;
    for (auto family: wordFamilies) {
        if (family.second.size() > maxWords) {
            maxWords = family.second.size();
            selectedFamily = family.first;
        }
    }
    if (emptyWords.size() >= wordFamilies[selectedFamily].size()) {
        returnWords = emptyWords;
    }
    else {
        returnWords = wordFamilies[selectedFamily];
        //below code should update wordShowcase with word family
        //don't need it in the above statement if nothing changes
        for (int i = 0; i < selectedFamily.length()-1; i++) {
            wordShowcase[int(selectedFamily[i])] = toupper(guess);
        }
    }
    // cout << "Num words: " << boiledWords.size() << endl;
    cout << "Num words: " << words.size() << endl;
    // cout << "Biggest Subgroup Size: " << *max_element(WordFam , WordFam+wordLength+1) << endl;
    cout << "Biggest Subgroup Size: " << returnWords.size() << endl;
    // int* targetPtr = find(&WordFam[0], WordFam + wordLength+1, *max_element(WordFam , WordFam+wordLength+1));
    // int targetIndex = targetPtr-WordFam;
    // cout << targetIndex << " " << wordLength << endl;
    // if (targetIndex < wordLength) {
    //     for (string word : boiledWords) {
    //         int Found = word.find(guess);
    //         if (Found == targetIndex) {
    //             returnWords.push_back(word);
    //         }
    //     }
    //     this->potWords = returnWords;
    // } else {
    //     this->potWords = emptyWords;
    // }
    this->potWords = returnWords;
    //.find
    //loop through word, add indicies to word if it exists
    //.find(start, end, letter), .find(prevStart, end, letter)
    //make mpa with string or array of digits where letter shows up, then add word to value with same string
}