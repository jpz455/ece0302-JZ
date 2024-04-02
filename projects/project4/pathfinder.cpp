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
//function to check that the maze only contains black white red and green pixels
bool validateMaze(const Image<Pixel>& image) {
    for (int row = 0; row < image.height(); ++row) {
        for (int col = 0; col < image.width(); ++col) {
            Pixel pixel = image(row, col);
            if (pixel != BLACK && pixel != WHITE && pixel != RED) {
                return false; // Found an invalid color
            }
        }
    }
    return true; // All colors are valid
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

    //run until all positions are explored
    while (!frontier.isEmpty()) {

      //retrieve the next position from the front of the queue and then remove it by dequeue indicating it has been searched
        currentPosition curNode = frontier.peekFront();
        frontier.dequeue();
      //if conditions of an exit are met mark as green indicating an exit
        if ((curNode.x == 0) || (curNode.x == width - 1) || (curNode.y == 0) || (curNode.y == height - 1)) {
            image(curNode.y, curNode.x) = GREEN;
            return true;
        }

       // Define adjacent positions
        currentPosition adjacent[4] = {
            {curNode.x, curNode.y - 1}, // previous row
            {curNode.x , curNode.y+1}, // next row
            {curNode.x-1, curNode.y}, // previous column
            {curNode.x +1, curNode.y}  // next column
            
        };

        // Explore adjacent positions
         for (int i = 0; i < 4; ++i) {
            int adjX = adjacent[i].x;
            int adjY = adjacent[i].y;
            //if the next position has not been explored add it to the queue and mark as explored
            if (adjX >= 0 && adjX < width && adjY >= 0 && adjY < height && image(adjY, adjX) == WHITE && !explored[adjY][adjX]) {
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



try {
        // Read maze input image
        Image<Pixel> image = readFromFile(input_file);

        // Validate maze image
        if (!validateMaze(image)) {
            std::cerr << "Error: Input maze image contains invalid colors.\n";
            return EXIT_FAILURE;
        }

        // Find starting position
        currentPosition start = findStart(image);
        if (start.x == -1 || start.y == -1) {
            std::cerr << "Error: Invalid start position or multiple start positions found.\n";
            return EXIT_FAILURE;
        }

        // Perform breadth-first search to find the solution path
        bool success = breadthFirstSearch(image, start);

        // Write solved maze to output image
        writeToFile(image, output_file);

        // Print solution status to standard output
        if (success) {
            std::cout << "Solution Found\n";
            return EXIT_SUCCESS;
        } else {
            std::cout << "No Solution Found\n";
            return EXIT_SUCCESS; // Return success as no error occurred
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
}