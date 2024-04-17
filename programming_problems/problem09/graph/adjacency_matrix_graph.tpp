#include "adjacency_matrix_graph.hpp"

template <typename LabelType>
AdjacencyMatrixGraph<LabelType>::AdjacencyMatrixGraph() {}

template <typename LabelType> 
int AdjacencyMatrixGraph<LabelType>::getNumVertices() const {
    return vertexIndices.size();
}

template <typename LabelType> 
int AdjacencyMatrixGraph<LabelType>::getNumEdges() const {
   int count = 0;
    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
        for (int j = i + 1; j < adjacencyMatrix.size(); ++j) {
            if (adjacencyMatrix[i][j]) {
                count++;
            }
        }
    }
    return count;
}
        
template <typename LabelType> 
bool AdjacencyMatrixGraph<LabelType>::add(LabelType start, LabelType end) {
    
   
    // Check if vertices already exist
    bool isNewStart = vertexIndices.find(start) == vertexIndices.end();
    bool isNewEnd = vertexIndices.find(end) == vertexIndices.end();
    
    if (isNewStart) {
        vertexIndices[start] = vertexIndices.size();
    }
    if (isNewEnd) {
        vertexIndices[end] = vertexIndices.size();
    }
    
    int startIndex = vertexIndices[start];
    int endIndex = vertexIndices[end];
    
    // Ensure matrix is large enough to accommodate both vertices
    int maxIndex = std::max(startIndex, endIndex) + 1;
    if (maxIndex > adjacencyMatrix.size()) {
        adjacencyMatrix.resize(maxIndex, std::vector<bool>(maxIndex, false));
    }
    
    // Check if edge already exists
    if (adjacencyMatrix[startIndex][endIndex]) {
        return false; // Edge already exists
    }
    
    // Add edge
    adjacencyMatrix[startIndex][endIndex] = true;
    adjacencyMatrix[endIndex][startIndex] = true;
    
    // Update the number of vertices if new vertices were added
    if (isNewStart || isNewEnd) {
        return true;
    }
    
    return false; // Edge added but no new vertices
    
     
       
}   

template <typename LabelType> 
bool AdjacencyMatrixGraph<LabelType>::remove(LabelType start, LabelType end) {
   
   
   if (vertexIndices.find(start) == vertexIndices.end() || vertexIndices.find(end) == vertexIndices.end()) {
        return false; // Vertices don't exist
    }
    
    int startIndex = vertexIndices[start];
    int endIndex = vertexIndices[end];
    
    if (!adjacencyMatrix[startIndex][endIndex]) {
        return false; // Edge doesn't exist
    }
    
    // Remove edge
    adjacencyMatrix[startIndex][endIndex] = false;
    adjacencyMatrix[endIndex][startIndex] = false;
    
    // Update number of edges
    int numEdges = 0;
    for (const auto& row : adjacencyMatrix) {
        for (bool edge : row) {
            if (edge) {
                numEdges++;
            }
        }
    }
    
    // Remove isolated vertices
    bool removedVertices = false;
    for (auto it = vertexIndices.begin(); it != vertexIndices.end();) {
        LabelType vertex = it->first;
        int index = it->second;
        
        bool hasEdges = false;
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            if (adjacencyMatrix[index][i]) {
                hasEdges = true;
                break;
            }
        }
        
        if (!hasEdges) {
            it = vertexIndices.erase(it);
            removedVertices = true;
        } else {
            ++it;
        }
    }
    
    if (removedVertices) {
        // Re-index the vertices
        int newIndex = 0;
        std::map<LabelType, int> newVertexIndices;
        for (const auto& entry : vertexIndices) {
            newVertexIndices[entry.first] = newIndex++;
        }
        vertexIndices = std::move(newVertexIndices);
    }
    
    return true;
}

template <typename LabelType> 
void AdjacencyMatrixGraph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {}

template <typename LabelType> 
void AdjacencyMatrixGraph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {}