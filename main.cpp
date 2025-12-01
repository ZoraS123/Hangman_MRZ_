#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

const int MAX_ERRORS = 6;

// ------------------------------------------------------------
//                   FUNCTION PROTOTYPES
// ------------------------------------------------------------

// ----- MARY: Menus + File I/O + Stats -----
int showMenu();
void showIntro();
vector<string> loadWordsFromFile(const string& filename);
void updateStats(bool won, int wrongGuesses);
void showStats();

// ----- REAGAN: Drawing + Random Word Logic -----
string chooseWord(const vector<string>& words);
void drawHangman(int wrongGuesses);
void displayWordState(const string& currentState);
void displayGuessedLetters(const bool guessedLetters[26]);
void displayWrongLetters(const string& wrongLetters);

// ----- ZORA: Gameplay Loop + Input Validation -----
char getValidGuess(bool guessedLetters[26]);
bool updateStateWithGuess(const string& secretWord, string& currentState, char guess);
bool isWordGuessed(const string& currentState);
void playOneGame(const vector<string>& words, bool& keepPlaying);

// ------------------------------------------------------------
//                           MAIN
// ------------------------------------------------------------
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    bool keepPlaying = true;

    // ----- MARY: File I/O -----
    vector<string> words = loadWordsFromFile("words.txt");

    if (words.empty()) {
        cout << "words.txt not found. Loading default words.\n";

        // ----- REAGAN: Default word list -----
        words = {"apple", "banana", "cherry", "hangman", "science",
                 "cplusplus", "project", "computer"};
    }

    // ----- MARY: Menu + control loop -----
    while (keepPlaying) {
        int choice = showMenu();

        switch (choice) {
            case 1:
                showIntro();
                playOneGame(words, keepPlaying);
                break;

            case 2:
                showStats();
                break;

            case 3:
                keepPlaying = false;
                break;

            default:
                cout << "Please enter 1–3.\n";
        }
    }

    cout << "\nThanks for playing Team Hangman!\n";
    return 0;
}

// ------------------------------------------------------------
//                MARY: Menus, File I/O, Stats
// ------------------------------------------------------------

int showMenu() {
    int pick;
    cout << "\n=============================\n";
    cout << "            MENU             \n";
    cout << "=============================\n";
    cout << "1) Play Hangman\n";
    cout << "2) View Statistics\n";
    cout << "3) Quit\n";
    cout << "Enter choice: ";
    cin >> pick;

    if (!cin) {
        cin.clear();
        cin.ignore(1000, '\n');
        return 0;
    }
    return pick;
}

void showIntro() {
    cout << "\n===============================\n";
    cout << "       WELCOME TO HANGMAN      \n";
    cout << "===============================\n";
    cout << "Guess the secret word one letter at a time.\n";
    cout << "You have " << MAX_ERRORS << " wrong guesses.\n\n";
}

vector<string> loadWordsFromFile(const string& filename) {
    vector<string> words;
    ifstream file(filename);
    string word;

    while (file >> word) {
        words.push_back(word);
    }

    return words;
}

void updateStats(bool won, int wrongGuesses) {
    int totalGames = 0, totalWins = 0, totalWrong = 0;

    ifstream in("stats.txt");
    if (in) {
        in >> totalGames >> totalWins >> totalWrong;
    }
    in.close();

    totalGames++;
    if (won) totalWins++;
    totalWrong += wrongGuesses;

    ofstream out("stats.txt");
    out << totalGames << " " << totalWins << " " << totalWrong;
    out.close();
}

void showStats() {
    int totalGames = 0, totalWins = 0, totalWrong = 0;

    ifstream in("stats.txt");
    if (!in) {
        cout << "\nNo stats recorded yet.\n";
        return;
    }

    in >> totalGames >> totalWins >> totalWrong;
    in.close();

    cout << "\n===== GAME STATISTICS =====\n";
    cout << "Games Played: " << totalGames << "\n";
    cout << "Wins: " << totalWins << "\n";

    if (totalGames > 0) {
        double winRate = (static_cast<double>(totalWins) / totalGames) * 100.0;
        cout << "Win Rate: " << winRate << "%\n";

        double avgWrong = static_cast<double>(totalWrong) / totalGames;
        cout << "Average Wrong Guesses: " << avgWrong << "\n";
    }

    cout << "===========================\n\n";
}

// ------------------------------------------------------------
//          REAGAN: Drawing + Random Word Logic
// ------------------------------------------------------------

string chooseWord(const vector<string>& words) {
    int index = rand() % words.size();
    return words[index];
}

void drawHangman(int wrongGuesses) {
    cout << "\n +---+\n";
    cout << " |   |\n";

    (wrongGuesses >= 1) ? cout << " O   |\n" : cout << "     |\n";

    if (wrongGuesses == 2)
        cout << " |   |\n";
    else if (wrongGuesses == 3)
        cout << "/|   |\n";
    else if (wrongGuesses >= 4)
        cout << "/|\\  |\n";
    else
        cout << "     |\n";

    if (wrongGuesses == 5)
        cout << "/    |\n";
    else if (wrongGuesses >= 6)
        cout << "/ \\  |\n";
    else
        cout << "     |\n";

    cout << "     |\n";
    cout << " =========\n";
}

void displayWordState(const string& currentState) {
    cout << "Word: ";
    for (char c : currentState) {
        cout << c << " ";
    }
    cout << "\n";
}

void displayGuessedLetters(const bool guessedLetters[26]) {
    cout << "Guessed Letters: ";
    for (int i = 0; i < 26; i++) {
        if (guessedLetters[i]) {
            cout << char('a' + i) << " ";
        }
    }
    cout << "\n";
}

void displayWrongLetters(const string& wrongLetters) {
    cout << "Wrong Letters: ";
    for (char c : wrongLetters) {
        cout << c << " ";
    }
    cout << "\n";
}

// ------------------------------------------------------------
//         ZORA: Game Loop + Input Validation
// ------------------------------------------------------------

char getValidGuess(bool guessedLetters[26]) {
    char guess;
    while (true) {
        cout << "Enter a letter: ";
        cin >> guess;
        guess = tolower(guess);

        if (guess < 'a' || guess > 'z') {
            cout << "Invalid. Enter a letter A–Z.\n";
            continue;
        }

        int idx = guess - 'a';
        if (guessedLetters[idx]) {
            cout << "You already guessed that.\n";
            continue;
        }

        guessedLetters[idx] = true;
        return guess;
    }
}

bool updateStateWithGuess(const string& secretWord,
                          string& currentState,
                          char guess) {
    bool found = false;

    for (int i = 0; i < secretWord.length(); i++) {
        if (tolower(secretWord[i]) == guess && currentState[i] == '_') {
            currentState[i] = secretWord[i];
            found = true;
        }
    }

    return found;
}

bool isWordGuessed(const string& currentState) {
    for (char c : currentState) {
        if (c == '_') return false;
    }
    return true;
}

void playOneGame(const vector<string>& words, bool& keepPlaying) {
    string secretWord = chooseWord(words);
    string currentState(secretWord.length(), '_');

    bool guessedLetters[26] = {false};
    string wrongLetters = "";
    int wrongGuesses = 0;

    cout << "\nStarting new game...\n";

    while (true) {
        drawHangman(wrongGuesses);
        displayWordState(currentState);
        displayGuessedLetters(guessedLetters);
        displayWrongLetters(wrongLetters);

        cout << "Wrong guesses left: " << (MAX_ERRORS - wrongGuesses) << "\n";

        char guess = getValidGuess(guessedLetters);
        bool correct = updateStateWithGuess(secretWord, currentState, guess);

        if (!correct) {
            wrongGuesses++;
            wrongLetters += guess;
            cout << "Incorrect guess.\n";
        } else {
            cout << "Correct!\n";
        }

        if (isWordGuessed(currentState)) {
            cout << "\nYou WIN! The word was: " << secretWord << "\n";
            updateStats(true, wrongGuesses);
            break;
        }

        if (wrongGuesses >= MAX_ERRORS) {
            drawHangman(wrongGuesses);
            cout << "\nYou LOST! The word was: " << secretWord << "\n";
            updateStats(false, wrongGuesses);
            break;
        }
    }

    // Replay?
    char again;
    cout << "\nPlay again? (y/n): ";
    cin >> again;
    if (tolower(again) == 'n') {
        keepPlaying = false;
    }
}
