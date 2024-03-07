#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // Seed the random number generator
    std::srand(std::time(0));

    // Generate a random number between 1 and 100
    int randomNumber = std::rand() % 100 + 1;

    // Game loop
    bool isGuessCorrect = false;
    int guess;
    int numGuesses = 0;

    while (!isGuessCorrect) {
        // Get user input
        std::cout << "Enter your guess (1-100): ";
        std::cin >> guess;

        // Increment the number of guesses
        numGuesses++;

        // Check if the guess is correct
        if (guess == randomNumber) {
            std::cout << "Congratulations! You guessed the correct number in " << numGuesses << " guesses." << std::endl;
            isGuessCorrect = true;
        } else if (guess < randomNumber) {
            std::cout << "Too low! Try again." << std::endl;
        } else {
            std::cout << "Too high! Try again." << std::endl;
        }
    }

    return 0;
}