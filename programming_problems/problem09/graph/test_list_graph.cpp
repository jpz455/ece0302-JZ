#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "adjacency_list_graph.hpp"

TEST_CASE("Test Construction", "[construction]") {
  AdjacencyListGraph<int>  listGraph;
  REQUIRE(listGraph.getNumVertices() == 0);
}

TEST_CASE("Test Adding Edges", "[add]") {
    AdjacencyListGraph<int> listGraph;

    listGraph.add(1, 2);
    listGraph.add(2, 3);
    listGraph.add(3, 4);
    listGraph.add(4, 1);

    REQUIRE(listGraph.getNumVertices() == 4);
    REQUIRE(listGraph.getNumEdges() == 4);

    REQUIRE_FALSE(listGraph.add(1, 2));

    REQUIRE(listGraph.getNumVertices() == 4); 
    REQUIRE(listGraph.getNumEdges() == 4);    
}

TEST_CASE("Test Removing Edges", "[remove]") {
    AdjacencyListGraph<int> listGraph;

  
    listGraph.add(1, 2);
    listGraph.add(2, 3);
    listGraph.add(3, 4);
    listGraph.add(4, 1);

    listGraph.remove(1, 2);


    REQUIRE(listGraph.getNumVertices() == 4);
    REQUIRE(listGraph.getNumEdges() == 3);

    REQUIRE_FALSE(listGraph.remove(5, 6));
    REQUIRE(listGraph.getNumVertices() == 4); 
    REQUIRE(listGraph.getNumEdges() == 3);    
}