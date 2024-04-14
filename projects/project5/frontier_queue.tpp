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
  
  //otherwise store element that will be popped
    State<T> popThis = queue[0];

    //overwrite root element with last element of the queue
    queue[0] = queue.back();
    queue.pop_back();

    //now restore format by heapify down
    int idx = 0;
    while (true) {
        int leftC = 2 * idx + 1;
        int rightC = 2 * idx + 2;
        int small = idx;

        //finding the least value amoung root, right, and left children
        if (leftC < queue.size() && queue[leftC].getFCost() < queue[small].getFCost()) {
            small = leftC;
        }
        if (rightC < queue.size() && queue[rightC].getFCost() < queue[small].getFCost()) {
            small = rightC;
        }

        if (small != idx) {
            std::swap(queue[idx], queue[small]); //swapping if new index is smaller
            idx = small; //reassign index to smallest node
        } else {
            break; //will break once heapify format is reached
        }
    }
    return popThis; 
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
  int tempParent = (tempSize - 1) /2; //calculating index

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
        //update the cost of the path if p value is the same and the cost is greater
        if (queue[i].getValue() == p && queue[i].getPathCost() > cost) {
            queue[i].updatePathCost(cost);
            return;
        }
    }
}


