#include "InputRecipe.hpp"

void InputRecipe::readFile(string filePath) {
  // do something
  ifstream itemRecipeFile(filePath);
  int row, col, i,lineIdx, quantity;
  string word, result;
  string * recipeArr;

  lineIdx = 0;
  // cout << filePath << '\n';
  i = 0;
  for (string line; getline(itemRecipeFile, line);) {
    // cout << "line: " << line << '\n';
    stringstream ss(line);
    if (lineIdx == 0) {
        ss >> word;
        row = stoi(word);
        ss >> word;
        col = stoi(word);
        // cout << row << " " << col << '\n';
        recipeArr = new string[row * col];
    } else if (lineIdx <= row) {
        for (int j = 0; j < col; j++) {
            ss >> word;
            recipeArr[i] = word;
            i++;
        }
    } else {
        ss >> word;
        result = word;
        ss >> word;
        quantity = stoi(word);
    }
    lineIdx++;
  }
  // for (int i = 0; i < row * col; i++) {
  //   cout << recipeArr[i] << " ";
  // }
  // cout << '\n';
  Crafting::trie.buildRecipe(row, col, recipeArr, result, quantity);
  delete[] recipeArr;
}