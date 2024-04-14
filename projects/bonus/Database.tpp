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

    //increment size
    ++dataSize;

    return true;
}

template <typename T>
bool Database<T>::remove(std::string key) {
  
   if (isEmpty()) {
        return false; //cannot remove from an empty database
    }

    bool removed = false; //initialize boolean to indicate removal has not occured

    //traverse key 1 and key 2 to check if either have key wanting to be removed
    for (int i = 0; i < dataSize; ++i) {
        if (KEY1[i] == key || KEY2[i] == key) {
            //remove item if the key matches any value in KEY1 or KEY2
            KEY1.erase(KEY1.begin() + i);
            KEY2.erase(KEY2.begin() + i);
            items.remove(i);//remove index from list

            //decrement data length
            --dataSize;

            //indicate removal was successful
            removed = true;
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
    //traverse both keys
   for (int i = 0; i < dataSize; ++i) {
        //if parameter key is found in either key use member functino to return the entry
        if (KEY1[i] == key || KEY2[i] == key) {
            return items.getEntry(i);
        }
    }
   //no matches found will return a default empty value
    return T();
}

template <typename T>
bool Database<T>::contains(std::string key) {
    //search through both keys
      for (int i = 0; i < dataSize; ++i) {
        //will return if either key holds the parameter key value
        if (KEY1[i] == key || KEY2[i] == key) {
            return true; 
        }
    }
    //will return false otherwise
    return false;
}