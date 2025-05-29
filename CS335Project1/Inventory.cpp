#include "Inventory.hpp"
#include <stdexcept>

/**
 * @brief Constructor with optional parameters for initialization.
 */
Inventory::Inventory(
    const std::vector<std::vector<Item>>& items,
    Item* equipped
) : inventory_grid_(items), equipped_(nullptr), weight_(0), item_count_(0) {
    // Initialize weight_ and item_count_ (excluding NONE items)
    for (const auto& row : inventory_grid_) {
        for (const auto& item : row) {
            if (item.type_ != NONE) {
                weight_ += item.weight_;
                item_count_++;
            }
        }
    }
    // Assign equipped_ only if a valid pointer is given
    if (equipped) {
        equipped_ = new Item(*equipped);
    }
}

/**
 * @brief Copy Constructor - Performs deep copy.
 */
Inventory::Inventory(const Inventory& rhs)
    : inventory_grid_(rhs.inventory_grid_), weight_(rhs.weight_), item_count_(rhs.item_count_) {
    if (rhs.equipped_) {
        equipped_ = new Item(*rhs.equipped_);
    }
    else {
        equipped_ = nullptr;
    }
}

/**
 * @brief Move Constructor - Transfers ownership.
 */
Inventory::Inventory(Inventory&& rhs)
    : inventory_grid_(std::move(rhs.inventory_grid_)),
    equipped_(rhs.equipped_),
    weight_(rhs.weight_),
    item_count_(rhs.item_count_) {
    rhs.equipped_ = nullptr;
    rhs.weight_ = 0;
    rhs.item_count_ = 0;
}

/**
 * @brief Copy Assignment Operator - Ensures deep copy.
 */
Inventory& Inventory::operator=(const Inventory& rhs) {
    if (this != &rhs) {
        inventory_grid_ = rhs.inventory_grid_;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;

        // Clean up old equipped item
        delete equipped_;
        equipped_ = rhs.equipped_ ? new Item(*rhs.equipped_) : nullptr;
    }
    return *this;
}

/**
 * @brief Move Assignment Operator - Transfers ownership.
 */
Inventory& Inventory::operator=(Inventory&& rhs) {
    if (this != &rhs) {
        inventory_grid_ = std::move(rhs.inventory_grid_);
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;

        delete equipped_;
        equipped_ = rhs.equipped_;

        rhs.equipped_ = nullptr;
        rhs.weight_ = 0;
        rhs.item_count_ = 0;
    }
    return *this;
}

/**
 * @brief Destructor - Cleans up allocated memory.
 */
Inventory::~Inventory() {
    delete equipped_;
}

/**
 * @brief Retrieves the equipped item.
 */
Item* Inventory::getEquipped() const {
    return equipped_;
}

/**
 * @brief Equips a new item.
 */
void Inventory::equip(Item* itemToEquip) {
    equipped_ = itemToEquip;
}

/**
 * @brief Discards the currently equipped item.
 */
void Inventory::discardEquipped() {
    delete equipped_;
    equipped_ = nullptr;
}

/**
 * @brief Retrieves the inventory items.
 */
std::vector<std::vector<Item>> Inventory::getItems() const {
    return inventory_grid_;
}

/**
 * @brief Retrieves the total weight of items.
 */
float Inventory::getWeight() const {
    return weight_;
}

/**
 * @brief Retrieves the number of stored items.
 */
size_t Inventory::getCount() const {
    return item_count_;
}

/**
 * @brief Retrieves an item at a specific position.
 */
Item Inventory::at(const size_t& row, const size_t& col) const {
    if (row >= inventory_grid_.size() || col >= inventory_grid_[row].size()) {
        throw std::out_of_range("Invalid row or column index");
    }
    return inventory_grid_[row][col];
}

/**
 * @brief Stores an item in the inventory.
 */
bool Inventory::store(const size_t& row, const size_t& col, const Item& pickup) {
    if (row >= inventory_grid_.size() || col >= inventory_grid_[row].size()) {
        throw std::out_of_range("Row or column out of bounds");
    }
    if (inventory_grid_[row][col].type_ != NONE) {
        return false;  // The cell is already occupied
    }

    inventory_grid_[row][col] = pickup;  // Store the item
    item_count_++;
    weight_ += pickup.weight_;  // Update total weight

    // ✅ Debugging: Print confirmation
    std::cout << "✅ Item stored at [" << row << "," << col << "]: "
        << pickup.name_ << " (Weight: " << pickup.weight_ << ")\n";

    return true;
}
