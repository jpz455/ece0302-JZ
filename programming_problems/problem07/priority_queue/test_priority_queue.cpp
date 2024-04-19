#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "list.hpp"
#include "sorted_list.hpp"
#include "priority_queue.hpp"

TEST_CASE("Testing Priority Queue Empty", "[priority queue]") {
  typedef SortedList<int, List<int>> SortedListType;
  typedef PriorityQueue<int, SortedListType>  PriorityQueueType;

  PriorityQueueType pq;

  REQUIRE(pq.isEmpty());
  pq.add(1);
  REQUIRE_FALSE(pq.isEmpty());
  pq.remove();
  REQUIRE(pq.isEmpty());
  REQUIRE_THROWS_AS(pq.remove(), std::range_error);

}
    
TEST_CASE("Testing Priority Queue Add", "[priority queue]") {
  typedef SortedList<int, List<int>> SortedListType;
  typedef PriorityQueue<int, SortedListType>  PriorityQueueType;

  PriorityQueueType pq;
    
  pq.add(1);
  pq.add(10);
  pq.add(5);
  REQUIRE(pq.peek() == 10);
  PriorityQueueType emptyPq;
  REQUIRE_THROWS_AS(emptyPq.peek(), std::range_error);

}

TEST_CASE("Testing Priority Queue Remove", "[priority queue]") {
  typedef SortedList<int, List<int>> SortedListType;
  typedef PriorityQueue<int, SortedListType>  PriorityQueueType;

  PriorityQueueType pq;
      
  pq.add(1);
  pq.add(10);
  pq.add(5);
  pq.remove();
  REQUIRE(pq.peek() == 5);
  pq.remove();
  REQUIRE(pq.peek() == 1);
  pq.remove();
  REQUIRE_THROWS_AS(pq.peek(), std::range_error);

}

TEST_CASE("Testing Priority Queue Peek", "[priority queue]") {
  typedef SortedList<int, List<int>> SortedListType;
  typedef PriorityQueue<int, SortedListType>  PriorityQueueType;

  PriorityQueueType pq;
 
  pq.add(1);
  pq.add(10);
  pq.add(5);
  REQUIRE(pq.peek() == 10);
  
    
}

TEST_CASE("Final review","[final review]"){
  typedef SortedList<int,List<int>> SortedListType;
  typedef PriorityQueue<int,SortedListType> PriorityQueueType;

  PriorityQueueType pq;

  pq.add(700);
  pq.add(450);
  pq.add(100);
  pq.add(23);

  REQUIRE(pq.peek() == 700);

  pq.remove();

  REQUIRE(pq.peek() == 450);

  pq.add(15);

  REQUIRE(pq.peek() == 450);

  pq.add(80);

  REQUIRE(pq.peek() == 450);

  pq.add(1600);

  REQUIRE(pq.peek() == 1600);
}
