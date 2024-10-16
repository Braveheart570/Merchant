#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;


class item {
public:
    string name;
    int value;
    item(string nameIn, int valueIn) {
        name = nameIn;
        value = valueIn;
    }
    
};

int playerGold = 50;
int merchantGold = 50;
vector<item> playerInventory;
vector<item> merchantInventory;
string userIn;

void printItemVector(vector<item> input) {
    int space = 12;
    for (int i = 0; i < input.size(); i++) {
        std::cout << input[i].name << string(space-input[i].name.length(), ' ') << input[i].value << "\n";
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
    

    std::cout << "Welcome to the shop!\n";
    
    while (true) {
        std::cout << "\nwhat would you like to do?\n";
        std::cin >> userIn;
        if (userIn == "exit") {
            break;
        }
        else if (userIn == "sell") {
            std::cout << "\nPlayer Inventory\n";
            printItemVector(playerInventory);
            bool notEnoughGold = false;
            bool itemSold = false;
            do {
                std::cout << "\nThe Merchant has " << merchantGold << " Gold.\nWhat do you want to sell?\n";
                std::cin >> userIn;

                // manual exit
                if (userIn == "exit") {
                    notEnoughGold = true;
                    break;
                }

                // look for item
                for (int c = 0; c < playerInventory.size(); c++) {

                    
                    if (userIn == playerInventory[c].name) {

                        if (merchantGold < playerInventory[c].value) {
                            notEnoughGold = true;
                            break;
                        }

                        std::cout << "\nYou sold the " << playerInventory[c].name << ".\n";
                        merchantInventory.push_back(playerInventory[c]);
                        playerInventory.erase(playerInventory.begin() + c);
                        itemSold = true;
                        break;
                    }

                }
                if (notEnoughGold) {
                    std::cout << "\nMerchant cannot aford this item.";
                }
                else if (!itemSold) {
                    std::cout << "\nItem does not exist in your inventory.";
                }
                
            } while (!itemSold);
            
            
        }
        else if (userIn == "buy") {

        }
    }


}
