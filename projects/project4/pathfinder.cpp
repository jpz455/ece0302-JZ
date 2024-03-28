#include <cstdlib>
#include <iostream>
#include "lib/image.h"
#include "list.hpp"
#include "queue.hpp"


//holding the position throughout the maze
struct currentPosition {
  int x;
  int y;
};


//finding the starting position (red pizel) within the maze
currentPosition findStart(Image<Pixel>& image) {
  currentPosition startP;
  //initialize as invalid
  startP.x = -1;
  startP.y = -1;
  //hold number of red pixels (will be invalid if more than 1)
  int redP = 0;

  for (int row = 0; row < image.height(); row++) {
    for (int col = 0; col < image.width(); col++) {
      if (image(row, col) == RED) {
        //assign start position and increment number of red pixels
        startP.x = col;
        startP.y = row;
        redP++;
      }
      //find maze errors of more than one red pixel or invalid colors
      if (redP > 1 || (image(row, col) != BLACK && image(row, col) != WHITE && image(row, col) != RED)) {
        return currentPosition{-1, -1}; 
      }
    }
  }
  //no start position found error
  if (redP == 0) {
    return currentPosition{-1, -1};
  }
  return startP;
}


bool breadthFirstSearch(Image<Pixel>& image, currentPosition& startP) {
    int height = image.height();
    int width = image.width();

    // Queue to hold all the unexplored states
    Queue<currentPosition, List<currentPosition>> frontier;

    // Explored array to keep track of explored states and not allow duplicates
    bool explored[height][width] = {false};

    // Add the start position to the queue and mark as visited
    frontier.enqueue(startP);
    explored[startP.y][startP.x] = true;

    while (!frontier.isEmpty()) {
        currentPosition curNode = frontier.peekFront();
        frontier.dequeue();

        if ((curNode.x == 0) || (curNode.x == width - 1) || (curNode.y == 0) || (curNode.y == height - 1)) {
            image(curNode.y, curNode.x) = GREEN;
            return true;
        }

        // Define adjacent positions
        currentPosition adjacent[4] = {
            {curNode.x, curNode.y - 1}, // Up
            {curNode.x + 1, curNode.y}, // Right
            {curNode.x, curNode.y + 1}, // Down
            {curNode.x - 1, curNode.y}  // Left
        };

        // Explore adjacent positions
         for (int i = 0; i < 4; ++i) {
            int adjX = adjacent[i].x;
            int adjY = adjacent[i].y;

            if (adjX >= 0 && adjX < width && adjY >= 0 && adjY < height && image(adjY, adjX) == WHITE && !=explored[adjY][adjX]) {
                frontier.enqueue(adjacent[i]);
                explored[adjY][adjX] = true;
            }
        }
    }

    return false;
}

int main(int argc, char *argv[]) {
  // Get input/output file names from command line arguments
  if (argc != 3) {
    std::cout << "Usage: pathfinder "
              << "<first_input_filename> <second_output_filename>\n"
              << std::endl;
    return EXIT_FAILURE;
  }

  std::string input_file = argv[1];
  std::string output_file = argv[2];


  Image<Pixel> image = readFromFile(input_file);

  currentPosition start = findStart(image);
  if (start.x == -1 || start.y == -1) {
    std::cout << "Invalid start position." << std::endl;
    return EXIT_FAILURE;
  }
  bool success = breadthFirstSearch(image, start);

  writeToFile(image, output_file);
}