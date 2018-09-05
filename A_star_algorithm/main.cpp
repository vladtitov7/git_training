#include <iostream>
#include <fstream>
#include <string>
#include "AStar.h"
#include "AStar.cpp"

int main()
{

  AStar::Generator generator;
  generator.setWorldSize({10, 10});
  generator.setHeuristic(AStar::Heuristic::manhattan);
  generator.setDiagonalMovement(true);
  std::string key;
  std::cout << "Do you want add walls to map? If yes - type 'yes', else - type 'no'" << std::endl;
  std::cin >> key;
  if(key == "yes")
    {
      std::ifstream file;
      file.open("walls.txt");
      int wall_x, wall_y;
      while(!file.eof())
	{
	  file >> wall_x >> wall_y;
	  generator.addCollision({wall_x, wall_y});
	}
    }
  else
    std::cout << "Ok!" << std::endl;

  int init_x, init_y;
  std::cout << "Enter initial point" << std::endl;
  std::cin >> init_x >> init_y;
  int dest_x, dest_y;
  std::cout << "Enter destination point" << std::endl;
  std::cin >> dest_x >> dest_y;

  auto path = generator.findPath({init_x, init_y}, {dest_x, dest_y});
  reverse(path.begin(), path.end());
  std::cout << "Path from initial point to point with coordinates (" << dest_x << ", " << dest_y << ") is: " << std::endl;
  for(auto& coordinate : path)
    if(coordinate.y != dest_y || coordinate.x != dest_x)
      std::cout << "(" << coordinate.x << ", " << coordinate.y << ") --> ";
    else
      std::cout << "(" << coordinate.x << ", " << coordinate.y << ") \n" << std::endl;
    
  return 0;
}
