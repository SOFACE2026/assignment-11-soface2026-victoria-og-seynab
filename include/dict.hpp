#pragma once
#include <algorithm>
#include <vector>
#include <tuple>
#include <iterator>
#include <optional>
#include <iostream>

/**
 * @brief Container used to store assoicate keys with values.
 * values can later be retrived using the corresponding key.
 * 
 * @tparam K type of the keys stored in the dictionary.
 * @tparam V type of the values assoicated with each key.
 */
template <class K, class V>
class Dict
{

private:
    // Vi bruger en vector af pairs til at gemme vores data.
    // Pair.first er nøglen (K), Pair.second er værdien (V).
    std::vector<std::pair<K, V>> items;

public:
    /**
     * @brief Associates the key with the specified value.
     * If the key is already in the dictionary its value is overwritten.
     * 
     * @param key key associated with the provided key.
     * @param val value assoicated with the provided key.
     * @pre none.
     * @post Hvis nøglen findes i forvejen, overskrives den gamle værdi, hvis ny nøgle, tilføjes et nyt par, og len() stiger med 1.
     */
    
    void set(K key, V val)
    {
        for (auto& item : items) {
            if (item.first == key) {
                std::cout << "[COVERAGE] set: opdaterer eksisterende" << std::endl; 
                item.second = val; // Overskriv eksisterende værdi
                return;
            }
        }
        std::cout << "[COVERAGE] set: tilføjer ny" << std::endl;
        items.push_back({key, val}); // Tilføj ny hvis ikke fundet
    }

    /**
     * @brief Determines if the key is defined in the dictionary.
     * 
     * @param key key for which to look for.
     * @return true if the key is defined in the dictionary.
     * @return false otherwise.
     * @pre none
     * @post Returnerer sandt hvis nøglen eksisterer i items. 
     */

    bool has(K key) const
    {
        for (const auto& item : items) {
            if (item.first == key) return true;
        }
        return false;
    }

    /**
     * @brief Returns the number of items in the dictionary.
     * 
     * @return the number of items in the dictionary.
     * @pre none
     * @post Returnerer det aktuelle antal unikke nøgle-værdi par.
     */

    size_t len() const
    {
        return items.size();
    }

    /**
     * @brief Get the value associated with the specified key.
     * If no value is found std::nullopt is returned.
     * 
     * @param key key for which to locate value.
     * @return value associated with key.
     * @pre none
     * @post Hvis nøglen findes, returneres værdien i std::optional. Hvis ikke, returneres std::nullopt.
     */

    std::optional<V> get(K key) const
    {
        for (const auto& item : items) {
            if (item.first == key) {
                std::cout << "[COVERAGE] get: fandt nøgle" << std::endl;
                return item.second;
            }
        }
        std::cout << "[COVERAGE] get: fandt intet" << std::endl;
        return std::nullopt;
    }

    /**
     * @brief Delete the specified key and its associated value
     * from the dictionary.
     * If the key is not present in the dictionary, nothing happens.
     * 
     * @param key A key currently present in the dictionary
     * which will be deleted.
     * @pre none.
     * @post Hvis nøglen fandtes, fjernes den fra ordbogen og len() falder med 1. Hvis nøglen ikke findes, ingenting sker.
     */
    void del(K key)
    {
        size_t start_size = items.size();
        items.erase(std::remove_if(items.begin(), items.end(),
            [&key](const std::pair<K, V>& item) {
                return item.first == key;
            }), items.end());

        if (items.size() < start_size) 
            std::cout << "[COVERAGE] del: slettede et element" << std::endl;
        else 
            std::cout << "[COVERAGE] del: intet at slette" << std::endl;
    }

    /**
     * @brief List all keys of the dictionary.
     * 
     * @return vector of keys.
     * @pre none.
     * @post Returnerer en vektor med alle gemte nøgler, hvor rækkefølgen ikke er garanteret.
     * 
     */
    std::vector<K> keys() const
    {
        std::vector<K> all_keys;
        for (const auto& item : items) {
            all_keys.push_back(item.first);
        }
        return all_keys;
    }

    /**
     * @brief List all values of the dictionary.
     * 
     * @return vector of values.
     * @pre none.
     * @post Returnerer en vektor med alle gemte værdier.
     */

    std::vector<V> values() const
    {
        std::vector<V> all_values;
        for (const auto& item : items) {
            all_values.push_back(item.second);
        }
        return all_values;
    }

};