#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "Game.h"

using namespace std;

vector<string> listLengthFilter(vector<string> editList, int wordLength) {
    ifstream dictionary ("dictionary.txt");
    string myString;
    // pull in words from scrabble dictionary
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
    //create list to load dictionary into
    vector<string> words;
    //create a string to hold intermediate processing for whether the user wants to show the number of possible words
    string showWordCount;
    // create a boolean to hold the true value for whether the user wants to show the number of possible words
    bool trueShowWordCount;
    // create a string to hold the user-inputted answer length
    string answerLength;

    cout << "Welcome to (Unfair) Hangman!" << endl;
    cout << "Would like to know how many words the answer can be? (Y/N)" << endl;
    //updates showWordCount to the user-inputted value
    getline(cin, showWordCount);
    while ((char)tolower(showWordCount[0]) != 'y' && (char)tolower(showWordCount[0]) != 'n') {
        cout << "Please type either Y or N" << endl;
        getline(cin, showWordCount);
    }
    //set value for boolean show word count
    if ((char)tolower(showWordCount[0]) == 'y') {
        trueShowWordCount = true;
    }
    else {
        trueShowWordCount = false;
    }
    cout << "Great! How long should the word be? " << endl;
    //take answer length from user
    getline(cin, answerLength);
    int trueAnswerLength = checkInput(answerLength);
    //filter dictionary to just the list of words that match the user-specified answer length
    words = listLengthFilter(words, trueAnswerLength);
    while (words.empty()) {
        // check to see if there are errors with the number entered
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
    //instantiate the game!
    Game game(trueAnswerLength, trueShowWordCount, words);
    while (game.numGuesses > 0) {
        //check if game is won, if it is then go to won game output
        if (game.winGame) {
            break;
        }
        //print game info and get user guess, update number of guesses remaining
        game.GetInfo();
        game.Guess();
    }
    if (!game.winGame) {
        //If the user runs out of turns and game won isn't true, then output lost information
        cout << "Sorry! You lost!" << endl;
        int randomIndex = rand() % game.potWords.size();
        string randomWord = game.potWords[randomIndex];
        //Find way to capitalize random word
        for (int x=0; x<randomWord.length(); x++)
            putchar(toupper(randomWord[x]));
        cout << "The correct word was: " << randomWord << endl;
    }
    else {
        // win output
        cout << "WHAT?!" << endl;
        cout << "I mean, congratulations! You won, I guess." << endl;
    }

    return 0;
}