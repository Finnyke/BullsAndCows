#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <time.h>

int read_amount() {
	std::string input;
	int res = 0;
	std::cout << "Enter the number of digits: ";
	while (true) {
		std::cin >> input;
		if (input.length() > 2) {
			std::cout << "Error: input string is too large. Try again: " << std::endl;
			continue;
		}
		if (input.length() == 1) {
			if (input[0] < '0' || input[0] > '9') {
				std::cout << "Error: input string is not a number. Try again: " << std::endl;
				continue;
			}
			if (input[0] > '9' || input[0] < '2') {
				std::cout << "Error: input is out of range. Valid range is from 2 to 10. Try again: " << std::endl;
				continue;
			}
		}
		if (input.length() == 2) {
			if (input[0] < '0' || input[0] > '9') {
				std::cout << "Error: input string is not a number. Try again: " << std::endl;
				continue;
			}
			if (input[1] < '0' || input[1] > '9') {
				std::cout << "Error: input string is not a number. Try again: " << std::endl;
				continue;
			}
			if (input[0] > '1' || input[1] != '0') {
				std::cout << "Error: input is out of range. Valid range is from 2 to 10. Try again: " << std::endl;
				continue;
			}
		}
		input.length() == 2 ? res = 10 : res = static_cast<int>(input[0] - 48);
		break;
	}
	return res;
}

std::pair<int, int> game() {
	int num = read_amount();
	std::vector<int> arr;
	for (auto i = 0; i < num; ++i) {
		int dig;
		for (bool flag = true; flag != false;) {
			dig = rand() % 10;
			flag = false;
			for (auto j : arr) {
				if (dig == j) {
					flag = true;
					break;
				}
			}
		}
		arr.push_back(dig);
	}
	int cows;
	int bulls;
	std::vector<int> guess;
	int guess_cnt = 0;
	while (true) {
		cows = 0;
		bulls = 0;
		guess_cnt++;
		std::cout << "Make a guess: ";
		std::string input;
		bool flag = true;
		while (flag) {
			flag = false;
			std::cin >> input;
			if (input.length() > static_cast<size_t>(num)) {
				std::cout << "Error: input string is too large. Try again: " << std::endl;
				flag = true;
				continue;
			}
			for (auto i = 0; i < num; ++i) {
				if (input[i] > '9' || input[i] < '0') {
					std::cout << "Error: invalid character found in the input. Try again: ";
					flag = true;
					break;
				}
			}
			if (flag) continue;
			for (auto i = 0; i < num; ++i) {
				for (auto j = 0; j < i; ++j) {
					if (input[i] == input[j]) {
						std::cout << "Error: repeating character found in the input. Try again: ";
						flag = true;
						break;
					}
				}
				if (flag) break;
			}
		}
		for (auto i = 0; i < num; ++i) {
			guess.push_back(static_cast<int>(input[i] - 48));
		}
		for (auto i = 0; i < num; ++i) {
			for (auto j = 0; j < num; ++j) {
				if (arr.at(i) == guess.at(j)) {
					if (i == j) bulls++;
					else cows++;
				}
			}
		}
		std::cout << bulls << " bulls, " << cows << " cows" << std::endl;
		if (bulls == num) break;
		guess.clear();
	}
	std::cout << "Congratulation, you won! It took you " << guess_cnt << " guesses!" << std::endl;
	return std::pair<int, int>(num, guess_cnt);
}

void get_answer(bool &b) {
	std::cout << "Do you want to play again? (Y/N)" << std::endl;
	std::string input;
	for (auto answer = 'N';;) {
		std::cin >> input;
		if (input.length() == 1) {
			answer = input.at(0);
		}
		else {
			std::cout << "Error: input string is too large. Valid inputs are Y and N. Try again: " << std::endl;
			continue;
		}
		if (toupper(answer) == 'Y') {
			b = true;
			return;
		}
		else if (toupper(answer) == 'N') {
			b = false;
			return;
		}
		else {
			std::cout << "Error: invalid input. Valid inputs are Y and N. Try again: " << std::endl;
			continue;
		}
	}
}

void save_result(std::pair<int, int> game_result) {
	std::ofstream fout("game_results.txt", std::ios_base::app);
	char time_output[40];
	tm current_time;
	const time_t timer = time(NULL);
	localtime_s(&current_time, &timer);
	strftime(time_output, 40, "%d.%m.%Y %H:%M:%S : ", &current_time);
	if (fout.is_open())
	{
		fout << time_output << "game was completed in " << game_result.second <<
			" guesses for " << game_result.first << " digits." << std::endl;
		fout.close();
	}
	else {
		std::cout << "Warning: the result of this game will not be saved as the file for storing results could not be opened/created" << std::endl;
	}
}

int main() {
	srand(static_cast<int>(time(NULL)));
	std::pair<int, int> game_result;
	for (auto answer = true; answer;) {
		game_result = game();
		save_result(game_result);
		get_answer(answer);
	}
	return 0;
}
