//Program: Rahmani_Erfan_huffmancoding_input.cpp
//Course: TCP2101 Algorithm Design & Analaysis
//Class: TC1L
//Trimester: 2220
//Member_1 1201102372 | Rahmani Erfan | 1201102372@student.mmu.edu.my | //+60 183120426
//********************************************************************************
//Task Distribution:
// Member 1: Everything
//********************************************************************************


#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>

// Function to generate a random word of length 4 or 5
std::string generateRandomWord() {
    static const std::string chars = "abcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    unsigned seed = rd() ^ 1201102372;
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(0, chars.size() - 1);

    int length = (dis(gen) % 2) + 4; // Randomly choose length 4 or 5 (length of word)
    std::string word;

    for (int i = 0; i < length; ++i) {
        word += chars[dis(gen)];
    }

    return word;
}

int main() {
    int numWords;

    // Set the seed for random number generation``
    std::random_device rd;
    unsigned seed = rd() ^ 1201102372; //bitwise XOR between random device and the seed. (If seed is used only, output will all be the same)
    std::mt19937 gen(seed); //Generator Engine
    std::uniform_int_distribution<> dis(1, 26);
    int randUniqueChars = dis(gen);

    std::cout << "Enter the number of words to generate: ";
    std::cin >> numWords;

    // Generate unique characters
    std::vector<char> uniqueChars;

    for (int i = 0; i < randUniqueChars; ++i) {
        std::string word = generateRandomWord();

        for (char c : word) { //itierate through every character in word.
            if (std::find(uniqueChars.begin(), uniqueChars.end(), c) == uniqueChars.end()) {
                uniqueChars.push_back(c); //appending the unique characters.
            }
        }
    }


    // Write the output to a text file
    std::ofstream outputFile("huffmancoding_" + std::to_string(numWords) + "_input.txt");
    if (!outputFile) {
        std::cerr << "Failed to open the output file." << std::endl;
        return 1;
    }

    // Write the number of unique characters
    int numUniqueChars = uniqueChars.size();
    outputFile << numUniqueChars << std::endl;

    // Write the list of unique characters
    for (char c : uniqueChars) {
        outputFile << c << "\n";
    }
    outputFile << std::endl;

    // Write the list of words
    for (int i = 0; i < numWords; ++i) {
        outputFile << generateRandomWord() << " ";
    }
    outputFile << std::endl;

    outputFile.close();

    std::cout << "File Generated." << std::endl;

    return 0;
}
