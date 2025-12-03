#include <iostream>
#include <string>
#include <fstream>
#include <vector>
int main()
{
  std::fstream file("input");
  std::string line;
  std::vector<std::string> lineArr;
  int totalJoltage = 0;

  // put every line in file into the vector
  while(getline(file, line))
  {
    lineArr.push_back(line);
  }

  for(std::string str : lineArr)
  {
    // we brutforcin
    int bigBoy = 0;
    for(size_t i = 0;i<str.size();i++)
    {

      for(size_t j = i+1;j<str.size();j++)
      {
        int first = str[i]-'0';
        int second = str[j]-'0';
        int current = first*10 + second;
        if(current > bigBoy)
          bigBoy = current;
      }
    }
    totalJoltage += bigBoy;
  }

  std::cout << "Total Joltage: " << totalJoltage << "\n";

}
