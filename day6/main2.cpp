/*
 * Using the code from main1
 */

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
  for(size_t rowI = 0; rowI < walrus.size(); rowI++)
  {
    size_t index = walrus.size()-rowI-1;
    char op = walrus[index][walrus[index].size()-1][0];
    //cout << op << "\n";

    size_t val = 0;
    vector<string> transposed;
    for(size_t col = 0; col < walrus[index].size()-1; col++)
    {
      //cout << walrus[index][col] << "|";
      string s = walrus[index][col];
      for(size_t i = 0;i<s.size();i++)
      {
        while(transposed.size() < i+1)
          transposed.push_back("");
        transposed[i].push_back(s[i]);
      }
    }
    cout << "\n";
    
    for(string& str : transposed)
    {
      cout << str << "\n";
    }
    
    // this is just demonic
    cout << "start calc: " << "\n";
    if(op == '*')
    {
      val = 1;
      for(string& str:transposed)
      {
        string clean;
        for(char c : str)
        {
          if(isdigit(c)) clean.push_back(c);
        }
        if(clean.empty())
          continue;
        
        cout << str << "|";
        val*=stol(clean);
      }
      cout << " -> " << op << " -> " << val << "\n";
    }
    else if(op == '+')
    {
      for(string& str:transposed)
      {
        string clean;
        for(char c : str)
          if(isdigit(c))
            clean.push_back(c);
        if(clean.empty())
          continue;
        cout << str << "|";
        val+=stol(clean);
      }
      cout << " -> " << op << " -> " << val << "\n";
    }
    
    counter += val;
    cout << "-------\n\n";
  } 
  
  cout << counter << "\n";
  return 0;
}