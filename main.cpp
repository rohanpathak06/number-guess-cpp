#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class NumberGuessingGame {
private:
    int secretNumber;
    int attempts;
    int maxAttempts;
    int lowerBound;
    int upperBound;

public:
    NumberGuessingGame(int lower = 1, int upper = 100, int maxTries = 7) 
        : lowerBound(lower), upperBound(upper), maxAttempts(maxTries), attempts(0) {
        srand(time(0));
        secretNumber = rand() % (upperBound - lowerBound + 1) + lowerBound;
    }

    void displayWelcome() {
        cout << "\n╔════════════════════════════════════════╗\n";
        cout << "║   🎮 NUMBER GUESSING GAME 🎮          ║\n";
        cout << "╚════════════════════════════════════════╝\n\n";
        cout << "I'm thinking of a number between " << lowerBound 
             << " and " << upperBound << ".\n";
        cout << "You have " << maxAttempts << " attempts to guess it!\n";
        cout << "Good luck! 🍀\n\n";
    }

    bool makeGuess() {
        int guess;
        cout << "Attempt " << (attempts + 1) << "/" << maxAttempts << " - Enter your guess: ";
        
        // Input validation
        while (!(cin >> guess)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number: ";
        }

        attempts++;

        if (guess == secretNumber) {
            return true;
        } else if (guess < secretNumber) {
            cout << "📈 Too low! Try a higher number.\n\n";
        } else {
            cout << "📉 Too high! Try a lower number.\n\n";
        }

        // Give hints when running out of attempts
        if (attempts == maxAttempts - 2) {
            cout << "💡 Hint: The number is " 
                 << (secretNumber % 2 == 0 ? "EVEN" : "ODD") << "\n\n";
        }

        return false;
    }

    void displayResult(bool won) {
        if (won) {
            cout << "\n🎉 CONGRATULATIONS! 🎉\n";
            cout << "You guessed the number " << secretNumber 
                 << " in " << attempts << " attempt(s)!\n";
            
            if (attempts == 1) {
                cout << "WOW! First try! Are you psychic? 🔮\n";
            } else if (attempts <= 3) {
                cout << "Amazing! You're really good at this! ⭐\n";
            } else if (attempts <= 5) {
                cout << "Nice job! Well played! 👍\n";
            } else {
                cout << "You made it! That was close! 😅\n";
            }
        } else {
            cout << "\n💔 Game Over!\n";
            cout << "The number was: " << secretNumber << "\n";
            cout << "Better luck next time! 🎲\n";
        }
    }

    bool hasAttemptsLeft() {
        return attempts < maxAttempts;
    }

    void play() {
        displayWelcome();
        
        while (hasAttemptsLeft()) {
            if (makeGuess()) {
                displayResult(true);
                return;
            }
        }
        
        displayResult(false);
    }
};

int main() {
    char playAgain;
    
    do {
        NumberGuessingGame game(1, 100, 7);
        game.play();
        
        cout << "\n🔄 Want to play again? (y/n): ";
        cin >> playAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
    } while (playAgain == 'y' || playAgain == 'Y');
    
    cout << "\nThanks for playing! Goodbye! 👋\n\n";
    
    return 0;
}