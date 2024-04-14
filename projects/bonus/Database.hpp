
#ifndef _DATABASE_H_
#define _DATABASE_H_
#include "list.hpp"
#include "binary_search_tree.hpp"
#include <vector>


template <typename T>
class Database
{
public:
  Database();

  // determine if the database is empty
  bool isEmpty();

  // return current number of entries
  std::size_t getNumberOfEntries();

  // insert entry 
  bool add(std::string key1, std::string key2, const T& item);

  // remove entry 
  bool remove(std::string key);

  // remove all entries
  void clear();

  // retrieve the value of the entry associated with the input key
  T getValue(std::string key);

  // return true if an entry exists associated with the input key
  bool contains(std::string key);

private:

  //initializing the two different binary trees, keys, creating a list of items, and a size variable
  BinarySearchTree<std::string,int> tree1, tree2; 
  std::vector<std::string> KEY1,KEY2;
  List<T> items;
  int dataSize;

};

#include "Database.tpp"
#endif // _DATABASE_H_
