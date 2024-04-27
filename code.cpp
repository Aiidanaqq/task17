#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <sstream>

using namespace std;

struct HuffmanNode {
    char data;
    unsigned freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, unsigned freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
    ~HuffmanNode() {
        delete left;
        delete right;
    }
};

struct CompareNodes {
    bool operator()(HuffmanNode* left, HuffmanNode* right) const {
        return left->freq > right->freq;
    }
};

HuffmanNode* buildHuffmanTree(const unordered_map<char, unsigned>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;

    for (const auto& pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

void generateHuffmanCodes(HuffmanNode* root, const string& code, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    if (!root->left && !root->right) {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

void compress(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open input file\n";
        return;
    }
    stringstream buffer;
    buffer << inputFile.rdbuf();
    string inputText = buffer.str();
    inputFile.close();

    unordered_map<char, unsigned> freqMap;
    for (char ch : inputText) {
        freqMap[ch]++;
    }

    HuffmanNode* root = buildHuffmanTree(freqMap);

    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    stringstream compressedStream;
    for (char ch : inputText) {
        compressedStream << huffmanCodes[ch];
    }
    string compressedData = compressedStream.str();

    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open output file\n";
        delete root;
        return;
    }
    outputFile << compressedData;
    outputFile.close();

    delete root;
}

void decompress(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open input file\n";
        return;
    }
    stringstream buffer;
    buffer << inputFile.rdbuf();
    string compressedData = buffer.str();
    inputFile.close();

    HuffmanNode* root = new HuffmanNode('\0', 0);
    HuffmanNode* current = root;
    for (char bit : compressedData) {
        if (bit == '0') {
            if (!current->left) {
                current->left = new HuffmanNode('\0', 0);
            }
            current = current->left;
        } else if (bit == '1') {
            if (!current->right) {
                current->right = new HuffmanNode('\0', 0);
            }
            current = current->right;
        }
        if (!current->left && !current->right) {
            current->data = '\0';
            current = root;
        }
    }

    stringstream decompressedStream;
    current = root;
    for (char bit : compressedData) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }
        if (!current->left && !current->right) {
            decompressedStream << current->data;
            current = root;
        }
    }
    string decompressedText = decompressedStream.str();

    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open output file\n";
        delete root;
        return;
    }
    outputFile << decompressedText;
    outputFile.close();

    delete root;
}

int main() {
    string inputFilename = "input.txt";
    string compressedFilename = "compressed.txt";
    string decompressedFilename = "decompressed.txt";

    compress(inputFilename, compressedFilename);
    cout << "Compression complete.\n";

    decompress(compressedFilename, decompressedFilename);
    cout << "Decompression complete.\n";

    return 0;
}
