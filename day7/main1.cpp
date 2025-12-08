#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;
using std::cout;

int main()
{
  std::fstream file("input");
  string line;
  vector<string> lines;
  size_t counter = 0;
  
  while(getline(file, line))
  {
    lines.push_back(line);
  }
  
  // first beam
  lines[1][lines[0].find('S')] = '|';
  
  // for part one the only interesting problem is to
  // check if the beam has already split from a 
  // neighbouring splitter
  for(size_t i = 2; i<lines.size();i++)
  {
    string lastLine = lines[i-1];
    string lineCopy = lines[i];
    
    for(size_t j = 0; j < lineCopy.length();j++)
    {
      if(lastLine[j] == '|')
      {
        if(lineCopy[j] == '^')
        {
          bool hasSplit = false;
          if(j > 0)
          {
            if(lines[i][j-1] != '|')
            {
              counter++;
              hasSplit = true;
            }
            //cout << "*";
            lines[i][j-1] = '|';
          }
          if(j < lines.size()-1)
          {
            //cout << "-";
            lines[i][j+1] = '|';
            if(!hasSplit)
              counter++;
          }
        }
        else if(lineCopy[j] == '.')
        {
          lines[i][j] = '|';
        }
      }
    }
    
    cout << "\n";
  
    for(string line : lines)
    {
      cout << line << "\n";
    }
    cout << counter << "\n";
  }
  
}