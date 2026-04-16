#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "dict.hpp"
#include <string>

using Catch::Matchers::UnorderedEquals;

TEST_CASE("Test Dict")
{
    // Implement your own tests. You can use below as a reference.
    // When implementing tests, think of the edge cases where you
    // suspect the program is likely to fail.
    // For example inserting the 'same' person twice or removing an
    // non existent person from the dictionary.

    Dict<std::string, int> name_to_age; //ordbog oprettes her

    SECTION("Initial state") {
        // En nydannet ordbog skal være tom
        REQUIRE(name_to_age.len() == 0);
        REQUIRE_FALSE(name_to_age.has("Jane"));
    }

    SECTION("Testing set and overwrite logic") {
        // Tilføjer en person
        name_to_age.set("Jane", 20);
        REQUIRE(name_to_age.len() == 1);
        REQUIRE(name_to_age.has("Jane"));

        // Tjekker om værdien kan hentes korrekt
        auto result = name_to_age.get("Jane");
        REQUIRE(result.has_value()); // get() returnerer en optional
        REQUIRE(result.value() == 20);

        //Overskriv eksisterende nøgle
        name_to_age.set("Jane", 21); 
        REQUIRE(name_to_age.len() == 1); // Længden må IKKE stige ved overskrivning
        REQUIRE(name_to_age.get("Jane").value() == 21); // Opdaterer værdi
    }

SECTION("Testing get with non-existent keys") {
        // EDGE CASE: Hvad sker der hvis vi søger efter noget der ikke findes?
        // Specifikationen siger det skal returnere std::nullopt
        auto result = name_to_age.get("InvisibleMan");
        REQUIRE_FALSE(result.has_value()); 
    }

    SECTION("Testing del (delete) logic") {
        name_to_age.set("Tarzan", 25);
        REQUIRE(name_to_age.len() == 1);
        
        // Vi sletter personen
        name_to_age.del("Tarzan");
        REQUIRE(name_to_age.len() == 0);
        REQUIRE_FALSE(name_to_age.has("Tarzan"));

        // EDGE CASE: Slet noget der allerede er slettet eller ikke findes
        // Specifikationen siger: "nothing happens" (ingen crash)
        name_to_age.del("NonExistent");
        REQUIRE(name_to_age.len() == 0);
    }

    SECTION("Testing bulk retrieval of keys and values") {
        name_to_age.set("A", 10);
        name_to_age.set("B", 20);
        
        // Tjekker om keys() returnerer alle de rigtige nøgler
        REQUIRE_THAT(name_to_age.keys(), UnorderedEquals(std::vector<std::string>{"A", "B"}));
        
        // Tjekker om values() returnerer alle de rigtige værdier
        REQUIRE_THAT(name_to_age.values(), UnorderedEquals(std::vector<int>{10, 20}));
    }
}
