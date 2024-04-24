#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "Game.h"

using namespace std;

vector<string> listLengthFilter(vector<string> editList, int wordLength) {
    ifstream dictionary ("testDictionary.txt");
    string myString;

    if (dictionary.is_open()) {
        while (!dictionary.eof()) {
            getline(dictionary, myString);
            if (myString.length() == wordLength) {
                editList.push_back(myString);
            }
        }
    }
    else {
        cout << "Couldn't open file\n";
    }

    dictionary.close();
    //if editList is empty, ask for new input and run it through
    return editList;
}

int checkInput(const string& input) {
    try {
        if (!stoi(input)) {
            throw;
        }
    }
    catch(...) {
        return -1;
    }
    int const potInput = stoi(input);
    if (potInput < 1) {
        return -1;
    }
    return potInput;
}

int main()
{
    vector<string> words;
    string showWordCount;
    bool trueShowWordCount;
    string answerLength;

    cout << "Welcome to (Unfair) Hangman!" << endl;
    cout << "Would like to know how many words the answer can be? (Y/N)" << endl;
    getline(cin, showWordCount);
    while ((char)tolower(showWordCount[0]) != 'y' && (char)tolower(showWordCount[0]) != 'n') {
        cout << "Please type either Y or N" << endl;
        getline(cin, showWordCount);
    }
    if ((char)tolower(showWordCount[0]) == 'y') {
        trueShowWordCount = true;
    }
    else {
        trueShowWordCount = false;
    }
    cout << "Great! How long should the word be? " << endl;
    cin >> answerLength;
    int trueAnswerLength = checkInput(answerLength);

    words = listLengthFilter(words, trueAnswerLength);
    while (words.empty()) {
        if (trueAnswerLength > 0) {
            cout << "No words of that length found. Please provide a new number." << endl;
        }
        else {
            cout << "Please try again with a positive number." << endl;
        }
        cin >> answerLength;
        trueAnswerLength = checkInput(answerLength);
        words = listLengthFilter(words, trueAnswerLength);
    }

    Game game(trueAnswerLength, trueShowWordCount, words);
    while (game.numGuesses > 0) {
        if (game.winGame) {
            break;
        }
        game.GetInfo();
        game.Guess();
    }
    if (!game.winGame) {
        //add LoseGame function
        cout << "Sorry! You lost!" << endl;
        int randomIndex = rand() % game.potWords.size();
        string randomWord = game.potWords[randomIndex];
        //Find way to capitalize random word
        cout << "The correct word was: " << randomWord << endl;
    }
    else {
        cout << "WHAT?!" << endl;
        cout << "I mean, congratulations! You won, I guess." << endl;
    }

    return 0;
}