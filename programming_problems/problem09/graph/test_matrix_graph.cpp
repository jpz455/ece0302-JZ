#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "adjacency_matrix_graph.hpp"

TEST_CASE("Test Construction", "[construction]") {
  AdjacencyMatrixGraph<int>  matrixGraph;
  REQUIRE(matrixGraph.getNumVertices() == 0);
}

TEST_CASE("adding and removing", "[AdjacencyMatrixGraph]") {
  AdjacencyMatrixGraph<int> listGraph;
  REQUIRE(listGraph.getNumVertices() == 0);
  listGraph.add(1,2);
  REQUIRE(listGraph.getNumVertices() == 2);
  REQUIRE(listGraph.getNumEdges() == 1);
  listGraph.add(1,3);
  REQUIRE(listGraph.getNumVertices() == 3);
  REQUIRE(listGraph.getNumEdges() == 2);
  listGraph.add(3,4);
  REQUIRE(listGraph.getNumVertices() == 4);
  REQUIRE(listGraph.getNumEdges() == 3);
  listGraph.add(2,4);
  REQUIRE(listGraph.getNumVertices() == 4);
  REQUIRE(listGraph.getNumEdges() == 4);
  listGraph.remove(2,4);
  REQUIRE(listGraph.getNumVertices() == 4);
  REQUIRE(listGraph.getNumEdges() == 3);
  listGraph.remove(3,4);
  REQUIRE(listGraph.getNumVertices() == 3);
  REQUIRE(listGraph.getNumEdges() == 2);
  listGraph.remove(1,3);
  REQUIRE(listGraph.getNumVertices() == 2);
  REQUIRE(listGraph.getNumEdges() == 1);
  listGraph.remove(1,2);
  REQUIRE(listGraph.getNumVertices() == 0);
  REQUIRE(listGraph.getNumEdges() == 0);
  
}


TEST_CASE("adding unconnected", "[AdjacencyMatrixGraph]") {
  AdjacencyMatrixGraph<int> listGraph;
  listGraph.add(1,2);
  REQUIRE(!listGraph.add(3,4));
}