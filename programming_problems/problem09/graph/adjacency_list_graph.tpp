#include "adjacency_list_graph.hpp"


template <typename LabelType>
AdjacencyListGraph<LabelType>::AdjacencyListGraph():edges(0) {}

template <typename LabelType> 
int AdjacencyListGraph<LabelType>::getNumVertices() const {
    return nodes.size();
}

template <typename LabelType> 
int AdjacencyListGraph<LabelType>::getNumEdges() const {
    return edges;
}
        
template <typename LabelType> 
bool AdjacencyListGraph<LabelType>::add(LabelType start, LabelType end) {
  
    if (start == end) {
        return false; 
    }
    if (nodes[start].count(end) || nodes[end].count(start)) {
        return false; 
    }
    nodes[start].insert(end);
    nodes[end].insert(start); 
    edges ++;
    return true;
}   

template <typename LabelType> 
bool AdjacencyListGraph<LabelType>::remove(LabelType start, LabelType end) {
    if (!nodes.count(start) || !nodes.count(end) ||
        !nodes[start].count(end) || !nodes[end].count(start)) {
        return false; 
    }
    nodes[start].erase(end);
    nodes[end].erase(start); 

    edges --;

    if (nodes[start].empty()) {
        nodes.erase(start);
    }
    if (nodes[end].empty()) {
        nodes.erase(end);
    }
    return true; 
}

template <typename LabelType> 
void AdjacencyListGraph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {
   
}

template <typename LabelType> 
void AdjacencyListGraph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {
    
}