#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;

class item {
    
public:
    item(string nameIn, int valueIn) {
        name = nameIn;
        value = valueIn;
    }
    string name;
    int value;
};

class command {
public:
    vector<string> variations;
    command(vector<string> in) {
        variations = in;
    }
};


vector<item> playerInventory;
vector<item> merchantInventory;

void printItemVector(vector<item> input) {
    for (int i = 0; i < input.size(); i++) {
        std::cout << input[i].name << "\t$" << input[i].value << std::endl;
    }
}


int main()
{
    playerInventory.push_back(item("sword",100));
    playerInventory.push_back(item("sheild", 50));
    playerInventory.push_back(item("potion", 15));

    merchantInventory.push_back(item("gun", 150));
    merchantInventory.push_back(item("ammo x10", 15));
    merchantInventory.push_back(item("bandage", 30));

    std::cout << "\nPlayer\n";
    printItemVector(playerInventory);
    std::cout << "\nmerchant\n";
    printItemVector(merchantInventory);


    while (true) {

    }


}
