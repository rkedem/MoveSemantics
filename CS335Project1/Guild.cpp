#include "Guild.hpp"

/**
 * @brief Constructs a new Guild object. Initializes the enlisted_players vector.
 */
Guild::Guild() : enlisted_players{ std::vector<Player>() } {}

/**
 * @brief Searches for a player in the guild by name
 *
 * @param playerName A const reference to the player's name to search for
 * @return std::vector<Player>::iterator An iterator pointing to the found player, or enlisted_players.end() if not found
 */
std::vector<Player>::iterator Guild::findPlayer(const std::string& playerName) {
    return std::find_if(enlisted_players.begin(), enlisted_players.end(), [&playerName](const Player& p) {
        return p.getName() == playerName;
        });
}

/**
 * @brief Attempts to enlist a player into the guild
 *
 * @param player An l-value reference to a Player object whose contents will be moved into the guild
 * @return True if the player was successfully enlisted, false if a player with the same name already exists
 */
bool Guild::enlistPlayer(Player& player) {
    if (findPlayer(player.getName()) != enlisted_players.end()) { return false; }
    enlisted_players.push_back(std::move(player));
    return true;
}

/**
 * @brief Moves a player from this guild to another guild
 *
 * @param playerName A const reference to the name of the player to move
 * @param target An l-value reference to the destination Guild
 * @return True if the player was successfully moved, false if the player doesn't exist in this guild
 */
bool Guild::movePlayerTo(const std::string& playerName, Guild& target) {
    auto existingPlayerItr = target.findPlayer(playerName);
    if (existingPlayerItr != target.enlisted_players.end()) { return false; }

    auto movingPlayerItr = findPlayer(playerName);
    if (movingPlayerItr == enlisted_players.end()) { return false; }

    target.enlisted_players.push_back(std::move(*movingPlayerItr));
    enlisted_players.erase(movingPlayerItr);

    return true;
}

/**
 * @brief Copies a player from this guild to another guild
 *
 * @param playerName A const reference to the name of the player to copy
 * @param
 **/
