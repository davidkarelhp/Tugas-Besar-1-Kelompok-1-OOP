#include "Item.hpp"
#include "Tool.hpp"
#include "NonTool.hpp"
#include <iostream>

int main(){
    //Driver Tool
    Tool (*t1) = new Tool(1, "test_tools", "item_type", 6);
    int durability = (*t1).getDurability();
    cout << "this is durability: " << durability << endl;
    (*t1).setDurability(30);
    durability = (*t1).getDurability();
    cout << "this is new durability: " << durability << endl;
    (*t1).useTool();
    durability = (*t1).getDurability();
    cout << "this is the item's durability after being used: " << durability << endl;
    cout << endl;

    //Memanggil fungsi dari Parent
    int item_id = (*t1).getId();
    cout << "this is the tools id: " << item_id << endl;
    string name_item = (*t1).getName();
    cout << "this is the tool name: " << name_item << endl;
    string item_type = (*t1).getType();
    cout << "this is the tool type: " << item_type << endl;


    //Membuat item baru menggunakan create Item dari sebuah Tool
    Item *t2;
    t2 = (*t1).createItem("Botol", 3);
    name_item = (*t2).getName();
    int quantity = t2->getQuantity();
    cout << "this is the item2 name: " << name_item << endl;
    cout << "this is the item2 quantity: " << quantity << endl;
    cout << endl;

    //Driver NonTool
    NonTool (*nt1) = new NonTool(3, "test_non_tools", "item_type2", 6);
    item_id = (*nt1).getId();
    cout << "this is the non-tools id: " << item_id << endl;
    name_item = (*nt1).getName();
    cout << "this is the non-tool name: " << name_item << endl;
    item_type = (*nt1).getType();
    cout << "this is the non-tool type: " << item_type << endl;
    if(nt1->keyExists("Botol")){
        cout << "Key Exists" << endl;
    }
}
