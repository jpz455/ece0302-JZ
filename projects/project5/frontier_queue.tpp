#include "frontier_queue.hpp"

// TODO implement the member functions here

template <typename T>
State<T> frontier_queue<T>::pop() {

  //first check if queue is empty...cannot remove from empty queue
  if(empty()) 
  throw std::logic_error("cannot remove from an empty queue");

  //next check if the queue has only one item...that will be the item popped
  if(queue.size()==1){
    State<T> popThis = queue[0];
    queue.pop_back();
    return popThis;
  }
  // Store the root element to be popped
    State<T> popThis = queue[0];

    // Replace the root element with the last element
    queue[0] = queue.back();
    queue.pop_back();

    // Restore the heap property by heapifying down from the root
    std::size_t current_index = 0;
    while (true) {
        std::size_t left_child = 2 * current_index + 1;
        std::size_t right_child = 2 * current_index + 2;
        std::size_t smallest = current_index;

        // Find the smallest element among the root, left child, and right child
        if (left_child < queue.size() && queue[left_child].getFCost() < queue[smallest].getFCost()) {
            smallest = left_child;
        }
        if (right_child < queue.size() && queue[right_child].getFCost() < queue[smallest].getFCost()) {
            smallest = right_child;
        }

        if (smallest != current_index) {
            std::swap(queue[current_index], queue[smallest]); // Swap the root with the smallest child
            current_index = smallest; // Move to the smallest child
        } else {
            break; // If the root is smaller than or equal to the smallest child, heap property is restored
        }
    }

    return popThis; // Return the popped element
}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur) {

  State<T> temp(p,cost, heur); //push a state with value p, cost and heur

  //if queue is empty just add new item to it
  if(empty()){
    queue.push_back(temp);
    return;
  }

  //if queue is not empty we add it onto the end
  queue.push_back(temp);
  int tempSize = queue.size() - 1;
  int tempParent = (tempSize - 1) /2;

  //need to make sure it stays in minheap format (swap spots if less than parent)
  while(tempParent!=0 && queue[tempParent].getFCost() > queue[tempSize].getFCost()){
  
      std::swap(queue[tempParent], queue[tempSize]); // Swap the elements if criterion met
      tempSize = tempParent; //update the position
      tempParent = (tempParent-1)/2; //this while loop will continue for as long as the the queue is not in minheap format
    }
  
}

template <typename T>
bool frontier_queue<T>::empty() {

   return queue.empty();
}

template <typename T> 
bool frontier_queue<T>::contains(const T &p) {

  for(int i=0; i < queue.size(); i++){
    if(queue[i].getValue() == p) 
    return true;
  }

  return false;

}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost) {

  //traverse the entire queue
  for (int i = 0; i < queue.size(); ++i) {
        // Check if the value matches and the current path cost is greater than the provided cost
        if (queue[i].getValue() == p && queue[i].getPathCost() > cost) {
            // Update the path cost
            queue[i].updatePathCost(cost);
            // Exit the function after updating the first occurrence
            return;
        }
    }
}


