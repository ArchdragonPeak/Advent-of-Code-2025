#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

int main()
{
    std::cout << "Hallo Welt!" << "\n";

    std::ifstream file("input");
    std::string line;

    int pointer = 50;
    int zeroCounter = 0;
    while(std::getline(file, line))
    {
        // get direction and rotation of line in file
        std::string direction = line.substr(0,1);
        int rawRotations = std::stoi(line.substr(1,line.length()-1));

        // the pointer doesnt move if rotation is 100, thats why we only
        // calculate the new position after we subtracted every full rotation
        int fullRotations = std::floor( std::abs(rawRotations) / 100 );
        zeroCounter = zeroCounter + fullRotations;

        // subtract all full rotations
        int rotations = rawRotations - (100*fullRotations);
        // until know correct

        std::cout << "Line: " << direction << ":" << rawRotations << " | extraRot: " << fullRotations;
        std::cout << " | adj. Rot: " << rotations << " --> ";
        if(direction == "R")
        {
          int rawResult = pointer + rotations;
          int realResult = rawResult;
          if(rawResult > 99)
          {
            realResult = rawResult - 100;
            zeroCounter++;
          }
          std::cout << pointer << " + " << rotations << " = " << rawResult << " -> " << realResult << "\n";
          pointer = realResult;
        }
        if(direction == "L")
        {
            int rawResult = pointer - rotations;
            int realResult = rawResult;

            if (pointer != 0) {
                if (rawResult < 0)
                {
                    realResult = rawResult + 100;
                    zeroCounter++;
                }
                else if (rawResult == 0)
                {
                    zeroCounter++;
                }
            } else {
                if (rawResult < 0)
                {
                    realResult = rawResult + 100;
                }
            }
            std::cout << pointer << " + " << rotations << " = " << rawResult << " -> " << realResult << "\n";
            pointer = realResult;
        }

        std::cout << zeroCounter << "\n";
    }

    std::cout << zeroCounter << "\n";
    file.close();
    return 0;
}
