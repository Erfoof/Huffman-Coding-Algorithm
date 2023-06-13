//Program: Rahmani_Erfan_huffmancoding_output.cpp
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
#include <map>
#include <queue>
#include <bitset>
#include <chrono>
#include <string>
#include <iomanip>
#include <algorithm>

// Node for huffman tree.
struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;

    Node(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

// Custom comparator for priority queue based on frequency
struct Compare {
    bool operator()(Node* lhs, Node* rhs) const {
        return lhs->frequency > rhs->frequency;
    }
};

// Traversing the tree recursivly to generate code map.
void generateCodes(Node* root, std::map<char, std::string>& codes, std::string code) { // map to store code.
    if (root == nullptr)
        return;

    //checking if current node is a leaf node.
    if (root->left == nullptr && root->right == nullptr) {
        codes[root->character] = code;
    }

    generateCodes(root->left, codes, code + "0");
    generateCodes(root->right, codes, code + "1");
}

// Building huffman tree using pq.
Node* buildHuffmanTree(const std::map<char, int>& frequencyMap) {
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq; // type node, contained in a vecot with a custom comparator ( declared above)

    // Storing each character-frequency pairs in a node.
    for (const auto& pair : frequencyMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Iterating through pq until one node left.
    while (pq.size() > 1) {
        //two lowest frequencies.
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        //creating parent node for the nodes.
        Node* parent = new Node('$', left->frequency + right->frequency); //parent node has a sum of children freq.
        parent->left = left;
        parent->right = right;

        //Parent merged with nodes.
        pq.push(parent);
    }
    //root of pq.
    return pq.top();
}

// Function to calculate the total bits and space percentage of compression
void calculateCompressionStats(const std::string& originalText, const std::string& compressedText, int& totalBits, double& spacePercentage) {
    totalBits = originalText.size() * 8;
    int compressedBits = compressedText.size();
    spacePercentage = (1 - static_cast<double>(compressedBits) / totalBits) * 100.0;
}


int main() {


    std::string numWords;
    std::cout << "(For File Reading Purposes) \n";
    std::cout << "Number of words? ";
    std::cin >> numWords;


    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream inputFile("huffmancoding_" + numWords + "_input.txt");
    /*std::ifstream inputFile("huffman_input.txt");*/
    if (!inputFile) {
        std::cerr << "Failed to open the input file." << std::endl;
        return 1;
    }

    int numUniqueChars;
    inputFile >> numUniqueChars;

    // Read the list of unique characters
    std::vector<char> uniqueChars(numUniqueChars);
    for (int i = 0; i < numUniqueChars; ++i) {
        inputFile >> uniqueChars[i];
    }

    // Read the list of words
    std::string word;
    std::string compressedText;
    while (inputFile >> word) {
        compressedText += word;
    }

    inputFile.close();

    // Count the frequency of each character in the words
    std::map<char, int> frequencyMap;
    for (char c : compressedText) {
        ++frequencyMap[c];
    }

    // Build the Huffman tree
    Node* root = buildHuffmanTree(frequencyMap);

    // Generate codes for each character
    std::map<char, std::string> codes; //code map
    generateCodes(root, codes, "");

    // Calculate the total bits and space percentage of compression
    int totalBits;
    double spacePercentage;

    calculateCompressionStats(compressedText, compressedText, totalBits, spacePercentage);

    // Output to a text file
    std::ofstream outputFile("huffmancoding_" + numWords + "_output.txt");
    if (!outputFile) {
        std::cerr << "Failed to open the output file." << std::endl;
        return 1;
    }

    // The number of unique characters
    outputFile << numUniqueChars << std::endl;

    // Characters, frequencies, codes, and number of character bits
    for (const auto& pair : frequencyMap) {
        char character = pair.first;
        int frequency = pair.second;
        std::string code = codes[character];
        int numBits = code.size();

        outputFile << character << " " << frequency << " " << code << " " << numBits << std::endl;
    }

    // Number of total bits
    outputFile << "\n" << compressedText.size() << " Of " << totalBits << std::endl;

    // Total space percentage of compression
    outputFile << "\n" << spacePercentage << "%" << std::endl;



    // Time taken
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    outputFile << "\n" << std::fixed << std::setprecision(5) << duration.count() << "s" << std::endl; // TIme taken set to 5 decimal places.

    outputFile.close();

    std::cout << "Compression complete!" << std::endl;

    return 0;
}
