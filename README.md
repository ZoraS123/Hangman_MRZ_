# Hangman (C++)

A console-based Hangman game built in **C++** as a collaborative team project.  
Players guess letters to reveal a hidden word before running out of attempts.

**Team:** Zora Smith, Mary Petros, Reagan DeLisle

---

## Features

- Interactive command-line gameplay
- Alphabetic input validation
- Case-insensitive letter matching
- Duplicate-guess prevention
- Incorrect-guess tracking
- Dynamic word-state updates
- Win/loss detection
- Replay functionality

## My Contributions

As part of a three-person development team, I was primarily responsible for implementing the core gameplay logic, including:

- Developed the main gameplay loop
- Implemented user input validation and character case normalization
- Added duplicate-guess prevention and incorrect-guess tracking
- Implemented logic for updating the displayed word state after each guess
- Developed win/loss detection and replay functionality
- Collaborated with team members to integrate individual components into the final C++ application

## Technologies

- C++
- CMake
- Git
- GitHub

## Run Locally

```bash
git clone https://github.com/zoraS123/Hangman_MRZ_.git
cd Hangman_MRZ_
g++ -std=c++17 main.cpp -o hangman
./hangman
