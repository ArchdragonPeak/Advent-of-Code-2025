/*
 * This time the idea is a little diffrent, I think it would be a lot better
 * to firstly convert the whole line into an array of ints.
 * The tricky part is to always check if we have enough elements left in the
 * array to get remaning elements.
 * I will try a more modular and iterative approach this time
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cmath>

// we loop through a window of digits provided to get the position of the highest digit,
// the logic should work as long as the correct window is provided
size_t demon(size_t start_pos, const size_t end_pos, const std::vector<int> &arr)
{
  std::cout << "demon with: " << start_pos << ":" << end_pos;
  uint8_t highest = 0;
  size_t highestPos = start_pos;
  while(start_pos <= end_pos)
  {
    const uint8_t current = arr[start_pos];
    if(current > highest)
    {
      highest = current;
      highestPos = start_pos;
    }
    start_pos++;
  }
  std::cout << " -> " << highestPos << "\n";
  return highestPos;
}


int main()
{
  std::fstream file("input");
  std::string line;
  std::vector<std::string> lineArr;
  uint64_t totalJoltage = 0;

  // just like in part 1, I wont bother to make this part better
  while(getline(file, line))
  {
    lineArr.push_back(line);
  }

  for(std::string str : lineArr)
  {
    // we will work with this vector
    std::vector<int> lineArrInts(str.size());
    size_t lineArrPointer = 0;
    int neededDigits = 12;
    uint64_t jolts = 0;
    // ascii to actual number
    for(size_t i = 0; i < lineArrInts.size(); i++)
    {
      lineArrInts[i] = (str[i] - '0');
    }

    // neededDigits*10 calculates the digits position
    // multiplying this with the digit on the pos of the return value gets the digit to the right place
    while(neededDigits > 0)
    {
      const size_t end = lineArrInts.size()-neededDigits;
      const size_t digitPos = demon(lineArrPointer, end, lineArrInts);
      const uint64_t j = powl(10,neededDigits-1) * lineArrInts[digitPos];
      jolts += j;
      lineArrPointer = digitPos + 1;
      neededDigits--;
    }

    std::cout << "Jolts: " << jolts << "\n\n";
    totalJoltage += jolts;
  }

  std::cout << "Total Joltage: " << totalJoltage << "\n";

}
