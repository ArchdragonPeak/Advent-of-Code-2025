/*
 * nothing to say today
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int getAdjacents(const std::vector<std::string>&lines, const int i, const int j)
{
  int counter = 0;
  for(int x = -1; x<=1; x++)
  {
    for(int y = -1; y<=1; y++)
    {
      const int dx = i+x;
      const int dy = j+y;
      if(dx >= 0 && dx < (int)lines.size() && dy >= 0 && dy < (int)lines[dx].size())
      {
        const char& c = lines[dx][dy];
        if(c == '@')
          counter++;
      }
    }
  }
  return counter-1;
}

int main()
{
  std::ifstream input ("input");
  std::string line;
  std::vector<std::string> lines;
  int rolls = 0;

  while(getline(input, line))
    lines.push_back(line);

  for(int i = 0;i<(int)lines.size();i++)
  {
    const std::string& line = lines[i];
    for(int j = 0;j<(int)line.size();j++)
    {
      const char& c = line[j];

      if(c == '@')
      {
        const int adjecent = getAdjacents(lines, i,j);
        if(adjecent < 4)
          rolls++;
      }
    }
  }
  std::cout << rolls << "\n";
}
