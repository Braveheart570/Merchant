#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;



class diologueSegment {

public:


};

class actor {
public:
    vector<item> inventory;
    string actorName;
    actor(string actorNameIn) {
        actorName = actorNameIn;
    };
    void printInv() {
        int space = 12;
        //header
        std::cout << "\nItem        Value       Amount\n";
        std::cout << string(space * 3, '-') << "\n";
        //items
        for (int i = 0; i < inventory.size(); i++) {

            std::cout << inventory[i].name << string(space - inventory[i].name.length(), ' ') << inventory[i].value << string(space - std::to_string(inventory[i].value).length(), ' ') << inventory[i].quantity << "\n";
        }
    }
};

class npc : actor {

};

class merchant : npc {

};

class player : actor {

};

class item {
public:
    string name;
    int value;
    int quantity;
    item(string nameIn, int valueIn, int quantityIn) {
        name = nameIn;
        value = valueIn;
        quantity = quantityIn;
    }
    
};



vector<item> playerInventory = {
    item("sword", 100, 1),
    item("sheild", 50, 1),
    item("potion", 15, 3),
    item("gun", 150, 0),
    item("ammo_box", 15, 0),
    item("bandage", 30, 0)
};
vector<item> merchantInventory = {
    item("sword", 100, 0),
    item("sheild", 50, 0),
    item("potion", 15, 0),
    item("gun", 150, 1),
    item("ammo_box", 15, 5),
    item("bandage", 30, 2)
};



int playerGold = 50;
int merchantGold = 180;
string userIn;




void printInventory(vector<item> input, bool showQuantityZero);
int getItemIndex(string itemName, vector<item> input);


int main()
{

    std::cout << "Welcome to the shop!\nType exit at any time to go back.\n";
    

    // Main Loop
    while (true) {
        std::cout << "\nWhat would you like to do? Exit, buy, sell, or view inventory with \"inv\"?\n";
        std::cin >> userIn;
        system("CLS");

        // exit condition for loop
        if (userIn == "exit") {
            break;
        }
        // view inventory
        else if(userIn == "inv") {
            printInventory(playerInventory, false);
            std::cout << "\nYou have " << playerGold << " Gold\n";
        }
        // sell items
        else if (userIn == "sell") {
            std::cout << "\nPlayer Inventory\n";
            printInventory(playerInventory, false);

            // selling loop
            while (true) {
                std::cout << "\nThe merchant has " << merchantGold << " Gold.\nWhat do you want to sell?\n";
                std::cin >> userIn;

                // manual exit
                if (userIn == "exit") {
                    break;
                }

                // check for valid item in invetory
                int itemIndex = getItemIndex(userIn, playerInventory);

                //invalid item or quantity 0
                if (itemIndex < 0 || playerInventory[itemIndex].quantity <= 0) {
                    std::cout << "\nYou don't have that item.";
                }
                // not enough gold
                else if (merchantGold < playerInventory[itemIndex].value) {
                    std::cout << "\nMerchant cannot aford this item.";
                }
                // transaction
                else {
                    system("CLS");
                    std::cout << "\nYou sold the " << playerInventory[itemIndex].name << ".\n";
                    merchantGold -= playerInventory[itemIndex].value;
                    playerGold += playerInventory[itemIndex].value;
                    playerInventory[itemIndex].quantity--;
                    merchantInventory[itemIndex].quantity++;
                    break;
                }
                
            }
            
            
        }
        //buy items
        else if (userIn == "buy") {
            std::cout << "\nMerchant Inventory\n";
            printInventory(merchantInventory,true);

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
                if (itemIndex < 0 ) {
                    std::cout << "\nThe merchant does not have that item.";
                }
                // sold out
                else if (merchantInventory[itemIndex].quantity <= 0) {
                    std::cout << "\nThat item is sold out";
                }
                // not enough gold
                else if (playerGold < merchantInventory[itemIndex].value) {
                    std::cout << "\You cannot aford this item.";
                }
                // transaction
                else {
                    system("CLS");
                    std::cout << "\nYou bought the " << merchantInventory[itemIndex].name << ".\n";
                    playerGold -= merchantInventory[itemIndex].value;
                    merchantGold += merchantInventory[itemIndex].value;
                    playerInventory[itemIndex].quantity++;
                    merchantInventory[itemIndex].quantity--;
                    break;
                }

            }
        }
    }

    return 0;

}
// an inventory vector with or without out of stock items.
void printInventory(vector<item> input, bool showQuantityZero) {
    int space = 12;
    string quantity = "";

    //header
    std::cout << "\nItem        Value       Amount\n";
    std::cout << string(space * 3, '-') << "\n";

    //items
    for (int i = 0; i < input.size(); i++) {

        //Handling quantity zero
        if (input[i].quantity < 1) {
            if (showQuantityZero == false) {
                continue;
            }
            quantity = "SOLD OUT";
        }
        else{
            quantity = std::to_string(input[i].quantity);
        }

        std::cout << input[i].name << string(space - input[i].name.length(), ' ') << input[i].value << string(space - std::to_string(input[i].value).length(), ' ') << quantity << "\n";
    }
}

// returns -1 if there is no index found
int getItemIndex(string itemName, vector<item> input) {
    for (int i = 0; i < input.size(); i++) {
        if (input[i].name == itemName) {
            return i;
        }
    }
    return -1;
}