#include "adjacency_matrix_graph.hpp"

template <typename LabelType>
AdjacencyMatrixGraph<LabelType>::AdjacencyMatrixGraph():edges(0) {}

template <typename LabelType> 
int AdjacencyMatrixGraph<LabelType>::getNumVertices() const {
   return verts.size();
}

template <typename LabelType> 
int AdjacencyMatrixGraph<LabelType>::getNumEdges() const {
  return edges;
}
        
template <typename LabelType> 
bool AdjacencyMatrixGraph<LabelType>::add(LabelType start, LabelType end) {
    
    //checking that start exists, check that there are verticies in the graph, and check that end exists
    if ((std::find(verts.begin(), verts.end(), start) == verts.end()) && (!verts.empty()) && (std::find(verts.begin(), verts.end(), end) == verts.end())) {
    return false;
    }

    //adding start if it doesnt already exist
   if (std::find(verts.begin(), verts.end(), start) == verts.end()) {
        verts.push_back(start);
        matrix.push_back(std::vector<bool>(verts.size(), 0));
        for (int i = 0; i < matrix.size(); i++) {
            matrix[i].push_back(0);
        }
    }

    //adding end if it doesnt already exist
   if (std::find(verts.begin(), verts.end(), end) == verts.end()) {
        verts.push_back(end);
        matrix.push_back(std::vector<bool>(verts.size(), 0));
        for (int i = 0; i < matrix.size(); i++) {
            matrix[i].push_back(0);
        }
    }


    //find start and end indexes
   int startI = std::find(verts.begin(), verts.end(), start) - verts.begin();
   int endI = std::find(verts.begin(), verts.end(), end) - verts.begin();

    //checking that the start and end indexes are found within verts
   if (startI == verts.size() || endI == verts.size()) {
      return false; 
    }

   //checking for duplicate edges
   if (matrix[startI][endI] || matrix[endI][startI]) {
      return false; 
   }
   //once all conditions are passed add the edge to the matrix
   matrix[startI][endI] = matrix[endI][startI] = true;
   //increment number of edges
   edges++;
   
   return true;
}   

template <typename LabelType> 
bool AdjacencyMatrixGraph<LabelType>::remove(LabelType start, LabelType end) {
   
    if (!std::count(verts.begin(), verts.end(), start) || !std::count(verts.begin(), verts.end(), end)) {
        return false;
    }
    int startIdx, endIdx;
    for (int i = 0; i < verts.size(); i++) {
        if (verts[i] == start) {
            startIdx = i;
        }
        if (verts[i] == end) {
            endIdx = i;
        }
    }
    if (!matrix[startIdx][endIdx] || !matrix[endIdx][startIdx]) {
        return false;
    }
    matrix[startIdx][endIdx] = 0;
    matrix[endIdx][startIdx] = 0;
    edges--;

   
    bool empty = true;
    for (int i = 0; i < matrix[startIdx].size(); i++) {
        if (matrix[startIdx][i]) {
            empty = false;
            break;
        }
    }
    if (empty) {
        for (int i = 0; i < matrix.size(); i++) {
            matrix[i].erase(matrix[i].begin() + startIdx);
        }
        matrix.erase(matrix.begin() + startIdx);
        verts.erase(std::find(verts.begin(), verts.end(), start));
       
        if (endIdx > startIdx) {
            endIdx--;
        }
    }


    empty = true;
    for (int i = 0; i < matrix[endIdx].size(); i++) {
        if (matrix[endIdx][i]) {
            empty = false;
            break;
        }
    }
    if (empty) {
        for (int i = 0; i < matrix.size(); i++) {
            matrix[i].erase(matrix[i].begin() + endIdx);
        }
        matrix.erase(matrix.begin() + endIdx);
        verts.erase(std::find(verts.begin(), verts.end(), end));
    }

    return true;
    }
template <typename LabelType> 
void AdjacencyMatrixGraph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {}

template <typename LabelType> 
void AdjacencyMatrixGraph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {}