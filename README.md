# BullsAndCows by Maxim Pupykin (https://github.com/Finnyke)
C++ implementation of the game "Bulls and cows". Console application.

Rules of the game:
A secret number consisting of N non-repeating digits (in this program, N in range from 2 to 10 is given by the user) is created.
Each turn player tries to guess the secret number.
The guess is then evaluated by giving an amount of matching digits following next rule:

 - If digit in a guessed number is in the same position as in the secret number, it is considered a "bull";
 - If it is in different position, it is considered a "cow".

The amounts of "bulls" and "cows" are presented to the player afterwards.
If amount of "bulls" equals N, meaning that the secret number has been guessed correctly, the game is won.
If not, the player makes another guess.

More about the game: https://en.wikipedia.org/wiki/Bulls_and_Cows

This program also saves the result of each game in file game_results.txt. The stored information is: N, number of guesses, date and time of game completion.
