#include <fstream>
#include <iostream>
#include <string>

int main()
{
  std::cout << "Hallo Welt!" << "\n";

  std::ifstream file("input");
  std::string line;

  int pointer = 50;
  int zeroCounter = 0;
  while (std::getline(file, line))
  {
    // get direction and rotation of line in file
    std::cout << "Current Line: " << line << " | Direction:";
    std::string direction = line.substr(0, 1);
    int rotations = std::stoi(line.substr(1, line.length() - 1));
    std::cout << direction << " | Rotations: " << rotations << "\n";

    // calc new pointer position
    if (direction == "R")
    {
      pointer += rotations;
    }
    else
    {
      pointer -= rotations;
    }

    // the math maths the problem
    if (pointer % 100 == 0)
      zeroCounter++;
  }

  std::cout << zeroCounter;
  file.close();
  return 0;
}
