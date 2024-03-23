#include <cstdlib>
#include <iostream>
#include "lib/image.h"
#include "list.hpp"
#include "queue.hpp"


struct currentPosition {
  int x;
  int y;
};


currentPosition findStart(Image<Pixel>& image) {
  currentPosition startP;
  startP.x = -1;
  startP.y = -1;
  int startNum = 0;

  for (int row = 0; row < image.height(); row++) {
    for (int col = 0; col < image.width(); col++) {
      if (image(row, col) == RED) {
        startP.x = col;
        startP.y = row;
        startNum++;
      }
      if (startNum > 1 || (image(row, col) != BLACK && image(row, col) != WHITE && image(row, col) != RED)) {
        return currentPosition{-1, -1}; 
      }
    }
  }
  if (startNum == 0) {
    return currentPosition{-1, -1};
  }

  return startP;
}


bool breadthFirstSearch(Image<Pixel>& image, currentPosition& startP) {
  int height = image.height();
  int width = image.width();

  Queue<currentPosition, List<currentPosition>> frontier;
  bool traversed[height][width];
  bool frontiered[height][width];
  for (int m = 0; m < height; m++) {
    for (int n = 0; n < width; n++) {
      traversed[m][n] = false;
      frontiered[m][n] = false;
    }
  }

  frontier.enqueue(startP);
  frontiered[startP.y][startP.x] = true;

  while (!frontier.isEmpty()) {
    currentPosition curNode = frontier.peekFront();
    frontier.dequeue();
    frontiered[curNode.y][curNode.x] = false;

    if ((curNode.x == 0) || (curNode.x == image.width() - 1) || (curNode.y == 0) || (curNode.y == image.height() - 1)) {
      image(curNode.y, curNode.x) = GREEN;
      return true; 
    }

    currentPosition up, right, down, left;
    up.x = curNode.x;
    up.y = curNode.y - 1;
    down.x = curNode.x;
    down.y = curNode.y + 1;
    left.x = curNode.x - 1;
    left.y = curNode.y;
    right.x = curNode.x + 1;
    right.y = curNode.y;

    if ((image(up.y, up.x) == WHITE) && !traversed[up.y][up.x] && !frontiered[up.y][up.x]) {
      frontier.enqueue(up);
      frontiered[up.y][up.x] = true;
    }

    if (image(down.y, down.x) == WHITE && !traversed[down.y][down.x] && !frontiered[down.y][down.x]) {
      frontier.enqueue(down);
      frontiered[down.y][down.x] = true;
    }

    if (image(left.y, left.x) == WHITE && !traversed[left.y][left.x] && !frontiered[left.y][left.x]) {
      frontier.enqueue(left);
      frontiered[left.y][left.x] = true;
    }

    if (image(right.y, right.x) == WHITE && !traversed[right.y][right.x] && !frontiered[right.y][right.x]) {
      frontier.enqueue(right);
      frontiered[right.y][right.x] = true;
    }

    traversed[curNode.y][curNode.x] = true;
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