#include "adjacency_list_graph.hpp"


template <typename LabelType>
AdjacencyListGraph<LabelType>::AdjacencyListGraph(): edges(0){}

template <typename LabelType> 
int AdjacencyListGraph<LabelType>::getNumVertices() const {
    return verts.size();
}

template <typename LabelType> 
int AdjacencyListGraph<LabelType>::getNumEdges() const {
    return edges;
}
        
template <typename LabelType> 
bool AdjacencyListGraph<LabelType>::add(LabelType start, LabelType end) {
  
    //checking that the verticies are connected otherwise you cannot add here
     if (verts.size() != 0 && verts.find(start) == verts.end() && verts.find(end) == verts.end()) {
        return false; 
    }
    
    //checking for duplicates
    if (verts[start].count(end) || verts[end].count(start)) {
        return false; 
    }

    //otherwise insert at specified values
    verts[start].insert(end);
    verts[end].insert(start); 
    //increment the number of edges
    edges ++;
    return true;//sucess!
}   

template <typename LabelType> 
bool AdjacencyListGraph<LabelType>::remove(LabelType start, LabelType end) {
    
    //check verticie and edges exist
    if (!verts.count(start) || !verts.count(end) || !verts[start].count(end) || !verts[end].count(start)) {
        return false; 
    }

    //erase verticies from adjacency lists that essentially removes edges
    verts[start].erase(end);
    verts[end].erase(start); 
    //decrement edge count
    edges --;

    //checking for isolated verticies
    if (verts[start].empty()) {
        verts.erase(start);//erase from overall graph if so
    }
    if (verts[end].empty()) {
        verts.erase(end);
    }
    return true; //success!
}

template <typename LabelType> 
void AdjacencyListGraph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {
   
}

template <typename LabelType> 
void AdjacencyListGraph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {
    
}