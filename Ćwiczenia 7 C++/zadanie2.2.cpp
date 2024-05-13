#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

constexpr int MAX_RED = 12;
constexpr int MAX_GREEN = 13;
constexpr int MAX_BLUE = 14;

bool isPossible(int red, int green, int blue) {
    return (MAX_RED >= red && MAX_GREEN >= green && MAX_BLUE >= blue);
}

std::string extractGameNumber(const std::string& input) {
    std::string gameNumber;
    std::istringstream iss(input);
    std::string word;

    while (iss >> word) {
        if (word == ":")
            iss >> gameNumber;
    }

    return gameNumber;
}

void analyze(const std::string& input) {
    int red = 0, green = 0, blue = 0;
    std::istringstream iss(input);
    std::string word;

    while (iss >> word) {
        int amount;
        std::istringstream(word) >> amount;
        iss >> word;

        if (word.empty())
            continue;

        char color = word[0];
        switch (color) {
            case 'r':
                red += amount;
                break;
            case 'g':
                green += amount;
                break;
            case 'b':
                blue += amount;
                break;
            default:
                break;
        }
    }

    if (isPossible(red, green, blue)) {
        std::cout << "Gra " << extractGameNumber(input) << std::endl;
    }
}

int main() {
    std::ifstream file("input_2.txt");
    if (!file.is_open()) {
        std::cerr << "Błąd otwarcia pliku" << std::endl;
        return 1;
    }

    std::cout << "Możliwe gry:" << std::endl;
    std::string line;
    while (std::getline(file, line)) {
        analyze(line);
    }

    file.close();
    return 0;
}
