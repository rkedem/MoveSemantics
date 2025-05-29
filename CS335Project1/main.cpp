#include "Inventory.hpp"
#include "Player.hpp"
#include <iostream>

void printInventory(const Inventory& inv) {
    std::cout << "Inventory contains " << inv.getCount() << " items.\n";
    std::cout << "Total weight: " << inv.getWeight() << " lbs\n";

    if (inv.getEquipped()) {
        std::cout << "Equipped Item: " << inv.getEquipped()->name_
            << " (Weight: " << inv.getEquipped()->weight_ << ")\n";
    }
    else {
        std::cout << "No item equipped.\n";
    }

    std::cout << "Stored Items:\n";
    for (size_t row = 0; row < inv.getItems().size(); row++) {
        for (size_t col = 0; col < inv.getItems()[row].size(); col++) {
            const Item& item = inv.getItems()[row][col];

            // Debugging: Print item info
            std::cout << "🔎 Checking item at [" << row << "," << col << "] - ";
            std::cout << "Name: '" << item.name_ << "', Weight: " << item.weight_
                << ", Type: " << item.type_ << "\n";

            if (!item.name_.empty() && item.type_ != NONE) {
                std::cout << "  [" << row << "," << col << "]: "
                    << item.name_ << " (Weight: "
                    << item.weight_ << ")\n";
            }
        }
    }
    std::cout << "-------------------------\n";
}
int main() {
    std::cout << "===== MMORPG Inventory & Player Test =====\n\n";

    // Create some items
    Item sword("Sword", 5.0, WEAPON);
    Item shield("Shield", 8.0, ARMOR);
    Item ring("Magic Ring", 1.0, ACCESSORY);
    Item helmet("Helmet", 3.5, ARMOR);
    Item boots("Boots", 2.0, ARMOR);

    // Debugging: Confirm items are created
    std::cout << " Items:\n";
    std::cout << "Sword: " << sword.name_ << " (Weight: " << sword.weight_ << ")\n";
    std::cout << "Shield: " << shield.name_ << " (Weight: " << shield.weight_ << ")\n";
    std::cout << "Ring: " << ring.name_ << " (Weight: " << ring.weight_ << ")\n";
    std::cout << "Helmet: " << helmet.name_ << " (Weight: " << helmet.weight_ << ")\n";
    std::cout << "Boots: " << boots.name_ << " (Weight: " << boots.weight_ << ")\n";

    // Create an inventory and add items
    Inventory inv;
    inv.store(0, 0, sword);
    inv.store(1, 1, shield);
    inv.store(2, 2, ring);

    // Equip an item
    inv.equip(new Item(helmet)); // Helmet is now equipped

    // Print inventory details
    printInventory(inv);

    // Create a player with this inventory
    Player player("Rusha", inv);
    std::cout << "Player Name: " << player.getName() << "\n";

    // Access and modify inventory through player
    std::cout << "\nModifying inventory through player...\n";
    player.getInventoryRef().store(3, 3, boots);

    // Print inventory again
    printInventory(player.getInventoryRef());

    return 0;
}
