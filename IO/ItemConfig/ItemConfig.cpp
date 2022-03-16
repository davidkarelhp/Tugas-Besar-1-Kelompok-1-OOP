#include "ItemConfig.hpp"
#include <string>
#include <fstream>
#include <vector>
ItemConfig::ItemConfig(string path)
{
  this->path = path;
}

Item *ItemConfig::getItemList()
{
  ifstream dataStream;
  vector<Item> itemList;
  dataStream.exceptions(ifstream::badbit);

  try
  {
    string item;

    dataStream.open(path);
    while (getline(dataStream, item))
    {
      itemList.push_back(parseItem(item));
    }
  }
  catch (const ifstream::failure &e)
  {
    cout << "Gagal membuka file konfigurasi item" << endl;
  }

  return itemList.data();
}
