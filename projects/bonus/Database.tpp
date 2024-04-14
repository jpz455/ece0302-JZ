#include "Database.hpp"

template <typename T>
Database<T>::Database() {
    dataSize = 0;
}

template <typename T>
bool Database<T>::isEmpty() {
    return dataSize == 0;
}

template <typename T>
std::size_t Database<T>::getNumberOfEntries() {
    return dataSize;
}

template <typename T>
bool Database<T>::add(std::string key1, std::string key2, const T& item) {

   
    if (contains(key1) || contains(key2)) {
        return false; // Entry already exists cannot add duplicates 
    }

    // Add keys to key vector
    KEY1.push_back(key1);
    KEY2.push_back(key2);

    // Add item to the overal items list at the correct index
    items.insert(dataSize,item);

    // Update size
    ++dataSize;

    return true;
}

template <typename T>
bool Database<T>::remove(std::string key) {
  
   if (isEmpty()) {
        return false; // Database is empty
    }

    bool removed = false; // Flag to track if an entry was removed

    // Iterate over both KEY1 and KEY2 simultaneously
    for (int i = 0; i < dataSize; ++i) {
        if (KEY1[i] == key || KEY2[i] == key) {
            // Found a match, remove corresponding elements
            KEY1.erase(KEY1.begin() + i);
            KEY2.erase(KEY2.begin() + i);
            items.remove(i);

            // Update data size
            --dataSize;

            // Set flag to true to indicate removal
            removed = true;

            // Break the loop after removing the first matching entry
            break;
        }
    }

    return removed;
    
}

template <typename T>
void Database<T>::clear() {
    KEY1.clear();
    KEY2.clear();
    items.clear();
    dataSize = 0;
}

template <typename T>
T Database<T>::getValue(std::string key) {
   for (int i = 0; i < dataSize; ++i) {
        if (KEY1[i] == key || KEY2[i] == key) {
            // Found a match, return the item associated with the entry
            return items.getEntry(i);
        }
    }
    // If no matching entry was found, return a default-constructed item
    return T();
}

template <typename T>
bool Database<T>::contains(std::string key) {
      for (int i = 0; i < dataSize; ++i) {
        if (KEY1[i] == key || KEY2[i] == key) {
            return true; // Found a match, key exists in the database
        }
    }
    // Key not found in any entry
    return false;
}