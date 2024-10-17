#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;


class item {
public:
    string name;
    int value;
    int quantity;
    item(string nameIn, int valueIn) {
        name = nameIn;
        value = valueIn;
        quantity = 1;
    }

    item(string nameIn, int valueIn, int quantityIn) {
        name = nameIn;
        value = valueIn;
        quantity = quantityIn;
    }
    
};

int playerGold = 50;
int merchantGold = 200;
vector<item> playerInventory;
vector<item> merchantInventory;
string userIn;

void printInventory(vector<item> input);
int getItemIndex(string itemName, vector<item> input);


int main()
{
    


    playerInventory.push_back(item("sword",100));
    playerInventory.push_back(item("sheild", 50));
    playerInventory.push_back(item("potion", 15));

    merchantInventory.push_back(item("gun", 150));
    merchantInventory.push_back(item("ammo box", 15, 3));
    merchantInventory.push_back(item("bandage", 30));
    

    std::cout << "Welcome to the shop!\nType exit at any time to go back.\n";
    
    while (true) {
        std::cout << "\nwhat would you like to do? buy or sell?\n";
        std::cin >> userIn;
        if (userIn == "exit") {
            break;
        }
        else if (userIn == "sell") {
            std::cout << "\nPlayer Inventory\n";
            printInventory(playerInventory);

            // selling loop
            while (true) {
                std::cout << "\nThe Merchant has " << merchantGold << " Gold.\nWhat do you want to sell?\n";
                std::cin >> userIn;

                // manual exit
                if (userIn == "exit") {
                    break;
                }

                // check for valid item in invetory
                int itemIndex = getItemIndex(userIn, playerInventory);

                //invalid item
                if (itemIndex < 0) {
                    std::cout << "\nItem does not exist in your inventory.";
                }
                // not enough gold
                else if (merchantGold < playerInventory[itemIndex].value) {
                    std::cout << "\nMerchant cannot aford this item.";
                }
                // transaction
                else {
                    std::cout << "\nYou sold the " << playerInventory[itemIndex].name << ".\n";
                    merchantGold -= playerInventory[itemIndex].value;
                    playerGold += playerInventory[itemIndex].value;
                    merchantInventory.push_back(playerInventory[itemIndex]);
                    playerInventory.erase(playerInventory.begin() + itemIndex);
                    break;
                }
                
            }
            
            
        }
        else if (userIn == "buy") {
            std::cout << "\nMerchant Inventory\n";
            printInventory(merchantInventory);

            // buying loop
            while (true) {
                std::cout << "\nYou have " << playerGold << " Gold.\nWhat do you want to buy?\n";
                std::cin >> userIn;

                // manual exit
                if (userIn == "exit") {
                    break;
                }

                // check for valid item in invetory
                int itemIndex = getItemIndex(userIn, merchantInventory);

                //invalid item
                if (itemIndex < 0) {
                    std::cout << "\nItem does not exist in the merchant's inventory.";
                }
                // not enough gold
                else if (playerGold < merchantInventory[itemIndex].value) {
                    std::cout << "\you cannot aford this item.";
                }
                // transaction
                else {
                    std::cout << "\nYou bought the " << merchantInventory[itemIndex].name << ".\n";
                    playerGold -= merchantInventory[itemIndex].value;
                    merchantGold += merchantInventory[itemIndex].value;
                    playerInventory.push_back(merchantInventory[itemIndex]);
                    merchantInventory.erase(merchantInventory.begin() + itemIndex);
                    break;
                }

            }
        }
    }



}

void printInventory(vector<item> input) {
    int space = 12;

    std::cout << "\nItem        Value       Amount\n";
    std::cout << string(space * 3, '-') << "\n";
    for (int i = 0; i < input.size(); i++) {
        std::cout << input[i].name << string(space - input[i].name.length(), ' ') << input[i].value << string(space - std::to_string(input[i].value).length(), ' ') << input[i].quantity << "\n";
    }
}

int getItemIndex(string itemName, vector<item> input) {
    for (int i = 0; i < input.size(); i++) {
        if (input[i].name == itemName) {
            return i;
        }
    }
    return -1;
}