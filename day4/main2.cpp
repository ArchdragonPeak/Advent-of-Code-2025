/*
 * :)
 */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int getAdjacents(const std::vector<std::string> &lines, const int i, const int j) {
  int counter = 0;

  for (int x = -1; x <= 1; x++)
  {
    for (int y = -1; y <= 1; y++)
    {
      const int dx = i + x;
      const int dy = j + y;

      if (dx >= 0 && dx < static_cast<int>(lines.size()) && dy >= 0 && dy < static_cast<int>(lines[dx].size())) {
        const char &c = lines[dx][dy];
        if (c == '@')
          counter++;
      }
    }
  }
  return counter - 1;
}

int main()
{
  std::ifstream input("input");
  std::string line;
  std::vector<std::string> lines;
  std::vector<std::string> next;
  int rolls = 0;
  int rollsRemoved = 0;

  while (getline(input, line))
    lines.push_back(line);

  next.insert(next.begin(), lines.begin(), lines.end());

  while (true)
  {
    rollsRemoved = 0;

    for (int i = 0; i < static_cast<int>(lines.size()); i++)
    {
      const std::string &line = lines[i];

      for (int j = 0; j < static_cast<int>(line.size()); j++)
      {
        const char &c = line[j];

        if (c == '@')
        {
          const int adjecent = getAdjacents(lines, i, j);

          if (adjecent < 4)
          {
            rolls++;
            rollsRemoved++;
            next[i][j] = 'x';
          }
        }
      }
    }

    lines.clear();
    lines.insert(lines.begin(), next.begin(), next.end());

    if (rollsRemoved == 0)
      break;
  }

  std::cout << rolls << "\n";
}
