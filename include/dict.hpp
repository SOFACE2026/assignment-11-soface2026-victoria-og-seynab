#pragma once
#include <algorithm>
#include <vector>
#include <tuple>
#include <iterator>
#include <optional>

/**
 * @brief Container used to store assoicate keys with values.
 * values can later be retrieved using the corresponding key.
 * 
 * @tparam K type of the keys stored in the dictionary.
 * @tparam V type of the values assoicated with each key.
 */


template <class K, class V>
class Dict
{

private:
    std::vector<K> keys_;
    std::vector<V> values_;

public:
    /**
     * @brief Associates the key with the specified value.
     * If the key is already in the dictionary its value is overwritten.
     * 
     * @param key key associated with the provided key.
     * @param val value assoicated with the provided key.
     */
    void set(K key, V val)
    {
        // We are going through all elements in the keys_ vector to check if the provided key is present in the dictionary.
        for(size_t i = 0; i < keys_.size(); i++)
        {
            if(keys_[i] == key)
            {
                values_[i] = val; // If the key is found in the dictionary we overwrite its value with the provided value.
                return;
            }
        }
        // If the key is not found in the dictionary we add it to the end of the keys_ vector 
        // and add its value to the end of the values_ vector.
        keys_.push_back(key);
        values_.push_back(val);

    }

    /**
     * @brief Determines if the key is defined in the dictionary.
     * 
     * @param key key for which to look for.
     * @return true if the key is defined in the dictionary.
     * @return false otherwise.
     */
    bool has(K key) const
    {
        // We are going through all elemnts in the keys_ vector to check if the provided key is present in the dictionary.
        for(size_t i = 0; i < keys_.size(); i++)
        {
            if(keys_[i] == key)
            {
                return true; // If the key is found in the dictionary we return true.
            }
        }
        return false; // If the key is not found in the dictionary we return false.
    }

    /**
     * @brief Returns the number of items in the dictionary.
     * 
     * @return the number of items in the dictionary.
     */
    size_t len()
    {
        return keys_.size(); // The number of items in the dict is returned
    }

    /**
     * @brief Get the value associated with the specified key.
     * If no value is found std::nullopt is returned.
     * 
     * @param key key for which to locate value.
     * @return value associated with key.
     */
    std::optional<V> get(K key) const
    {
        for(size_t i = 0; i < keys_.size(); i++){
            if(keys_[i] == key)
            {
                return values_[i]; // If the key is found in the dictionary we return its value.
            }
        }
        return std::nullopt; // If the key is not found in the dictionary we return std::nullopt (nothing)
    }

    /**
     * @brief Delete the specified key and its associated value
     * from the dictionary.
     * If the key is not present in the dictionary, nothing happens.
     * 
     * @param key A key currently present in the dictionary
     * which will be deleted.
     */
    void del(K key)
    {
        for(size_t i = 0; i < keys_.size(); i++){
            if(keys_[i] == key){
                // Delete the key and its associated value from the dictionary by erasing them from the keys_ and values_ vectors.
                keys_.erase(keys_.begin() + i);
                values_.erase(values_.begin() + i);

                return; // After deleting the key and its associated value we return from the function.
            }
        }

        // If the key is not found in the dictionary we do nothing and return from the function.
    }

    /**
     * @brief List all keys of the dictionary.
     * 
     * @return vector of keys.
     */
    std::vector<K> keys()
    {
        return keys_; // Return the keys_ vector, containing all keys
    }

    /**
     * @brief List all values of the dictionary.
     * 
     * @return vector of values.
     */
    std::vector<V> values()
    {
        return values_; // Return the values_ vector, containing all values
    }
};