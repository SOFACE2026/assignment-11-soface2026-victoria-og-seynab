#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "dict.hpp"
#include <string>

using Catch::Matchers::UnorderedEquals;

TEST_CASE("Test Dict")
{
    
    Dict<std::string, int> scores;

    // Test for an empty dictionary
    REQUIRE(scores.len() == 0); // The length of the dictionary should be 0 since it is empty
    REQUIRE(scores.has("Player1") == false); // The dictionary should not have "Player1" since it is empty

    // Test for adding key-value pairs to the dictionary
    scores.set("Player1", 150);
    REQUIRE(scores.len() == 1); // The length of the dictionary should be 1 since we only added one key value peir
    REQUIRE(scores.has("Player1") == true); // The dictornary should have Player1 since we added it

    scores.set("Player2", 200);   
    REQUIRE(scores.len() == 2); 
    REQUIRE(scores.has("Player2") == true);

    // Test retrieving existing values from the dictionary (non existing keys)
    std::optional<int> score_player1 = scores.get("Player1");
    REQUIRE(score_player1.has_value() == true); // score_player1 should have a value
    REQUIRE(score_player1.value() == 150); // The value of score_player1 should be 150

    // Retrieving non existing values from the dictionary (non existing keys)
    std::optional<int> score_player3 = scores.get("Player3");
    REQUIRE(score_player3.has_value() == false); // score_player3 should not have a value since "Player3" is not in the dictionary

    // Updating an existing key in the dictionary
    scores.set("Player1", 650); // We overrite the value of "Player1" to 650
    REQUIRE(scores.len() == 2); // The length of the dictionary should still be 2 since we only updated an existing key value pair
    REQUIRE(scores.get("Player1").value() == 650); // The value of "Player1" should now be 650 since we updated it

    // Retrieving values and keys
    REQUIRE_THAT(scores.keys(), UnorderedEquals(std::vector<std::string>{"Player1", "Player2"}));
    REQUIRE_THAT(scores.values(), UnorderedEquals(std::vector<int>{650, 200}));

    // Deleting an existing key from the dictionary
    scores.del("Player2");
    REQUIRE(scores.len() == 1); // The length of the dictionary should now be 1 since we deleted one key value pair
    REQUIRE(scores.has("Player2") == false); // The dictionary should not have "Player2" since it is deleted

    // Deleting an non existing key from the dictionary
    scores.del("Player3"); // We try to delete "Player3" which is not in the dictionary, nothing should happen
    REQUIRE(scores.len() == 1); // The length of the dictionary should still be 1 since we tried to delete a non existing key value pair
}
