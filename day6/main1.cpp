#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using std::cout;
using std::string;
using std::vector;
using std::string_view;

int main()
{
  std::ifstream file("input");
  if(!file.is_open()) return 1;
  string line;
  vector<string> lines;
  vector<vector<string>> walrus;
  size_t counter = 0;
  
  while(getline(file,line))
  {
    lines.push_back(line);
    //cout << line << "\n";
  }
  
  // first we create a vector containing strings
  size_t cursor = 0;
  for(size_t i = 0; i < lines[0].size();i++)
  {
    // if next char in last line is not whitespace
    char c = lines[lines.size()-1][i+1];
    if(c != ' ')
    {
      // save a string per line from cursor to current line
      vector<string> row;
      for(size_t r = 0; r < lines.size(); r++)
      {
        string l = lines[r].substr(cursor, i - cursor + 1);
        row.push_back(l);
      }
      
      walrus.push_back(row);
      cursor = i+1;
    }
  }
  
  // second we calculate our rows and
  // add them to the counter while using the right operaton
  // in the sloppiest manner possible
  for(vector<string> row : walrus)
  {
    size_t val;
    if(row[4].find('*') != string::npos)
    {
      size_t a = stol(row[0]);
      size_t b = stol(row[1]);
      size_t c = stol(row[2]);
      size_t d = stol(row[3]);
      val = a * b * c * d;
      cout << a << " * " << b << " * " << c << " * " << d << " = " << val << "\n";
    }
    else
    {
      val = stol(row[0]) + stol(row[1]) + stol(row[2]);
      size_t a = stol(row[0]);
      size_t b = stol(row[1]);
      size_t c = stol(row[2]);
      size_t d = stol(row[3]);
      val = a + b + c + d;
      cout << a << " + " << b << " + " << c << " + " << d << " = " << val << "\n";
    }
    counter += val;
  }
  
  cout << counter << "\n";
  return 0;
}
