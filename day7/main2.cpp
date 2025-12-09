#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;
using std::cout;

// we only get the part of the tree (wait is this a pun?)
// that we want to traverse, so the current line and downwards
// we don't care about the upper parts
// ideally we get a copy so we dont destroy our precious tree

size_t counter = 0;

vector<string> goDown(vector<string> &lines, size_t lineCursor, size_t vectorCursor)
{
  //cout << "Cursor: " << lineCursor << "\n";
  
  for(size_t i = vectorCursor; i < lines.size();i++)
  {
    if(lines[i][lineCursor] == '^' || lines[i][lineCursor] == 'X')
    {
      //vector<string> cpy;
      // go left
      if(lineCursor > 0)
      {
        //cpy.assign(lines.begin(), lines.end());
        //cpy[i][lineCursor-1] = '|';
        goDown(lines, lineCursor-1, i);
      }
      // then go right
      if(lineCursor < lines[i].size()-1)
      {
        //cpy.assign(lines.begin(), lines.end());
        //cpy[i][lineCursor+1] = '|';
        return goDown(lines, lineCursor+1, i);
      }
      
    }
    else
    {
      lines[i][lineCursor] = '|';
    }
  }
  
  counter++;
  if(counter % 1 == 0)
  {
    for(string line : lines)
    {
      cout << line << "\n";
    }
    cout << "Counter: " << counter << "\n";
  }
  
  return lines;
}

int main()
{
  std::fstream file("test");
  string line;
  vector<string> lines;
  vector<vector<size_t>> visited;
  
  while(getline(file, line))
  {
    lines.push_back(line);
  }
  
  // first beam
  size_t first = lines[0].find('S');
  lines[1][first] = '|';
  
  vector<string> cpy;
  cpy.assign(lines.begin()+2, lines.end());
  goDown(cpy, first, 0);
  
  cout << counter << "\n";
}