#include "OutputFile.hpp"

void OutputFile::outputFile(string outputPath) {
    int **outputArr = Inventory::output();
    ofstream outputFile(outputPath);
    for (int i = 0; i < 27; i++) {
        outputFile << outputArr[i][0];
        outputFile << ':';
        outputFile << outputArr[i][1];
        outputFile << '\n';
    }

    for (int i = 0; i < 27; i++) {
        delete[] outputArr[i];
    }
    delete[] outputArr;
}