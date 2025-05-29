#include "Player.hpp"

/**
 * @brief Constructs a Player with a given name and inventory.
 */
Player::Player(const std::string& name, const Inventory& inventory)
    : name_(name), inventory_(inventory) {}

/**
 * @brief Copy Constructor - Performs deep copy.
 */
Player::Player(const Player& rhs)
    : name_(rhs.name_), inventory_(rhs.inventory_) {}

/**
 * @brief Move Constructor - Transfers ownership.
 */
Player::Player(Player&& rhs)
    : name_(std::move(rhs.name_)), inventory_(std::move(rhs.inventory_)) {}

/**
 * @brief Copy Assignment Operator - Ensures deep copy.
 */
Player& Player::operator=(const Player& rhs) {
    if (this != &rhs) {
        name_ = rhs.name_;
        inventory_ = rhs.inventory_;
    }
    return *this;
}

/**
 * @brief Move Assignment Operator - Transfers ownership.
 */
Player& Player::operator=(Player&& rhs) {
    if (this != &rhs) {
        name_ = std::move(rhs.name_);
        inventory_ = std::move(rhs.inventory_);
    }
    return *this;
}

/**
 * @brief Retrieves the player's name.
 */
std::string Player::getName() const {
    return name_;
}

/**
 * @brief Retrieves a reference to the player's inventory.
 */
Inventory& Player::getInventoryRef() {
    return inventory_;
}
