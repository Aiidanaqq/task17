#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string compress(const string& inputText) {
    stringstream compressedStream;
    char currentChar = inputText[0];
    int count = 1;

    for (size_t i = 1; i < inputText.size(); ++i) {
        if (inputText[i] == currentChar) {
            count++;
        } else {
            compressedStream << count << currentChar;
            currentChar = inputText[i];
            count = 1;
        }
    }
    compressedStream << count << currentChar;

    return compressedStream.str();
}

string decompress(const string& compressedText) {
    stringstream decompressedStream;
    for (size_t i = 0; i < compressedText.size(); i += 2) {
        int count = compressedText[i] - '0';
        char ch = compressedText[i + 1];
        decompressedStream << string(count, ch);
    }
    return decompressedStream.str();
}

int main() {
    ifstream inputFile("input.txt");
    ofstream compressedFile("compressed.txt");
    ofstream decompressedFile("decompressed.txt");

    if (!inputFile || !compressedFile || !decompressedFile) {
        cerr << "Error: Unable to open files\n";
        return 1;
    }

    stringstream buffer;
    buffer << inputFile.rdbuf();
    string inputText = buffer.str();
    inputFile.close();

    string compressedText = compress(inputText);
    compressedFile << compressedText;
    compressedFile.close();

    string decompressedText = decompress(compressedText);
    decompressedFile << decompressedText;
    decompressedFile.close();

    cout << "Compression and decompression complete.\n";

    return 0;
}

